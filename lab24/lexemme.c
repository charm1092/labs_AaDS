#include "lexemme.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Lexemme Variable(char *name){
    Lexemme l;
    l.Type = VARIABLE;
    strcpy(l.Value.str, name);
    return l;
}

Lexemme PrimitiveOperator(char symbol){
    Lexemme l;
    l.Type = PRIMITIVE_OPERATOR;
    l.Value.symbol = symbol;
    return l;
}

Lexemme Number(double number){
    Lexemme l;
    l.Type = NUMBER;
    l.Value.number = (int)number;
    return l;
}

Lexemme Function(char *name){
    Lexemme l;
    l.Type = FUNCTION;
    strcpy(l.Value.str, name);
    return l;
}

Lexemme Bracket(char symbol){
    Lexemme l;
    l.Type = BRACKET;
    l.Value.symbol = symbol;
    return l;
}

Lexemme End(){
    Lexemme l;
    l.Type = END;
    return l;
}

Lexemme Begin(){
    Lexemme l;
    l.Type = BEGIN;
    return l;
}

Lexemme Error(){
    Lexemme l;
    l.Type = ERROR;
    return l;
}

double LexemmeGetNumber(Lexemme *lex){
    return lex->Value.number;
}

char LexemmeGetSymbol(Lexemme *lex){
    return lex->Value.symbol;
}

char *LexemmeGetStr(Lexemme *lex){
    return lex->Value.str;
}

Type LexemmeGetType(Lexemme *lex){
    return lex->Type;
}

bool IsSeparator(int c){
    return (c == ' ' || c == '\t' || c == ',');
}

bool IsDigit(int c){
    return isdigit(c);
}

bool IsAlpha(int c){
    return (isalpha(c) || c == '_');
}

bool IsBracket(int c){
    return (c == '(' || c == ')');
}

bool IsOperatorSymbol(int c){
    return strchr("+-*/^", c) != NULL;
}

void PrintLexemme(Lexemme l, bool withSpace){
    if (l.Type == NUMBER){
        printf("%d", l.Value.number);
    }
    else if (l.Type == VARIABLE){
        printf("%s", l.Value.str);
    }
    else if (l.Type == PRIMITIVE_OPERATOR){
        printf("%c", l.Value.symbol);
    }
    else if (l.Type == FUNCTION){
        printf("%s", l.Value.str);
    }

    if (withSpace){
        printf(" ");
    }
}