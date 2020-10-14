#include "rotor.h"
#include "configHelpers.h"
#include "constants.h"
#include <iostream>

Rotor::Rotor() {
  for(int i = 0; i < ALPHA_MAX; i++) {
    mappings[i] = -1;
  }
}

void Rotor::setID(int id) {
  this->id = id;
}

int Rotor::configMapAndNotches(char* config) {
  std::ifstream config_stream(config);

  if (config_stream.fail()) {
    std::cerr << "Couldn't open the rotor configuration file rotor.rot!";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int mappings_error = configMappings(config_stream);
  if (mappings_error)
    return mappings_error;

  int notches_error = configNotches(config_stream);
  if (notches_error)
    return notches_error;

  config_stream.close();

  /* if both rotor config tests fully pass */
  return NO_ERROR;
}

int Rotor::configMappings(std::ifstream &in_stream) {
  in_stream >> std::ws;
  int mapping;
  
  for(int map_index = 0; map_index < ALPHA_MAX; map_index++) {
    if (in_stream.eof()) {
      std::cerr << "Not all rotor inputs are mapped in rotor file rotor.rot"
		<< " #" << id
		<< "\n(zero-indexed left-to-right on command line)!";
      return INVALID_ROTOR_MAPPING;
    }

    if (nonNumericChar(in_stream)) {
      std::cerr << "rotor file rotor.rot #" << id <<
	"\n(zero-indexed left-to-right on command line)!";; 
      return NON_NUMERIC_CHARACTER;
    }

    in_stream >> mapping;
  
    if (invalidIndex(mapping)) {
      std::cerr << "rotor file rotor.rot #" << id
		<< "\n(zero-indexed left-to-right on command line)!";
      return INVALID_INDEX;
    }


    if (duplicateMapping(map_index, mapping, mappings)) {
      std::cerr << "rotor file rotor.rot #" << id
		<< "\n(zero-indexed left-to-right on command line)!";
      return INVALID_ROTOR_MAPPING;
    }
    
    mappings[map_index] = mapping;
    in_stream >> std::ws;
  }

  /* if all config stream tests pass for every rotor */
  return NO_ERROR;
}

int Rotor::configNotches(std::ifstream &in_stream) {
  in_stream >> std::ws;
  int notch;

  while(!in_stream.eof()) {
    if (nonNumericChar(in_stream)) {
      std::cerr << "rotor file rotor.rot #" << id
		<< "\n(zero-indexed left-to-right on command line)!";
      return NON_NUMERIC_CHARACTER;
    }

    in_stream >> notch;
    
    if (invalidIndex(notch)) {
      std::cerr << "rotor file rotor.rot #" << id
		<< "\n(zero-indexed left-to-right on command line)!";
      return INVALID_INDEX;
    }

    /* duplicate notch specification is fine - no duplicateChar() call */

    notches[notch] = 1; /* presence of notch represented by 1 */
    in_stream >> std::ws;
  }

  /* if all config stream tests pass for every rotor */
  return NO_ERROR;
}

void Rotor::configStartingPosition(int pos) {
  position = pos;
}

bool Rotor::rotate() {
  position = (position + 1) % ALPHA_MAX; /* rotation by 1 */
  return notches[position] ? true : false; /* notch presence configured to 1 */
}

int Rotor::toReflectorTransform(int ch) {
  int offset_input = (ch + position) % ALPHA_MAX; /* rotational offset */
  int wire_mapping = mappings[offset_input];
  int offset_output = wire_mapping - position;

  if (offset_output < 0) 
    return offset_output + ALPHA_MAX; /* emulating modular functionalty */
  return offset_output;
}

int Rotor::fromReflectorTransform(int ch) {
  int offset_input = (ch + position) % ALPHA_MAX; /* rotational offset */
  int wire_mapping;
  
  for (int i = 0; i < ALPHA_MAX ; i++) {
    if(mappings[i] == offset_input)
      wire_mapping = i; /* inverse mapping post-reflection */
  }
 
  int offset_output = wire_mapping - position;

  if (offset_output < 0) 
    return offset_output + ALPHA_MAX; /* emulating modular functionality */
  return offset_output;
}


