%{

#include <kParser.hpp>
#include <kLexer.h>
#include <iostream>

using namespace std;

int kerror( yyscan_t scanner, int& result, const char* msg )
{
    cerr << "kerror called: '" << msg << "'" << endl;
    return 0;
}

%}

%code requires
{

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

#define YYSTYPE KSTYPE

}

%define api.prefix {k}
%define api.pure
%param { yyscan_t scanner }
%parse-param { int& result }

%union {
    int Number;
}

%token MUL
%token PLUS
%token <Number> NUMBER
%type <Number> Expression

%left PLUS
%left MUL

%%

Start: Expression[E] { result = $E; }
;

Expression: NUMBER[N] { $$ = $N; }
    | Expression[L] PLUS Expression[R] { $$ = $L + $R; }
    | Expression[L] MUL Expression[R] { $$ = $L * $R; }
;
