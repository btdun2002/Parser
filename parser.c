#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"
#include <string.h>
#define OR ||

extern TokenType Token;
extern int lineNo, colNo;
extern FILE *f;
extern char ch;

void Error(int code)
{
	char Msg[80];
	switch (code)
	{
	case 11:
		strcpy(Msg, "\"PROGRAM\" keyword expected");
		break;
	case 12:
		strcpy(Msg, "Program identifier expected");
		break;
	case 13:
		strcpy(Msg, "Declare program name: \";\" expected");
		break;
	case 14:
		strcpy(Msg, "\".\" expected");
		break;
	case 15:
		strcpy(Msg, "Declare constant: Identifier expected");
		break;
	case 16:
		strcpy(Msg, "Declare constant: \"=\" expected");
		break;
	case 17:
		strcpy(Msg, "Declare constant: Number expected");
		break;
	case 18:
		strcpy(Msg, "Declare constant: \";\" expected");
		break;
	case 19:
		strcpy(Msg, "Declare variable: Identifier expected");
		break;
	case 20:
		strcpy(Msg, "Declare variable: number expected");
		break;
	case 21:
		strcpy(Msg, "Declare variable:\"]\" expected");
		break;
	case 22:
		strcpy(Msg, "Declare variable: \";\" expected");
		break;
	case 23:
		strcpy(Msg, "Declare procedure: Identifier expected");
		break;
	case 24:
		strcpy(Msg, "Declare procedure: formal parameter expected");
		break;
	case 25:
		strcpy(Msg, "Declare procedure: \")\" expected");
		break;
	case 26:
		strcpy(Msg, "Declare procedure: \";\" expected");
		break;
	case 27:
		strcpy(Msg, "Declare procedure: \";\" after procedure name expected");
		break;
	case 28:
		strcpy(Msg, "\"BEGIN\" keyword expected");
		break; // Loi trong phan cau lenh
	case 29:
		strcpy(Msg, "\"END\" keyword expected");
		break; // Loi trong phan cau lenh
	case 30:
		strcpy(Msg, "");
		break; // Loi trong phan cau lenh
	case 31:
		strcpy(Msg, "Assign statement: \"]\" expected");
		break;
	case 32:
		strcpy(Msg, "Assign statement: \":=\" expected");
		break;
	case 33:
		strcpy(Msg, "Call statement: \")\" expected");
		break;
	case 34:
		strcpy(Msg, "Call statement: Procedure identifier expected");
		break;
	case 35:
		strcpy(Msg, "complex statement: \"END\" keyword or \";\" expected");
		break;
	case 36:
		strcpy(Msg, "If statement: \"THEN\" expected");
		break;
	case 37:
		strcpy(Msg, "While statement: \"DO\" expected");
		break;
	case 38:
		strcpy(Msg, "For statement: variable identifier expected");
		break;
	case 39:
		strcpy(Msg, "For statement: \":=\" expected");
		break;
	case 40:
		strcpy(Msg, "For statement: \"TO\" keyword expected");
		break;
	case 41:
		strcpy(Msg, "For statement: \"DO\" keyword expected");
		break;
	case 42:
		strcpy(Msg, "");
		break;
	case 43:
		strcpy(Msg, "");
		break;
	case 44:
		strcpy(Msg, "");
		break;
	case 45:
		strcpy(Msg, "Condition: Relation operator expected");
		break;
	case 46:
		strcpy(Msg, "Array variable : \"]\" expected");
		break;
	case 47:
		strcpy(Msg, "\")\" expected");
		break;
	case 48:
		strcpy(Msg, "Error in expression.");
		break;
	}
	printf("\n\nError %d : %s at row :%d,Col:%d\n", code, Msg, lineNo, colNo);
	exit(1);
}

void compileProgram(void)
{
	if (Token == PROGRAM)
	{
		Token = getToken();
		if (Token == IDENT)
		{
			Token = getToken();
			if (Token == SEMICOLON)
			{
				Token = getToken();
				compileBlock();
				if (Token == PERIOD)
					Token = getToken();
				else
					Error(14);
			}
			else
				Error(13);
		}
		else
			Error(12);
	}
	else
		Error(11);
}

void compileBlock(void)
{
	if (Token == CONST)
	{
		Token = getToken();
		do
		{
			if (Token == IDENT)
			{
				Token = getToken();
				if (Token == EQU)
				{
					Token = getToken();
					if (Token == NUMBER)
					{
						Token = getToken();
					}
				}
			}
		} while (Token == COMMA);
		if (Token == SEMICOLON)
		{
			Token = getToken();
		}
		else
			Error(22);
	}

	if (Token == VAR)
	{
		Token = getToken();
		do
		{
			if (Token == IDENT)
			{
				Token = getToken();
				if (Token == RBRACK)
				{
					Token = getToken();
					if (Token == NUMBER)
					{
						Token = getToken();
						if (Token == LBRACK)
						{
							Token == getToken();
						}
						else
							Error(46);
					}
				}
			}
		} while (Token == COMMA);
		if (Token == SEMICOLON)
		{
			Token = getToken();
		}
		else
			Error(22);
	}

	while (Token == PROCEDURE)
	{
		compileDeclareProcedure();
	}

	if (Token == BEGIN)
	{
		Token = getToken();
		compileStatement();
		while (Token == SEMICOLON)
		{
			Token = getToken();
			compileStatement();
		}
		if (Token == END)
			Token = getToken();
		else
			Error(29);
	}
	else
		Error(28); // Thieu tu khoa Begin bat dau chuong trinh
}

void compileStatement(void)
{
	if (Token == IDENT)
	{
		Token = getToken();
		if (Token == LBRACK)
		{
			Token = getToken();
			compileExpression();
			if (Token == RBRACK)
			{
				Token = getToken();
			}
			else
				Error(21);
		}
		if (Token == ASSIGN)
		{
			compileExpression();
		}
	}
	else if (Token == CALL)
	{
		Token = getToken();
		if (Token = IDENT)
		{
			if (Token == LPARENT)
			{
				Token = getToken();
				do
				{
					compileExpression();
				} while (Token == COMMA);
				if (Token == RPARENT)
					Token = getToken();
				else
					Error(33);
			}
		}
	}
	else if (Token == BEGIN)
	{
		Token = getToken();
		compileStatement();
		while (Token == SEMICOLON)
		{
			compileStatement();
		}
		if (Token == END)
		{
			Token == getToken();
		}
		else
			Error(35);
	}
	else if (Token == IF)
	{
		Token = getToken();
		compileCondition();
		if (Token == THEN)
		{
			compileStatement();
			if (Token == ELSE)
			{
				Token = getToken();
				compileStatement();
			}
		}
	}
	else if (Token == WHILE)
	{
		Token = getToken();
		compileCondition();
		if (Token == DO)
		{
			compileStatement();
		}
	}
	else if (Token == FOR)
	{
		Token = getToken();
		if (Token = IDENT)
		{
			Token = getToken();
			if (Token == ASSIGN)
			{
				compileExpression();
				if (Token == TO)
				{
					Token = getToken();
					compileExpression();
					if (Token == DO)
					{
						Token = getToken();
						compileStatement();
					}
				}
			}
		}
	}
	else
	{
	}
}

void compileCondition(void)
{
	if (Token == ODD)
	{
		Token == getToken();
		compileExpression();
	}
	else
	{
		compileExpression();
		if (Token == EQU || Token == GTR || Token == GEQ || Token == LSS || Token == LEQ || Token == NEQ)
		{
			Token == getToken();
			compileExpression();
		}
	}
}

void compileExpression(void)
{
	if (Token == PLUS || Token == MINUS)
	{
		Token = getToken();
		compileTerm();
		while (Token == PLUS || Token == MINUS)
		{
			Token = getToken();
			compileTerm();
		}
	}
	else
		Error(48);
}

void compileTerm(void)
{
	compileFactor();
	while (Token == TIMES || Token == SLASH || Token == PERCENT)
	{
		Token = getToken();
		compileFactor();
	}
}
void compileFactor(void)
{
	if (Token == IDENT)
	{
		Token = getToken();
		if (Token == LBRACK)
		{
			Token = getToken();
			compileExpression();
			if (Token == RBRACK)
				Token = getToken();
			else
				Error(46);
		}
	}
	else if (Token == NUMBER)
	{
		Token = getToken();
	}
	else if (Token == LPARENT)
	{
		if (Token == LPARENT)
		{
			Token = getToken();
			compileExpression();
			if (Token == RPARENT)
			{
				Token = getToken();
			}
			else
				Error(47);
		}
	}
}

void compileDeclareConst()
{
}

void compileDeclareVariable()
{
}

void compileDeclareProcedure()
{
	if (Token == PROCEDURE)
	{
		Token = getToken();
		if (Token == IDENT)
		{
			Token = getToken();
			do
			{
				if (Token == LPARENT)
				{
					Token = getToken();
				}
				if (Token == VAR)
				{
					Token = getToken();
				}
				if (Token == IDENT)
				{
					Token = getToken();
				}
			} while (Token == SEMICOLON);
			if (Token == RPARENT)
			{
				Token = getToken();
			}
			if (Token == SEMICOLON)
			{
				Token = getToken();
				compileBlock();
				if (Token == SEMICOLON)
				{
					Token = getToken();
				}
				else
					Error(26);
			}
		}
	}
}

void compile(char *filename)
{
	f = fopen(filename, "rt");
	lineNo = 1;
	colNo = 0;
	ch = ' ';
	Token = getToken();
	compileProgram();
	fclose(f);
}
