#include "header.h"

using namespace std;

bool ispowerof2(unsigned int x) {
   return x && !(x & (x - 1));
 }

void main(int argc, const char *argv[]){
    unsigned int mat_dimension;
    char run_mode;
    if(argc >= 2){
        
        mat_dimension = (unsigned int)argv[0];
        if(!ispowerof2(mat_dimension)){
            cout << ">>> The number received is not valid! It must be a power of 2 (such as 2, 4, 8, 16, 32...)" << endl;
            return EXIT_SUCCESS;    
        }
        
        run_mode = (char) argv[1];
        if(run_mode != 'S' or run_mode != 'C'){
            cout << ">>> The execution mode received is not valid! It must be either 'S' for sequential or 'C' for concurrent. "<< endl;
            return EXIT_SUCCESS;
        }

    } else {
        cout << ">>> Not enough arguments passed" << endl;
        cout << ">>> You should execute the program as ./multimat [number] [mode]" << endl;
        cout << ">>> [number] should be an integer that is 2 to the power of an integer" << 
        cout << " higher than 1 (as in 2, 4, 8, 16, 32...)." << endl;
        cout << ">>> [mode] should be either the letters S or C, for sequential and concurrent " <<
        cout << "execution, respectivelly." << endl;
        return EXIT_SUCCESS;
    }

    
}