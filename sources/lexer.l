%{

#include <kParser.hpp>
#include <iostream>

using namespace std;

%}

%option prefix="k"
%option reentrant noyywrap never-interactive nounistd

DIGIT [0-9]
NUMBER {DIGIT}+

%%

{NUMBER}        { cout << "NUMBER "; return NUMBER; }
"+"             { cout << "PLUS "; return PLUS; }
"*"             { cout << "MUL "; return MUL; }
" "             {}
