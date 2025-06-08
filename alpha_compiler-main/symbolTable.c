#include "symbolTable.h"
#include "stackFrames.h"
int forNamingFunc = 0;
char *functionName = "$func_";


SymbolTableEntry *SymbolTable[SYMBOLTABLE_SIZE] = {NULL};


/*
    HashFunction implementation
*/
unsigned int hashFunction(const char *symbol_name) {
    unsigned int hash = 0;
    while (*symbol_name) {
        hash = (hash << 5) + *symbol_name++; // simple hashing function
    }
    unsigned int adjusted_hash = (hash % (SYMBOLTABLE_SIZE - 1)) + 1;
    // Add offset to avoid the first cell
    return adjusted_hash; // cell 0 is always empty 
}

/*
    Function that makes a new SymbolTable node
*/
SymbolTableEntry *createEntry(const char *name, unsigned int scope, unsigned int line, enum SymbolType type, enum UnionType union_type, int isActive){
    
    SymbolTableEntry *newEntry = malloc(sizeof(SymbolTableEntry));
    if (newEntry == NULL) {
        printf("NO MORE MEMORY SPACE\n");
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    
    
    newEntry->isActive=1;
    newEntry->scope_type = type;
    newEntry->cell_link = NULL;
    newEntry->scope_link = NULL;
    newEntry->s_scope = scope;
    newEntry->s_name = strdup(name);
    newEntry->line = line;

    switch(type) {
        case LIBFUNC:
            newEntry->type = libraryfunc_s;  // for library functions
            break;
        case VAR:
            newEntry->type = var_s;          // variables
            break;
        case USERFUNC:
            newEntry->type = programfunc_s;  // user functions
            break;
        default:
            newEntry->type = var_s;          // default fallback
            break;
    }

    if (union_type == FUNC) {
        newEntry->u_type = FUNC;
        newEntry->value.funcVal = malloc(sizeof(Function)); // Allocate memory for Function struct
        if (newEntry->value.funcVal == NULL) {
            printf("NO MORE MEMORY SPACE\n");
            // Handle memory allocation failure
            exit(EXIT_FAILURE);
        }
        newEntry->value.funcVal->line = line;
        // add argument list
        newEntry->value.funcVal->scope = scope;
        newEntry->value.funcVal->name = strdup(name); // Allocate and copy name
    } else {
        newEntry->u_type = VAR;
        newEntry->value.varVal = malloc(sizeof(Variable)); // Allocate memory for Variable struct
        if (newEntry->value.varVal == NULL) {
            printf("NO MORE MEMORY SPACE\n");
            // Handle memory allocation failure
            exit(EXIT_FAILURE);
        }
        newEntry->value.varVal->line = line;
        newEntry->value.varVal->scope = scope;
        newEntry->value.varVal->name = strdup(name); // Allocate and copy name
    }
    return newEntry;
}


void SymbolTableInsert(SymbolTableEntry* entry){
    SymbolTableEntry *head = SymbolTable[0];
    SymbolTableEntry *tmp = NULL, *prev = NULL;
    unsigned int position;

    while (head != NULL && head->s_scope != entry->s_scope ){
        prev = head;
        head = head->cell_link;
    }
    if(head == NULL && prev == NULL){       // empty cell 
        SymbolTable[0] = entry;

    }else if( head != NULL && head->s_scope == entry->s_scope){           // there are already elements of this scope in the scope list 
        if(entry->u_type == FUNC){
            position = hashFunction(entry->value.funcVal->name);

        }else {
            position = hashFunction(entry->value.varVal->name);
        }   
        // add the element in the hash table 
        tmp = SymbolTable[position];
        if (tmp == NULL){   // empty cell
            SymbolTable[position] = entry;
        }else{
            while(tmp->cell_link!= NULL){
                tmp = tmp->cell_link;
            }
            tmp->cell_link = entry;
        }
        // TRaverse the  scope list to connect the element in the back end of the list
        while(head->scope_link != NULL){
            head = head->scope_link;
        }
        head->scope_link = entry;

    }else{
        // there are no entries for this scope so innsert it in the scope list 
        prev->cell_link = entry;

    }

}
/*
    Function to print Hashtable ---- DONE
*/
void printSymbolTable(void){
    int i;
    SymbolTableEntry* scope_head = SymbolTable[0];
    printf("\n");
    while(scope_head != NULL){

        printf("----------  Scope #%d   ----------\n", scope_head->s_scope);
        SymbolTableEntry* tmp = scope_head;
        while(tmp!=NULL){

            if(tmp->scope_type == LIBFUNC){
                printf("\"%s\" [library function] (line %d) (scope %d)\n",tmp->value.funcVal->name , tmp->value.funcVal->line , tmp->value.funcVal->scope);

            }else if(tmp->scope_type == USERFUNC){
                    printf("\"%s\" [user function] (line %d) (scope %d)\n",tmp->value.funcVal->name , tmp->value.funcVal->line , tmp->value.funcVal->scope);
            
            }else if(tmp->scope_type == FORMAL){
                    printf("\"%s\" [formal argument] (line %d) (scope %d)\n",tmp->value.varVal->name , tmp->value.varVal->line , tmp->value.varVal->scope);
            
            }else if(tmp->u_type == FUNC){
                if(tmp->scope_type == GLOBAL){
                    printf("\"%s\" [global function] (line %d) (scope %d)\n",tmp->value.funcVal->name , tmp->value.funcVal->line , tmp->value.funcVal->scope);
                }else if(tmp->scope_type == LOCL){
                    printf("\"%s\" [local function] (line %d) (scope %d)\n",tmp->value.varVal->name , tmp->value.varVal->line , tmp->value.varVal->scope);
                }
            
            }else{
                if(tmp->scope_type == GLOBAL){
                    printf("\"%s\" [global variable] (line %d) (scope %d)\n",tmp->value.varVal->name , tmp->value.varVal->line , tmp->value.varVal->scope);
                }else if(tmp->scope_type == LOCL){
                    printf("\"%s\" [local variable] (line %d) (scope %d)\n",tmp->value.varVal->name , tmp->value.varVal->line , tmp->value.varVal->scope);
                }
            }
            tmp = tmp->scope_link;
        }
        scope_head = scope_head->cell_link;
    }
}

/*
    Inserts Lib functions in the table ---- DONE
*/
void insertLibFunctions(void){

    SymbolTableInsert(createEntry("print",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("input",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("objectmemberkeys",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("objecttotalmembers",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("objectcopy",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("totalarguments",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("argument",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("typeof",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("strtonum",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("sqrt",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("cos",0,0,LIBFUNC,FUNC,1));
    SymbolTableInsert(createEntry("sin",0,0,LIBFUNC,FUNC,1));

}

/*
    Function that searches in SymbolTable based on the mode
    Modes = lvalue_ID,   lvalue_local_ID,    lvalue_d_colon_ID,  funcdef,    formal_arg
*/
SymbolTableEntry *lookup(SymbolTableEntry *entry, char *mode){
    int name_found = 0;
    unsigned int index = hashFunction(entry->s_name);
    SymbolTableEntry *temp, *prev;
    
    if(strcmp(mode,"lvalue_ID")==0){
        temp = NULL;
        prev=NULL;
        if(entry->s_scope == 0){ // GLOBAL
            SymbolTableEntry *t = checkLibFuncName(entry->s_name);
            
            if(t!=NULL){ // found same name as lib function so i return
                return t;
            }
            temp = SymbolTable[0];
            temp = temp->scope_link;
            while(temp != NULL){
                if(strcmp(entry->s_name, temp->s_name)==0){
                    name_found = 1;
                    // δεν χρειάζεται έλεγχος για ίδιο όνομα με lib function αφού είμαστε σε scope 0
                    return temp;
                }
                temp = temp->scope_link;
            }
            return NULL; // we have to add it in the symbol table
            
        }else{  // LOCAL 
            SymbolTableEntry *t = checkLibFuncName(entry->s_name);
            
            if(t!=NULL){ // found same name as lib function so i return
                return t;
            }
            name_found=0;
            // search inside same scope
            temp = foundScopeHead(entry->s_scope);
            
            while(temp != NULL){
                
                if(strcmp(entry->s_name, temp->s_name)==0 && temp->isActive == 1){
                    name_found = 1;
                    return temp;
                    break;
                }
                temp = temp->scope_link;
            }
            temp = NULL;
            // search inside smaller scopes
            
            if(name_found == 0){    // did not find name inside the same scope so we look everywhere
                int tempo = entry->s_scope - 1;
                while(tempo>=0 && name_found==0){                  
                    temp = foundScopeHead(tempo);

                    while(temp!=NULL){
                        if(strcmp(entry->s_name, temp->s_name)==0 && temp->isActive == 1){
                            
                            prev = temp;
                            name_found = 1;
                            break;
                        }
                        temp = temp->scope_link;             
                    }
                    tempo -= 1; 
                }
                
                if(prev == NULL){
                    return NULL; // if we did not find anything with same name anywhere ----> we add it to the symbol table
                }

                // look up inside every scope (all nodes have same name as entry)
                if(HasAccess(prev) == 0){
                    return prev;
                }else{
                    printf("\033[31mError: No access lvalue -> id in line %d due to function interference\033[30m\n", entry->value.varVal->line);
                    entry->isActive = 0;
                    return entry;
                }
            }
        }
    }else if(strcmp(mode,"lvalue_local_ID")==0){
        
        temp = NULL;
        prev=NULL;
        // check inside same scope
        temp = foundScopeHead(entry->s_scope);
        
        SymbolTableEntry *t = checkLibFuncName(entry->s_name);
        
        // chack for same name as lib functions
        if(t!=NULL && entry->s_scope == 0){
            return t;
        }else if(t!=NULL && entry->s_scope != 0){
            printf("\033[31mError: Collision with Library Function in Line: %d\033[0m\n", entry->value.varVal->line);
            t->isActive = 0;
            return t;
        }
        
        
        while(temp!=NULL){
            
            if(strcmp(entry->s_name, temp->s_name)==0 && temp->isActive == 1){
                
                name_found = 1;
                if(!checkSameScopeRedefinition(entry->u_type,temp)){
                    return temp;
                }else{
                    printf("\033[31mError: Collision with Library Function in Line: %d\033[0m\n", entry->value.varVal->line);
                    temp->isActive = 0;
                    return temp;
                }

            }
            temp = temp->scope_link;             
        }
        
        if(name_found == 0){
            if(entry->s_scope == 0){
                entry->scope_type = GLOBAL;
            }
            return NULL; // we didn't find the name locally so we insert it to symboltable
        }

    }else if(strcmp(mode,"lvalue_d_colon_ID")==0){
        temp = NULL;
        temp = foundScopeHead(0);
        prev=NULL;
        while(temp!=NULL){
            if(strcmp(entry->s_name, temp->s_name)==0){
                name_found = 1;
                return temp;
            }
            prev = temp;
            temp = temp->scope_link;
        }
        if(name_found == 0){
            //error
            prev->isActive = 0;
            return prev;
        }

    }else if(strcmp(mode,"funcdef")==0){
        temp = NULL;
        SymbolTableEntry *t = checkLibFuncName(entry->s_name);
        if(t!=NULL){
            printf("\033[31mSame name as lib function in funcdef. Line: %d\033[0m\n",entry->value.funcVal->line);
            t->isActive = 0;
            return t;
        }
        temp = foundScopeHead(entry->s_scope);
        while(temp!=NULL){
            if(strcmp(entry->s_name, temp->s_name)==0 && temp->isActive == 1){
                name_found = 1;
                printf("\033[31mName collision in same scope in funcdef. Line: %d\033[0m\n", entry->value.funcVal->line);
                temp->isActive = 0;
                return temp;
            }
            temp = temp->scope_link;
        }
        if(name_found == 0){
            return NULL; // we add it to the symbol table at the entry's scope
        }

    }else if(strcmp(mode,"formal_arg")==0){ // μπορώ να το ενώσω με την προηγούμενη περίπτωση αλλά πρέπει να το δούμε
        temp = NULL;
        prev=NULL;
        SymbolTableEntry *t = checkLibFuncName(entry->s_name);
        if(t!=NULL){
            // return error
            printf("\033[31mFormal argument name collision with lib function\033[0m\n");
            t->isActive = 0;
            return t;
        }

        temp = foundScopeHead(entry->s_scope);

        while(temp!=NULL){
            if(strcmp(entry->s_name, temp->s_name)==0 && temp->scope_type == FORMAL && temp->value.varVal->line == entry->value.varVal->line){
                name_found = 1;
                printf("\033[31mFormal argument name collision with already existing formal argument\033[0m\n");

                // return error
                temp->isActive = 0;
                return temp;
            }
            temp = temp->scope_link;
        }
        if(name_found == 0){
            return NULL; // we add it to the symbol table at the entry's scope
        }
    }
    return NULL;
}

char* generateName(){

    ++forNamingFunc;
    char *funcNameBuffer = malloc(sizeof(char) * (strlen(functionName) + 10)); // 10 for the integer part
    if (funcNameBuffer == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    snprintf(funcNameBuffer, sizeof(funcNameBuffer), "%s%d", functionName, forNamingFunc);
    return funcNameBuffer;

}

/*
    Function that finds the head of the scope link
*/
SymbolTableEntry *foundScopeHead(int scope){
    SymbolTableEntry *tmp = SymbolTable[0];

    while(tmp != NULL){
        if(tmp->s_scope == scope){
            return tmp;
        }
        tmp = tmp->cell_link;
    }
    return tmp;
}

/*
    Function that checks if symbol has access
*/
int HasAccess(SymbolTableEntry *entry){ // search all stack 
    stackFrame *tmp = topStack();
    if(tmp == NULL){
        return 0;
    }
    if((entry->s_scope <= tmp->scope) && (entry->scope_type == FORMAL || entry->scope_type == LOCL)){
        return 1; // NO ACCESS there is a function between variables
    }else{
        printf("\033[32mHas access\033[0m\n");
        return 0; // HAS ACCESS
    }
}

/*
    Function that checks if symbol has same name as a lib function
*/
SymbolTableEntry *checkLibFuncName(char *symbol_name){
    SymbolTableEntry *tmp = SymbolTable[0];
    
    while(tmp != NULL ){
        if(tmp->scope_type != LIBFUNC){
            break;
        }
        
        if(strcmp(symbol_name,tmp->s_name) == 0){
            return tmp; // found same name with lib function
        }
        
        tmp = tmp->scope_link;
    }
    return NULL; // haven't found lib function name
}

/*
    Function that hides specific scope's symbols
*/
void HideSymbolsAtScope(int scope){
    SymbolTableEntry *curr = foundScopeHead(scope);
    while (curr != NULL)
    {
        curr->isActive = 0;
        curr = curr->scope_link;
    }    
}

int checkSameScopeRedefinition(enum UnionType type,SymbolTableEntry *entry){
    if((type == FUNC) && (entry->u_type == FUNC)){
        return 1;   //ERROR
    }else if((type == VAR) && (entry->u_type == FUNC)){
        return 1;   //ERROR
    }else if((type == FUNC) && (entry->u_type == VAR)){
        return 1;   //ERROR
    }else if((type == VAR) && (entry->u_type == VAR)){
        return 0;   // OK
    }
    return 1;
}

SymbolTableEntry *lookup_current_scope(char *name, int scope){
    SymbolTableEntry *temp = foundScopeHead(scope);

    while(temp != NULL){       
        if(strcmp(name, temp->s_name)==0 && temp->isActive == 1){
            return temp;
            break;
        }
        temp = temp->scope_link;
    }
    return NULL;
}
