# Enigma Simulator

## Background
<img src="images/diagram.png" height="400">

The key components of an Enigma machine are:
- a set of input switches (1)
- a plugboard (2) with a number of plug cables (3)
- a number of rotors (4)
- a reflector (5)
- an output board (6)

## To run
The program is invoked on the command line and is passed configuration file names as arguments. The first configuration file specifies the wiring map for the plugboard, the second file will specify the wiring map for the reflector, the next files will specify the wiring maps for the rotors and the last file will specify the rotors’ initial starting positions.

So, for example, the following program would be configured to use three rotors and a sample plugboard and reflector as follows:
`./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos`

Here the leftmost rotor would use the mapping described in I.rot, and the middle and right-hand rotors would use the mapping described in II.rot and III.rot respectively, with their starting positions specified in rotors/I.pos; the plugboard would use the mapping described in I.pb and the reflector the one in I.rf.

The program then (in a loop) reads input characters from the standard input stream. White-space characters (space, tab, carriage-return and newline) are discarded and upper case characters (A-Z) should be encrypted by the machine with the resulting upper case character output to the standard output stream. 
