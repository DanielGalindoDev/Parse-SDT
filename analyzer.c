#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "parser.h"


/*
Pila para almacenar los simbolos leidos durante el analisis sintactico.
Esta informacion se ocupa durante el analisis semantico
*/

typedef struct 
{
    SYMBOL stack[100];
    int top;

    char semanticError;
}SYNTAX_TREE;

/*
Funciones relacionadas con el analizador semantico
*/
void addSymbol(SYNTAX_TREE *tree, const SYMBOL *symbol);
void resetTree(SYNTAX_TREE *tree);
void reduceTree(SYNTAX_TREE *tree,int rule,int *num);
void semanticResult(SYNTAX_TREE *tree);


int main(int argc,char* argv[])
{
    /*Se espera que se pase como argumento desde la terminal un archivo con el cual trabajar*/
    if( argc == 1)
    {
        puts("Necesitas poner la ruta de un archivo para leer.");
        puts("Ejemplo: .\\a.exe prueba.txt");
        return 1;
    }

    
    LEXER lex;
    //Incialización del analizador léxico
    lex.pf = fopen(argv[1],"r");
    if (lex.pf == NULL)
    {
        puts("Error al abrir el archivo");
        return 1;
    }
    lex.i = 0; 
    lex.peek = 0; 
    lex.current_state = 0; 
    size_t chars_read = fread(lex.buffer,sizeof(char),255,lex.pf);
    lex.buffer[chars_read] = '\0';


    Stack parser;
    //Inicializacion de las variables para el analizador sintactico
    int current_state;
    char type_action;
    initialize(&parser);
    push(&parser,0);

    
    SYNTAX_TREE tree; 
    //Inicialización para el trabajo del analizador semántico
    resetTree(&tree);

    //Variable que va a ir guardando la información conrrespondiente a cada token que leemos
    SYMBOL sb;
    nextSymbol(&lex,&sb);

    int sentNum = 0; 

    while (1)
    {
       
        current_state = peek(&parser);
        type_action = ACTION[current_state][sb.token];
            
        if (type_action == -1)
        {
            
            if (sb.token == $ && tree.semanticError == 0)break;

            ++sentNum;
            printf("\nSentencia (%d):\n",sentNum);
            printf("Error sintactico\n");
            printf("Error semantico\n");


            /*"Error recovery" technique. Cada que se encuentra un error sintactico, busca 
            reiniciar el análisis después de un punto y coma. */
            nextSymbol(&lex,&sb);
            while(sb.token != SEMICOLON && sb.token != $)
            {
                nextSymbol(&lex,&sb);
            }
            nextSymbol(&lex,&sb);

            //Se resetea la pila de estados
            initialize(&parser);
            push(&parser,0);

            //Se resetea la pila de simbolos
            resetTree(&tree);
            
        }
        else if (type_action < 30)
        {
            
            //Se añade el la informacion del token leido a la pila de simbolos
            addSymbol(&tree,&sb);

            //Se añade el estado al cual se hace shift en el automata LR. 
            push(&parser,type_action);

            //Se lee el siguiente token
            nextSymbol(&lex,&sb);


        }
        else if(type_action == 30)
        {
            break;
        }
        else
        {
            int rule = type_action - 31;
            int i = ruleSize[rule];
            
            reduceTree(&tree,rule,&sentNum);

            for (int j = 0; j < i;j++)
            {
                pop(&parser);
            }
            current_state = peek(&parser);
            NONTERMINAL nonterminal = ruleTransform[rule];
            current_state = GOTO[current_state][nonterminal];
            push(&parser,current_state);

        }
    }

    fclose(lex.pf);

}


//Añade símbolos a la pila de símbolos 
void addSymbol(SYNTAX_TREE *tree, const SYMBOL *symbol)
{
    tree->stack[++tree->top] = *symbol;
}

//Resetea la pila de símbolos a sus valores iniciales
void resetTree(SYNTAX_TREE *tree)
{
    tree->top = -1; 
    tree->semanticError = 0; 
}

//Realiza las acciones semánticas de acuerdo a cada regela de producción. 
void reduceTree(SYNTAX_TREE *tree,int rule, int *num)
{
    SYMBOL node; 
    switch (rule)
    {
    case 0:
        break;

    case 1:
        break;

    case 2:
        --tree->top;
        (*num)++;
        printf("\nSentencia (%d):\nSintacticamente correcta.\n",*num);
        semanticResult(tree);
        resetTree(tree);
        break; 

    case 3: 
        break; 

    case 4:
        
        if (tree->stack[tree->top-2].type == CHAR || tree->stack[tree->top].type == CHAR)
        {
            if (tree->stack[tree->top-2].type != tree->stack[tree->top].type)
            {
                if (tree->semanticError == 0) tree->semanticError = 1; 
                break;
            }
        }

        tree->stack[tree->top-2].ST = tree->stack[tree->top].ST;
        tree->stack[tree->top-2].hasValue = 1; 

        tree->top -=2;
        break; 

    case 5: 

        tree->stack[tree->top].type = tree->stack[tree->top-1].type;
        tree->stack[tree->top-1] = tree->stack[tree->top];

        --tree->top; 
        break; 

    case 6:

        if (tree->stack[tree->top-2].type == CHAR || tree->stack[tree->top].type == CHAR)
        {
            tree->semanticError = 2; 
            break;
        }

        if (tree->stack[tree->top].type == FLOAT || tree->stack[tree->top-2].type == FLOAT)
        {
            tree->stack[tree->top-2].type = FLOAT; 
        }
        else
        {
            tree->stack[tree->top-2].type = INT;    
        }

        if (tree->stack[tree->top-1].input[0] == '+')
        {
            tree->stack[tree->top-2].ST.floatValue += tree->stack[tree->top].ST.floatValue;
        }
        else
        {
            tree->stack[tree->top-2].ST.floatValue -= tree->stack[tree->top].ST.floatValue;
        }

        tree->top -= 2; 
        break; 

    case 7:
        break; 

    case 8: 

        if (tree->stack[tree->top-2].type == CHAR || tree->stack[tree->top].type == CHAR)
        {
            tree->semanticError = 3; 
            break;
        }

        if (tree->stack[tree->top].type == FLOAT || tree->stack[tree->top-2].type == FLOAT)
        {
            tree->stack[tree->top-2].type = FLOAT; 
        }
        else
        {
            tree->stack[tree->top-2].type = INT;    
        }

        if (tree->stack[tree->top-1].input[0] == '*')
        {
            tree->stack[tree->top-2].ST.floatValue *= tree->stack[tree->top].ST.floatValue;
        }
        else
        {
            tree->stack[tree->top-2].ST.floatValue /= tree->stack[tree->top].ST.floatValue;
        }

        tree->top -= 2;
        break; 
    
    case 9: 
        break;
    
    case 10: 
        tree->stack[tree->top-2] = tree->stack[tree->top-1]; 
        tree->top -= 2; 
        break;
    
    case 11:
        break;
    case 12: 

        if (tree->stack[tree->top].type == CHAR)
        {
            tree->semanticError = 3; 
            break;
        }

        if (tree->stack[tree->top-1].input[0] == '-')
        {
            tree->stack[tree->top].ST.floatValue *=  -1;
        }

        tree->stack[tree->top-1] = tree->stack[tree->top];
        --tree->top; 

    }

}


void semanticResult(SYNTAX_TREE *tree)
{
    if (tree->semanticError != 0)
    {
        printf("Semanticamente incorrecto.\n");
        
        switch (tree->semanticError)
        {
        case 1:
            printf("\t->Tipos de datos incompatibles.\n");
            break;
        case 2:
        case 3:
            printf("\t->Constantes de tipo CHAR no se pueden utilizar dentro de expresiones aritmeticas.\n");
            break;
        }
        return; 
    }

    printf("Semanticamente correcto.\n");
    printf("\t->Nombre de variable: %s\n",tree->stack[tree->top].input);
    switch (tree->stack[tree->top].type)
    {
    case INT:
        printf("\t->Tipo: INT\n"); 
        break;
    case FLOAT:
        printf("\t->Tipo: FLOAT\n"); 
        break;
    case CHAR:
        printf("\t->Tipo: CHAR\n"); 
        break;
    default:
        break;
    }
    if (tree->stack[tree->top].hasValue)
    {
        switch (tree->stack[tree->top].type)
        {
        case INT:
            printf("\t->Valor: %d\n",(int) tree->stack[tree->top].ST.floatValue); 
            break;
        case FLOAT:
            printf("\t->Valor: %.3f\n",tree->stack[tree->top].ST.floatValue);  
            break;
        case CHAR:
            printf("\t->Valor: %c\n",tree->stack[tree->top].ST.charValue); 
            break;
        default:
            break;
        }
    }
}




