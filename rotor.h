#ifndef ROTOR_H
#define ROTOR_H
#include <fstream>

class Rotor {
 public:
  Rotor();

  /* Requires an integer to assign an ID for the rotor (0 representing the 
     leftmost rotor) */
  void setID(int id);

  /* Requires the rotor configuration filename to configure the rotor's 
     mappings and notches.
     Checks configuration validity according to the its two helper functions.
     Returns an appropriate error code after attempted configuration. */
  int configMapAndNotches(char* config);

  /* Requires an integer to set the rotor's starting position to the 
     corresponding offset from 'A' in top position. */  
  void configStartingPosition(int pos);

  /* Rotates the rotor in the opposite direction to which the alphabet's letters
     are ordered on its ring. */ 
  bool rotate();

  /* Requires an integer that represents the input character into the rotor
     (signal flowing towards the reflector) and maps this to the configured 
     output character.
     Returns an integer that represents the output character. */ 
  int toReflectorTransform(int ch);

  /* Requires an integer that represents the input character into the rotor
     (signal flowing away from the reflector) and maps this to the configured 
     output character.
     Returns an integer that represents the output character. */ 
  int fromReflectorTransform(int ch);

 private:
  int id;
  int mappings [26];
  int notches [26];
  int position;

  /* Helper function that configures the rotor's mappings given a stream of 
     mapping configurations.
     Tests the validity of the configuration file according to several criteria.
     Returns the appropriate error code after attempted configuration. */ 
  int configMappings(std::ifstream &in_stream);

  /* Helper function that configures the rotor's notches given a stream of 
     mapping configurations.
     Tests the validity of the configuration file according to several criteria.
     Returns the appropriate error code after attempted configuration. */ 
  int configNotches(std::ifstream &in_stream);
};

#endif
