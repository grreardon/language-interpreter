%code requires
{
   #include <string>
   #include <vector>
   class Expr;
   class Stmt;
   class BlockStmt;
}

%{
#include <stdio.h>
#include <math.h>
#include "./AST/Expr/Expr.hpp"
#include "./AST/Stmt/Statement.hpp"
int yylex(void);
void yyerror(const char *s);
extern int yylineno;
%}

%define parse.error detailed
%union { double num; char* str; char ch; int boolean; int op; Expr* expr; Stmt* stmt; BlockStmt* blockstmt; std::vector<Stmt*>* stmts; std::vector<std::string>* names; std::vector<Expr*>* exprs;}
%token IF ELSE LET WHILE FOR FUNC RETURN BREAK CONTINUE
%token PLUSEQUAL MINUSEQUAL MULTEQUAL DIVEQUAL MODEQUAL
%token OR AND EQ NEQ LEQ GEQ SL SR POW
%token <num> NUMBER
%token <str> STRING IDENTIFIER
%token <ch> CHAR
%token <boolean> BOOLEAN
%type <expr> expr or and cmp bit_or bit_xor bit_and shift additive multiplicative unary power
%type <expr> postfix primary literal array_lit lvalue for_cond
%type <stmt> stmt if else while for func let assign return break continue for_init for_update
%type <blockstmt> block
%type <stmts> stmt_list
%type <op> assign_op cmp_op
%type <names> params param_list
%type <exprs> args arg_list
%type <str> id



//program, stmt_list, assign_op, params,

%%

   program
   : stmt_list;
   stmt_list
   : stmt_list stmt { $1->push_back($2); $$ = $1; }
   | %empty { $$ = new std::vector<Stmt*>(); };
   stmt
   : if | while | for | func | let ';' | assign ';'
   |  expr ';' {$$ = new ExprStmt(std::unique_ptr<Expr>($1)); }
   | return | break | continue;
   block
   : '{' stmt_list '}' {
      std::vector<std::unique_ptr<Stmt>> arguments;
      for(Stmt* expr: *$2) {
      arguments.push_back(std::unique_ptr<Stmt>(expr));
      }
      delete $2;
      $$ = new BlockStmt(std::move(arguments));
   };
   if
   : IF '(' expr ')' block else { $$ = new IfStmt(std::unique_ptr<Expr>($3), std::unique_ptr<BlockStmt>($5), std::unique_ptr<Stmt>($6)); };
   else
   : ELSE if { $$ = $2; }
   | ELSE block { $$ = $2; }
   | %empty { $$ = nullptr; };
   let
   : LET id '=' expr { $$ = new LetStmt(std::string($2), std::unique_ptr<Expr>($4)); };
   assign
   : lvalue assign_op expr { $$ = new AssignmentStmt(std::unique_ptr<Expr>($1), $2, std::unique_ptr<Expr>($3)); };
   lvalue
   : id { $$ = new VariableExpr(std::string($1)); }
   | postfix '[' expr ']' { $$ = new IndexExpr(std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)); }
   | postfix '.' id { $$ = new MemberExpr(std::unique_ptr<Expr>($1), std::string($3)); };
   postfix
   : postfix '[' expr ']' { $$ = new IndexExpr(std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3));}
   | postfix '(' args ')' {
   std::vector<std::unique_ptr<Expr>> arguments;
   for(Expr* expr : *$3) {
   arguments.push_back(std::unique_ptr<Expr>(expr));
   }
   delete $3;
   $$ = new CallExpr(std::unique_ptr<Expr>($1), std::move(arguments));}
   | postfix '.' id { $$ = new MemberExpr(std::unique_ptr<Expr>($1), std::string($3)); free($3);}
   | primary;
   assign_op
   : '=' { $$ = '='; }
   | PLUSEQUAL { $$ = PLUSEQUAL; }
   | MINUSEQUAL { $$ = MINUSEQUAL; }
   | MULTEQUAL { $$ = MULTEQUAL; }
   | DIVEQUAL { $$ = DIVEQUAL; }
   | MODEQUAL { $$ = MODEQUAL; };
   while
   : WHILE '(' expr ')' block { $$ = new WhileStmt(std::unique_ptr<Expr>($3), std::unique_ptr<BlockStmt>($5)); };
   for
   : FOR '(' for_init ';' for_cond ';' for_update ')' block { $$ = new ForStmt(std::unique_ptr<Stmt>($3), std::unique_ptr<Expr>($5), std::unique_ptr<Stmt>($7), std::unique_ptr<BlockStmt>($9)); };
   for_init
   : let | assign | %empty { $$ = nullptr; };
   for_cond
   : expr | %empty { $$ = nullptr; };
   for_update
   : assign | postfix | %empty { $$ = nullptr; };
   func
   : FUNC id '(' params ')' block { $$ = new FunctionStmt($2, $4, std::unique_ptr<BlockStmt>($6)); };
   params
   : param_list | %empty { $$ = new std::vector<std::string>(); };
   param_list
   : param_list ',' id { $1->push_back($3); $$ = $1; }
   | id { $$ = new std::vector<string>(); $$->push_back($1); };
   return
   : RETURN expr ';' { $$ = new ReturnStmt(std::unique_ptr<Expr>($2)); }
   | RETURN ';' { $$ = new ReturnStmt(nullptr); };
   break
   : BREAK ';' { $$ = new BreakStmt(); };
   continue
   : CONTINUE ';' { $$ = new ContinueStmt(); };
   args
   : arg_list | %empty { $$ = new std::vector<Expr*>(); };
   arg_list
   : arg_list ',' expr { $1->push_back($3); $$ = $1; }
   | expr { $$ = new std::vector<Expr*>(); $$->push_back($1); };
   expr
   : or;
   or
   : or OR and { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), OR, std::unique_ptr<Expr>($3)); }
   | and;
   and
   : and AND cmp { $$ = new BinaryExpr(std::unique_ptr<Expr>($1),AND, std::unique_ptr<Expr>($3)); }
   | cmp;
   cmp
   : bit_or cmp_op bit_or { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), $2, std::unique_ptr<Expr>($3)); }
   | bit_or;
   cmp_op
   : EQ { $$ = EQ; }
   | NEQ { $$ = NEQ; }
   | '<' { $$ = '<'; }
   | LEQ { $$ = LEQ; }
   | '>' { $$ = '>'; }
   | GEQ { $$ = GEQ; };
   bit_or
   : bit_or '|' bit_xor { $$ = new BinaryExpr(std::unique_ptr<Expr>($1),'|', std::unique_ptr<Expr>($3)); }
   | bit_xor;
   bit_xor
   : bit_xor '^' bit_and { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '^', std::unique_ptr<Expr>($3)); }
   | bit_and;
   bit_and
   : bit_and '&' shift  { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '&', std::unique_ptr<Expr>($3)); }
   | shift;
   shift
   : shift SL additive { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), SL, std::unique_ptr<Expr>($3)); }
   | shift SR additive { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), SR, std::unique_ptr<Expr>($3)); }
   | additive;
   additive
   : additive '+' multiplicative { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '+', std::unique_ptr<Expr>($3)); }
   | additive '-' multiplicative  { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '-', std::unique_ptr<Expr>($3)); }
   | multiplicative;
   multiplicative
   : multiplicative '*' unary { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '*', std::unique_ptr<Expr>($3)); }
   | multiplicative '/' unary { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '/', std::unique_ptr<Expr>($3)); }
   | multiplicative '%' unary { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), '%', std::unique_ptr<Expr>($3)); }
   | unary;
   unary
   : '-' unary { $$ = new UnaryExpr(std::unique_ptr<Expr>($2), '-');}
      | '!' unary { $$ = new UnaryExpr(std::unique_ptr<Expr>($2), '!');}
      | '~' unary { $$ = new UnaryExpr(std::unique_ptr<Expr>($2), '~');}
      | power;
   power
   : postfix POW unary { $$ = new BinaryExpr(std::unique_ptr<Expr>($1), POW, std::unique_ptr<Expr>($3)); }
   | postfix;
   primary
   : id { $$ = new VariableExpr(std::string($1)); free($1);}
   | literal
   | '(' expr ')' {$$ = $2; }
   | array_lit;
   array_lit
   : '[' args ']' {
   std::vector<std::unique_ptr<Expr>> arguments;
   for(Expr* expr: *$2) {
   arguments.push_back(std::unique_ptr<Expr>(expr));
   }
   delete $2;
   $$ = new ArrayExpr(std::move(arguments));
   };
   id
   : IDENTIFIER { $$ = $1 };
   literal
   : NUMBER { $$ = new LiteralExpr($1);}
   | CHAR { $$ = new LiteralExpr($1);}
   | STRING { $$ = new LiteralExpr(std::string($1)); free($1);}
   | BOOLEAN {$$ = new LiteralExpr(static_cast<bool>($1));};

%%
void yyerror(const char *s) { fprintf(stderr, "line %d: %s\n", yylineno, s); }
int main(void) { return yyparse(); }


