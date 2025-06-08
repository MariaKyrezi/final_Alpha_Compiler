#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SYMBOLTABLE_SIZE 100

typedef enum scopespace_t{
    programvar,
    functionlocal,
    formalarg
}scopespace_t;


typedef enum symbol_t {
    var_s, 
    programfunc_s, 
    libraryfunc_s
}symbol_t;

enum SymbolType { 
    GLOBAL, LOCL, FORMAL, USERFUNC, LIBFUNC 
};

enum UnionType { // i made this enum
    FUNC, VAR
};

typedef struct Variable { 
    const char *name; 
    unsigned int scope; 
    unsigned int line; 
} Variable; 

typedef struct returnList{
    unsigned label;
    struct returnList* next;
}returnList;

typedef struct Function { 
    const char *name; 
    //List of arguments
    
    unsigned int scope; 
    unsigned int line; 
    int iaddress;   // holds information about the function definition for phase 4-5
    int totalLocals;
    
    returnList* retList;

} Function; 

typedef struct SymbolTableEntry { 

    int isActive;    // it works as a boolean but c doesn't have this type of variables
    int s_scope;
    char* s_name;
    enum UnionType u_type;
    enum SymbolType scope_type;
    unsigned taddress;  // xreiazetai?
    
    symbol_t type; // holds same information as SymbolType so it is not needed

    scopespace_t    space;
    unsigned        offset;
    unsigned        line;

    union { 
        Variable *varVal; 
        Function *funcVal; 
    } value;


    struct SymbolTableEntry *cell_link;  // this is use to connect elements on the same cell
    struct SymbolTableEntry *scope_link; // this is used to connect elements on the same scope

}SymbolTableEntry;



unsigned int hashFunction(const char *symbol_name) ;
SymbolTableEntry *createEntry(const char *name, unsigned int scope, unsigned int line, enum SymbolType type, enum UnionType union_type, int isActive);
void SymbolTableInsert(SymbolTableEntry* entry);
void printSymbolTable(void);
void insertLibFunctions(void);
SymbolTableEntry *lookup(SymbolTableEntry *entry, char *mode);
SymbolTableEntry *foundScopeHead(int scope);
int HasAccess(SymbolTableEntry *entry);
SymbolTableEntry* checkLibFuncName(char *symbol_name);
void HideSymbolsAtScope(int scope);
int checkSameScopeRedefinition(enum UnionType type,SymbolTableEntry *entry);
char* generateName();
SymbolTableEntry *lookup_current_scope(char *name, int scope);