/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019 
 *
 * This programme contains the global constants that are used for configuration
 * results and the encyryption mechanism. 
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

/* Confiuration error codes */
#define INSUFFICIENT_NUMBER_OF_PARAMETERS         1
#define INVALID_INPUT_CHARACTER                   2
#define INVALID_INDEX                             3
#define NON_NUMERIC_CHARACTER                     4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
#define INVALID_ROTOR_MAPPING                     7
#define NO_ROTOR_STARTING_POSITION                8
#define INVALID_REFLECTOR_MAPPING                 9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
#define ERROR_OPENING_CONFIGURATION_FILE          11
#define NO_ERROR                                  0

/* Alphabetical maximum for components (connections all be between A-Z) */
#define ALPHA_MAX 26

#endif
