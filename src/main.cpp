#include "header.h"

using namespace std;

bool is_power_of2(unsigned int x) {
   return x && !(x & (x - 1));
 }

bool check_valid_arguments(unsigned int mat_dimension, char run_mode){
    bool flag = true;
    if(!is_power_of2(mat_dimension)){
        cout << ">>> The number received is not valid! It must be a power of 2 (such as 2, 4, 8, 16, 32...)" << endl;    
        flag = false;
    }
    if(run_mode != 'S' && run_mode != 'C'){
        cout << ">>> The execution mode received is not valid! It must be either 'S' for sequential or 'C' for concurrent. "<< endl;
        flag = false;
    }
    return flag;
}

void print_error_message(){
    cout << ">>> Not enough arguments passed" << endl;
    cout << ">>> You should execute the program as ./multimat [number] [mode]" << endl;
    cout << ">>> [number] should be an integer that is 2 to the power of an integer";
    cout << " higher than 1 (as in 2, 4, 8, 16, 32...)." << endl;
    cout << ">>> [mode] should be either the letters S or C, for sequential and concurrent ";
    cout << "execution, respectivelly." << endl;
}

string create_file_names (char mat_letter, int mat_size){
    stringstream stream_a;
    stream_a << "../data/" << string(1, mat_letter) << mat_size << "x" << mat_size << ".txt";
    return stream_a.str();
}

//bool createfilenames (string &)

int main(int argc, const char *argv[]){
    unsigned int mat_dimension;
    char run_mode;
    if(argc >= 3){
        mat_dimension = strtoul(argv[1], NULL, 10);
        run_mode = *argv[2];
        if(!check_valid_arguments(mat_dimension, run_mode)){
            return EXIT_SUCCESS;
        }
    } else {
        print_error_message();
        return EXIT_SUCCESS;
    }
    string file_a, file_b;
    file_a = create_file_names('A', mat_dimension);
    file_b = create_file_names('B', mat_dimension);

}