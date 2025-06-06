#include "phase3.h"

struct quad* quads = (struct quad*)0;
unsigned total = 0;
unsigned currQuad = 0;

instruction *instructions = NULL;
unsigned currInstruction = 0;
unsigned totalInstructions = 0;


incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned         ij_total = 0;

char **strings = NULL;
unsigned currString = 0;
unsigned totalStrings = 0;

double* numbers = NULL;
unsigned currNumber = 0;
unsigned totalNumbers = 0;

char** libraryFuncs = NULL;
unsigned currLib = 0;
unsigned totalLibs = 0;

func* userFuncs = NULL;
unsigned currUserFuncs = 0;
unsigned totalUserFuncs = 0;

unsigned programVarOffset       = 0;
unsigned functionLocalOffset    = 0;
unsigned formalArgsOffset       = 0;
unsigned scopeSpaceCounter      = 1;

int tempcounter = 0;
generator_func_t generators[] = {
    
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_ASSIGN,
    generate_NOP,
    generate_JUMP,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_GREATER,
    generate_IF_GREATEREQ,    
    generate_IF_LESS,
    generate_IF_LESSEQ,
    generate_NOT,
    generate_OR,
    generate_AND,
    generate_PARAM,
    generate_CALL,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_RETURN,
    generate_FUNCEND,
    generate_UMINUS
};
/* Δημιουργεί ένα νέο expression βασισμένο στα δεδομένα ενός συμβόλου
   basically βάζει το type*/
expr* lvalue_expr(SymbolTableEntry* sym){
    assert(sym);
    expr * e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = (expr*) 0;
    e->sym = sym;

    switch(sym->type){
        case var_s:
            e->type = var_e;
            break;
        case programfunc_s:
            e->type = programfunc_e;
            break;
        case libraryfunc_s:
            e->type = libraryfunc_e;
            break;
        default:
            assert(0);
    }
    return e;
}

/* Κάνει generate ένα νέο όνομα για τις temprary μεταβλητές*/
char* newtempname(void){

    //tempcounter += 1;
    char * tempname = (char*)malloc(sizeof(char) * 10);
    sprintf(tempname, "_t%d", tempcounter);
    tempcounter += 1;
    return tempname;
}

/* Κάνει τον counter που μετράει τις temprary μεταβλητές 0 */
void resettemp(void)    { tempcounter = 0; }


SymbolTableEntry * newtemp(int scope, int line_number){
    char *name = newtempname();
    SymbolTableEntry *sym = lookup_current_scope(name, scope);
    SymbolTableEntry * entry;
    if (sym == NULL){
        if(scope == 0){
            entry = createEntry(name,scope,line_number,GLOBAL,VAR,1);
        }else{
            entry = createEntry(name,scope,line_number,LOCL,VAR,1);
        }        
        entry->offset = currscopeoffset();
        entry->space = programvar;
        entry->s_name = name;
        entry->s_scope = scope;
        entry->line = line_number;
        entry->type = var_s;

        SymbolTableInsert(entry);

        return entry;
    }else{
        return sym;

    }
}

/* Αρχικοποιεί το quad με όλα τα δεδομένα */
void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line){
    if(currQuad == total) expand();

    quad* p     = quads+currQuad++;
    p->op       = op;
    p->arg1     = arg1;
    p->arg2     = arg2;
    p->result   = result;
    p->label    = label;
    p->line     = line;
    p->taddress = 0;
}

//check τι είναι το LABEL
expr *emit_arithOp(iopcode op, expr* arg1, expr* arg2, unsigned label, int scope, int line_number){
    expr* result= newexpr(arithexpr_e);
    
    if(check_arith(arg1,"Arithmetic Expression (+,-,*,/,%%)")==0 && check_arith(arg2,"Arithmetic Expression (+,-,*,/,%%)")==0){       
        if(op == add){
            result->numConst = arg1->numConst + arg2->numConst;
        }else if(op == sub){ 
            result->numConst = arg1->numConst - arg2->numConst;
        }else if(op == mul){ 
            result->numConst = arg1->numConst * arg2->numConst;
        }else if(op == divv){
            if(arg2->numConst == 0){
                printf("\033[31mError: Division by zero in line: %d\033[0m\n", line_number);
            }else{
                result->numConst = arg1->numConst / arg2->numConst;
            }
        }else{
            if( ((int)arg2->numConst) == 0){
                printf("\033[31mError: Division by zero in line: %d\033[0m\n", line_number);
            }else{
                result->numConst = ((int)arg1->numConst) % ((int)arg2->numConst);
            }
            
        }
    }

    if(istempexpr(arg1) != 0){
        result->sym = arg1->sym;
    }else{
        result->sym = newtemp(scope, line_number);
    }

    emit(op,arg1,arg2,result,label,line_number);
    return result;
}

expr *emit_comparisonOp(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, int scope, int line_number){
    result = newexpr(boolexpr_e);
    result->sym = newtemp(scope,line_number);

    /**
     * Check for arithmetic?
    */

    result->truelist = newlist(nextQuad());
    result->falselist = newlist(nextQuad()+1);

    emit(op,arg1,arg2,result,nextQuad()+3,line_number);
    
    emit(jump, NULL, NULL, NULL,0,line_number);
    
    return result;
}

/* Μεγαλώνει τον πίνακα που περιέχει τα quads*/
void expand(void){
    assert(total==currQuad);
    quad* p = (quad*)malloc(NEW_SIZE);
    if(quads){
        memcpy(p,quads,CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

/* Δημιουργεί ένα νέο expression με type t */
struct expr* newexpr(expr_t t){
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type = t;
    return e;
}

/* Δημιουργεί νέο expression με τον σωστό τύπο και περιεχόμενο */
expr* newexpr_conststring(char* s){
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

/* Δημιουργεί νέο expression με τον σωστό τύπο και περιεχόμενο */
expr* newexpr_constnum(double i){
    expr* e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}

/* Δημιουργεί νέο expression με τον σωστό τύπο και περιεχόμενο */
expr* newexpr_constbool (unsigned int b) {
    expr* e = newexpr(constbool_e);
    e->boolConst = !!b;
    return e;
}

/* Κάνει emit εάν είναι table item*/
expr* emit_iftableitem(expr* e,int scope, int yylineno ){
    if(e->type != tableitem_e){
        return e;
    }else{
        expr* result = newexpr(var_e);
        result->sym = newtemp(scope, yylineno);
        emit(tablegetelem,e,e->index,result, -1, yylineno);
        return result;
    }
}

/* Υλοποιεί ένα call με τα απαραίτητα params*/
expr* make_call(expr* lv, expr* reversed_elist, int scope, int yylineno){
    expr* func = emit_iftableitem(lv, scope, yylineno);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL, -1,  yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(calll, func,NULL, NULL, -1, yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp(scope, yylineno);
    emit(getretval, NULL, NULL, result, -1, yylineno);
    return result;
}

/* Αναγνωρίζει εάν είναι temprary μεταβλητή*/
unsigned int istempname(char* s){
    return *s == '_';
}

/* Ελέγχει αν υπάρχει ορισμένη κρυφή μεταβλητή με ίδιο όνομα με το expression*/
unsigned int istempexpr (expr* e) {
    return e->sym && istempname(e->sym->s_name);
}

/* Updates the label of jumps after the end of stmts */
/* USED IN IF AFTER stmt TO UPDATE THE VALUE OF JUMP*/
void patchlabel (unsigned quadNo, unsigned label) {
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

/* Επιστρέφει το τρέχον quad */
unsigned nextQuad (void) { 
    return currQuad; 
}

/* creates break and continue lists for loop stmts */
stmt_t *make_stmt (void){
    struct stmt_t *s =(struct stmt_t *)malloc(sizeof(struct stmt_t));
    memset((void *)s, 0, sizeof(stmt_t));

    s->breakList = 0;
    s->contList = 0; 
    return s;
}

/*Βάζει στη θέση i του πίνακα των quads το label ίσο με 0*/
int newlist (int i){
    quads[i].label = 0; 
    return i; 
}

int mergelist (int label1, int label2) {
    if (!label1){
        return label2;
    }else if (!label2){
        return label1;
    }else {
        int i = label1;
        while (quads[i].label){
            i = quads[i].label;
        }
        quads[i].label = label2;
        return label1;
    }
}

void patchlist (int list, unsigned label) {
   
    while (list) {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

/* Καλείται όταν τελειώσουν τα formal arguments*/
void resetformalargsoffset(void){
    formalArgsOffset = 0;
}

/* Καλείται όταν κλείνει το block της συνάρτησης */
void resetfunctionlocaloffset(void){
    functionLocalOffset = 0;
}

/* Θα την καλούμε όταν έχουμε εμφωλευμένες συναρτήσεις 
    για να κρατάμε κάπου το offset της αρχικής και μόλις τελειώνει
    η εμφωλευμένη να το επαναφέρουμε*/
void restorecurrscopeoffset(unsigned n){
    switch (currscopespace())
    {
    case programvar : programVarOffset = n; break;
    case functionlocal : functionLocalOffset = n; break;
    case formalarg : formalArgsOffset = n; break;
    
    default: assert(0);

    }
}

/* Returns the type of scope space you are in */
scopespace_t currscopespace(void){
    if(scopeSpaceCounter == 1){
        return programvar;
    }else if(scopeSpaceCounter % 2 == 0){
        return formalarg;
    }else{
        return functionlocal;
    }
}

/* Επιστρέφει το offset του current scope space*/
unsigned currscopeoffset(void){
    switch(currscopespace()){ // το κοιτάμε δεν βγάζει νόημα
        case programvar        : return programVarOffset;
        case functionlocal     : return functionLocalOffset;
        case formalarg         : return formalArgsOffset;
        default: assert(0);
    }
}

/* Αυξάνει το τρέχον offset του συγκεκριμένου scope space στο οποίο βρισκόμαστε*/
void inccurrscopeoffset(void){
    switch(currscopespace()){
        case programvar        : ++programVarOffset; break;
        case functionlocal     : ++functionLocalOffset; break;
        case formalarg         : ++formalArgsOffset; break;
        default: assert(0);
    }
}

void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

// Use this function to check correct use of
// of expression in arithmetic
int check_arith (expr* e, const char* context) {
   if ( e->type == constbool_e	|| 
        e->type == conststring_e	|| 
        e->type == nil_e	|| 
        e->type == newtable_e	||
        e->type == programfunc_e	||
        e->type == libraryfunc_e	||
        e->type == boolexpr_e ){

            printf("Illegal expr used in %s!", context);
            return 1;
        }
    return 0;
}

// Το offset θα πρέπει να αυξάνεται κάθε φορά που δηλώνεται μια μεταβλητή
void printQuads(void){
    /*FILE *file;
    file = fopen("quads.txt", "w"); // Open file for writing
    
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }*/
    int i;
    printf("\nquad#\topcode\t      result\t      arg1\t        arg2\t\t      label\n");
    printf("---------------------------------------------------------------------------------------\n");
    /*for(i=0;i<currQuad;i++){
        printf("%d ",quads[i].op); 
    }*/

    for(i=0;i<currQuad;i++){     
        printf("%d:\t",i);
        printOpcode(quads[i]);
        printf("\n");  
    }
    printf("---------------------------------------------------------------------------------------\n");
    // Close the file when done
    //fclose(file);
}

void printOpcode(quad quad){
    iopcode opcode = quad.op;
    char *result = NULL;
    if(quad.result!=NULL && quad.result->sym!=NULL){
        result = quad.result->sym->s_name;
    } 
    expr *arg1 = quad.arg1;
    expr *arg2 = quad.arg2;
    switch (opcode)
    {
    case assign:
        printf("%-17s","assign");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);      
        break;  
    case add:
        printf("%-17s","add");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case sub:
        printf("%-17s","sub");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case mul:
        printf("%-17s","mul");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case divv:
        printf("%-17s","div");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case mod:
        printf("%-17s","mod");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case uminus:
        printf("%-17s","uminus");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        break;
    case and:
        printf("%-17s","and");        
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        
        break;
    case or:
        printf("%-17s","or");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments(arg1);
        printArguments(arg2);        
        break;
    case not:
        printf("%-17s","not");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        if(arg1!=NULL)
        {
            printArguments(arg1);
        }
        if(arg2!=NULL)
        {
            printArguments(arg2);
        }
        break;
    case if_eq:
        printf("%-17s","if_eq");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break;
    case if_noteq:
        printf("%-17s","if_noteq");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break;
    case if_lesseq:
        printf("%-17s","if_lesseq");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break; 
    case if_greatereq:
        printf("%-17s","if_greatereq");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break;
    case if_less:
        printf("%-17s","if_less");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break;
    case if_greater:
        printf("%-17s","if_greater");
        printf("%-17s","");
        printArguments( arg1);
        printArguments(arg2);
        printf("%-17u",quad.label);
        break;
    case calll:
        printf("%-17s","call");
        printf("%-17s","");
        printArguments( arg1);
        break;
    case param:
        printf("%-17s","param");
        printf("%-17s","");
        printArguments( arg1);
        break;
    case ret:
        printf("%-17s","ret");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            if(quad.result->type == constbool_e){
                if(quad.result->boolConst == 1){
                    printf("%-17s","TRUE");
                }else{
                    printf("%-17s","FALSE");
                }
            }else if(quad.result->type == constnum_e){
                printf("%-17f",quad.result->numConst);
            }else{
                printf("%-17s","");
            }
        }
        printf("%-17s","");
        printf("%-17s","");
        break;
    case getretval:
        printf("%-17s","getretval");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        break;
    case funcstart:
        printf("%-17s","funcstart");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        if(quad.arg1!=NULL){
            printf("%-17s",quad.arg1->sym->s_name);
        }
        break;
    case funcend:
        printf("%-17s","funcend");
        printf("%-17s","");
        if(quad.arg1!=NULL){
            
            printf("%-17s",quad.arg1->sym->s_name);
        }
        break;
    case jump:
        printf("%-17s","jump");
        printf("%-17s","");
        printf("%-17s","");
        printf("%-17s","");
        printf("%-17u",quad.label);
        break;
    case tablecreate:
        printf("%-17s","tablecreate");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printf("%-17s","");
        printf("%-17s","");
        break;
    case tablegetelem:
        printf("%-17s","tablegetelem");
        if(result!=NULL){
            printf("%-17s",result);
        }else{
            printf("%-17s","");
        }
        printArguments( arg1);
        printArguments(arg2);
        break;
    case tablesetelem:
        printf("%-17s","tablesetelem");
        if(result!=NULL){
            printf("%-17s",result);

        }else{
            if(quad.result->type == constnum_e){
                printf("%-17f",quad.result->numConst);
            }else{
                printf("%-17s","");
            }
        }
        printArguments( arg1);
        printArguments( arg2);
        break;
    default:
        printf("WRONG OPCODE GIVEN IN QUAD !!!\n");
        break;
    }
    return;
}

void printArguments(expr *expr){
    expr_t type = expr->type;
    if(expr == NULL){
        return;
    }

    if(type == constbool_e){
        if(expr->boolConst == 0){
            printf("%-17s","\"FALSE\"");
        }else{
            printf("%-17s","\"TRUE\"");
        }
    }else if(type == constnum_e){
        printf("%-17f",expr->numConst);
    }else if(type == conststring_e){
        printf("\"%s\"",expr->strConst);
        printf("%-12s","");
    }else if(type == nil_e){
        printf("%-17s","NIL");
    }else{      /* if(type == var_e || type == boolexpr_e || type == arithexpr_e){*/
        printf("%-17s",expr->sym->s_name);
    }
}

call* new_call(struct expr* elist,unsigned char method,char* name){
    call* new = (call*)malloc(sizeof(struct call));
    if(!new){
        printf("\033[31m Error in memory allocation!\n\033[0m");
        return NULL;
    }
    new->elist = elist;
    new->method = method;
    new->name = name;

    return new;
}

/* Createa new tableitem expression lvalue["id"] or lvalue.id */
expr* member_item(expr* lv, char* name){
    
    lv = emit_iftableitem(lv, 0, 0);    // set scope and line as 0 

    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

struct expr* reverseElist(struct expr* start){
    struct expr *prev, *next, *curr;
    prev = NULL;
    curr = start;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } 
    start = prev;
    return start;
}

struct tablepair* reverseIndexed(struct tablepair* start){
    struct tablepair *prev, *next, *curr;
    prev = NULL;
    curr = start;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        
    } 

    start = prev;
    return start;
}

expr* get_last( expr* first){
    expr* last;
    last = first;

    while( last->next != NULL){
        last = last->next;
    }
    return last;
}

struct tablepair* make_pair(expr* expr1, expr* expr2){
    struct tablepair* pair = (struct tablepair*)malloc(sizeof(struct tablepair));
    if(!pair){
        printf("Error in memory allocation\n");
    }
    
    pair->key = expr1;
    pair->value = expr2;
    pair->next = NULL;
    return pair;
}

/*
*   jump1 for truelist
*   jump2 for falselist
*/
expr* createBoolexpr(expr* expr1, int jump1, int jump2, int scope, int line){
    expr* boolexpr;
    if(nextQuad() == total){
        expand();
    }
    if ( expr1->type == boolexpr_e){
        return expr1;
    }

    boolexpr = newexpr(boolexpr_e);
    boolexpr->sym = newtemp(scope, line);
    boolexpr->truelist = newlist(jump1);
    boolexpr->falselist = newlist(jump2);
    emit(if_eq,expr1,newexpr_constbool(1),NULL,0,line);
    emit(jump, NULL,NULL,NULL,0,line);

    return boolexpr;

}

void shortCircuitEval(expr* expr, int line){

    if(expr->type == boolexpr_e){

        patchlist(expr->truelist, nextQuad());
        emit(assign, newexpr_constbool(1), NULL, expr, 0, line);
        
        /* +2 label in order to jump after the truelist assignment*/
        emit(jump, NULL, NULL, NULL, nextQuad() + 2, line); 

        
        patchlist(expr->falselist, nextQuad());
        emit(assign, newexpr_constbool(0), NULL, expr, 0, line);
    }
}

/**
 * 
 * 
 * ******** PHASE 4-5 **********
 * 
 * 
*/

/* pinakes sta8erwn timwn kai synartisewn */
unsigned consts_newstring(char *s){
    unsigned index;
    index = currString;
    if ( index == totalStrings) expandStrings();
    strings[index++] = strdup(s);
    return index;
}

void expandStrings(void){
    assert(totalStrings==currString);
    char** s = (char**)malloc(NEW_STRING_SIZE);
    if(strings){
        memcpy(s,strings,CURR_STRING_SIZE);
        free(strings);
    }
    strings = s;
    totalStrings += EXPAND_SIZE;
}

unsigned consts_newnumber(double num){
    unsigned index;
    index = currNumber;
    if ( index == totalNumbers) expandNums();
    numbers[index++] = num;
    return index;
}

void expandNums(void){
    assert(totalNumbers==currNumber);
    double* n = (double*)malloc(NEW_NUM_SIZE);
    if(numbers){
        memcpy(n,numbers,CURR_NUM_SIZE);
        free(numbers);
    }
    numbers = n;
    totalNumbers += EXPAND_SIZE;
}

void generateInstr(void){
    unsigned total = total;
    for(unsigned i =0; i<total; i++){
        (*generators[quads[i].op])(quads+i);
    }
}

unsigned libfuncs_newused(char* s){
    unsigned index;
    index = currLib;
    if ( index == totalLibs) expandLib();
    libraryFuncs[index++] = s;
    return index;
}

void expandLib(void){
    assert(totalLibs==currLib);
    char** l = (char**)malloc(NEW_LIBFUNCS_SIZE);
    if(libraryFuncs){
        memcpy(l,libraryFuncs,CURR_LIBFUNCS_SIZE);
        free(libraryFuncs);
    }
    libraryFuncs = l;
    totalLibs += EXPAND_SIZE;
}

unsigned userfuncs_newfunc(SymbolTableEntry* sym){
    unsigned index;
    index = currUserFuncs;

    if(index == totalUserFuncs) expandUserFuncs();
    userFuncs[index].address = sym->value.funcVal->iaddress;
    userFuncs[index].localsize= sym->value.funcVal->totalLocals;
    userFuncs[index].id = sym->s_name;
    index++;
    return index;
}

void expandUserFuncs(void){
    assert(totalUserFuncs==currUserFuncs);
    func* f = (func*)malloc(NEW_USERFUNCS_SIZE);
    if(userFuncs){
        memcpy(f,userFuncs,CURR_USERFUNCS_SIZE);
        free(userFuncs);
    }
    userFuncs = f;
    totalUserFuncs += EXPAND_SIZE;
}

void make_operand(expr* e, vmarg* arg){
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e: {
            assert(e->sym);
            arg->val = e->sym->offset;
            switch (e->sym->space){
                case programvar: arg->type = global_a; break;
                case functionlocal: arg->type = local_a; break; 
                case formalarg: arg->type = formal_a; break;
                default: assert(0);
            }
            break;
        }
        case constbool_e:{
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }
        case conststring_e:{
            arg->val = e->strConst;
            arg->type = string_a;
            break;
        }
        case constnum_e:{
            arg->val = e->numConst;
            arg->type = number_a;
            break;
        }
        case nil_e: arg->type = nil_a; break;
        case programfunc_e:{
            arg->type = userfunc_a;
            arg->val = e->sym->taddress;
            /* or */
            // arg->val = userfuncs_newfunc(e->sym);
            break;
        }
        case libraryfunc_e:{
            // arg->val = libfuncs_newused(e->sym->name);
            arg->type = libfunc_a;
            break;
        }
        default: assert(0);
    }
}

/* Helper functions to produce common arguments for generated instructions, like 1,0,
"true", "false" and function return values */

void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}
void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}

/**
 * Adds elements(jumps) at the end of a list of incomplete jump elements
*/
void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
    incomplete_jump *curr = ij_head, *prev;

    while( curr != NULL){
        prev = curr;
        curr = curr->next;
    }

    ij_total++;
    incomplete_jump* new_jump = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    new_jump->instrNo = instrNo;
    new_jump->iaddress = iaddress;
    new_jump = NULL;

    if( prev == NULL){      // empty list 
        ij_head = new_jump;
    }else{
        prev->next = new_jump;  // add new jump at the end of the list 
    }

}

void patch_incomplete_jumps(void){
    incomplete_jump* curr;
    vmarg result;
    result.type = label_a;
    while(curr){
        if (curr->iaddress == nextQuad()){
            result.val = currInstruction;
            instructions[curr->instrNo].result = result;
        }else{
            result.val = quads[curr->iaddress].taddress;
        }
    }
}

unsigned nextinstructionlabel(void){
    return currInstruction;
}

void expandInstructions(void){
    assert(totalInstructions ==currInstruction);
    instruction * i = (instruction *)malloc(NEW_INSTR_SIZE);
    if(instructions){
        memcpy(i,instructions,CURR_INSTR_SIZE);
        free(instructions);
    }
    instructions = i;
    totalInstructions += EXPAND_SIZE;
}

void emitInstruction(instruction instruction){
    if(currInstruction == totalInstructions) expand();

    struct instruction* i    = instructions + currInstruction++;
    i->opcode   = instruction.opcode;
    i->arg1     = instruction.arg1;
    i->arg2     = instruction.arg2;
    i->result   = instruction.result;
    i->srcLine  = instruction.srcLine;
}
void reset_operand(vmarg *arg){
    arg->val = 0;
}
unsigned currprocessedquad(){

}
void generate(vmopcode op, quad* q){
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    make_operand(q->arg1,&t.arg1);
    make_operand(q->arg2,&t.arg2);
    make_operand(q->result,&t.result);
    q->taddress = nextinstructionlabel();
    emitInstruction(t);

}
void generate_relational(vmopcode op, quad* q){
    instruction t;
    t.opcode = op;
    make_operand(q->arg1,&t.arg1);
    make_operand(q->arg2,&t.arg2);

    t.result.type = label_a;
    t.srcLine = q->line;

    if( q->label < currprocessedquad()){
        t.result.val = quads[q->label].taddress;
    }else{
        add_incomplete_jump(nextinstructionlabel(), q->label);
    }
    q->taddress = nextinstructionlabel();
    emitInstruction(t);
}
void generate_ADD(quad *q)              { generate(and_vm, q); }
void generate_SUB(quad *q)              { generate(sub_vm, q); }
void generate_MUL(quad *q)              { generate(mul_vm, q); }
void generate_DIV(quad *q)              { generate(div_vm, q); }
void generate_MOD(quad *q)              { generate(mod_vm, q); }
void generate_NEWTABLE(quad *q)         { generate(newtable_vm, q); }
void generate_TABLEGETELEM(quad *q)     { generate(tablegetelem_vm, q); }
void generate_TABLESETELEM(quad *q)     { generate(tablesetelem_vm, q); }
void generate_ASSIGN(quad *q)           { generate(assign_vm, q); }
void generate_NOP()                     { instruction t; t.opcode = nop_vm; emitInstruction(t);}
void generate_JUMP(quad *q)             { generate_relational(jump_vm, q); }
void generate_IF_EQ(quad *q)            { generate_relational(jeq_vm, q); }
void generate_IF_NOTEQ(quad *q)         { generate_relational(jne_vm, q); }
void generate_IF_GREATER(quad *q)       { generate_relational(jgt_vm, q); }
void generate_IF_GREATEREQ(quad *q)     { generate_relational(jge_vm, q); }
void generate_IF_LESS(quad *q)          { generate_relational(jlt_vm, q); }
void generate_IF_LESSEQ(quad *q)        { generate_relational(jle_vm, q); }
void generate_NOT(quad *q)              {
    instruction t;
    q->taddress = nextinstructionlabel();
    t.srcLine = q->line;

    t.opcode = jeq_vm;
    make_operand(q->arg1,&t.arg1);
    make_booloperand(&t.arg2, 0);       // sti dialeksi leei false
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 3;
    
    emitInstruction(t);

    t.opcode = assign_vm;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);

    t.opcode = jump_vm;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emitInstruction(t);

    t.opcode = assign_vm;
    make_booloperand(&t.arg1, 1);       // sti dialeksi leei true
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);

}
void generate_OR(quad *q)               {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.srcLine = q->line;

    t.opcode = jeq_vm;
	make_operand(q->arg1, &t.arg1);
	make_booloperand(&t.arg2, 1);       // sti dialeksi leei true
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel() + 4;
	emitInstruction(t);

	make_operand(q->arg2, &t.arg1);
	t.result.val  = nextinstructionlabel() + 3;
	emitInstruction(t);

    t.opcode = assign_vm;
	make_booloperand(&t.arg1, 0);       // false
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emitInstruction(t);

	t.opcode = jump_vm;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel() + 2;
	emitInstruction(t);

	t.opcode = assign_vm;
	make_booloperand(&t.arg1, 1);       // true
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emitInstruction(t);

}
void generate_AND(quad *q)              {}
void generate_PARAM(quad *q)            {

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_vm;
    make_operand(q->arg1, &t.arg1);
    t.srcLine = q->line;
    emitInstruction(t);

}
void generate_CALL(quad *q)             {

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_vm;
    make_operand(q->arg1,&t.arg1);
    t.srcLine = q->line;
    emitInstruction(t);

}

void generate_GETRETVAL(quad *q)        {

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_vm;
    make_operand(q->result,&t.result);
    make_retvaloperand(&t.arg1);
    t.srcLine = q->line;
    emitInstruction(t);
}

void generate_FUNCSTART(quad *q)        {
    SymbolTableEntry* f = q->result->sym;
    instruction t;

    f->value.funcVal->iaddress = nextinstructionlabel();
    q->taddress = nextinstructionlabel();

    // userfunctions.add(f.id,f.address,f.totallocals);
    // push(funstack,f)

    t.opcode = funcstart_vm;
    t.srcLine = q->line;
    make_operand(q->result, &t.result);
    emitInstruction(t);

}

void generate_RETURN(quad *q)           {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.srcLine = q->line;

    t.opcode = assign_vm;
    make_retvaloperand(&t.result);
    make_operand(q->arg1, &t.arg1);
    emitInstruction(t);

    // stackFrame* f = topStack(funcstack);
    // append(f.returnlist,nextinstructionlabel());

    t.opcode = jump_vm;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    emitInstruction(t);
}

void generate_FUNCEND(quad *q)          {
    // f = pop(funcstack);
    // backpatch(f.returnlist, nextinstructionlabel());

    q->taddress = nextinstructionlabel();
    instruction t;

    // mallon xreiazetai kapoies allages gia to result 
    t.opcode = funcend_vm;
    make_operand(q->result,&t.result);
    t.srcLine = q->line;
    emitInstruction(t);

}

void generate_UMINUS(quad *q)           {
    
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = mul_vm;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.arg1);
    make_numberoperand(&t.arg2, -1);     // pollaplasiasmos epi -1
    make_operand(q->result, &t.result);

    emitInstruction(t);
}

void createPrintFile(FILE* filename){

    FILE* stream = fopen(filename, "w+"); // gia na grapsw binary file thelei wb

    if(stream == NULL){
        printf("\033[131mError opening file\033[0m\n");
        exit(1);
    }
    fprintf(stream, "---------------- VM ----------------\n");

    fprintf(stream, "---------------- Instructions: %u ----------------\n", currInstruction);
    for(int i=0; i < currInstruction; i++){
        fprintf(stream, "%d arg1: %d %u arg2: %d %u result: %d %u", instructions[i].opcode, instructions[i].arg1.type, instructions[i].arg1.val, instructions[i].arg2.type,
        instructions[i].arg2.val, instructions[i].result.type, instructions[i].result.val);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");

    fprintf(stream, "---------------- Strings: %u ----------------\n", currString);
    for(int i=0; i < currString; i++){
        fprintf(stream, "s", strings[i]);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");

    fprintf(stream, "---------------- Numbers: %u ----------------\n", currNumber);
    for(int i=0; i < currNumber; i++){
        fprintf(stream, "%f", numbers[i]);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");

    fprintf(stream, "---------------- User Functions: %u ----------------\n", currNumber);
    for(int i=0; i < currUserFuncs; i++){
        fprintf(stream, "%u %u %s", userFuncs[i].address, userFuncs[i].localsize, userFuncs[i].id);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");

    fprintf(stream, "---------------- Library Functions: %u ----------------\n", currNumber);
    for(int i=0; i < currUserFuncs; i++){
        fprintf(stream, "%s", libraryFuncs[i]);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
    fclose(stream);
}