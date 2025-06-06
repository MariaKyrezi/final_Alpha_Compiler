
#include <assert.h>
#include "symbolTable.h"

#define EXPAND_SIZE 1024
// quad array
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

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

extern struct quad* quads;

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
