#include <stdio.h>
#include <stdio.h>


/*Classification of tokens*/
typedef enum
{
    TYPE, //value 0
    ID, // value  1

    MATH1, // value 2
    MATH2, // value 3

    CONSTANT, // value 4

    SEMICOLON, // value 5
    EQUAL, // value 6

    LP, // value 7
    RP, // value 8

    NO_VALID, // value 9
    $ // value 10
}TOKEN;


typedef enum
{
    CHAR, 
    INT,
    FLOAT
}DATA_TYPE;

typedef struct
{
    char input[50];
    DATA_TYPE type;

    TOKEN token;
    char hasValue;
    
    union
    {
        int intValue; 
        float floatValue; 
        char charValue;
    }ST;

}SYMBOL;


typedef struct lex
{
    FILE *pf;
    char buffer[256];

    int i; 
    int peek;  
    int current_state; 
}LEXER;


extern const char FA [][97];

void getSymbolData(LEXER *const lex, SYMBOL *symbol);

void isKeyWord(LEXER *const lex, SYMBOL *symbol);

void nextSymbol(LEXER *const lex, SYMBOL *symbol);

float string_to_float(const LEXER *const lex);

void printTokenInfo(const LEXER *const lex,const SYMBOL *const symbol);
