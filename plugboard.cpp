#include "plugboard.h"
#include "configHelpers.h"
#include "constants.h"
#include <iostream>

Plugboard::Plugboard() {
  for(int i = 0; i < ALPHA_MAX; i++)
    board[i] = -1; /* arbitrary non-configured default */
}

int Plugboard::configPlugs(char* configFile){
  std::ifstream in_stream(configFile);

  if (in_stream.fail()) {
    std::cerr << "Couldn't open plugboard file plugboard.pb!";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  in_stream >> std::ws;
  int plug_pair[2];
  int plugboard_index = 0;
  
  while (!in_stream.eof()) {    
    if (plugboard_index >= ALPHA_MAX) {
      std::cerr << "More connections than exactly 13 plug pairs specified"
		<< " in plugboard file plugboard.pb!";
     return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    
    if (nonNumericChar(in_stream)) {
      std::cerr << "plugboard file plugboard.pb!";
      return NON_NUMERIC_CHARACTER;
    }
    
    int pair_index = plugboard_index % 2;
    in_stream >> plug_pair[pair_index];
    
    if (invalidIndex(plug_pair[pair_index])) {
      std::cerr << "plugboard file plugboard.pb!";
      return INVALID_INDEX;
    }
    
    if (duplicateMapping(plugboard_index, plug_pair[pair_index], board)) {
      std::cerr << "plugboard file plugboard.pb!";
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
    
    if (plugboard_index % 2) {
      if (plug_pair[0] == plug_pair[1]) {
	std::cerr << "Plug has been connected with itself"
		  << " in plugboard file plugboard.pb!";
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
      board[plug_pair[0]] = plug_pair[1];
      board[plug_pair[1]] = plug_pair[0];
    }
    
    in_stream >> std::ws;
    plugboard_index++; 
  }
  
  if (plugboard_index % 2) {
    std::cerr << "Must be an even number of plug connections"
	      << " in plugboard file plugboard.pb!";
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  
  in_stream.close();
  setNonConfigs();
  
  /* if all above plugboard configuration tests pass */
  return NO_ERROR;
}

void Plugboard::setNonConfigs() {
  for (int i = 0; i < ALPHA_MAX; i++) {
    if (board[i] == -1)
      board[i] = i;
  }
}

int Plugboard::transformChar(int ch) {
  return board[ch];
}
