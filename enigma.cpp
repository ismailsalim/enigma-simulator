#include "enigma.h"
#include "configHelpers.h"
#include "constants.h"
#include <iostream>

Enigma::Enigma(){
  plugboard = new Plugboard;
  reflector = new Reflector;
  rotors = nullptr;
  numberOfRotors = 0;
}

Enigma::~Enigma(){
  delete plugboard;
  delete reflector;
  delete [] rotors;
}

int Enigma::config(int argc, char** argv){
  /* arguments must include reflector, plugboard, and rotor position files */
  int required_args = 3;
  if (argc > required_args) {
    int non_rotor_args = 4;
    numberOfRotors = argc - non_rotor_args;
    rotors = new Rotor[numberOfRotors];
  }
  
  int plugboard_config_error = configPlugboard(plugboard, argv[1]);
  if (plugboard_config_error)
    return plugboard_config_error;

  int reflector_config_error = configReflector(reflector, argv[2]); 
  if (reflector_config_error)
    return reflector_config_error;
  
  int pos_file_index = argc - 1; /* last file specified in command line */
  char* rotor_positions = argv[pos_file_index];

  for(int i = 0; i < numberOfRotors; i++) {
    int rotor_config_error = configRotor(rotors[i], argv[i + 3]);
    if (rotor_config_error)
      return rotor_config_error;
    rotors[i].setID(i);
  }

  int positions_config_error = configRotorStartingPositions(rotor_positions);
  if (positions_config_error)
    return positions_config_error;
  
  /* if all the above component configuration tests pass */
  return NO_ERROR;
}

int Enigma::configPlugboard(Plugboard* plugboard, char* plugboard_config){
  int config_error = plugboard->configPlugs(plugboard_config);
  if (config_error)
    return config_error;
  return NO_ERROR;
}

int Enigma::configReflector(Reflector* reflector, char* reflector_config) {
  int config_error = reflector->configReflections(reflector_config);
  if (config_error)
    return config_error;
  return NO_ERROR;
}

int Enigma::configRotor(Rotor &rotor, char* rotor_config) {
  int config_error = rotor.configMapAndNotches(rotor_config);
  if (config_error) {
    return config_error;
  }
  return NO_ERROR;
}

int Enigma::configRotorStartingPositions(char* rotor_positions){
  std::ifstream in_stream(rotor_positions);
  int position;
  in_stream >> std::ws;
  
  for(int rotor = 0; rotor < numberOfRotors; rotor++) {
    if (in_stream.eof()) {
      std::cerr << "Starting positions for rotor " << rotor
		<< " have been specified in rotor positions file!";
      return NO_ROTOR_STARTING_POSITION;
    }
    
    if (nonNumericChar(in_stream)) {
      std::cerr << "rotor positions file for rotor " << rotor
		<< " (zero-indexed)!";
      return NON_NUMERIC_CHARACTER;
    }

    in_stream >> position;
  
    if (invalidIndex(position)) {
      std::cerr << "Rotor " << rotor
		<< " has been set to an invalid position"
		<< " in rotor positions file!";
      return INVALID_INDEX;
    }

    in_stream >> std::ws;
    rotors[rotor].configStartingPosition(position);
  }

  /* if all the above position file configuration tests pass */
  return NO_ERROR;
}

char Enigma::charTransform(char ch) {
  char processed_char = ch - 'A';
  
  if (numberOfRotors > 0)
    rotateRotors();

  processed_char = plugboard->transformChar(processed_char);

  for (int i = numberOfRotors - 1; i >= 0; i--)
    processed_char = rotors[i].toReflectorTransform(processed_char);

  processed_char = reflector->transformChar(processed_char);

  for (int i = 0; i <= numberOfRotors - 1; i++)
    processed_char = rotors[i].fromReflectorTransform(processed_char);
  
  processed_char = plugboard->transformChar(processed_char);

  return processed_char + 'A';
}

void Enigma::rotateRotors() {
  /* always rotate the rightmost rotor (if one exists)
     rotate the rotor to its left also if a notch is hit */
  for (int current_rotor = numberOfRotors - 1; current_rotor >= 0;
       current_rotor--) {
      bool notch_hit = rotors[current_rotor].rotate();
      if (!notch_hit)
	break;
  }
}

