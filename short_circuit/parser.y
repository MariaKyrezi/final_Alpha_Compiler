%{
        #include "stdio.h"
        #include "stackFrames.h"
        #include "phase4.h"

        void yyerror(char* yaccProvideMessage);
        
        int yylex(void);
        extern int yylineno;
        extern char* yytext;
        extern FILE* yyin;
        int line_number = 0;
        int scope = 0;
        int inloop = 0; /* check if yor are inside a loop ( >0 )*/ 
        int isfunc = 0; /* check for lvalue if it's a function */
        int func_block = 0;
        int funcDefinition = 0;
        int breakstmt = 0;
        char* userFuncName =  NULL;
        int unnamedFunc = 0; /* check if the function is anonymoys */
        int prevOffset = 0; /* It stores the recovered offset */
        stackFrame* topOfStack;
        int loopcounter = 0;
%}


%start program

%union {
    int intVal;
    char* strVal;
    float floatVal;
    struct expr* expression;
    struct SymbolTableEntry *symTabEntry;
    struct stmt_t* stm;
    struct call* calls; 
    unsigned undef;   
    struct forloop* forloop;
    struct tablepair* tablepair;
}

%token <intVal> INTEGER;
%token <strVal> STRING;
%token <floatVal> REALCONST;
%token <strVal> ID;

%token  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL 
%token  ASSIGN PLUS MINUS MUL DIV MOD EQUAL DIFF PLUS_PLUS MINUS_MINUS GREATER LESS GREATER_EQUAL LESS_EQUAL
%token  LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA COLON D_COLON DOT D_DOT

%type <expression> lvalue expr member primary call elist objectdef const term assignexpr
%type <intVal>    M N
%type <strVal>   funcname 
%type <calls> callsuffix normcall methodcall
%type <stm> stmt stmts ifstmts whilestmts forstmts returnstmts loopstmt BREAK CONTINUE block
%type <undef> ifprefix elseprefix whilestart whilecond funcbody
%type <symTabEntry> funcprefix funcdef
%type <forloop> forprefix
%type <tablepair> indexedelem indexed
 

%nonassoc IF
%nonassoc ELSE
/* Increasing priority from top to bottom */

%left ASSIGN
%left OR 
%left AND
%nonassoc EQUAL DIFF
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL
%left PLUS MINUS 
%left MUL DIV MOD 
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT D_DOT
%left LEFT_BRACE RIGHT_BRACE
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS


%%

program : stmts
            |{
                printf("Program: stmts, Line: %d\n",yylineno);
            }
        ;

stmts : stmts stmt{
                printf("stmts: stmts stmt Line: %d\n",yylineno);
                if ($2 && $1){
                        $$->breakList=mergelist($2->breakList, $1->breakList);
                        $$->contList=mergelist($2->contList, $1->contList);
                }else if($1){                    
                        $$=$1;                      
                }else if($2){                       
                        $$=$2;
                }else{                       
                        $$=NULL;
                }
        }       
        | stmt{
                printf("stmts: stmt Line: %d\n",yylineno);              
                $$ = $1;}              
        ;

stmt    : expr SEMICOLON {
                shortCircuitEval($1, yylineno);
                resettemp();
                $$ = NULL;
                printf("stmt: Expression semicolon Line: %d\n",yylineno);
        }
        | ifstmts {
                $$ = $1;
                printf("stmt: if statement Line: %d\n",yylineno);
        }
        | whilestmts{
                $$ = NULL;
                printf("stmt: while statement Line: %d\n",yylineno);
        }
        | forstmts{
                $$ = NULL;
                printf("stmt: for statement Line: %d\n",yylineno);
        }
        | returnstmts{
                /* check on whether you can return based on some scope 
                yyerror();*/
                $$ = NULL;
                printf("stmt: return statement Line: %d\n",yylineno);
        }
        | BREAK SEMICOLON{
                /* check if theres a break statement outside of a loop */
                if(loopcounter == 0){
                        yyerror("Break statement outside of loop");
                }else{
                        breakstmt  = 1;
                        printf("stmt: Break statement Line: %d\n",yylineno);
                }
                $1 = make_stmt();
                $1->breakList = newlist(nextQuad()); 
                emit(jump,NULL,NULL,NULL,nextQuad(),yylineno); 
                $$ = $1;
                
        }
        | CONTINUE SEMICOLON{
                /* check if theres a break statement outside of a loop */
                if(loopcounter == 0){
                        yyerror("Continue statement outside of loop");
                }else{
                        printf("stmt: Continue statement Line: %d\n",yylineno);
                }
                $1 = make_stmt();
                $1->contList = newlist(nextQuad()); 
                emit(jump,NULL,NULL,NULL,0,yylineno); 
                $$ = $1;
        }
        | block{
                $$ = $1;
                printf("stmt: Block of code Line: %d\n",yylineno);
        }
        | funcdef{
                /* should i increase the scope in this section ?????? */
                $$ = NULL;
                printf("stmt: Function (definition) Line: %d\n",yylineno);
        }
        | SEMICOLON {
                $$ = NULL;
                printf(" - - ; - - \n");
        }
        ;

expr    : assignexpr                    {       $$ = $1; }

        | expr PLUS expr                { 
                                                $$ = emit_arithOp(add,$1,$3,-1,scope,yylineno);
                                                printf("Expression: %f + %f \n", $1->numConst,$3->numConst);
                                        }

        | expr MINUS expr               { 
                                                $$ = emit_arithOp(sub,$1,$3,-1,scope,yylineno);
                                                printf("Expression: %f - %f \n", $1->numConst,$3->numConst);
                                        }

        | expr MUL expr                 { 
                                                $$ = emit_arithOp(mul,$1,$3,-1,scope,yylineno);
                                                printf("Expression: %f * %f \n", $1->numConst,$3->numConst);
                                        }

        | expr DIV expr                 { 
                                                $$ = emit_arithOp(divv,$1,$3,-1,scope,yylineno);
                                                printf("Expression: %f / %f \n", $1->numConst,$3->numConst);
                                        }

        | expr MOD expr                 { 
                                                $$ = emit_arithOp(mod,$1,$3,-1,scope,yylineno);
                                                printf("Expression: %f %% %f \n", $1->numConst,$3->numConst);
                                        }

        | expr GREATER expr             {       printf("Expression:  >  \n"); 
                                                $$ = emit_comparisonOp(if_greater, $1, $3, $$, -1, scope, yylineno);
                                        } 

        | expr GREATER_EQUAL expr       {       printf("Expression:  >=  \n");
                                                $$ = emit_comparisonOp(if_greatereq, $1, $3, $$, -1, scope, yylineno);
                                        }

        | expr LESS expr                {       printf("Expression:  <  \n");
                                                $$ = emit_comparisonOp(if_less, $1, $3, $$, -1, scope, yylineno);
                                        }

        | expr LESS_EQUAL expr          {       printf("Expression:  <=  \n");
                                                $$ = emit_comparisonOp(if_lesseq, $1, $3, $$, -1, scope, yylineno);
                                        }
        
        | expr EQUAL { shortCircuitEval($1, yylineno); } expr               
                                        {       
                                                shortCircuitEval($4,yylineno);
                                                printf("Expression:  ==  \n");
                                                $$ = emit_comparisonOp(if_eq, $1, $4, $$, -1, scope, yylineno);
                                        }

        | expr DIFF { shortCircuitEval($1, yylineno); } expr                
                                        {       
                                                shortCircuitEval($4, yylineno);
                                                printf("Expression:  !=  \n");
                                                $$ = emit_comparisonOp(if_noteq, $1, $4, $$, -1, scope, yylineno);
                                        }
        
        | expr AND {$1 = createBoolexpr($1,nextQuad(), nextQuad()+1, scope, yylineno);} M expr                   
                                        {       
                                                $5 = createBoolexpr($5,nextQuad(), nextQuad()+1, scope, yylineno );                        
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(scope,yylineno);

                                                patchlist($1->truelist,$4);
                                                $$->truelist = $5->truelist;
                                                $$->falselist = mergelist($1->falselist,$5->falselist);
                                        }

        | expr OR { $1 = createBoolexpr($1,nextQuad(), nextQuad()+1, scope, yylineno);} M expr                   
                                        {       
                                                $5 = createBoolexpr($5,nextQuad(), nextQuad()+1, scope, yylineno );

                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(scope,yylineno);

                                                patchlist($1->falselist, $4);
                                                $$->truelist = mergelist($1->truelist,$5->truelist);
                                                $$->falselist = $5->falselist;

                                                printf("Expression:  ||  \n");
                                        }

        | term                          {       
                                                printf("Expression: term Line: %d\n", yylineno);
                                                $$ = $1;
                                        }
        ;

term    : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{
                shortCircuitEval($2,yylineno);
                $$ = $2;
                printf("term: ( expression ) Line: %d\n",yylineno);              
        }
        | MINUS expr %prec UMINUS{
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith($2, "uminus statement");
                        $$ = newexpr(arithexpr_e);
                        $$->sym = newtemp(scope, yylineno);
                        emit(uminus,$2, NULL, $$,-1,yylineno);
                }
                printf("term: -lvalue Line: %d\n",yylineno);
        }
        | NOT expr {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        $2 = createBoolexpr($2, nextQuad(), nextQuad()+1, scope, yylineno);

                        $$ = newexpr(boolexpr_e);
                        $$->sym = newtemp(scope, yylineno);

                        $$->truelist = $2->falselist;
                        $$->falselist = $2->truelist;

                        printf("term: !lvalue Line: %d\n",yylineno);
                }
        }
        | PLUS_PLUS lvalue{
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith($2, "++lvalue");
                        if ($2->type == tableitem_e) {
                                $$ = emit_iftableitem($2,scope, yylineno);
                                emit(add, $$, newexpr_constnum(1), $$,-1,yylineno);
                                emit(tablesetelem, $2, $2->index, $$,-1,yylineno);
                        }
                        else {
                                emit(add, $2, newexpr_constnum(1), $2, -1, yylineno);
                                $$ = newexpr(arithexpr_e);
                                $$->sym = newtemp(scope,yylineno);
                                emit(assign, $2, NULL, $$, -1,yylineno);
                        }
                }
                printf("term: ++lvalue Line: %d\n",yylineno);
        }
        | lvalue PLUS_PLUS{
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }
                check_arith($1, "lvalue++");
                $$ = newexpr(var_e);
                $$->sym = newtemp(scope, yylineno);
                if ($1 != NULL && $1->type == tableitem_e) {
                        expr* val = emit_iftableitem($1, scope, yylineno);
                        emit(assign, val, NULL, $$,-1,yylineno);
                        emit(add, val, newexpr_constnum(1), val,-1,yylineno);
                        emit(tablesetelem, $1, $1->index, val,-1,yylineno);
                }
                else {
                        emit(assign, $1, NULL, $$,-1,yylineno);
                        emit(add, $1, newexpr_constnum(1), $1,-1,yylineno);
                }   
                printf("term: lvalue++ Line: %d\n",yylineno);
        }
        | MINUS_MINUS lvalue{
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith($2, "--lvalue");
                        if ($2->type == tableitem_e) {
                                $$ = emit_iftableitem($2, scope, yylineno);
                                emit(sub, $$, newexpr_constnum(1), $$,-1,yylineno);
                                emit(tablesetelem, $2, $2->index, $$,-1,yylineno);
                        }
                        else {
                                emit(sub, $2, newexpr_constnum(1), $2, -1, yylineno);
                                $$ = newexpr(arithexpr_e);
                                $$->sym = newtemp(scope, yylineno);
                                emit(assign, $2, NULL, $$, -1, yylineno);
                        }
                }
                     
                printf("term: --lvalue Line: %d\n",yylineno);
        }
        | lvalue MINUS_MINUS{
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith($1, "lvalue--");
                        $$ = newexpr(var_e);
                        $$->sym = newtemp(scope, yylineno);
                        if ($1->type == tableitem_e) {
                                expr* val = emit_iftableitem($1, scope, yylineno);
                                emit(assign, val, NULL, $$,-1,yylineno);
                                emit(sub, val, newexpr_constnum(1), val,-1,yylineno);
                                emit(tablesetelem, $1, $1->index, val,-1,yylineno);
                        }
                        else {
                                emit(assign, $1, NULL, $$,-1,yylineno);
                                emit(sub, $1, newexpr_constnum(1), $1,-1,yylineno);
                        }  
                }
                printf("term: lvalue-- Line: %d\n",yylineno);
        }
        | primary{
                $$ = $1;
                printf("term: primary | Line: %d\n",yylineno);
        }
        ;

assignexpr      : lvalue ASSIGN expr{

                        /* check if the assignment has a function on the left e.g. func f(){}; f=10; */
                        if( isfunc == 1){
                                yyerror("Function used as an lvalue");
                                isfunc = 0;
                        }
                        if( $1->type == tableitem_e ){
                                shortCircuitEval($3,yylineno);
                                emit(tablesetelem,$1->index,$3,$1,-1,yylineno);     /*¬ Use result operand for the assigned value*/
                                $$ = emit_iftableitem($1, scope, yylineno);      /* ¬ Will always emit*/
                                $$->type = assignexpr_e;
                        }else {
                                shortCircuitEval($3,yylineno);
                                emit(assign,$3,NULL,$1,-1,yylineno);        /*that is: lvalue = expr*/
                                $$ = newexpr(assignexpr_e);
                                $$->sym = newtemp(scope, yylineno);
                                emit(assign, $1, NULL, $$,-1,yylineno);
                        }
                        
                        printf("assignexpr: lvalue = expression Line: %d\n",yylineno);
                }
                ;

primary : lvalue {
                /* here we have to check for emit tableitem*/
                $$ = emit_iftableitem($1, scope, yylineno);   
                
                printf("primary: lvalue Line: %d\n",yylineno);
        }
        | call  {
                $$ = $1; /* the semantic action assigns $1 (the result of the call rule) to $$ */
                printf("call\n");
        }
        | objectdef{
                /* don't know what is needed here */
                printf("primary: object definition | Line: %d\n",yylineno);
        }
        | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{
                $$ = newexpr(programfunc_e);    /* create a new expression of program function type*/
                $$->sym = $2;              /* assign the symbol of the function to the expression */
                printf("primary: (function definition) Line: %d\n",yylineno);
        }
        | const {
                $$ = $1; /* assigns the result of the 'const' rule to $$ */
                printf("primary: const Line: %d\n",yylineno);
        }
        ;

lvalue  : ID {
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id Line: %d\n",yylineno);
                isfunc = 0;
                if(scope == 0){
                        entry = createEntry(yylval.strVal,scope,yylineno,GLOBAL,VAR,1);
                        
                }else{
                        entry = createEntry(yylval.strVal,scope,yylineno,LOCL,VAR,1);
                }

                entry->offset = currscopeoffset();
                entry->space = currscopespace();
                entry->s_name = yylval.strVal;
                entry->s_scope = scope;
                entry->line = yylineno;
                entry->type = var_s;
                
                $$ = NULL;

                if((check=lookup(entry,"lvalue_ID")) == NULL){
                        if (scope == 0 && checkLibFuncName(yylval.strVal) != NULL){
                                isfunc = 1;
                                yyerror("ID collision with library function name");
                        }else{
                                SymbolTableInsert(entry);
                                inccurrscopeoffset();
                                $$ = lvalue_expr(entry); 
                        }                              
                }else{
                        if(check->isActive == 0 && check->scope_type != LIBFUNC){
                                if(check->scope_type != USERFUNC && check->scope_type != GLOBAL){
					yyerror("ID collision");
                        	}
			}else{
                                printf("Symbol found\n");
                                if( check->scope_type == USERFUNC){
                                        isfunc = 1;
                                }
                                inccurrscopeoffset();
                                $$ = lvalue_expr(check); 
                        }
                }                
        }
        | LOCAL ID{

                SymbolTableEntry *entry, *check;
                printf("lvalue -> local id\n");
                isfunc = 0;
                entry = createEntry($2,scope,yylineno,LOCL,VAR,1);
                
                entry->offset = currscopeoffset();
                entry->space = currscopespace();
                entry->s_name = $2;
                entry->s_scope = scope;
                entry->line = yylineno;
                entry->type = var_s;
                
                $$ = NULL;

                if((check=lookup(entry,"lvalue_local_ID")) == NULL){
                        SymbolTableInsert(entry);
                        $$ = lvalue_expr(entry);
                        inccurrscopeoffset();
                }else{
                        if(check->isActive == 0){
                                yyerror("local ID collision");
                        }else{
                                printf("Symbol found\n");
                                if( check->scope_type == USERFUNC && scope == 0){
                                        isfunc = 1;
                                }
                                $$ = lvalue_expr(check);
                                inccurrscopeoffset();
                        }
                }
        }
        | D_COLON ID{ /* only lookup on scope == 0 */
                SymbolTableEntry *entry, *check;
                printf("lvalue -> :: id\n");
                $$ = NULL;
                entry = createEntry($2,scope,yylineno,GLOBAL,VAR,1);

                check=lookup(entry,"lvalue_d_colon_ID");
                
                if(check->isActive == 0){
                        yyerror("Global ID does not exist");
                }else{
                        printf("Symbol found\n");
                        $$ = lvalue_expr(check);
                }              
        }
        | member{
                $$ = $1;
                printf("lvalue: member Line: %d\n",yylineno);
        }
        ;

member  : lvalue DOT ID                                 {
                printf("member: lvalue.id Line: %d\n",yylineno);
                $$ = member_item($1, $3);
        }
        | lvalue LEFT_BRACKET expr RIGHT_BRACKET        {
                printf("member: lvalue[expr] Line: %d\n",yylineno);
                $1 = emit_iftableitem($1, scope, yylineno); 
                shortCircuitEval($3,yylineno);
                $$ = newexpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;
        }
        | call DOT ID                                   { 
                printf("member: call.id Line: %d\n",yylineno);
                $$ = member_item($1, $3);
        }
        | call LEFT_BRACKET expr RIGHT_BRACKET          {   
                    
                printf("member: call[expr] Line: %d\n",yylineno);
                $1 = emit_iftableitem($1, scope, yylineno); 
                shortCircuitEval($3,yylineno);
                $$ = newexpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;
        }
        ;
   
call    : call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS{
                printf("call: call(elist) Line: %d",yylineno);
                $3 = reverseElist($3);
                $$ = make_call($1, $3, scope, yylineno);
          }
        | lvalue callsuffix{

                $1 = emit_iftableitem($1, scope, yylineno); /* in case it was a table item too */
                

                if ($2->method){

                        get_last($2->elist)->next = $1;  /*insert first (reversed, so from last) */
                        $1 = emit_iftableitem(member_item($1, $2->name), scope, yylineno);
                }

                
                $$ = make_call($1, $2->elist, scope, yylineno);
                printf("call: lvalue callsuffix Line: %d\n",yylineno);
                }

        | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                
                printf("call: (funcdef)(elist) Line: %d\n",yylineno);
                expr* func = newexpr(programfunc_e);
                func->sym = $2;
                $5 = reverseElist($5);
                $$ = make_call(func, $5, scope, yylineno); /* here it may needed to put $5 in a reverse elist func */
                }
        ;

callsuffix      : normcall { printf("callsuffix: Normal call Line: %d\n",yylineno);
                        $$ = $1;
                }
                |   methodcall {printf("Method call\n");
                        $$ = $1;
                }
                ;

normcall        : LEFT_PARENTHESIS elist RIGHT_PARENTHESIS{
                        $$ = new_call($2,0,NULL);
                        printf("normcall: (elist) Line: %d\n",yylineno);
                }
                ;

methodcall      : D_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS{
                        $$ = new_call($4,1,$2);
                        printf("methodcall: ..id(elist) Line: %d\n",yylineno);
                }
                ;

elist   : {
                $$=NULL;
                printf("empty elist\n");
        }
        | expr { 
                shortCircuitEval($1,yylineno);
                printf("elist: expr Line: %d\n",yylineno);
                $$=$1;
        }
        | elist COMMA expr{
                printf("elist: elist comma expr Line: %d\n",yylineno);
                shortCircuitEval($3,yylineno);
                $3->next = $1;
                $$ = $3;
        }       
        ;

objectdef       : LEFT_BRACKET elist RIGHT_BRACKET{
                        expr* t = newexpr(newtable_e);
                        t->sym = newtemp(scope,yylineno);
                        emit(tablecreate,NULL,NULL,t,-1,yylineno);

                        expr* list = reverseElist($2);

                        for(int i=0;list;list=list->next){
                                emit(tablesetelem,newexpr_constnum(i++),list,t,-1,yylineno);
                        }
                        $$ = t;
                        printf("[elist]\n");
                }
                | LEFT_BRACKET indexed RIGHT_BRACKET{
                        struct tablepair* ind;
                        expr* t = newexpr(newtable_e);
                        t->sym = newtemp(scope,yylineno);
                        emit(tablecreate,NULL,NULL,t,-1,yylineno);

                        ind = reverseIndexed($2);

                        while(ind!=NULL){                               
                                emit(tablesetelem,ind->key,ind->value,t,-1,yylineno);                                
                                ind = ind->next;
                        }
                        $$ = t;
                        printf("[indexed]\n");
                }               
                ;

indexed : indexedelem {
               $$ = $1;
               printf("indexed: indexedelem Line: %d\n",yylineno); 
        }
        |indexed COMMA indexedelem{
                $3->next = $1;
                $$ = $3;
                printf("indexed: indexed,indexedelem Line: %d\n",yylineno);  
        }
        ;
        
indexedelem     : LEFT_BRACE expr COLON expr RIGHT_BRACE{
                        shortCircuitEval($2,yylineno);
                        shortCircuitEval($4,yylineno);

                        printf("indexedelem: { expr : expr } Line: %d\n",yylineno);
                        $$ = make_pair($2,$4);
                }
                ;

block   : LEFT_BRACE  { // if the brackets {} are empty the scope stays the same since it increases by 1 and decreases by 1 immediately
                if(funcDefinition != 1){
                        scope++;
                }else{
                        funcDefinition = 0;
                }
                
        } RIGHT_BRACE   { 
                /* hide function */
                HideSymbolsAtScope(scope);
                scope--;
                if(func_block == 1){
                        popStack();
                        func_block = 0;
                }
                
                printf("block: {} Line: %d\n",yylineno); 
        }
        | LEFT_BRACE {
                        printf("block: Left brace Line: %d\n",yylineno);
                        if(funcDefinition != 1){
                                scope++;
                        }else{
                                funcDefinition = 0;
                        }
                } 
                stmts
                RIGHT_BRACE {
                        /* hide function */
                        HideSymbolsAtScope(scope);
                        scope--;
                        
                        if(func_block == 1){
                                popStack();
                                func_block = 0;
                        }
                        
                        $$ = $3;
                        printf("block: { statement } Line: %d\n",yylineno);
                }
        ;

funcname: ID {
                $$ = $1;
                unnamedFunc = 0;
        }  
        | {
                userFuncName = generateName();
                $$ = userFuncName;
                unnamedFunc = 1;
                
        }     

funcprefix      :FUNCTION {funcDefinition = 1;} funcname {
                        SymbolTableEntry *entry = createEntry($3,scope,yylineno,USERFUNC,FUNC,0), *check;
                        entry->value.funcVal->iaddress = nextQuad();

                        $$ = entry;
                        if(unnamedFunc == 1){ /* we can combine if else with if(unnamedFunc == 1 || (check=lookup(entry,"funcdef")) == NULL )*/
                                SymbolTableInsert(entry);
                                printf("Symbol Inserted in line: %d\n", yylineno);
                                pushStack(entry->s_name, entry->s_scope,currscopeoffset()); /*save current offset*/
                                emit(funcstart, lvalue_expr($$),NULL, NULL, 0, yylineno );
                                enterscopespace();              /*Entering function arguments scope space*/
                                resetformalargsoffset();        /*Start formals from zero*/

                        }else{
                                if((check=lookup(entry,"funcdef")) == NULL){
                                        SymbolTableInsert(entry);
                                        printf("Symbol Inserted in line: %d\n", yylineno);
                                        pushStack(entry->s_name, entry->s_scope,currscopeoffset()); /*save current offset*/
                                        emit(funcstart, lvalue_expr($$),NULL, NULL, 0, yylineno );
                                        enterscopespace();      /*Entering function arguments scope space*/
                                        resetformalargsoffset();        /*Start formals from zero*/
                                }else{
                                        if(check->isActive == 0){
                                                yyerror("Name of function already exists");
                                        }else{
                                                printf("Symbol found\n");
                                        }
                                }
                        }
                        printf("funcprefix: FUNCTION funcname Line: %d\n",yylineno);
                }

funcargs        : LEFT_PARENTHESIS {scope++;} idlist RIGHT_PARENTHESIS{ 
                        func_block = 1;	
                        enterscopespace();              /* Now entering function locals space */
                        resetfunctionlocaloffset();    /* Start counting locals from zero */
                }               
funcbody        : block{ 
                        $$ = currscopeoffset();  /* Extract #total locals */
                        exitscopespace();       /* Exiting function locals space */
                        funcDefinition = 0;
                }

funcdef : funcprefix funcargs funcbody{ 

                exitscopespace();                              /* Exiting function definition space */
                $1->value.funcVal->totalLocals = $3;                           /* Store #locals in symbol entry */
                topOfStack = popStack();        /* pop and get pre scope offset */
                prevOffset = topOfStack->scopeOffset;
                restorecurrscopeoffset(prevOffset);            /* Restore previous scope offset */
                $$ = $1;                                        /* The function definition returns the symbol */
                emit(funcend, lvalue_expr($1), NULL, NULL, 0, yylineno);

                printf("function (idlist) block\n");        
        }
        ;

const   : INTEGER       {
                $$ = newexpr_constnum(yylval.intVal);
                printf("Integer\n");
        }
        | REALCONST     {
                $$ = newexpr_constnum(yylval.floatVal);
                printf("Real number\n");
        }
        | STRING        {
                $$ = newexpr_conststring(yylval.strVal);
                printf("String %s\n",yylval.strVal);}

        | NIL           {
                $$ = newexpr(nil_e);
                printf("Nil\n");}

        | TRUE          {
                $$ = newexpr_constbool(1);
                printf("True\n");}
                
        | FALSE         {
                $$ = newexpr_constbool(0);
                printf("False\n");}
        ;

idlist  : 
        |ID{
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id\n");

                
                entry = createEntry(yylval.strVal,scope,yylineno,FORMAL,VAR,1);
                
                if((check=lookup(entry,"formal_arg")) == NULL){
                        SymbolTableInsert(entry);
                        printf("Symbol Inserted\n");
                }else{
                        if(check->isActive == 0){
                                yyerror("ID collision\n");
                        }else{
                                printf("Symbol found\n");
                        }
                }
        }
        | idlist COMMA ID{
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id\n");

                
                entry = createEntry($3,scope,yylineno,FORMAL,VAR,1);
                
                if((check=lookup(entry,"formal_arg")) == NULL){
                        SymbolTableInsert(entry);
                        printf("Symbol Inserted\n");
                }else{
                        if(check->isActive == 0){
                                yyerror("ID collision");
                        }else{
                                printf("Symbol found\n");
                        }
                }
        }
        ;

ifprefix        : IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{
                        /* check if $3(expr) is equal to true and set label as +2 positions */
                        shortCircuitEval($3,yylineno);
                        emit(if_eq, $3, newexpr_constbool(1), NULL, nextQuad()+2,yylineno);
                        $$ = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno );
                }
                ;

elseprefix      : ELSE{
                        $$ = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno);

                }

ifstmts : ifprefix stmt {
                /* $1 should have $ifprefix in order to patch the label */
                patchlabel($1, nextQuad());
                $$ = make_stmt();
                $$ = $2;
                printf("if (expr) stmts\n");
        }       
        | ifprefix stmt elseprefix stmt { 

                /* $1 should have $ifprefix in order to patch the label */
                /*  $3 should have $elseprefix in order to patch the other label*/
                
                patchlabel($1, $3+1);
                patchlabel($3, nextQuad());

                $$ = make_stmt();
                
                if ($2 && $4){
                        $$->breakList=mergelist($2->breakList, $4->breakList);
                        $$->contList=mergelist($2->contList, $4->contList);
                }else if($2){                       
                        $$ = $2;                      
                }else if($4){                       
                        $$ = $4;
                }else{                       
                    $$=NULL;
                }
                printf("if (expr) stmts else stmts");
                
        }
        ;

whilestart      : WHILE{
                        $$ = nextQuad();
                        printf("whilestart: WHILE Line: %d\n",yylineno);
                }
                ;

whilecond       : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{
                        shortCircuitEval($2,yylineno);
                        emit(if_eq, $2, newexpr_constbool(1), NULL, nextQuad()+2, yylineno);
                        $$ = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno);
                        inloop++;
                        printf("opening while statement\n");
                }
                ;

whilestmts      : whilestart whilecond loopstmt{

                        /* $1 because the jump should be at while start unless there is a break/continue*/
                        emit(jump, NULL, NULL,NULL,$1,yylineno);
                        patchlabel($2,nextQuad());             

                        if($3 && $3->breakList ){
                                patchlist($3->breakList, nextQuad());
                        }
                        
                        if($3 && $3->contList){
                                patchlist($3->contList,  $1);
                        }

                        if(breakstmt == 1){
                                breakstmt = 0;
                        }else{
                                inloop--;
                        }
                        
                        printf("closing while statement\n");
                }
                ;

N               :{ 
                 $$ = nextQuad();
                 emit(jump,NULL,NULL,NULL,0,yylineno); 
                }
                ;

M               : { $$ = nextQuad();};


forprefix       :FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON {
                        shortCircuitEval($6,yylineno);
                        $$ = (struct forloop*)malloc(sizeof(struct forloop));
                        $$->test = $5;
                        $$->enter = nextQuad();
                        emit(if_eq,$6,newexpr_constbool(1),NULL,0,yylineno);
                }
                ;

forstmts        :forprefix N elist RIGHT_PARENTHESIS N loopstmt N {
                        patchlabel($1->enter, $5+1);
                        patchlabel($2, nextQuad());
                        patchlabel($5, $1->test);
                        patchlabel($7, $2+1);

                        if ($6 && $6->breakList){
                                patchlist($6->breakList, nextQuad());
                        }
                        
                        if($6 && $6->contList){
                                patchlist($6->contList, $2+1);
                        }
                        if(breakstmt == 1){
                                breakstmt = 0;
                        }                     
                        printf("for (elist; expr; elist) stmts\n");
                }
                ;

loopstart       :{++loopcounter;};
loopend         :{--loopcounter;};
loopstmt        :loopstart stmt loopend {
                        printf("loopstmt: loopstart stmt loopend Line: %d\n",yylineno);
                        $$=$2;
                };

returnstmts     :  RETURN SEMICOLON{
                        if(func_block != 0){
                                emit(ret, NULL,NULL,NULL,-1,yylineno); 
                                printf("returnstmts: return; Line: %d\n",yylineno);
                        }else{
                                yyerror("Return statement outside function\n");
                        }
                }
                | RETURN expr SEMICOLON{
                        if(func_block != 0){
                                shortCircuitEval($2,yylineno);
                                emit(ret, NULL,NULL,$2,-1,yylineno);
                                printf("returnstmts: return expr; Line: %d\n",yylineno);
                        }else{
                                yyerror("Return statement outside function\n");
                        }
                }
                ;

%%

void yyerror(char* yaccProvideMessage){
        fprintf(stderr, "\033[31mError: %s: at line %d, before token %s\033[0m ", yaccProvideMessage, yylineno, yytext);
        fprintf(stderr,"\n");
}



int main(int argc, char **argv){

        if(argc>1){
                if(!(yyin = fopen(argv[1],"r"))){
                        fprintf(stderr,"Cannot read file: %s\n", argv[1]);
                        return 1;
                }
        }else{
                yyin = stdin;
        }
        insertLibFunctions();
        yyparse();
        printSymbolTable();
        printQuads();
        generateInstr();
        createPrintFile("file.bin");
        file_read_Arrays("file.bin");
        return 0;
}
