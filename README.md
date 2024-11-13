
# Syntax and semantic analyzer

## Authors:
- Bolaños Guerrero Julián  
- Castillo Soto Jacqueline  
- Galindo Reyes Daniel Adrian  
- Isidro Castro Karen Cristina  
- Zurita Cámara Juan Pablo  

## Dependencies:
Important: to compile the program, a c99 or higher c compiler version is required. the necessary files for compilation are:

- **lex.h**: header file containing declarations of functions and data structures for lexical analysis.  
- **lex.c**: implements functions and initializes predefined variables from `lex.h`. serves as the heart of the lexical analyzer.  
- **parser.h**: header file containing declarations of functions and data structures for syntax analysis.  
- **parser.c**: implements functions and initializes predefined variables from `parser.h`. serves as the heart of the syntax analyzer.  
- **analyzer.c**: integrates the lexical and syntax analysis modules. adds necessary functions and data structures for the semantic analyzer. serves as the main file of the analyzer.  

These files are available in the [github repository]([https://github.com/DanielGalindoDev?tab=repositories](https://github.com/DanielGalindoDev/Parse-SDT)).

## Installation guide:
**NOTE:** Ensure that a c99 or higher c compiler version is installed.

1. Download the necessary files for compilation (see dependencies section).
2. Place the files in the same folder.
3. Open a terminal and navigate to the folder containing the files.
4. Compile the `.c` files (`lex.c`, `parser.c`, and `analyzer.c`) using the following command:
   ```
   gcc lex.c parser.c analyzer.c -o analyzer
   ```
5. The resulting executable will be `analyzer.exe` (windows) or `analyzer` (macos).

## Usage:
After generating the executable, it can analyze any text file for syntax and semantic correctness according to the specified grammar.

**Command to execute:**
```
./analyzer <file_path>
```
- `<file_path>`: path to the text file to be analyzed.
- the program outputs whether the programming statements (variable declarations or initializations) in the file are correct.

**Example:**
Create a text file with variable initialization statements in the same folder as the executable. execute the following command to analyze the file:
```
./analyzer example.txt
```

---

## Architecture and design:

### Grammar:
```
statementList → statement statementList
statementList → statement
statement → variable_creation ;
variable_creation → definition
variable_creation → definition = expression
definition → type identifier
expression → expression math1 factor
expression → factor
factor → factor math2 term
factor → term
term → ( expression )
term → constant
term → math1 term
```

- **Terminals:** `;`, `=`, `type`, `identifier`, `math1`, `math2`, `constant`.  
- **Non-terminals:** `statementList`, `statement`, `variable_creation`, `definition`, `expression`, `factor`, `term`.  
- **Start symbol:** `statementList`.  

### Syntax analysis:
Uses an slr parser. semantic analysis is performed during reductions in the slr algorithm.

#### diagram of lexical analyzer and parser workflow:
<br>
<img width="400" alt="image" src="https://github.com/user-attachments/assets/d9ff5249-8d37-4206-abf0-0fd278ecd76d">
<br>



### Parsing algorithm:
```c
let a be the first symbol of w$;
while (1) {
    let s be the state on top of the stack;
    if (ACTION[s,a] == shift t) {
        push t onto the stack;
        let a be the next input symbol;
    } else if (ACTION[s,a] == reduce A → β) {
        pop |β| symbols off the stack;
        let t = top of the stack;
        push GOTO[t,A] onto the stack;
        output production A → β;
    } else if (ACTION[s,a] == accept) {
        break;
    } else {
        call error-recovery routine;
    }
}
```

### Semantic analysis:
Semantic actions are executed during reductions. attributes of syntax tree leaves are passed upwards to the root. an example with `int a = 4;` illustrates this process.

#### example of stack behavior during semantic analysis:
<br>
<img width="543" alt="Captura de pantalla 2024-11-12 a la(s) 8 20 24 p m" src="https://github.com/user-attachments/assets/e370842c-f163-44b3-9a4a-60d23db97aeb">
<br>


#### Example of semantic actions:
| production        | semantic actions                                                                                                                                       |
|--------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|
| `A → B A`         | none                                                                                                                                                  |
| `A → B`           | none                                                                                                                                                  |
| `B → C ;`         | `B = C`  <br> print("parsing success") <br> print("sdt verified") <br> // print `B` attributes.                                                        |
| `C → D`           | `C = D`                                                                                                                                               |
| `C → D = E`       | validate type compatibility between `D` and `E` <br> perform assignments if valid.                                                                     |
| `E → E1 math1 F`  | validate types and perform arithmetic operation between `E1` and `F`.                                                                                  |
| `F → F1 math2 G`  | validate types and perform arithmetic operation between `F1` and `G`.                                                                                  |
| `G → constant`    | `G = constant`.                                                                                                                                       |

---

## Code implementation:
### User-defined data structures:
#### **Symbol**:
```c
typedef struct {
    char input[50];
    TOKEN token;
    DATA_TYPE type;
    char hasValue;
    STORAGE;
} SYMBOL;
```

- `input`: stores read characters for token categorization.
- `token`: enumerates token types (e.g., `TYPE`, `ID`, `MATH1`).
- `type`: enumerates data types (e.g., `CHAR`, `FLOAT`, `INT`).
- `hasValue`: indicates if the token is a constant.
- `STORAGE`: union for storing float or char values.

### Parsing table implementation:
#### **Action table**:
- stored as a 2d array:
  - rows: states of the lr(0) automaton.
  - columns: tokens.

- values:
  - `< 30`: shift action.
  - `30`: accept.
  - `> 30`: reduce action.
  - `-1`: error.

#### **Goto table**:
- stored as a 2d array:
  - rows: states of the lr(0) automaton.
  - columns: non-terminals.

### For more information:
To explore the full documentation, including detailed explanations and additional examples, you can download the complete user manual here:
[Download the full user manual](https://github.com/user-attachments/files/17725237/TEAM_6_PARSER_MANUAL.pdf)

