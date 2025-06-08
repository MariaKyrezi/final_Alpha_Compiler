#include "phase4.h"

/**
 * 
 * 
 * ******** PHASE 4-5 **********
 * 
 * 
*/

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP
};

instruction *instructions = (instruction*)0; //previously NULL
unsigned currInstruction = 0;
unsigned totalInstructions = 0;

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned         ij_total = 0;

char **strings = (char**)0; //previously NULL
unsigned currString = 0;
unsigned totalStrings = 0;

double* numbers = (double*)0; //previously 0
unsigned currNumber = 0;
unsigned totalNumbers = 0;

char** libraryFuncs = (char**)0; //previously NULL
unsigned currLib = 0;
unsigned totalLibs = 0;

userfunc* userFuncs = (userfunc*)0; //previously NULL
unsigned currUserFuncs = 0;
unsigned totalUserFuncs = 0;

struct funcstack* funchead = (struct funcstack*) 0;

int currprocessquad = 0;

/**
 * String array - adds strings to the array
 */
unsigned consts_newstring(char *s){
    unsigned index;
    //index = currString;
    if ( currString == totalStrings) expandStrings();
    strings[currString++] = strdup(s);
    return currString-1;
}

/** 
 * Expands string array
 */
void expandStrings(){
    assert(totalStrings==currString);
    char** s = (char**)malloc(NEW_STRING_SIZE);
    if(strings){
        memcpy(s,strings,CURR_STRING_SIZE);
        free(strings);
    }
    strings = s;
    totalStrings += EXPAND_SIZE;
}

/**
 * Number array - adds numbers to the array 
 */
unsigned consts_newnumber(double num){
    unsigned index;
    //index = currNumber;
    if ( currNumber == totalNumbers) expandNums();
    numbers[currNumber++] = num;
    return currNumber-1;
}

/**
 * Expands numbers array
 */
void expandNums(){
    assert(totalNumbers==currNumber);
    double* n = (double*)malloc(NEW_NUM_SIZE);
    if(numbers){
        memcpy(n,numbers,CURR_NUM_SIZE);
        free(numbers);
    }
    numbers = n;
    totalNumbers += EXPAND_SIZE;
}

/**
 * Iterates over all generated quads
 * For each quad calls the appropriate code generator to turn it 
 * into target code
 * Then it patches any incomplete jumps
 */
void generateInstr(void){
    
    printf("Current Quad: %d\n",nextQuad() );
    for(unsigned i = 0; i < nextQuad() ; i++){
        printf("i: %d\n",i);
        printf("op: %d\n", quads[i].op);
        (*generators[quads[i].op])(quads+i);
    }
    patch_incomplete_jumps();
    printf("Phase 4.2\n");
}

/**
 * Library Function Array - adds lib func elements to the array 
 */
unsigned libfuncs_newused(char* s){
    printf("went inside libfuncs\n");
    unsigned index;
    //index = currLib;
    if ( currLib == totalLibs) expandLib();
    libraryFuncs[currLib++] = s;
    return currLib-1;
}

/**
 * Expands lib func array
 */
void expandLib(){
    assert(totalLibs==currLib);
    char** l = (char**)malloc(NEW_LIBFUNCS_SIZE);
    if(libraryFuncs){
        memcpy(l,libraryFuncs,CURR_LIBFUNCS_SIZE);
        free(libraryFuncs);
    }
    libraryFuncs = l;
    totalLibs += EXPAND_SIZE;
}

/**
 * User Function Array - Adds user functions to the array
 */
unsigned userfuncs_newfunc(SymbolTableEntry* sym){
    //unsigned index;
    //index = currUserFuncs;

    if(currUserFuncs == totalUserFuncs) expandUserFuncs();
    userFuncs[currUserFuncs].address = sym->value.funcVal->iaddress;
    userFuncs[currUserFuncs].localsize= sym->value.funcVal->totalLocals;
    userFuncs[currUserFuncs].id = sym->s_name;
    currUserFuncs++;
    return currUserFuncs-1;
}

/**
 * Expands user function array
 */
void expandUserFuncs(){
    assert(totalUserFuncs==currUserFuncs);
    userfunc* f = (userfunc*)malloc(NEW_USERFUNCS_SIZE);
    if(userFuncs){
        memcpy(f,userFuncs,CURR_USERFUNCS_SIZE);
        free(userFuncs);
    }
    userFuncs = f;
    totalUserFuncs += EXPAND_SIZE;
}

/**
 * Turns expr operand to vmarg operand
 */
void make_operand(expr* e, vmarg* arg){
    if (!e) {
        fprintf(stderr, "make_operand error: expr pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }
    printf("make_operand called with expr type=%d\n", e->type);
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case assignexpr_e:
        case newtable_e: {
	    printf("expr with symbol: %p\n", (void*)e->sym);
            assert(e->sym);
            arg->val = e->sym->offset;
	    printf("symbol offset: %d\n", e->sym->offset);
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
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        case constnum_e:{
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }
        case nil_e: arg->type = nil_a; break;
        case programfunc_e:{
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym); //e->sym->taddress;
            break;
        }
        case libraryfunc_e:{
	    if (!e->sym || !e->sym->s_name) {
                fprintf(stderr, "make_operand error: NULL sym or sym->s_name for libraryfunc_e\n");
                exit(EXIT_FAILURE);
            }
	    arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->s_name);
            
            break;
        }
        default: 
	    fprintf(stderr, "make_operand: unknown expr type %d\n", e->type);
            assert(0);

    }
}

/**
 * Helper functions to produce common arguments for generated instructions, like 1,0,
 * "true", "false" and function return values 
*/

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
    incomplete_jump *curr = ij_head, *prev = NULL;

    while( curr != NULL){
        prev = curr;
        curr = curr->next;
    }

    ij_total++;
    incomplete_jump* new_jump = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    new_jump->instrNo = instrNo;
    new_jump->iaddress = iaddress;
    new_jump->next = NULL; 

    if( prev == NULL){      // empty list 
        ij_head = new_jump;
    }else{
        prev->next = new_jump;  // add new jump at the end of the list 
    }
}

/**
 * Patches any incomplete jumps that exist in the incomplete_jump list
 */
void patch_incomplete_jumps(void){
    incomplete_jump* curr = ij_head;

    vmarg result;
    result.type = label_a;

    while(curr){
        if (curr->iaddress == nextQuad()){ 
            result.val = currInstruction;
            instructions[curr->instrNo].result = result;
        }else{
            result.val = quads[curr->iaddress].taddress;
            instructions[curr->instrNo].result = result;
        }
        curr = curr->next;
    }
}

/**
 * Returns current instruction
 */
unsigned nextinstructionlabel(void){
    return currInstruction;
}

/**
 * Expand the instructions array
 */
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

/**
 * Create a new instruction record
 */
void emitInstruction(instruction instruction){
    if(currInstruction == totalInstructions) expandInstructions();

    struct instruction* i    = instructions + currInstruction++;
    i->opcode   = instruction.opcode;
    i->arg1     = instruction.arg1;
    i->arg2     = instruction.arg2;
    i->result   = instruction.result;
    i->srcLine  = instruction.srcLine;
}

void generate(vmopcode op, quad* q){
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    if (q->arg1 != NULL) {
        make_operand(q->arg1, &t.arg1);
    } else {
        printf("Arg1 NULL\n");
    }

    if (q->arg2 != NULL) {
        make_operand(q->arg2, &t.arg2);
    } else {
        printf("Arg2 NULL\n");
    }

    if (q->result != NULL) {
        printf("result type: %d\n", q->result->type);
        make_operand(q->result, &t.result);
    } else {
        printf("Result NULL\n");
    }
    q->taddress = nextinstructionlabel();
    emitInstruction(t);

}

void generate_ADD(quad *q)              { generate(add_vm, q); }
void generate_SUB(quad *q)              { generate(sub_vm, q); }
void generate_MUL(quad *q)              { generate(mul_vm, q); }
void generate_DIV(quad *q)              { generate(div_vm, q); }
void generate_MOD(quad *q)              { generate(mod_vm, q); }
void generate_NEWTABLE(quad *q)         { generate(newtable_vm, q); }
void generate_TABLEGETELEM(quad *q)     { generate(tablegetelem_vm, q); }
void generate_TABLESETELEM(quad *q)     { generate(tablesetelem_vm, q); }
void generate_ASSIGN(quad *q)           { generate(assign_vm, q); }
void generate_NOP()                     { instruction t; t.opcode = nop_vm; emitInstruction(t);}

/**
 * Returns the last quad that thas been processed
 */
unsigned currprocessedquad(){
    return currprocessquad;
}

/**
 * Generates instructions for relational operations (==, <, !=, etc.)
 */
void generate_relational(vmopcode op, quad* q){

    instruction t;
    t.opcode = op;
    printf("Generate Relational\n");
    if (q->arg1 != NULL) {
        make_operand(q->arg1, &t.arg1);
        printf("Make operand1\n");
    } else {
        printf("Warning: arg1 is NULL at quad %d\n", q->line); // or q->line

    }

    if (q->arg2 != NULL) {
        make_operand(q->arg2, &t.arg2);
        printf("Make operand2\n");
    } else {
        printf("Warning: arg2 is NULL at quad %d\n", q->line);

    }
    
    t.result.type = label_a;
    t.srcLine = q->line;

    if( q->label < currprocessedquad()){ // the jump target label has already been processed 
        t.result.val = quads[q->label].taddress;
    }else{                                // forward jump -> we can't fill the address
        add_incomplete_jump(nextinstructionlabel(), q->label);
    }
    q->taddress = nextinstructionlabel();
    emitInstruction(t);
}

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

void reset_operand(vmarg *arg){
    arg->val = 0;
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

void generate_AND(quad *q)              {return;}

void generate_PARAM(quad *q)            {
    printf("generate_PARAM called with q->arg1=%p\n", (void*)q->arg1);
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_vm;
    make_operand(q->arg1, &t.arg1);
    t.srcLine = q->line;
    emitInstruction(t);

}

/*void generate_CALL(quad *q)             {
    if (q == NULL) {
        fprintf(stderr, "generate_CALL: q is NULL!\n");
        exit(EXIT_FAILURE);
    }
    printf("generate_CALL called, q=%p\n", (void*)q);

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_vm;
    if(!q->arg1) {
        fprintf(stderr, "generate_CALL error: q->arg1 is NULL\n");
        exit(EXIT_FAILURE);
    }
    printf("generate_CALL: q->arg1->type = %s\n", q->arg1->type);
    make_operand(q->arg1,&t.arg1);
    t.srcLine = q->line;
    emitInstruction(t);

}*/

void generate_CALL(quad *q) {
    printf("generate_CALL called, q=%p\n", q);

    q->taddress = nextinstructionlabel();
    printf("After setting taddress\n");

    instruction t;
    printf("After declaring t\n");

    t.opcode = call_vm;
    printf("After setting opcode\n");

    make_operand(q->arg1,&t.arg1);
    printf("After make_operand\n");

    t.srcLine = q->line;
    printf("After setting srcLine\n");

    emitInstruction(t);
    printf("After emitInstruction\n");
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

    f->value.funcVal->iaddress = nextinstructionlabel(); // iaddress or taddress
    q->taddress = nextinstructionlabel();

    struct userfunc* userfunc = (struct userfunc*)malloc(sizeof(struct userfunc));
    userfunc->id = NULL;
    userfunc->id = malloc(sizeof(char)*(strlen(f->s_name)+1));
    userfunc->id = strdup(f->s_name);
    userfunc->address = f->taddress;
    userfunc->localsize = f->value.funcVal->totalLocals;
    funchead = func_push(f);

    t.opcode = funcstart_vm;
    t.opcode = q->line;
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

    struct SymbolTableEntry *f = malloc(sizeof(struct SymbolTableEntry*));
    f = func_top();
    f->value.funcVal->retList = append(f->value.funcVal->retList,nextinstructionlabel());

    t.opcode = jump_vm;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    emitInstruction(t);
}

void generate_FUNCEND(quad *q)          {
    struct SymbolTableEntry* f = func_pop();
    backpatch_Instruction(f->value.funcVal->retList, nextinstructionlabel());

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

void createPrintFile(char* filename){

    unsigned magicnumber = 1234567890;
    FILE* stream = fopen(filename, "wb"); // write binary 
    FILE* fp = fopen("output.txt", "w");
    size_t size;

    if(stream == NULL){
        printf("\033[131mError opening file\033[0m\n");
        exit(1);
    }
    
    fwrite(&magicnumber, sizeof(magicnumber),1, stream);

    // numbers 
    fwrite(&currNumber, sizeof(currNumber), 1, stream);
    for(int i=0; i < currNumber; i++){
        fwrite(&numbers[i], sizeof(numbers[i]), 1, stream);
    }
    
    // strings 
    fwrite(&currString, sizeof(currString), 1, stream);
    for(int i=0; i < currString; i++){
        size = strlen(strings[i]) + 1; // +1 for null terminator
        fwrite(&size, sizeof(size),1 , stream);
        fwrite(&strings[i], sizeof(strings[i]), 1, stream);
    }

    // user functions
    fwrite(&currUserFuncs, sizeof(currUserFuncs), 1, stream);
    for(int i=0; i < currUserFuncs; i++){
        size = strlen(userFuncs[i].id);
        fwrite(&size, sizeof(size), 1, stream);
        fwrite(&userFuncs[i].id, sizeof(userFuncs[i].id), 1, stream);
        fwrite(&userFuncs[i].address, sizeof(userFuncs[i].address), 1, stream);
        fwrite(&userFuncs[i].localsize, sizeof(userFuncs[i].localsize), 1, stream);
    }

    
    // library functions
    fwrite(&currLib, sizeof(currLib), 1, stream);
    for(int i=0; i < currLib; i++){
        size = strlen(libraryFuncs[i])+1;
        fwrite(&size, sizeof(size), 1, stream);
        fwrite(&libraryFuncs[i], sizeof(libraryFuncs[i]), 1, stream);

    }

    // instructions 
    fwrite(&currInstruction, sizeof(currInstruction), 1, stream);
    for(int i=0; i < currInstruction; i++){
        
        fwrite(&instructions[i].opcode, sizeof(instructions[i].opcode), 1, stream);
        fwrite(&instructions[i].result, sizeof(instructions[i].result), 1, stream);
        fwrite(&instructions[i].arg1.type, sizeof(instructions[i].arg1.type), 1,stream);
        fwrite(&instructions[i].arg1.val, sizeof(instructions[i].arg1.val),1, stream);
        fwrite(&instructions[i].arg2.type, sizeof(instructions[i].arg2.type), 1,stream);
        fwrite(&instructions[i].arg2.val, sizeof(instructions[i].arg2.val),1, stream);
               
    }

    txt_print_instructions(fp);
    fclose(stream);
    fclose(fp);
}

void file_read_Arrays(const char *filename) {
    unsigned magicnumber;
    unsigned currNumber;
    FILE *stream = fopen(filename, "rb"); // read binary

    if (stream == NULL) {
        printf("\033[131mError opening file\033[0m\n");
        exit(1);
    }

    // Read and print the magicnumber
    fread(&magicnumber, sizeof(magicnumber), 1, stream);
    printf("magicnumber: %u\n", magicnumber);

    // Read and print the currNumber
    fread(&currNumber, sizeof(currNumber), 1, stream);
    printf("currNumber: %u\n", currNumber);

    // Allocate memory for the numbers array
    double *numbers = (double *)malloc(currNumber * sizeof(double));
    if (numbers == NULL) {
        printf("Memory allocation error\n");
        fclose(stream);
        exit(1);
    }

    // Read and print each number in the numbers array
    for (int i = 0; i < currNumber; i++) {
        fread(&numbers[i], sizeof(double), 1, stream);
        printf("number[%d]: %lf\n", i, numbers[i]);
    }

    // Clean up
    free(numbers);
    fclose(stream);
}

void backpatch_Instruction(returnList* ret, int label){
    struct returnList* temp = ret;
    while(temp!=NULL){
        if(temp->label >= 0){
            instructions[temp->label].result.val = label;
            instructions[temp->label].result.type = label_a;
        }
        temp = temp->next;
    }
}

struct returnList* append(returnList* ret, int label){
    returnList* newnode = (struct returnList*)malloc(sizeof(struct returnList));
    newnode->label = label;
    newnode->next = ret;
    return newnode;
}

struct SymbolTableEntry *func_pop(){
    struct SymbolTableEntry *temp;
    if (func_isEmpty(funchead))
        return NULL;
    struct funcstack* tmp = funchead;
    struct SymbolTableEntry* sym = tmp->entry;
    funchead = funchead->next;
    free(tmp);
    return sym;
}

struct funcstack *func_push(SymbolTableEntry *entry){
    struct funcstack* newEntry = (struct funcstack*)malloc(sizeof(struct funcstack));
    newEntry->entry = entry;
    newEntry->next = funchead;
    funchead = newEntry;
    return funchead;
}

int func_isEmpty(struct funcstack *entry){
    if(entry != NULL){
        return 1;
    }
    return 0;
}

struct SymbolTableEntry *func_top(){
    return funchead->entry;
}



/*void file_print_target_arg(FILE *fp, struct vmarg* arg){
    fwrite(&arg->type,sizeof(unsigned), 1, fp);
    fwrite(&arg->val,sizeof(int), 1, fp);
}*/

/*void file_print_Arrays(FILE *fp){
    int i;
    int size;
    fwrite(&currNumber, sizeof(unsigned), 1, fp);
    for(i=0; i < currNumber; i++){
        fwrite(&numbers[i], sizeof(double), 1, fp);
    }
    fwrite(&currString, sizeof(unsigned), 1, fp);
    for(i=0; i < currString; i++){
        size = strlen(strings[i])*sizeof(char) + 1;
        fwrite(&size, sizeof(unsigned), 1, fp);
        fwrite(strings[i], size* sizeof(char), 1, fp);
    }
    fwrite(&currLib, sizeof(unsigned), 1, fp);
    for(i=0; i < currLib; i++){
        size = strlen(libraryFuncs[i])*sizeof(char) + 1;
        fwrite(&size, sizeof(unsigned), 1, fp);
        fwrite(libraryFuncs[i], size*sizeof(char), 1, fp);
    }
    fwrite(&currUserFuncs, sizeof(unsigned), 1, fp);
    for(i=0; i < currUserFuncs; i++){
        size = strlen(userFuncs[i].id) + 1;
        fwrite(&size, sizeof(unsigned), 1, fp);
        fwrite(userFuncs[i].id, size*sizeof(char), 1, fp);
        fwrite(&userFuncs[i].address, sizeof(unsigned), 1, fp);
        fwrite(&userFuncs[i].localsize, sizeof(unsigned), 1, fp);
    }
}*/

/*void txt_print_instructions(FILE *fp){
    txt_print_Arrays(fp);
    fprintf(fp,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TARGET CODE~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp,"Ins\topcode         result\t\targ1\t\targ2\n");
    int i;
    printf("Number of instructions %d\n", currInstruction);
    for(i=0; i<currInstruction; i++){
        fwrite(&instructions[i].opcode, sizeof(instructions[i].opcode), 1, fp);
        fwrite(&instructions[i].result, sizeof(instructions[i].result), 1, fp);
        fwrite(&instructions[i].arg1.type, sizeof(instructions[i].arg1.type), 1,fp);
        fwrite(&instructions[i].arg1.val, sizeof(instructions[i].arg1.val),1, fp);
        fwrite(&instructions[i].arg2.type, sizeof(instructions[i].arg2.type), 1,fp);
        fwrite(&instructions[i].arg2.val, sizeof(instructions[i].arg2.val),1, fp);
    }
}*/

void txt_print_instructions(FILE *fp){
    txt_print_Arrays(fp);
    fprintf(fp,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TARGET CODE~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp,"Ins\topcode         result\t\targ1\t\targ2\n");
    int i;
    printf("Number of instructions %d\n", currInstruction);
    for(i=0; i<currInstruction; i++){
        fprintf(fp, "%-6d %-14d %-16d %-16d %-16d\n",
            i,
            instructions[i].opcode,
            instructions[i].result.val,
            instructions[i].arg1.val,
            instructions[i].arg2.val
        );
    }
}


/*void txt_print_instruction(FILE *fp, int i){
    struct instruction t = instructions[i];
    fprintf(fp,"%d:\t", i); 
    fprintf(fp,"%-15s ",t.opcode);
    switch(t.opcode){
        case assign_vm:
            file_print_target_arg(fp, t.result);
            file_print_target_arg(fp, t.arg1);
            break;
        case add_vm:
        case sub_vm:
        case mul_vm:
        case div_vm:
        case mod_vm:
        case jeq_vm:
        case jne_vm:
        case jle_vm:
        case jge_vm:
        case jlt_vm:
        case jgt_vm:
            file_print_target_arg(fp, t.result);
            file_print_target_arg(fp, t.arg1);
            file_print_target_arg(fp, t.arg2);
            break;
        case call_vm:
        case pusharg_vm:
        case funcstart_vm:
        case funcend_vm:
        case jump_vm:
        case newtable_vm:
            file_print_target_arg(fp, t.result);
            break;
        case tablegetelem_vm:
            file_print_target_arg(fp, t.result);
            file_print_target_arg(fp, t.arg1);
            file_print_target_arg(fp, t.arg2);
            break;
        case tablesetelem_vm:
            file_print_target_arg(fp, t.result);
            file_print_target_arg(fp, t.arg1);
            file_print_target_arg(fp, t.arg2);
            break;
        case nop_vm:
            break;
        default:
            assert(0);
    }
    fprintf(fp,"\n");
}*/

void txt_print_Arrays(FILE *fp){
    int i;
    fprintf(fp,"\ntotal number constants: %d\n",currNumber);
    fprintf(fp,"NUMBER CONSTANTS ARRAY\n");
    for(i=0; i<currNumber; i++){
        fprintf(fp,"%d: %lf\n", i, numbers[i]);
    }
    fprintf(fp,"\ntotal number strings: %d\n",currString);
    fprintf(fp,"STRING CONSTANTS ARRAY\n");
    for(i=0; i<currString; i++){
        fprintf(fp,"%d: \"%s\"\n", i, strings[i]);
    }
    fprintf(fp,"\ntotal library functions: %d\n",totalLibs);
    fprintf(fp,"LIBRARY FUNCTIONS\n");
    for(i=0; i<currLib; i++){
        fprintf(fp,"%d: %s\n", i, libraryFuncs[i]);
    }
    fprintf(fp,"\ntotal user functions: %d\n",currUserFuncs);
    fprintf(fp,"USER FUNCTIONS\n");
    fprintf(fp,"No\tid\taddr\tloc\n");
    for(i=0; i<currUserFuncs; i++){
        fprintf(fp,"%d: %s\t %d\t %d\n", i, userFuncs[i].id, userFuncs[i].address,userFuncs[i].localsize);
    }
}
