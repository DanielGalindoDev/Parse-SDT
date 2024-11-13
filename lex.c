#include <stdio.h>
#include <stdlib.h>
#include "lex.h"


/*Automata finitio para la identificación de tokens*/
const char FA[][97] =
{
    {
    0, 7,12,12, 1,12,12, 9, 6, 6, 7, 7,12, 7, 4, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,12, 6, 7, 7, 7,12,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,12,12,12,12, 1,12, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6,12, 6,12,0,0  
    }, //q_0

    {
    -1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1    
    }, //q_1

    {
    -1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1, 1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,-1,-1,-1,-1,-1,-1 
    }, //q_2

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1   
    }, //q_3

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    }, //q_4

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1   
    }, //q_5

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    }, //q_6

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 
    }, //q_7

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1   
    }, //q_8

    {
    -1,10,10,10,10,10,10,-1,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,-1,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,-1,-1    
    }, //q_9

    {
    -1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1    
    }, //q_10

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1    
    }, //q_11

    {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1    
    } //q_12
};


/*Categoriza el tipo de token de acuerdo al estado del automata*/
void getSymbolData(LEXER *const lex, SYMBOL *symbol)
{
    symbol->hasValue = 0; 

    switch (lex->current_state)
    {
    case -1: 
    symbol->token = $;
    break;
    case 1:
    symbol->token = ID; 
    break; 
    case 2: 
    isKeyWord(lex,symbol);
    break;
    case 3: 
    symbol->token = CONSTANT;
    symbol->type = INT;
    symbol->ST.floatValue = (int)string_to_float(lex);
    symbol->hasValue = 1; 
    break;
    case 5: 
    symbol->token = CONSTANT;
    symbol->type = FLOAT;
    symbol->ST.floatValue = string_to_float(lex);
    symbol->hasValue = 1; 
    break;
    case 6: 

        switch (lex->buffer[lex->i])
        {
        case ';': 
        symbol->token = SEMICOLON; 
        break; 
        case '(':
        symbol->token = LP;
        break; 
        case ')':
        symbol->token = RP; 
        break; 
        default: 
        symbol->token = NO_VALID; 
        break; 
        }

        break;

    case 7: 
        switch (lex->buffer[lex->i])
        {
        case '=':
        symbol->token = EQUAL; 
        break; 
        case '+':
        case '-':
        symbol->token = MATH1;
        break; 
        case '/':
        case '*':
        symbol->token = MATH2;
        break; 

        default: 
        symbol->token = NO_VALID; 
        break;
        }
        break;
    case 8:
        symbol->token = NO_VALID;
        break;
    case 11: 
    symbol->token = CONSTANT; 
    symbol->type = CHAR; 
    symbol->ST.charValue = lex->buffer[lex->i+1];
    symbol->hasValue = 1; 
    break;
    default: 
    symbol->token = NO_VALID; 
    break; 
    }

    int inputSize = lex->peek - lex->i - 1;
    if (inputSize > 49)
    {
        symbol->token = NO_VALID; 
    }
    else if (symbol->token != $)
    {
        for (int i = lex->i; i < lex->peek; i++)
        {
            symbol->input[i - lex->i] = lex->buffer[i];
        }
        symbol->input[inputSize+1] = '\0';
        
    }


    //printTokenInfo(lex,symbol);

    /*The token has been categorized. We need to move our "cursors" to search for other tokens*/
    lex->i = lex->peek; 
    lex->current_state = 0;
}


/*Distinguish whether a lexeme is an identifier or a keyword*/
void isKeyWord(LEXER *const lex, SYMBOL *symbol)
{
    if (lex->peek - lex->i > 5)
    {
        symbol->token = ID; 
        return; 
    }

    /* Hash function */
    int sum = 0;
    for (short i = lex->i; i < lex->peek; i++) 
    {
        short aux = i - lex->i; 
        sum += lex->buffer[i] * (2*aux+1);
    }
    
    symbol->token = TYPE; 
    switch (sum)
    {
        /*Mapping case for 'int'*/
        case 1015:
        symbol->type = INT; 
        break; 
        /*Mapping case for 'char'*/
        case 1694:
        symbol->type = CHAR; 
        break;
        /*Mapping case for 'float'*/
        case 2704:
        symbol->type = FLOAT; 
        break;
        default:
        symbol->token = ID;
        break;
    }
}

/*Encuentra el siguiente token del input de entrada*/
void nextSymbol(LEXER *const lex, SYMBOL *symbol)
{
    while (1)
    {
        if (lex->buffer[lex->peek] == '\0')
        {
            /*Necessary to update the buffer*/
            if(!feof(lex->pf))
            {
                
                long shift = lex->i - lex->peek; 
                fseek(lex->pf,shift,SEEK_CUR);
                size_t chars_read = fread(lex->buffer,sizeof(char),255,lex->pf);
                lex->buffer[chars_read] = '\0';
                lex->i = 0; 
                lex->peek = -1 * shift;
                
            }
            else
            {
                if (lex->current_state == 0) lex->current_state = -1;
                break;
            }
        }

        unsigned char c;  
        if (lex->buffer[lex->peek] < 10)
        {
            c = 96; 
        }
        else if (lex->buffer[lex->peek] == 10)
        {
            c = 95; 
        }
        else
        {
            c = lex->buffer[lex->peek] - 32; 
        }
        
        char production = FA[lex->current_state][c];

        if(production == -1)
        {
            break;
        }
        else
        {
            if (lex->current_state == 0) lex->i = lex->peek; 
            lex->peek++;
            lex->current_state = production;
        }
    }

    getSymbolData(lex,symbol);

}

/*Ecuentra el valor numerico de una cadena*/
float string_to_float(const LEXER *const lex) {
    float result = 0.0;
    int i = lex->i;

    // Parte entera
    for (; lex->buffer[i] != '.' && i < lex->peek; i++)
    {
        int digit = lex->buffer[i] - '0'; 
        result = result * 10 + digit;
    }

    i++;
    float decimal_place = 0.1;

    for (; i < lex->peek; i++)
    {
        int digit = lex->buffer[i] - '0';
        result += digit * decimal_place; 
        decimal_place *= 0.1;
    }
    
    return result;
}


void printTokenInfo(const LEXER *const lex,const SYMBOL *const symbol)
{
    switch (symbol->token)
    {
    case ID:
        printf("<IDENTIFIER, ' ");
        break;
    case TYPE:
        printf("<TYPE, ' ");
        break;
    case CONSTANT:
        printf("<CONSTANT, ' ");
        break;
    case SEMICOLON:
        printf("<SEMICOLON, ' ");
        break;
    case MATH1:
        printf("<MATH1, ' ");
        break;
    case MATH2:
        printf("<MATH2, ' ");
        break;
    case EQUAL:
        printf("<EQUAL, ' ");
        break;
    case LP: 
        printf("<LR, ' ");
        break;
    case RP: 
        printf("<LR, ' ");
        break;
    case NO_VALID:
        printf("<NON VALID, ' ");
        break;
    }
    if (symbol->token == $)
    {
        printf("END OF FILE\n");
    }
    else
    {
        printf("%s ' >\n",symbol->input);
    }
}




