
#include "phase4.h"
#define AVM_STACKSIZE   4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKENV_SIZE   4
#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v
#define AVM_ENDING_PC codeSize

typedef enum avm_memcell_t{
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7
}avm_memcell_t;

typedef struct avm_memcell{
    avm_memcell_t type;
    union{
        double numVal;
        char* strVal;
        unsigned char boolVar;
        struct avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
}avm_memcell; 


typedef void (*execute_func_t)(instruction*);
typedef void (*memclear_func_t)(avm_memcell*);
typedef char* (*tostring_func_t)(avm_memcell*);
typedef void (*library_func_t)(void);



typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;
}userfunc;


double numConsts;
unsigned totalNumConsts;
char** stringConsts;
unsigned totalStringConsts;
char** namedLibfuncs;
unsigned totalNamedLibfuncs;
userfunc* userFuncs;
unsigned totalUserFuncs;

typedef struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
}avm_table_bucket;

typedef struct avm_table{
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
}avm_table;


avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;




/*For simplicity only support numeric and string keys
Bonus for teams implementing keys for user functions, library functions and booleans */



avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_memcell* key);
void avm_tablesetelem(avm_memcell* hey, avm_memcell* value);
void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);
void avm_memcellclear(avm_memcell* m);
void avm_tablebucketsdestroy(avm_table_bucket**p);
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

double consts_getnumber(unsigned index);
char* consts_getstring(unsigned index);
char* libfuncs_getused(unsigned index);
userfunc* userfuncs_getfunc(unsigned index); //

void execute_assign(instruction*);
void execute_add(instruction*);
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_uminus(instruction*);
void execute_and(instruction*);
void execute_or(instruction*);
void execute_not(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_funcexit(instruction*);
void execute_funcenter(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_nop(instruction*);

void memcellclear(avm_memcell* m);
void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);
void avm_assign(avm_memcell* lv, avm_memcell* rv);
void avm_error(char* format);
char* avm_tostring(avm_memcell*);
void avm_calllibfunc(char* funcName);
void avm_callsaveenvironment(void);
void avm_call_functor(avm_table* t);
void avm_push_table_arg(avm_table *t);

void avm_registerlibfunc(char* id, library_func_t addr);

char* number_tostring(avm_memcell*);
char* string_tostring(avm_memcell*);
char* bool_tostring(avm_memcell*);
char* table_tostring(avm_memcell*);
char* userfunc_tostring(avm_memcell*);
char* libfunc_tostring(avm_memcell*);
char* nil_tostring(avm_memcell*);
char* undef_tostring(avm_memcell*);

void libfunc_print();
void libfunc_input();
void libfunc_objectmemberkeys();
void libfunc_objecttotalmembers();
void libfunc_objectcopy();
void libfunc_arguments();
void libfunc_strtonum();
void libfunc_sqrt();
void libfunc_cos();
void libfunc_sin();
void libfunc_typeof();

library_func_t lib_Funcs[] = {
    libfunc_print,
    libfunc_input,
    libfunc_objectmemberkeys,
    libfunc_objecttotalmembers,
    libfunc_objectcopy,
    libfunc_arguments,
    libfunc_strtonum,
    libfunc_sqrt,
    libfunc_cos,
    libfunc_sin,
    libfunc_typeof
};