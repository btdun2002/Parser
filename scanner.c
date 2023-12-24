#include <stdio.h>  //cho thao tac doc ky tu tu file getChar()
#include "scanner.h"

struct {
  	char string[MAX_IDENT_LEN + 1];
  	TokenType Token;
} keywords[KEYWORDS_COUNT] = {
  		{"BEGIN", BEGIN},
  		{"CALL", CALL},
  		{"CONST", CONST},
  		{"DO", DO},
    	{"ELSE", ELSE},
      	{"END", END},
        {"FOR", FOR},
   		{"IF", IF},
     	{"ODD",ODD},
  		{"PROCEDURE", PROCEDURE},
		{"PROGRAM", PROGRAM},
    	{"THEN", THEN},
    	{"TO", TO},
		{"VAR", VAR},
  		{"WHILE", WHILE}
};

TokenType Token;
int		  Num;
char	  Id[MAX_IDENT_LEN + 1];

int lineNo, colNo;
char ch;
FILE * f;

char getCh(){
	int c = fgetc(f);
	putchar(c);
  	colNo ++;
  	if (c == '\n') {
    	lineNo ++;
    	colNo = 0;
  	}
  return toupper(c);
}

TokenType checkKeyword(char * str){
	int i;
	for(i=0; i < KEYWORDS_COUNT;i++)
	   if(!strcmp(str,keywords[i].string))
	      return keywords[i].Token;
	return IDENT;
}

TokenType getToken(){

	while((ch==' ') || ch=='\n' || (ch=='\t')) ch = getCh(); //dau phan cach

	if( isalpha(ch)){		//bat dau la mot chu cai
		int l = 0;
		do{
			if(l < MAX_IDENT_LEN) Id[l++] = ch;
			ch = getCh();
		}while(isdigit(ch) || isalpha(ch));

		Id[l]='\0';
		return checkKeyword(Id);
	}else if( isdigit(ch)){  //bat dau la mot chu so
		Num = 0;
		do{
			Num = Num * 10 + ch - 48;
			ch = getCh();
		}while (isdigit(ch));
		return NUMBER;		//chu y canh bao: so qua lon
	} else if (ch == ':') {   //doan nhan tu vung :=
		ch = getCh();
		if (ch == '='){
			ch = getCh();
			return ASSIGN;
		}else return NONE;
	}else if(ch == '>'){
		 ch = getCh();
		 if(ch == '='){ ch = getCh();	 return GEQ;}
		 else return GTR;
	}else if(ch == '<'){
		 ch = getCh();
		 if(ch == '='){ch = getCh(); return LEQ;}
		 else if(ch == '>') {ch = getCh(); return NEQ;}
		 return LSS;
	}else if (ch == '='){ ch = getCh(); return EQU;}
	else if (ch == ';') { ch = getCh(); return SEMICOLON;}
	else if (ch == ',') { ch = getCh(); return COMMA;}
	else if (ch == '.') { ch = getCh(); return PERIOD;}
	else if (ch == '+') { ch=getCh(); return PLUS;}
	else if (ch == '-') { ch=getCh(); return MINUS;}
	else if (ch == '*') { ch=getCh(); return TIMES;}
	else if (ch == '/') { ch=getCh(); return SLASH;}
	else if (ch == '%') { ch=getCh(); return PERCENT;}
	else if (ch == '[') { ch=getCh(); return LBRACK;}
	else if (ch == ']') { ch=getCh(); return RBRACK;}
	else if (ch == '(') { ch=getCh(); return LPARENT;}
	else if (ch == ')') { ch=getCh(); return RPARENT;}
	else return NONE;
}

