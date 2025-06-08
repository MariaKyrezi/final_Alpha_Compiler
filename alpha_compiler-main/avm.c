#include "avm.h"

execute_func_t executeFuncs[]={
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

memclear_func_t memclearFuncs[]={ 
    0,//number
    memclear_string,
    0,//bool
    memclear_table,
    0,//userfunc
    0,//livfunc
    0,//nil
    0//undef
};


tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};


unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currline = 0;
unsigned codeSize = 0;
instruction* code = (instruction*)0;


void execute_cycle(void){
    if(executionFinished ){
        return;
    }else{
        if(pc == AVM_ENDING_PC){
            executionFinished = 1;
            return;
        }else{
            assert(pc<AVM_ENDING_PC);
            instruction* instr = code + pc;
            assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
            if(instr->srcLine){
                currline = instr->srcLine;
            }
            unsigned oldPC = pc;
            (*executeFuncs[instr->opcode])(instr);
            if(pc == oldPC){
                ++pc;
            }
        }


    }
}


void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

/*Automatic garbage collection for tables when reference counter gets zero*/
void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p){
    for(unsigned i=0 ; i<AVM_TABLE_HASHSIZE; i++){
        p[i] = (avm_table_bucket*)0;
    }
}

/*The referende counter is initially zero*/
avm_table* avm_tablenew(void){
    avm_table* t = (avm_table*) malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    return t;
}

/*when a cell is cleared, it has to destroy all dynamic data content or
reset is reference to a table*/
void avm_tablebucketsdestroy(avm_table_bucket**p){
    for(unsigned i=0 ; i<AVM_TABLE_HASHSIZE; i++, p++){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free (del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}

void avm_tabledestroy(avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);

}

/*Will be used from functinons that implement the execute_ commands of the VM*/
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch(arg->type){
        //Variables --1-- 
        case global_a:  return &stack[AVM_STACKSIZE-1-arg->val];

        case local_a:   return &stack[topsp-arg->val];

        case formal_a:  return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];

        //--1-- From --1-- to --1-- the imlementation of the enviroment function to fetch a variable address!
        case retval_a:  return &retval;
        //oi mones periptwseis gia oprerands variables ^

        case number_a:  {//--2--
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a:  {
            reg->type = string_a;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }//--2-- για τιμες ορισματων που αποθηκεύονται σε πινακα σταθερων τιμων 
        //η εξαγωγή γίνεται χρησιμοποιώντας to operand value ws index

        case bool_a:    {
            reg->type = bool_m;
            reg->data.boolVar = arg->val;
            return reg;
        }
        case nil_a:     reg->type = nil_a; return reg;
       
        case userfunc_a: {
            reg->type = userfunc_m;
            //if function address is directly stored
            reg->data.funcVal = arg->val;
            //if function index in func table is stored
            reg->data.funcVal = userfuncs_getused(arg->val)->address;
            return reg;
        }
        //oi συναρτήσεις βιλιοθήκης αντιμετωπίζονται ως σταθερές τιμές με την τιμή του ορίσμτος
        //να είναι index στον πίνακα των ονομάτων των συναρτήσεων βιβλιοθήκης στο εταγλωτισμένο προγραμμα
        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.funcVal = libfuncs_getused(arg->val);
            return reg;
        }

        default:    assert(0);

        
    }
}   


void memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f)
            (*f)(m);
        m->type = undef_m;
    }
}

void memclear_string(avm_memcell* m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

// void avm_warning(char* format,...){}
void execute_assign(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);

    assert(lv && (&stack[N-1] = lv && lv > &stack[top]));
    assert(rv);//similar asser tests here(

    avm_assign(lv,rv);
}

void avm_assign(avm_memcell* lv, avm_memcell* rv){
    if(lv == rv)    //same cell
        return;
    if(lv->type == table_m && rv->type ==table_m && lv->data.tableVal == rv->data.tableVal)
        return;//same tables
    if(rv->type == undef_m)
        avm_warning("assign from 'undef'!");
    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));

// take care of copied values or reference counters
    if(lv->type == string_m)
        lv->data.strVal = strdup(rv->data.strVal);
    else{
        if(lv->type == table_m)
            avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    switch(func->type){
        case userfunc_m: {
            avm_callsaveenvironment();
            pc = func->func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_vm);
            break;
        }
//μποροθμε να καλουμε lib functions σαν strings
        case string_m: avm_calllibfunc(func->data.strVal); break;

        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;

        case table_m: avm_call_functor(func->data.tableVal); break;

        default: {
            char* s = avm_tostring(func);
            avm_error("call: CANNOT BIND %s to function",s);
            free(s);
            executionFinished = 1;
        }
    }
}

void avm_call_functor(avm_table *t){
    cx.type = string_m;
    cx.data.strVal = "()";
    avm_memcell* f = avm_tablegetelem(t, &cx);
    if(!f)
        avm_error("in calling table no'()' found!");
    else
        if(f->type == table_m)
            avm_call_functor(f->data.tableVal);
        else
            if(f->type == userfunc_a){
                avm_push_table_arg(t);
                avm_callsaveenviroment();
                pc = f->data.funcVal;
                assert(pc < AVM_ENDING_PC && code[pc].opcode == funcenter_v);
            }
            else{
                avm_error("in calling table : illegal '()' found!");
            }
}

unsigned totalActuals = 0;

void avm_dec_top(void){
    if(!top){
        avm_error("stach overflow!");
        executionFinished = 1;
    }    
    else{
        --top;
    }
}

void avm_push_envalue(unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal= val;
    avm_dec_top();
}

void avm_callsaveenviroment(void){
    avm_push_envalue(totalActuals);
    assert(code[pc].opcode == call_v);
    avm_push_envalue(pc+1);
    avm_push_envalue(top + totalActuals + 2);
    avm_push_envalue(topsp);
}

extern userfunc* avm_getfuncinfo(unsigned address);

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);//func address sould match pc

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

unsigned avm_get_envalue(unsigned i){
    assert(stack[i].type = number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].sta.numVal == ((double)val));
    return val;
}

#define AVM_NUMACTUALS_OFFSET   +4
#define AVM_SAVEDPC_OFFSET      +3
#define AVM_SAVEDTOP_OFFSET     +2
#define AVM_SAVEDTOPSP_OFFSET   +1

void execute_funcexit(instruction* unused){
    unsigned oldTop = top;//epanafora prohgoymenou periballodont kai epistrofh apo klshsh
    top = avm_get_envalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp  = avm_get_envalue(topsp + AVM_SAVEDTOPSP_OFFSET);
//clean activation record
    while(++oldTop <= top){
        avm_memcellclear(&stack[oldTop]);
    }
}

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        avm_error("unsupported lib function %s!", id);
        executionFinished = 1;
    }
    else{
        avm_callsaveenviroment();
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished){
            execute_tablesetelem((instruction*)0);
        }
            
    }
}

unsigned avm_totalactuals(void){
    return avm_get_envalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactuals(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE +1 +i];
}
void libfunc_print(void){
    unsigned n = avm_totalactuals();
    for(unsigned i = 0 ; i<n ; i++){
        char*s = avm_tostring(avm_getactuals(i));
        put(s);
        free(s);
    }
}
void avm_push_table_arg(avm_table* t){
    stack[top].type = table_m;
    avm_tableincrefcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(&instr->arg1, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

char* avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type <= undef+m);
    return(*tostringFuncs[m->type])(m);
}


static void avm_initstack(void){
    for(unsigned i=0 ; i<AVM_STACKSIZE; i++ ){
        AVM_WIPEOUT(stack[i]); 
        stack[i].type = undef_m;
    }
}

