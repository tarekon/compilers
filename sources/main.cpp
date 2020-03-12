#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include <kParser.hpp>
#include <kLexer.h>

using namespace std;

enum TCommand {
    C_Print,
    C_Lexer,
};

unordered_map<string,TCommand> commandMap = {
    { "print", C_Print },
    { "lexer", C_Lexer },
};

int main( int argc, char* argv[] )
{
    if( argc <= 1 || argc > 3 ) {
        cerr << "Invalid argument count" << endl;
        return -1;
    }

    string command = argv[1];
    string fileName = argv[2];

    auto cmd = commandMap.find( command );
    if( cmd == commandMap.end() ) {
        cerr << "Unknown command " << command << endl;
        return -2;
    }

    ifstream inputFileStream( fileName, ios::ios_base::in );
    if( !inputFileStream ) {
        cerr << "Unable to open file " << fileName << endl;
        return -3;
    }
    string content{ istreambuf_iterator<char>( inputFileStream ),
        istreambuf_iterator<char>() };

    if( cmd->second == C_Print ) {
        cout << content << endl;
        return 0;
    }

    yyscan_t lexer;
    if( klex_init( &lexer ) ) {
        cerr << "Unable to initialize lexer" << endl;
        return -4;
    }
    YY_BUFFER_STATE lexerState = k_scan_string( content.c_str(), lexer );
    if( cmd->second == C_Lexer ) {
        KSTYPE semanticValue;

        int code = klex( &semanticValue, lexer );
        while( code != 0 ) {
            if( code == NUMBER ) {
                cout << "<" << semanticValue.Number << "> ";
            }
            code = klex( &semanticValue, lexer );
        }
    }

    k_delete_buffer( lexerState, lexer );
    klex_destroy( lexer );

    return 0;
}