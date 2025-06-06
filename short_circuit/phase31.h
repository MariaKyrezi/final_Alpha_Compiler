
#include <assert.h>
#include "symbolTable.h"

#define EXPAND_SIZE 1024

// quad array
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

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
#define CURR_USERFUNCS_SIZE (totalUserFuncs * sizeof(func))
#define NEW_USERFUNCS_SIZE (EXPAND_SIZE * sizeof(func) + CURR_USERFUNCS_SIZE)

typedef enum iopcode{
    assign,         add,            sub, 
    mul,            divv,           mod, 
    uminus,         and,            or,
    not,            if_eq,          if_noteq, 
    if_lesseq,      if_greatereq,   if_less,
    if_greater,     calll,           param, 
    ret,            getretval,      funcstart, 
    funcend,        jump,
    tablecreate,    tablegetelem,   tablesetelem      
}iopcode;

typedef struct quad{
    iopcode op;
    struct expr* result;
    struct expr*arg1;
    struct expr* arg2;
    unsigned label;
    unsigned line;
    unsigned taddress;
}quad;


typedef enum expr_t{
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e
}expr_t;

typedef struct stmt_t {
    int breakList;
    int contList;
}stmt_t;

typedef struct expr{
    expr_t  type;
    SymbolTableEntry* sym;
    struct expr*   index;
    double  numConst;
    char*   strConst;
    unsigned char boolConst; // check newexpr_constbool
    struct expr*   next;

    // short circuit evaluation
    int truelist;
    int falselist;
}expr;



typedef struct call {
    struct expr* elist;
    unsigned char method;
    char* name;
}call;

typedef struct forloop{
    int test;
    int enter;
}forloop;

struct tablepair{
    expr * key;
    expr * value;
    struct tablepair * next;
};

typedef struct func{
    char* id;
    unsigned address;
    unsigned localsize;
}func;

scopespace_t currscopespace(void);
void enterscopespace(void);
void exitscopespace(void);
void resetformalargsoffset(void);
expr* lvalue_expr(SymbolTableEntry* sym);
char* newtempname(void);
SymbolTableEntry* newtemp(int scope, int line_number);
void resettemp(void);  
unsigned currscopeoffset(void);
void inccurrscopeoffset(void);
void expand(void);
void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
expr* newexpr(expr_t t);
expr* newexpr_conststring(char* s);
expr* newexpr_constnum(double i);
expr* newexpr_constbool(unsigned int b);
expr* emit_iftableitem(expr* e, int scope, int yylineno);
expr* make_call(expr* lv, expr* revesred_elist , int scope, int yylineno);
unsigned int istempname(char* s);   // check if this is needed
unsigned int istempexpr (expr* e);  // check if this is needed
void patchlabel (unsigned quadNo, unsigned label);
unsigned nextQuad (void);
stmt_t *make_stmt (void);
int newlist (int i);
int mergelist (int l1, int l2);
void patchlist (int list, unsigned label);
void resetformalargsoffset(void);
void resetfunctionlocaloffset(void);
void restorecurrscopeoffset(unsigned n);
void patchlabel(unsigned quadNo, unsigned label);
int check_arith (expr* e, const char* context);
expr *emit_arithOp(iopcode op, expr* arg1, expr* arg2, unsigned label, int scope, int line_number);
expr *emit_comparisonOp(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, int scope, int line_number);
void printQuads(void);
void printOpcode(quad quad);
void printArguments(expr * expr);
expr* member_item(expr* lv, char* name);
call* new_call(struct expr* elist,unsigned char method,char* name);
struct expr* reverseElist(struct expr* start);
struct tablepair* reverseIndexed(struct tablepair* start);
expr* get_last( expr* first);
struct tablepair* make_pair(expr* expr1, expr* expr2);
expr* createBoolexpr(expr* expr1, int jump1, int jump2, int scope,int line);
void shortCircuitEval(expr* expr, int line);

/***
 * 
 * 
 * ************ PHASE 4-5 ***********
 * 
 * 
 * 
****/

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
unsigned userfuncs_newfunc(SymbolTableEntry* sym);
void expandStrings(void);
void expandLib(void);
void expandNums(void);
void expandUserFuncs(void);
void createPrintFile(FILE* filename);
void generate(vmopcode op, quad* q);
void generate_relational(vmopcode op, quad* q);
void createPrintFile(FILE* filename);