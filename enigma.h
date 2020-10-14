/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019 
 *
 * This programme contains the declarations of the enigma class that 
 * represents the machine in its entirety.
 */

#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"

class Enigma {
 public:
  Enigma();

  ~Enigma();

  /* Requires the number and full list of the enigma's component configuration 
     files (specified by the user in the command line) and configures all of 
     the machine's components.
     Checks the validity of the configuration according to all its component's
     configuration tests.
     Returns an appropriate error code after attempted configuration. */
  int config(int argc, char** argv);

  /* Requires a single character and encrypts/decrypts it according to the 
     machine's configuration. 
     Returns the encrypted/decrypted character */  
  char charTransform(char ch);
   
 private:
  Plugboard* plugboard;
  Reflector* reflector;
  int numberOfRotors;
  Rotor* rotors;

  /* Requires the plugboard component of the enigma and its configuration 
     filename to configure the plugboard's input/output signal mappings.
     Checks configuration validity according to the component's
     configuration tests.
     Returns an appropriate error code after attempted configuration. */
  int configPlugboard(Plugboard* plugboard, char* plugboard_config);

  /* Requires the reflector component of the enigma and its configuration 
     filename to configure the reflector's input/output signal mappings.
     Checks configuration validity according to the component's
     configuration tests.
     Returns the appropriate error code after attempted configuration. */
  int configReflector(Reflector* reflector, char* reflector_config);

  /* Requires a rotor component of the enigma and its configuration filename 
     to configure the rotor's input/output singal mappings and its notches.
     Checks configuration validity according to component's
     configuration tests.
     Returns the appropriate error code after attempted configuration. */
  int configRotor(Rotor &rotor, char* rotor_config);

  /* Requires the rotors' starting positions filename to set the rotors' 
     starting positions before any encryption/decryption (possible none).
     Tests the validity of the configuration file according to several criteria.
     Returns the appropriate error code after attempted configuration. */
  int configRotorStartingPositions(char* rotor_positions);

  /* Rotates the rotors according to the mechanism governed by the rotors'
     positions and notches (each time a character siginal is inputted). */
  void rotateRotors();
};

#endif
