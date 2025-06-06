%{

    #include "parser.h"
    int number_token = 0;
    
%}

%option yylineno
%option noyywrap

integer [0-9]+
float   [0-9]*\.[0-9](e|E)?[0-9]*
id      [a-zA-Z][a-zA-Z0-9_]*

%%

"//".*   {number_token++; }

"/*"    {
            int comment_size = 0;
            int buffer_size = 1024;
            char* comment_buffer = (char*)malloc(buffer_size * sizeof(char));

            int nested_comms = 0;           
            unsigned int end = 0;

            char* comment = (char*)malloc(buffer_size * sizeof(char));
            char result[100]={0};
            int begin[100]={0};

            int is_multiline=0;
            int index = 0 , index_comment=0, counter =1;
            begin[nested_comms] = yylineno;
            int line_number = yylineno;
            nested_comms++;

            if (comment_buffer == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }

            do {
                int c = input();
                if (c == EOF || c == '\0') {
                    if(counter>0){
                        fprintf(stderr, "ERROR: The multiline comment is still open. Line: %d\n", yylineno); //edw kati prepei na ginei
                        //perror("");
                    }
                    // End of comment or unexpected character
                    break;
                }
                comment_buffer[comment_size++] = (char)c;   
                
                if (comment_size == buffer_size - 1) {
                    // Resize buffer if needed
                    buffer_size *= 2;
                    comment_buffer = (char*)realloc(comment_buffer, buffer_size * sizeof(char));

                    if (comment_buffer == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if (comment_buffer[comment_size-2] == '/' && comment_buffer[comment_size-1] == '*') {
                    counter++;
                }
                if (comment_buffer[comment_size - 2] == '*' && comment_buffer[comment_size-1] == '/') {
                    counter--;
                    if(counter == 0){
                        break;
                    }
                }
            } while (1);

            comment_buffer[comment_size] = '\0'; 

            while (comment_buffer[index]!='\0') {
                if (comment_buffer[index] == '/') {
                    index++;
                    if (comment_buffer[index] == '*') {
                        begin[nested_comms] = line_number;
                        nested_comms++;
                        
                        if(nested_comms > 1){
                            is_multiline = 1;
                        }
                        index++; // skip '*'
                    }
                } else if (comment_buffer[index] == '*') {
                    index++;
                    if (comment_buffer[index] == '/') {
                        nested_comms--;
                        end = line_number;
                        number_token++;
                        sprintf(result, "%d - %d", begin[nested_comms], end);
                        
                        if ( nested_comms == 0  && is_multiline == 1) {
                            //make_new_alpha_node((struct alpha_token_t **)&head, begin[nested_comms], number_token, result,BLOCK_COMMENT,"");
                            break;
                        }
                        //make_new_alpha_node((struct alpha_token_t **)&head, begin[nested_comms], number_token, result,NESTED_COMMENT,"");
                        index++;
                    }
                }
                if (index_comment == buffer_size - 1) {
                    // Resize buffer if needed
                    buffer_size *= 2;
                    comment = (char*)realloc(comment, buffer_size * sizeof(char));

                    if (comment == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if (comment_buffer[index] != '*' && comment_buffer[index] != '/' ){
                    if(comment_buffer[index] == '\n'){
                        line_number++;
                    }
                    comment[index_comment++] = comment_buffer[index];
                    index++;
                } 
            }
            comment[index++] = '\0';
            free(comment_buffer);
            
        }

\"([^\"\\]|\\(.|\n))*. {
    
    char* str = yytext + 1; // Skip the opening quote
    int buffer_size = 1024;
    char* modifiedString = (char*)malloc(buffer_size * sizeof(char)); // Adjust the size as needed
    int index = 0;
    int line = yylineno;
    while (*str && *str != '\"') {
        if (index == buffer_size - 1) {
            // Resize buffer if needed
            buffer_size *= 2;
            modifiedString = (char*)realloc(modifiedString, buffer_size * sizeof(char));

            if (modifiedString == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        if (*str == '\\') {
            str++;
            
            switch (*str) {
                case 'n':
                    modifiedString[index++] = '\n';
                    break;
                case 't':
                    modifiedString[index++] = '\t';
                    break;
                case '\"':
                    modifiedString[index++] = '\"';
                    break;
                case '\\':
                    modifiedString[index++] = '\\';
                    break;
                default:
                    printf("Warning : the string contains invalid escape character \\%c. Line: %d\n",*str,yylineno);
                    modifiedString[index++] = '\\';
                    modifiedString[index++] = *str;
                    break;
            }
            
        } else {
            modifiedString[index++] = *str;
        }
        str++;
    }

    if (*(str) != '\"') {
        //make_new_alpha_node((struct alpha_token_t **)&head,line,number_token, "Error in string: missing terminating quotes.", UNDEFINED, "");
        return 1;
    }
    modifiedString[index] = '\0'; // Null-terminate the string
    number_token++; 
    //make_new_alpha_node((struct alpha_token_t **)&head,line,number_token, modifiedString, STRING, "STRING");
    yylval.strVal = strdup(modifiedString);
    free(modifiedString);
    return STRING;
}

"if"        { return IF; }	
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"function"  { return FUNCTION; }
"return"    { return RETURN; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"and"       { return AND; }
"not"       { return NOT; }
"or"        { return OR; }
"local"     { return LOCAL; }
"true"      { return TRUE; }
"false"     { return FALSE; }
"nil"       { return NIL; }

"="         { return ASSIGN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"=="        { return EQUAL; }
"!="        { return DIFF; }
"++"        { return PLUS_PLUS; }
"--"        { return MINUS_MINUS; }
">"         { return GREATER; }
"<"         { return LESS; }
">="        { return GREATER_EQUAL; }
"<="        { return LESS_EQUAL; }

"{"         { return LEFT_BRACE;}
"}"         { return RIGHT_BRACE;}
"["         { return LEFT_BRACKET;}
"]"         { return RIGHT_BRACKET;}
"("         { return LEFT_PARENTHESIS;}
")"         { return RIGHT_PARENTHESIS;}
";"         { return SEMICOLON;}
","         { return COMMA;}
":"         { return COLON;}
"::"        { return D_COLON;}
"."         { return DOT;}
".."        { return D_DOT;}

{id}            { yylval.strVal = strdup(yytext); return ID;}
{float}         { yylval.floatVal = atoi(yytext); return REALCONST;}
{integer}       { yylval.intVal = atoi(yytext); return INTEGER;}

[ \t\n\r] {
    // Skip spaces, tabs, and newlines
}
. {
    printf("Undefined character: %c\n",yytext[0]);
}

%%