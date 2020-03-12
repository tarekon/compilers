#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

enum TCommand {
    C_Print,
};

unordered_map<string,TCommand> commandMap = {
    { "print", C_Print },
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

    cout << "Hello world";
    return 0;
}