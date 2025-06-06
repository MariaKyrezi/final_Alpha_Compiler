#include "phase3.h"

/*
 * 
 * 
 * ************ PHASE 4-5 ***********
 * 
 * 
 * 
*/

// instruction array 
#define CURR_INSTR_SIZE (totalInstructions * sizeof(instruction))
#define NEW_INSTR_SIZE (EXPAND_SIZE * sizeof(instruction) + CURR_INSTR_SIZE)

// numbers array 
#define CURR_NUM_SIZE (totalNumbers * sizeof(double))
#define NEW_NUM_SIZE (EXPAND_SIZE * sizeof(double) + CURR_NUM_SIZE)

// string array 
#define CURR_STRING_SIZE (totalStrings * sizeof(char *))
#define NEW_STRING_SIZE (EXPAND_SIZE * sizeof(char *) + CURR_STRING_SIZE)

// library functions array 
#define CURR_LIBFUNCS_SIZE (totalLibs * sizeof(char *))
#define NEW_LIBFUNCS_SIZE (EXPAND_SIZE * sizeof(char *) + CURR_LIBFUNCS_SIZE)

// user functions array 
#define CURR_USERFUNCS_SIZE (totalUserFuncs * sizeof(userfunc))
#define NEW_USERFUNCS_SIZE (EXPAND_SIZE * sizeof(userfunc) + CURR_USERFUNCS_SIZE)

typedef void (*generator_func_t)(quad*);

void generateInstr(void);
void generate_ADD(quad *q);
void generate_SUB(quad *q);
void generate_MUL(quad *q);
void generate_DIV(quad *q);
void generate_MOD(quad *q);
void generate_NEWTABLE(quad *q);
void generate_TABLEGETELEM(quad *q);
void generate_TABLESETELEM(quad *q);
void generate_ASSIGN(quad *q);
void generate_NOP();
void generate_JUMP(quad *q);
void generate_IF_EQ(quad *q);
void generate_IF_NOTEQ(quad *q);
void generate_IF_GREATER(quad *q);
void generate_IF_GREATEREQ(quad *q);
void generate_IF_LESS(quad *q);
void generate_IF_LESSEQ(quad *q);
void generate_NOT(quad *q);
void generate_OR(quad *q);
void generate_PARAM(quad *q);
void generate_CALL(quad *q);
void generate_GETRETVAL(quad *q);
void generate_FUNCSTART(quad *q);
void generate_RETURN(quad *q);
void generate_FUNCEND(quad *q);
void generate_UMINUS(quad *q);
void generate_AND(quad *q);



typedef enum vmarg_t{
    global_a,
    local_a,
    formal_a,
    bool_a,
    string_a,
    number_a,
    userfunc_a,
    libfunc_a,
    nil_a,
    retval_a,
    label_a
}vmarg_t;

typedef struct vmarg{
    vmarg_t type;
    unsigned val;
}vmarg;

typedef enum vmopcode{
    assign_vm,
    add_vm,
    sub_vm,
    mul_vm,
    div_vm,
    mod_vm,
    uminus_vm,
    and_vm,
    or_vm,
    not_vm,
    jump_vm,
    jeq_vm,
    jne_vm,
    jle_vm,
    jge_vm,
    jlt_vm,
    jgt_vm,
    call_vm,
    ret_vm,
    funcstart_vm,
    funcend_vm,
    newtable_vm,
    tablegetelem_vm,
    tablesetelem_vm,
    pusharg_vm,
    nop_vm
}vmopcode;

typedef struct incomplete_jump{
    unsigned instrNo;               // jump instruction number 
    unsigned iaddress;              // i-code jump-target address
    struct incomplete_jump* next;   // trivial linked list
}incomplete_jump;

typedef struct instruction
{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;

} instruction;

typedef struct userfunc{
    char* id;
    unsigned address;
    unsigned localsize;
}userfunc;

typedef struct funcstack{
    struct SymbolTableEntry *entry;
    struct funcstack *next;
}funcstack;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps(void);

void make_operand(expr* e, vmarg* arg);
void make_numberoperand(vmarg* arg, double val);
void make_booloperand(vmarg* arg, unsigned val);
void make_retvaloperand(vmarg* arg);

void emitInstruction(instruction instruction);
void expandInstructions(void);

unsigned nextinstructionlabel(void);
unsigned currprocessedquad(void);

void reset_operand(vmarg *arg);

unsigned consts_newstring(char *s);
unsigned libfuncs_newused(char *s);
unsigned consts_newnumber(double num);
unsigned userfuncs_newfunc(struct SymbolTableEntry* sym);

void expandStrings();
void expandLib();
void expandNums();
void expandUserFuncs();

void createPrintFile(char* filename);
void generate(vmopcode op, quad* q);
void generate_relational(vmopcode op, quad* q);

void backpatch_Instruction(struct returnList* ret, int label);
struct returnList* append(returnList* ret, int label);
struct SymbolTableEntry *func_pop();
struct funcstack *func_push(struct SymbolTableEntry *entry); 
int func_isEmpty(struct funcstack *entry);
struct SymbolTableEntry *func_top(void);

void file_print_Arrays(FILE *fp);
void txt_print_instructions(FILE *fp);
void txt_print_Arrays(FILE *fp);
void file_read_Arrays(const char *filename);