#include "reflector.h"
#include "configHelpers.h"
#include "constants.h"
#include <iostream>

Reflector::Reflector() {
  for (int i = 0; i < ALPHA_MAX; i++)
    reflections[i] = -1; /* arbitrary non-configured defaults */ 
}

int Reflector::configReflections(char* configFile){
  std::ifstream in_stream(configFile);

  if (in_stream.fail()) {
    std::cerr << "Coudn't open reflector configuration file"
	      << " reflector.rf!" << std::endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  in_stream >> std::ws;
  int reflection_pair[2];  
  int reflector_index = 0;

  while (!in_stream.eof()) {
    if (reflector_index >= ALPHA_MAX) {
      std::cerr << "More connections than exactly 13 pairs specified"
		<< " in reflector file reflector.rf!";
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    
    if (nonNumericChar(in_stream)) {
      std::cerr << "reflector file reflector.rf!";
      return NON_NUMERIC_CHARACTER;
    }
    
    int pair_index = reflector_index % 2;
    in_stream >> reflection_pair[pair_index];

    if (invalidIndex(reflection_pair[pair_index])) {
      std::cerr << "reflector file reflector.rf!";
      return INVALID_INDEX;
    }
    
    if (duplicateMapping(reflector_index, reflection_pair[pair_index],
			 reflections)) {
      std::cerr << "refelctor file reflector.rf!";
      return INVALID_REFLECTOR_MAPPING;
      }
    	
    if (reflector_index % 2) {
      if (reflection_pair[0] == reflection_pair[1]) {
	std::cerr << "A self-reflection has been found"
		  << " in reflector file reflector.rf!";
	return INVALID_REFLECTOR_MAPPING;
      }
      reflections[reflection_pair[0]] = reflection_pair[1];
      reflections[reflection_pair[1]] = reflection_pair[0]; 
    }

    in_stream >> std::ws;
    reflector_index++;
  }

  if((reflector_index % 2)) {
    std::cerr << "Odd number of parameters specified"
	      << " in reflector file reflector.rf!";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  if((reflector_index < ALPHA_MAX)) {
    std::cerr << "Insufficient number of reflections specifed"
	      << " in reflector file reflector.rf!";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  in_stream.close();

  /* if all reflector config stream tests pass */
  return NO_ERROR;
}

int Reflector::transformChar(int ch) {
  return reflections[ch];
}
