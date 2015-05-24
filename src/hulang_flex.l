%option reentrant
%option warn nodefault
%option prefix="hulang_yy"
%option header-file="hulang_flex_lexer.h"
%option outfile="hulang_flex_lexer.c"
%option noyywrap yylineno never-interactive nounistd

%{
#include <hulang_token_type_def.h>
#include <hulang_read_stream.h>

#define YY_INPUT(buf, result, max_size) \
    result = hulang_read_stream(buf, max_size, yyextra)
%}


ws       [ \r\n\t]+
id       (_[[:alnum:]]*)|([[:alpha:]][[:alnum:]]*)
integer  0|[1-9][[:digit:]]*
float    {integer}?\.[[:digit:]]+

%%

{ws}        {}
{id}        { return HULANG_TOKEN_TYPE_ID; }
{integer}   { return HULANG_TOKEN_TYPE_INTEGER; }
{float}     { return HULANG_TOKEN_TYPE_FLOAT; }
"?"         { return HULANG_TOKEN_TYPE_QMARK; }
":"         { return HULANG_TOKEN_TYPE_COLON; }
"="         { return HULANG_TOKEN_TYPE_ASSIGN; }
"+="        { return HULANG_TOKEN_TYPE_PLUS_ASSIGN; }
"-="        { return HULANG_TOKEN_TYPE_MINUS_ASSIGN; }
"*="        { return HULANG_TOKEN_TYPE_MULTIPLY_ASSIGN; }
"/="        { return HULANG_TOKEN_TYPE_DIVIDE_ASSIGN; }
"%="        { return HULANG_TOKEN_TYPE_MOD_ASSIGN; }
"++"        { return HULANG_TOKEN_TYPE_INC; }
"--"        { return HULANG_TOKEN_TYPE_DEC; }
"||"        { return HULANG_TOKEN_TYPE_OR; }
"&&"        { return HULANG_TOKEN_TYPE_AND; }
"<"         { return HULANG_TOKEN_TYPE_LT; }
">"         { return HULANG_TOKEN_TYPE_GT; }
"<="        { return HULANG_TOKEN_TYPE_LE; }
">="        { return HULANG_TOKEN_TYPE_GE; }
"=="        { return HULANG_TOKEN_TYPE_EQ; }
"!="        { return HULANG_TOKEN_TYPE_NE; }
"!"         { return HULANG_TOKEN_TYPE_NOT; }
"+"         { return HULANG_TOKEN_TYPE_PLUS; }
"-"         { return HULANG_TOKEN_TYPE_MINUS; }
"*"         { return HULANG_TOKEN_TYPE_MULTIPLY; }
"/"         { return HULANG_TOKEN_TYPE_DIVIDE; }
"%"         { return HULANG_TOKEN_TYPE_MOD; }
"^"         { return HULANG_TOKEN_TYPE_POWER; }
"("         { return HULANG_TOKEN_TYPE_LPAR; }
")"         { return HULANG_TOKEN_TYPE_RPAR; }
"/*"        {
                int c = 0;
                while(0 != (c = input(yyscanner)))
                {
                    if(c == '*')
                    {
                        c = input(yyscanner);
                        if('/' == c) break;
                        else unput(c);
                    }
                }
            }
"//"        {
                int c = 0;
                while(0 != (c = input(yyscanner)) && '\n' != c);
            }
<<EOF>>     { return HULANG_TOKEN_TYPE_EOS; }
.           { return HULANG_TOKEN_TYPE_ERROR; }


%%
