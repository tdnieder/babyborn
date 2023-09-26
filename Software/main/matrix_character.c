/**
 * Provides matrices for characters (letters and numbers) for neopixel matrix
 * @author fni
 * @date 10.03.2022
 */
 
#include "matrix_character.h"

/*----------------------------------------------
 * Defines
 *----------------------------------------------*/

/*----------------------------------------------
 * Global Variables
 *----------------------------------------------*/
const int letterWidth = 6;
const int spaceWidth = 4;
const int punctWidth = 3;

/*----------------------------------------------
 * Local Variables
 *----------------------------------------------*/ 
 
/*----------------------------------------------
 * Local Prototypes
 *----------------------------------------------*/ 

/*----------------------------------------------
 * Functions
 *----------------------------------------------*/

/**
 * Returns column width of a letter character
 * including spacing to following characters
 * 
 * @return width of letter in columns
 */
int getLetterWidth()
{
  return letterWidth;
}

/**
 * Returns column width of a number character
 * including spacing to following characters
 * 
 * @return width of number in columns
 */
int getNumberWidth()
{
  return letterWidth;
}

/**
 * Returns column width of a space character
 * including spacing to following characters
 * 
 * @return width of space character in columns
 */
int getSpaceWidth()
{
  return spaceWidth;
}

/**
 * Returns column width of a punctuation character
 * only avalable is '.' & ':'
 * including spacing to following characters
 * 
 * @return width of punctuation in columns
 */
int getPunctuationWidth()
{
  return punctWidth;
}
 
 /**
  * Function converts a given character (letter or number) a matrix.
  * Height of matrix is 8-bit (or sizeof char). Width of character is n.
  * The origin [0,LSB] is at the top left. MSB at the bottom
  *
  * e.g. Letter 'A', n=5
  *
  * +- - - - ->n
  * |  1 1 1
  * |1       1
  * |1       1
  * |1 1 1 1 1
  * |1       1
  * |1       1
  * |1       1
  * |1       1
  *	
  * Supported width n:
  * 6 - for letters and numbers
  * 2 - for punctuations
  *
  * @param char character		letter or number that matrix shall represent
  * @param char* matrix			matrix that holds image of character
  * @param int n 				    witdh of matrix for character
  *
  */
 void char2Matrix(char character, char *matrix, int n)
 {	 	 
	 // Clear Matrix
	 int i;
	 for (i = 0; i < n; i++)
	 {
		 matrix[i] = 0b00000000;
	 }
	
	 // Letters and numbers with witdh 6
	 if(n == letterWidth)
	 {	 	 
		 switch(character)
		 {
			 case '0':
				matrix[0] = 0b01111110;
				matrix[1] = 0b10000111;
				matrix[2] = 0b10001001;
				matrix[3] = 0b11110001;
				matrix[4] = 0b01111110;
			 break;
			 case '1':
				matrix[0] = 0b10000100;
				matrix[1] = 0b10000010;
				matrix[2] = 0b11111111;
				matrix[3] = 0b10000000;
				matrix[4] = 0b10000000;
			 break;
			 case '2':
				matrix[0] = 0b11100010;
				matrix[1] = 0b10010001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b10000110;
			 break;
			 case '3':
				matrix[0] = 0b01000010;
				matrix[1] = 0b10000001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110110;
			 break;
			 case '4':
				matrix[0] = 0b00001000;
				matrix[1] = 0b00001100;
				matrix[2] = 0b00001010;
				matrix[3] = 0b00001001;
				matrix[4] = 0b11111111;
			 break;
			 case '5':
				matrix[0] = 0b01001111;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110001;
			 break;
			 case '6':
				matrix[0] = 0b01111110;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110010;
			 break;
			 case '7':
				matrix[0] = 0b11100001;
				matrix[1] = 0b00010001;
				matrix[2] = 0b00001001;
				matrix[3] = 0b00000101;
				matrix[4] = 0b00000011;
			 break;
			 case '8':
				matrix[0] = 0b01110110;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110110;
			 break;
			 case '9':
				matrix[0] = 0b01000110;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01111110;
			 break;
			 
			 case 'a':
			 case 'A':
				matrix[0] = 0b11111110;
				matrix[1] = 0b00001001;
				matrix[2] = 0b00001001;
				matrix[3] = 0b00001001;
				matrix[4] = 0b11111110;
			 break;
			 case 'b':
			 case 'B':
				matrix[0] = 0b11111111;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110110;
			 break;
			 case 'c':
			 case 'C':
				matrix[0] = 0b00111100;
				matrix[1] = 0b01000010;
				matrix[2] = 0b10000001;
				matrix[3] = 0b10000001;
				matrix[4] = 0b10000001;
			 break;
			 case 'd':
			 case 'D':
				matrix[0] = 0b11111111;
				matrix[1] = 0b10000001;
				matrix[2] = 0b10000001;
				matrix[3] = 0b10000001;
				matrix[4] = 0b01111110;
			 break;
			 case 'e':
			 case 'E':
				matrix[0] = 0b11111111;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b10001001;
			 break;
			 case 'f':
			 case 'F':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00001001;
				matrix[2] = 0b00001001;
				matrix[3] = 0b00001001;
				matrix[4] = 0b00001001;
			 break;
			 case 'g':
			 case 'G':
				matrix[0] = 0b01111100;
				matrix[1] = 0b10000010;
				matrix[2] = 0b10000001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01111001;
			 break;
			 case 'h':
			 case 'H':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00001000;
				matrix[2] = 0b00001000;
				matrix[3] = 0b00001000;
				matrix[4] = 0b11111111;
			 break;
			 case 'i':
			 case 'I':
				matrix[0] = 0b10000001;
				matrix[1] = 0b10000001;
				matrix[2] = 0b11111111;
				matrix[3] = 0b10000001;
				matrix[4] = 0b10000001;
			 break;
			 case 'j':
			 case 'J':
				matrix[0] = 0b01000000;
				matrix[1] = 0b10000000;
				matrix[2] = 0b10000001;
				matrix[3] = 0b01111111;
				matrix[4] = 0b00000001;
			 break;
			 case 'k':
			 case 'K':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00001000;
				matrix[2] = 0b00010100;
				matrix[3] = 0b00100010;
				matrix[4] = 0b11000001;
			 break;
			 case 'l':
			 case 'L':
				matrix[0] = 0b11111111;
				matrix[1] = 0b10000000;
				matrix[2] = 0b10000000;
				matrix[3] = 0b10000000;
				matrix[4] = 0b10000000;
			 break;
			 case 'm':
			 case 'M':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00000110;
				matrix[2] = 0b00011000;
				matrix[3] = 0b00000110;
				matrix[4] = 0b11111111;
			 break;
			 case 'n':
			 case 'N':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00000111;
				matrix[2] = 0b00011100;
				matrix[3] = 0b01100000;
				matrix[4] = 0b11111111;
			 break;
			 case 'o':
			 case 'O':
				matrix[0] = 0b01111110;
				matrix[1] = 0b10000001;
				matrix[2] = 0b10000001;
				matrix[3] = 0b10000001;
				matrix[4] = 0b01111110;
			 break;
			 case 'p':
			 case 'P':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00001001;
				matrix[2] = 0b00001001;
				matrix[3] = 0b00001001;
				matrix[4] = 0b00000110;
			 break;
			 case 'q':
			 case 'Q':
				matrix[0] = 0b00111100;
				matrix[1] = 0b01000010;
				matrix[2] = 0b10100001;
				matrix[3] = 0b01000010;
				matrix[4] = 0b10111100;
			 break;
			 case 'r':
			 case 'R':
				matrix[0] = 0b11111111;
				matrix[1] = 0b00001001;
				matrix[2] = 0b00011001;
				matrix[3] = 0b00101001;
				matrix[4] = 0b11000110;
			 break;
			 case 's':
			 case 'S':
				matrix[0] = 0b10000110;
				matrix[1] = 0b10001001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10001001;
				matrix[4] = 0b01110001;
			 break;
			 case 't':
			 case 'T':
				matrix[0] = 0b00000001;
				matrix[1] = 0b00000001;
				matrix[2] = 0b11111111;
				matrix[3] = 0b00000001;
				matrix[4] = 0b00000001;
			 break;
			 case 'u':
			 case 'U':
				matrix[0] = 0b01111111;
				matrix[1] = 0b10000000;
				matrix[2] = 0b10000000;
				matrix[3] = 0b10000000;
				matrix[4] = 0b01111111;
			 break;
			 case 'v':
			 case 'V':
				matrix[0] = 0b00011111;
				matrix[1] = 0b00100000;
				matrix[2] = 0b11000000;
				matrix[3] = 0b00100000;
				matrix[4] = 0b00011111;
			 break;
			 case 'w':
			 case 'W':
				matrix[0] = 0b01111111;
				matrix[1] = 0b10000000;
				matrix[2] = 0b01110000;
				matrix[3] = 0b10000000;
				matrix[4] = 0b01111111;
			 break;
			 case 'x':
			 case 'X':
				matrix[0] = 0b10000001;
				matrix[1] = 0b01100110;
				matrix[2] = 0b00011000;
				matrix[3] = 0b01100110;
				matrix[4] = 0b10000001;
			 break;
			 case 'y':
			 case 'Y':
				matrix[0] = 0b00000011;
				matrix[1] = 0b00000100;
				matrix[2] = 0b11111000;
				matrix[3] = 0b00000100;
				matrix[4] = 0b00000011;
			 break;
			 case 'z':
			 case 'Z':
				matrix[0] = 0b11100001;
				matrix[1] = 0b10010001;
				matrix[2] = 0b10001001;
				matrix[3] = 0b10000101;
				matrix[4] = 0b10000011;
			 break;
			 
			 case ' ':
				matrix[0] = 0b00000000;
				matrix[1] = 0b00000000;
				matrix[2] = 0b00000000;
				matrix[3] = 0b00000000;
				matrix[4] = 0b00000000;
       break;
			 case '-':
				matrix[0] = 0b00001000;
				matrix[1] = 0b00001000;
				matrix[2] = 0b00001000;
				matrix[3] = 0b00001000;
				matrix[4] = 0b00001000;
			 break;
			 
			 default:
				matrix[0] = 0b00000010;
				matrix[1] = 0b00000001;
				matrix[2] = 0b10110001;
				matrix[3] = 0b00001001;
				matrix[4] = 0b00000110;
			 break;
		 }
	 } 
	 
   // Space width
	 else if(n == spaceWidth)
	 {
		 switch(character)
		 {
			 case ' ':
       // Space charactr is empty
			 break;
       default:
       break;
		 }
	 }

	 // Punctuation width
	 else if(n == punctWidth)
	 {
		 switch(character)
		 {
			 case '.':
				 matrix[0] = 0b10000000;
			 break;
       case ':':
         matrix[0] = 0b00100100;
        break;
			 default:
			 break;
		 }
	 }
	 
 }
