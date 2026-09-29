%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
char *unescape(const char *s, int len);
%}
%option noyywrap yylineno

%%

[ \t\r\n]+  ;
"//".*   ;
"if"  { return IF; }
"else"  {return ELSE;}
"let"  {return LET;}
"+="  {return PLUSEQUAL; }
"-="  {return MINUSEQUAL; }
"/="  {return DIVEQUAL; }
"*="  {return MULTEQUAL; }
"%="  {return MODEQUAL; }
"while" { return WHILE; }
"for" { return FOR; }
"func" { return FUNC; }
"return" {return RETURN; }
"break" { return BREAK; }
"continue" { return CONTINUE; }
"||" { return OR; }
"&&" { return AND; }
"==" { return EQ; }
"!=" { return NEQ; }
">=" { return GEQ; }
"<=" { return LEQ; }
"<<" { return SL; }
">>" { return SR; }
"**" { return POW; }
[(){}[\]=.;,<>!\|^\&\+\*%/~-] { return yytext[0]; }
\'([^'\\\n]|\\.)\'   { char *s = unescape(yytext + 1, yyleng - 2); yylval.ch = s[0]; free(s); return CHAR; }
\"([^"\\\n]|\\.)*\"  { yylval.str = unescape(yytext + 1, yyleng - 2); return STRING; }
[0-9]+(\.[0-9]+)?    { yylval.num = atof(yytext); return NUMBER; }
"true"   { yylval.boolean = 1; return BOOLEAN; }
"false"  { yylval.boolean = 0; return BOOLEAN; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFIER; }
\"([^"\\\n]|\\.)*        { fprintf(stderr, "line %d: unterminated str '%s'\n", yylineno, yytext); exit(1); }
.                    { fprintf(stderr, "line %d: unexpected '%s'\n", yylineno, yytext); exit(1); }

%%

char *unescape(const char *s, int len) {
    char *out = malloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '\\' && i + 1 < len) {
            i++;
            switch (s[i]) {
                case 'n':  out[j++] = '\n'; break;
                case 't':  out[j++] = '\t'; break;
                case '\\': out[j++] = '\\'; break;
                case '"':  out[j++] = '"';  break;
                case '\'': out[j++] = '\''; break;
                case '0':  out[j++] = '\0'; break;
                default:   out[j++] = s[i]; break;
            }
        } else {
            out[j++] = s[i];
        }
    }
    out[j] = '\0';
    return out;
}
