/* MSc C++ Programming Excercise No.2
 * Author: Ismail Salim
 * Last edited: 16/11/2019 
 *
 * This programme contains the declarations of the helper functions that are   
 * used for all the components configurations
 */

#ifndef CONFIG_HELPERS
#define CONFIG_HELPERS

#include <fstream>

/* Checks if an input stream contains a non-numeric character.
   Returns true if does, and false otherwise.*/
bool nonNumericChar(std::ifstream &in); 

/* Checks if an integer is between 0 and 25 (inclusive). 
   Returns true if it is, and false otherwise. */
bool invalidIndex(int stream_ch);

/* Checks if a character is repeated in an input stream. 
   Returns true if it is, and false otherwise.*/
bool duplicateMapping(int index, int wiring, int wirings[]);

#endif
