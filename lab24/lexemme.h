#ifndef __LEXEMME__
#define __LEXEMME__
#include<stdbool.h>

typedef enum Type Type;
typedef union Value Value;
typedef struct Lexemme Lexemme;
typedef struct ReadContext ReadContext;

enum Type{
    NUMBER, VARIABLE, PRIMITIVE_OPERATOR, FUNCTION, BRACKET, END, BEGIN, ERROR
};

union Value {
    int number;
    char str[100];
    char symbol;
};

struct Lexemme{
    Value Value;
    Type Type;
};

struct ReadContext{
    Lexemme previous;
};

Lexemme Variable(char *name);
Lexemme PrimitiveOperator(char symbol);
Lexemme Number(double number);
Lexemme Function(char *name);
Lexemme Bracket(char symbol);
Lexemme End();
Lexemme Begin();
Lexemme Error();

double LexemmeGetNumber(Lexemme *lex);
char LexemmeGetSymbol(Lexemme *lex);
char *LexemmeGetStr(Lexemme *lex);
Type LexemmeGetType(Lexemme *lex);

bool IsSeparator(int c);
bool IsDigit(int c);
bool IsAlpha(int c);
bool IsBracket(int c);
bool IsOperatorSymbol(int c);
void PrintLexemme(Lexemme lex, bool withSpace);

#endif