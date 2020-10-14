/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019
 *
 * This programme enables a user to encrypt and decrypt messages according
 * to the original enigma machine's implementation.
 * The user should specify an input file that contains only uppercase characters 
 * (and whitespace) to encrypt/decrypt the text into an output file.
 *
 * The user should also specify the following configuration files for each of
 * the enigma's components:
 *  - One plugboard  
 *  - One reflector
 *  - Any number of rotors (zero or more)
 *  - A starting position for every rotor specified
 */ 

#include "enigma.h"
#include "constants.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  int args_threshold = 4;
  if (argc < args_threshold) {
    std::cerr << "Insufficient number of command line parameters entered..."
	      << "\nUsage: enigma plugboard-file reflector-file" 
	      <<"(<rotor-file>)* rotor-positions";
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Enigma machine = Enigma();
  int enigma_config_error = machine.config(argc, argv);  
  if (enigma_config_error)
    return enigma_config_error;

  char input;
  std::cin >> std::ws;
  std::cin.get(input);
  
  while(!std::cin.eof()) {
    if(!std::isupper(input)) {
      std::cerr << input << " is not a valid input character " <<
	"(input characters must be uppercase letters A-Z)!";
      return INVALID_INPUT_CHARACTER;
    }
   
    char encrypted_letter = machine.charTransform(input);
    
    std::cout << encrypted_letter;
    std::cin >> std::ws;
    std::cin.get(input);
  }

  return NO_ERROR;
}
