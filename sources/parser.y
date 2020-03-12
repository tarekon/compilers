%{

#include <kLexer.h>
#include <iostream>

using namespace std;

int kerror( const char* msg )
{
    cerr << "kerror called: '" << msg << "'" << endl;
    return 0;
}

%}


%define api.prefix {k}
%define api.pure


%token MUL
%token PLUS
%token NUMBER

%%

Start: %empty