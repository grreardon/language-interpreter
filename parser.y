%{
#include <stdio.h>
#include <math.h>
int yylex(void);
void yyerror(const char *s);
extern int yylineno;
%}

%define parse.error detailed
%union { double num; char *str; char ch; int boolean; }
%token IF ELSE LET WHILE FOR FUNC RETURN BREAK CONTINUE
%token PLUSEQUAL MINUSEQUAL MULTEQUAL DIVEQUAL MODEQUAL
%token OR AND EQ NEQ LEQ GEQ SL SR POW
%token <num> NUMBER
%token <str> STRING IDENTIFIER
%token <ch> CHAR
%token <boolean> BOOLEAN

%%

   program
   : stmt_list;
   stmt_list
   : stmt stmt_list | %empty;
   stmt
   : if | while | for | func | let ';' | assign ';' | expr ';' | return | break | continue;
   block
   : '{' stmt_list '}';
   if
   : IF '(' expr ')' block else;
   else
   : ELSE if | ELSE block | %empty;
   let
   : LET id '=' expr;
   assign
   : lvalue assign_op expr;
   lvalue
   : id | postfix '[' expr ']' | postfix '.' id;
   postfix
   : postfix '[' expr ']'
   | postfix '(' args ')'
   | postfix '.' id
   | primary;
   assign_op
   : '=' | PLUSEQUAL | MINUSEQUAL| MULTEQUAL | DIVEQUAL | MODEQUAL;
   while
   : WHILE '(' expr ')' block;
   for
   : FOR '(' for_init ';' for_cond ';' for_update ')' block;
   for_init
   : let | assign | %empty;
   for_cond
   : expr | %empty;
   for_update
   : assign | postfix | %empty;
   func
   : FUNC id '(' params ')' block;
   params
   : param_list | %empty;
   param_list
   : param_list ',' id | id;
   return
   : RETURN expr ';' | RETURN ';';
   break
   : BREAK ';';
   continue
   : CONTINUE ';';
   args
   : arg_list | %empty;
   arg_list
   : arg_list ',' expr | expr;
   expr
   : or;
   or
   : or OR and | and;
   and
   : and AND cmp | cmp;
   cmp
   : bit_or cmp_op bit_or | bit_or;
   cmp_op
   : EQ | NEQ | '<' | LEQ | '>' | GEQ;
   bit_or
   : bit_or '|' bit_xor | bit_xor;
   bit_xor
   : bit_xor '^' bit_and | bit_and;
   bit_and
   : bit_and '&' shift | shift;
   shift
   : shift SL additive | shift SR additive | additive;
   additive
   : additive '+' multiplicative | additive '-' multiplicative | multiplicative;
   multiplicative
   : multiplicative '*' unary | multiplicative '/' unary | multiplicative '%' unary | unary;
   unary
   : '-' unary | '!' unary | '~' unary | power;
   power
   : postfix POW unary | postfix;
   primary
   : id | literal | '(' expr ')' | array_lit;
   array_lit
   : '[' args ']';
   id
   : IDENTIFIER;
   literal
   : NUMBER | CHAR | STRING | BOOLEAN;

%%
void yyerror(const char *s) { fprintf(stderr, "line %d: %s\n", yylineno, s); }
int main(void) { return yyparse(); }


