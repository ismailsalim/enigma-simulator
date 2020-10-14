#include "configHelpers.h"
#include <iostream>

bool nonNumericChar(std::ifstream &in) {
  int stream_start = in.tellg();
  char ch;

  in.get(ch);
  while(!isspace(ch) && !in.eof()) {
    if(!isdigit(ch)) {
      std::cerr << "Found an invalid character (first identified was '"
		<< ch << "') in "; 
      return true;
    }
    in.get(ch);
  }

  in.seekg(stream_start);
  return false;
}

bool invalidIndex(int stream_ch) {
  if (!(stream_ch >= 0 && stream_ch < 26)) {
    std::cerr << "Found invalid index of " << stream_ch <<
      ".\nIndex not between 0 and 25 in "; 
    return true;
  }
  return false;
}

bool duplicateMapping(int index, int wiring, int wirings[]) {
  for(int i = 0; i < 26; i++) {
    if (wiring == wirings[i]) {
      std::cerr << "Invalid mapping of input " << index <<
	" to output " << wiring << " (zero-indexed)."
	"\nOutput " << wiring  <<
	" has already been mapped to " << i <<
	" in ";
      return true;
    }
  }
  return false;
}

