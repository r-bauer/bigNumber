//
//  File: MAIN.C
//  Author: Roberto Bauer
//  Comments: Central program file, main () function
//


#define __MAIN_C__

#include "main.h"

int main(int argc, char *argv[])
{
//    return ( CalcInfix(argc, argv) );

    int iRet = EXIT_SUCCESS;



    return iRet;
}

PRIVATE void UseFile (char *fName )
{
  FILE *fin; 
  char *ptrStr;
  char strValue[256];
  int iChar;


  fin = fopen (fName, "rt");
  if (fin)
    {
      fprintf (stdout, "\nReading file %s\n", fName);

      // start checking file
      while (!feof (fin))
        {
          // go through all text, jumping space and punctuaction
          do
            {
              iChar = getc (fin);
            }
          while (iChar != EOF && (isspace (iChar) || ispunct (iChar)));

          // valid char
          // start to mount word
          ptrStr = strValue;
          do
            {
              *ptrStr++ = iChar;
              iChar = getc (fin);
            }
          while (iChar != EOF && !isspace (iChar) && !ispunct (iChar));

          // end of file, stop looping
          if (iChar == EOF)
            break;

          // close word with nul
          *ptrStr = '\0';

        }                       // while (!feof(fin)) 

      fclose (fin);

      fprintf (stdout, "\nFinished\n");

    }
  else
    {
      fprintf (stderr, "Could not find/open file %s\n",fName);
    }

}


