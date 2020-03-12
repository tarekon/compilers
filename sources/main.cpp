#include <iostream>

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc <= 1 || argc > 3 ) {
        cerr << "Invalid argument count" << endl;
        return -1;
    }

    

    cout << "Hello world";
    return 0;
}