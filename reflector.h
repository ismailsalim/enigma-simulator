/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019 
 *
 * This programme contains the declarations of the reflector class that 
 * represents the unique reflector component of the enigma machine.
 */

#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector {
 public:
  Reflector();

  /* Requires the reflector's configuration filename to configure the 
     reflector's input/output signal mappings.
     Tests the validity of the configuration file according to several criteria.
     Returns an appropriate error code after attempted configuration. */
  int configReflections(char* reflector_config);

  /* Requires an integer that represents the input character into the reflector,
     which gets mapped to its configured output character.
     Returns an integer that represents the output character. */ 
  int transformChar(int ch);

 private:
  int reflections [26];
};

#endif
