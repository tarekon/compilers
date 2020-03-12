%{

#include <iostream>

using namespace std;

%}

%option prefix="k"
%option reentrant noyywrap never-interactive nounistd

DIGIT [0-9]
NUMBER {DIGIT}+

%%

{NUMBER}        { cout << "NUMBER "; }
"+"             { cout << "PLUS "; }
"*"             { cout << "MUL "; }
" "             {}
