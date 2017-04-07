/*
   File: STACKDRV.C
   Author: Roberto Bauer
   Comments:
               Stack controller
*/


#define __STACKDRV_C__

#include "main.h"

LOCAL BOOL Prcd(char, char);
LOCAL int VerifyStrInfix(int, char *[], char **);
LOCAL int MakeStrPostfix(char **, char **);
LOCAL int CalcPostfix(char **, float *);
LOCAL int CreateTableArg(char *, char ***);
LOCAL BOOL VerifyBrackets(char *);


/*
Function:
            CalcInfix

     Purpose:
            Checks and calculates the input expression

     Parameters:
            int argc - total command line elements
			char * argv [] - command-line parameters

     Return:
			EXIT_SUCESS - parsed a valid expression
			EXIT_FAILURE - received invalid expression, or lack of resources

     Description:
            Checks the input infrase
            Converts from infix to postfix
            Calculates the postfix expression
*/
int CalcInfix(int argc, char *argv[])
{
	char *strInfix;
	char *strPostfix;
	float fRes;
	int i;

    if (argc == 1)
    {
        fprintf(stderr, "Uso: infixa <expressaoh>\n");
        return (EXIT_FAILURE);
    }

	i = VerifyStrInfix(argc, argv, &strInfix);

	if (i == EXIT_SUCCESS)
	{
		printf("%s\n", strInfix);
		i = MakeStrPostfix(&strInfix, &strPostfix);

		if (i == EXIT_SUCCESS)
		{
			printf("%s\n", strPostfix);
			i = CalcPostfix(&strPostfix, &fRes);

			if (i == EXIT_SUCCESS)
			{
				printf("%f\n", fRes);
			}
		}
	}

	return (i);
}

/*
	Function:
		VerifyStrInfix

	Purpose:
		Checks if input eh validates and formats string

	Parameters:
		int argc - total command line elements
		char * argv [] - command-line parameters
		char ** strInfix - pointer to a string pointer

	Return:
		EXIT_SUCESS - parsed a valid string expression
		*strInfix - pointer to allocated area containing the infix expression
		EXIT_FAILURE - received invalid expression, or lack of resources

	Description:
	
		A user-entered expression is entered by the user through the command line, 
		before verifying the validity, a string similar to the one inserted, the 
		number of strings pointed to by argv, refers to the total of BLANK SPACES 
		that separate The string, to facilitate the verification, a string will be 
		mounted where the operators and operands will be separated by space for 
		validation of the string, follow the rules:	
			1 - will only accept parentheses, digits and operators as a symbol
			2 - '+ - / * $' operators need to be between operands '01234567689'
			3 - parenthesis () 'have to always be in pairs respecting posicaoh
			4 - operand naoh can be followed by another operand
			5 - operators '+ - / * $' naoh can be on the left of ')'
			6 - operators '+ - / * $' naoh can be to the right of '('

*/
LOCAL int VerifyStrInfix(int argc, char *argv[], char **strInfix)
{
	int iCnt;
	unsigned int jCnt;
	size_t iSizStr;
	char *ptr;

	for (iCnt = 1, iSizStr = 0; iCnt < argc; ++iCnt)
	{
		iSizStr += strlen(argv[iCnt]);
	}

	if ((*strInfix = malloc(iSizStr * 2 + 1)) == NULL)
	{
        return (EXIT_FAILURE);
	}

	ptr = *strInfix;

	for (iCnt = 1; iCnt < argc; iCnt++)
	{
		for (jCnt = 0; jCnt < strlen(argv[iCnt]); jCnt++)
		{
			*ptr++ = argv[iCnt][jCnt];
			if (!( IsOperator(argv[iCnt][jCnt]) || IsBracket(argv[iCnt][jCnt]) || IsDigit(argv[iCnt][jCnt]) ))
			{
				fprintf(stderr, "expressaoh invalidah, simbolo naoh suportado\n");
				return (EXIT_FAILURE);
			}

			if ((IsOperator(argv[iCnt][jCnt])) ||
				(IsBracket(argv[iCnt][jCnt])) ||
				(IsDigit(argv[iCnt][jCnt]) && IsOperator(argv[iCnt][jCnt+1])) ||
				(IsDigit(argv[iCnt][jCnt]) && IsBracket(argv[iCnt][jCnt+1])) ||
				(IsDigit(argv[iCnt][jCnt]) && argv[iCnt][jCnt+1] == '\0'))
			{
				*ptr++ = ' ';
			}
		}
	}
	ptr--;
	*ptr = '\0';

	ptr = *strInfix;
	while (*ptr)
	{
		if (*ptr == ' ') 
		{
			if ((*(ptr-1) == '(' && IsOperator(*(ptr+1))) ||
				(IsOperator(*(ptr-1)) && *(ptr+1) == ')') ||
				(IsOperator(*(ptr-1)) && IsOperator(*(ptr+1))) ||
				(IsDigit(*(ptr-1)) && IsDigit(*(ptr+1))))
			{
				*(ptr+2) = '\0';
				fprintf(stderr, "%s <- expressaoh invalidah\n", *strInfix);
				return (EXIT_FAILURE);
			}
		}
		ptr++;
	}

	if (VerifyBrackets(*strInfix))
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		fprintf(stderr, "%s <- expressaoh invalidah", *strInfix);
		return (EXIT_FAILURE);
	}
}

/*
	Function:
               MakeStrPostfix

     Purpose:
               Converts an infix expression to postfix

     Parameters:
		char **strInfix - string with infix expression
		char **strPostfix - pointer to a string pointer

     Return:
		EXIT_SUCESS - mounted postfix string
		*strPostfix - pointer to allocated area containing the infix expression
		EXIT_FAILURE - lack of resources

     Description:
		The order between the operands does not change, only the operators need 
		to be rearranged, the operator is stacked to compare it with the next one 
		to be found, the top of the stack having greater or equal precedence is 
		peeled and included in the Expression, stacking the smaller one, the opposite, 
		keeping the top and stacking the new operator on it, in the end, those on 
		the stack will be sorted, simply empty the stack and insert in the expression.

*/
LOCAL int MakeStrPostfix(char **strInfix, char **strPostfix)
{
    int argc;
    char **argv;
    int iCnt;
    SSTACK *stkIn;
    size_t iSizStr;
    char *ptrP;
    SDATAIN sdEl;
    SDATAIN *sdTop;


    iSizStr = strlen(*strInfix);
    if ((*strPostfix = malloc(iSizStr + 1)) == NULL)
    {
        return (EXIT_FAILURE);
    }

    ptrP = *strPostfix;
    *ptrP = '\0';

    argc = CreateTableArg(*strInfix, &argv);

    stkIn = inCreateStack(argc);       
    if (stkIn == NULL)
    {
        return (EXIT_FAILURE);
    }

    for (iCnt = 0; iCnt < argc; ++iCnt)
    {
        if ( IsNumber(argv[iCnt]) )
        {
            if (*ptrP == '\0')
                sprintf(ptrP, "%s", argv[iCnt]);
            else
                sprintf(ptrP, "%s %s", ptrP, argv[iCnt]);
        }
        else //IsOperator
        {
            sdTop = inViewTopData(stkIn);

            if (sdTop == NULL) //IsEmpty
            {
                inPushData(stkIn, &argv[iCnt][0]);
            }
            else
            {
                if (argv[iCnt][0] == ')')
                {
                    while (inPopData(stkIn, &sdEl) && sdEl.cOpr != '(')
                    {
                        sprintf(ptrP, "%s %c", ptrP, sdEl.cOpr);
                    }
                }
                else if (argv[iCnt][0] == '(')
                {
				    inPushData(stkIn, &argv[iCnt][0]);
                }
                else if (Prcd(sdTop->cOpr, argv[iCnt][0]))
                {
                    inPopData(stkIn, &sdEl);
                    sprintf(ptrP, "%s %c", ptrP, sdEl.cOpr);
                    inPushData(stkIn, &argv[iCnt][0]);
                }
                else
                {
                    inPushData(stkIn, &argv[iCnt][0]);
                }				
            }
        }
    }

    while (inPopData(stkIn, &sdEl) && sdEl.cOpr != '(')
    {
        sprintf(ptrP, "%s %c", ptrP, sdEl.cOpr);
    }

    DestroyStack(stkIn);
    free(argv);

    return (EXIT_SUCCESS);
}

/*
	Function:
               CalcPostfix

     Purpose:
               Calculates a postfix expression

     Parameters:
		char ** strPostfix - string with postfix expression
		float * fRes - pointer to load response

     Return:
		EXIT_SUCESS - rated expression
		FRes - operating result
		*strPostfix - pointer to allocated area containing the infix expression
		EXIT_FAILURE - lack of resources

     Description:

*/
LOCAL int CalcPostfix(char **strPostfix, float *fRes)
{
	int argc;
	char **argv;
    SDATAPOST sdEl;
    SSTACK *stkPost;
    int iCnt;

	argc = CreateTableArg(*strPostfix, &argv);

	stkPost = postCreateStack(argc);
    if (stkPost == NULL)
    {
        return (EXIT_FAILURE);
    }

    for (iCnt = 0; iCnt < argc; ++iCnt)
    {
        if ( IsNumber(argv[iCnt]) )
        {
            sdEl.fVal = (float) Atoi(argv[iCnt]);
            if (!postPushData(stkPost, &sdEl)) {
                return (EXIT_FAILURE);
            }
        }
        else if ( IsOperator(argv[iCnt][0]) )
        {
            float fVal1, fVal2;

            postPopData(stkPost, &fVal2);
            postPopData(stkPost, &fVal1);

            switch (argv[iCnt][0])
            {
                case '+':	
                    sdEl.fVal = fVal1 + fVal2;
                    break;

                case '-':	
                    sdEl.fVal = fVal1 - fVal2;
                    break;

                case '/':	
                    sdEl.fVal = fVal1 / fVal2;
                    break;

                case '*':	
                    sdEl.fVal = fVal1 * fVal2;
                    break;

                case '$':	
                    sdEl.fVal = Expon(fVal1, (int)fVal2);
                    break;
            }
            postPushData(stkPost, &sdEl);
        }
    }

	postPopData(stkPost, fRes);

	DestroyStack(stkPost);
	free(argv);


    return (EXIT_SUCCESS);
}



/*
	Function:
               ConvPrcd

     Purpose:
               Returns the value of the operator symbol in the precedence list

     Parameters:
		char Opr - operator

     Return:
		Value from 0 to 3 based on the operator

     Description:
		Converts the character containing the operator's symbol to a numerical value that represents its precedence

*/
LOCAL int ConvPrcd(char cOpr)
{
	switch (cOpr)
	{
		default:
		case '(':	return 0;
		case '-':
		case '+':	return 1;
		case '/':
		case '*':	return 2;
		case '$':	return 3;
	}
}

/*
	Function:
               Prcd

     Purpose:
		Compare precedence between operators
		Function to support the MakeStrPostfix routine
               Returns the value of the operator symbol in the precedence list

     Parameters:
		char cOpr1 - operator symbol
		char cOpr2 - operator symbol

     Return:
		TRUE - operator 1 greater than or equal to operator 2
		FALSE - operator 1 smaller than operator 2

     Description:
		Converts the character containing the operator's symbol to a numerical 
		value that represents its precedence
*/
LOCAL BOOL Prcd(char cOpr1, char cOpr2)
{
	if (ConvPrcd(cOpr1) >= ConvPrcd(cOpr2))
		return TRUE;
	else
		return FALSE;
}

/*
	Function:
        CreateTableArg

     Purpose:
		Creates a table that points to each argument in the string

     Parameters:
		char * str - string with the expression to be used in the table
		char *** argv - pointer to table of arguments to be created

     Return:
		argc - total of arguments that the table has
		**argv - table with expressions arguments notes

     Description:
		The functions to convert infix to postfix and calculate postfix, 
		receive a string with each argument separated by a space, to 
		facilitate the process of traversing the string, a pointer vector 
		is created, where each position points to an argument .

*/
LOCAL int CreateTableArg(char *str, char ***myargv)
{
	char *pBegin;
	char *pEnd;
	int argc = 0;
	char *pTable;

	pBegin = str;
	while (*pBegin) {
		if (*pBegin++ == ' ')
			argc++;
	}
	argc++;
	
	 save initial position with pTable
	pTable = *myargv = malloc(argc * sizeof(char *));

	if (*myargv == NULL)
	{
        return 0;
	}

	pEnd = pBegin = str;
	while (*pEnd) 
	{
		if (*pEnd == ' ')
		{
			*pEnd = '\0';
			**myargv = pBegin;
			(*myargv)++;
			pBegin = pEnd + 1;
		}
		pEnd++;
	}
	**myargv = pBegin;

	*myargv = pTable;

	return argc;
}

/*
	Function:
        VerifyBrackets

     Purpose:
		Checks the correct order and quantity of parentheses

     Parameters:
		char * cBuf - points to the expression to be evaluated

     Return:
		TRUE - correct sequence of parentheses
		FALSE - incorrect quantity or order

     Description:
		Always stack '(', and popup when it finds ')', 
		the error indication occurs when we have a ')' 
		and the stack is empty, or at the end of the 
		expression, the stack still has stored values.
*/
LOCAL BOOL VerifyBrackets(char *cBuf)
{
    SDATA sdEl;
    SSTACK *stk;
    char c;
    int i;
	BOOL bOk = TRUE;

    stk = brcCreateStack((int)strlen(cBuf));
    if (stk == NULL)
    {
        return (FALSE);
    }


    for (i = 0; cBuf[i] != '\0'; ++i)
    {
        switch (c = cBuf[i])
        {
            case '(':
                sdEl.cOpener = c;
                if (!brcPushData(stk, &sdEl))
                {
					bOk = FALSE;
                }
                break;

            case ')':
                if (!brcPopData(stk, &sdEl))
                {
					bOk = FALSE;
                }
                else 
                {
                    if (c == ')' && sdEl.cOpener != '(')
                    {
						bOk = FALSE;
                    }
                }
                break;

            default:
                continue;
        }
    }


    if (brcViewData(stk, 0) != NULL) 
    {
        while (brcPopData(stk, &sdEl) != 0)
        {
			bOk = FALSE;
        }
    }

	DestroyStack(stk);

    return (bOk);
}
