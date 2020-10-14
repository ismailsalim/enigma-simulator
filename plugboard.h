/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019 
 *
 * This programme contains the declarations of the plugboard class that 
 * represents the unqiue plugboard component of the enigma machine.
 */

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard {
 public:
  Plugboard();

  /* Requires the plugboard's configuration filename to configure the 
     plugbaord's input/output signal mappings.
     Tests the validity of the configuration file according to several criteria.
     Returns an appropriate error code after attempted configuration. */
  int configPlugs(char* configFile);

  /* Requires an integer that represents the input character to the plugboard,
     which gets mapped to its configured output character.
     Returns an integer that represents the output character. */ 
  int transformChar(int ch);

 private:
  int board[26];

  /* Sets all the plugboard contacts to connect to themselves if a mapping 
     is not specified in its configuration file. */
  void setNonConfigs();
};

#endif
