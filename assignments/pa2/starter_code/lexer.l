%{

// This section should contain any includes and global variables needed for lexing
#include "parser.tab.hh" //include the parser header so that we have access to the union and the token enum
#include <sstream>
#define YY_DECL extern "C" int yylex() //this is needed to use C-format code in C++

  static std::stringstream ss; // this is needed for lexing string literals
%}

%option noyywrap

%x strlit

%%
  /* You will need to decide which tokens you need for lexing.
  In general, any "word" or symbol which appears on its own in the code should become a token.
  For example, the word "int", used in variable declarations, should be a token. A semicolon should also be a token.
  You should define these tokens next to the "%token" directive in the parser file.
  */
"int"                     {return INT_TYPE;}
  /* fill in remaining data types */
"float"                   {return FLOAT_TYPE;}
"String"                  {return STRING_TYPE;}
"bool"                    {return BOOL_TYPE;}
"void"                    {return VOID_TYPE;}

";"                       {return SEMICOLON;}
"("                       {return LPAREN;}
  /* fill in remaining single-character symbols */
")"                       {return RPAREN;}
"{"                       {return LBRACE;}
"}"                       {return RBRACE;}
","                       {return COMMA;}

"if"                      {return IF;}
  /* fill in remaining single-word commands */
"else"                    {return ELSE;}
"while"                   {return WHILE;}
"break"                   {return BREAK;}
"return"                  {return RETURN;}

"="                       {return EQUALS_SIGN;}
  /* fill in remaining operators (arithmetic, logical, relational) */
"!"                       {return NOT;}
"<"                       {return LT;}
">"                       {return GT;}
"&&"                      {return AND;}
"||"                      {return OR;}
"<="                      {return LE;}
">="                      {return GE;}
"!="                      {return NE;}
"=="                      {return EE;}
"+"                       {return ARITH_PLUS;}
"-"                       {return ARITH_MINUS;}
"*"                       {return ARITH_TIMES;}
"/"                       {return ARITH_DIV;}
"%"                       {return ARITH_MOD;}

"..."                     {return VARIADIC;} //this is used for defining functions with a variable number of arguments in C-like syntax
[0-9]+                    {yylval.intval = atoi(yytext); return INT_LITERAL;}
  /* fill in remaining literals (except for the string literal, which is below */
[0-9]+\.[0-9]+            {yylval.fltval = atof(yytext); return FLOAT_LITERAL;}
"true"                    {yylval.boolval = true; return BOOL_LITERAL;}
"false"                    {yylval.boolval = false; return BOOL_LITERAL;}

  /* This is the string literal definition.
  You aren't required to change this at all, since it is somewhat beyond the scope of the material we're covering here.
  For a quick overview, this defines "strlit" to be start state, which means that any of the following patterns beginning with <strlit>
  can only be preceeded by another part of the string literal. This ends when "return" is called inside of the action, which happens when an end-quote is matched.
  */
\"                        { BEGIN strlit; ss.str(std::string()); /* build the string using an std::stringstream */}
<strlit>[^\\"\n]*         { ss << yytext;}
<strlit>\\n               { ss << '\n';}
<strlit>\\t               { ss << '\t';}
<strlit>\\[\\"]           { ss << yytext[1]; /*escaped quote or backslash*/ }
<strlit>\"                { yylval.strval = strdup((char *) ss.str().c_str()); BEGIN 0; return STRING_LITERAL; }
<strlit>\\.               { printf("Lexing error: invalid escape character '%s'\n", yytext); }
<strlit>\n                { printf("Lexing error: found newline in string\n"); }
  /* This concludes the string literal definition */	   

  /* Fill in a definition for a C-style identifier (like a variable or function name)
  These are strings of alphanumeric characters or underscores, but cannot begin with a number.
  For example: abc, _0a2, i are valid identifiers, but 0a is not (since it begins with a number).
  You should return a token specifying that you've matched an ID, as well as its name.
  */  
[A-z_][0-9A-z_]*          {yylval.strval = yytext; return ID;}
[ \t]                     {}
.                         {printf("Unrecognized character %c\n", *yytext);}
%%

/* int main(int argc, char **argv) {
  int tok;

  while((tok = yylex())) {
    printf("Read token %d", tok);
    if(tok == INT_LITERAL) printf(" = %d\n", yylval.intval);
    else if (tok == FLOAT_LITERAL) printf(" = %0.3f\n", yylval.fltval);
    else if (tok == STRING_LITERAL) printf(" = %s\n", yylval.strval);
    else if (tok == ID) printf(" called %s\n", yylval.strval);
    else printf("\n");
  }
} */

