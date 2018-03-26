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
    stream_a << "data/" << string(1, mat_letter) << mat_size << "x" << mat_size << ".txt";
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
    vector<vector<double>> matrix_a(mat_dimension, vector<double>(mat_dimension,1));
    vector<vector<double>> matrix_b(mat_dimension, vector<double>(mat_dimension,1));
    for(int count = 0; count < 2; count++){
        ifstream file_mat;
        if(count == 0) file_mat.open(file_a, ifstream::in);
        else if(count == 1) file_mat.open(file_b, ifstream::in);
        
        if(!file_mat.eof()){
            string line;
        
            getline(file_mat, line);

            istringstream dim_line(line);

            string aux_dim_line, aux_dim_col;
            dim_line >> aux_dim_line;
            dim_line >> aux_dim_col;

            if (aux_dim_line == to_string(mat_dimension) && aux_dim_col == to_string(mat_dimension)){
                string aux;
                for(int i = 0; i < mat_dimension; i++){
                    getline(file_mat, line);
                    stringstream value_line(line);
                    for(int j = 0; j < mat_dimension; j++){
                        value_line >> aux;
                        if(count == 0)
                            matrix_a[i][j] = stod(aux);
                        if(count == 1)
                            matrix_b[i][j] = stod(aux);
                    }
                }
            }
            else {
                char mat_letter;
                if (count == 0) mat_letter = 'A';
                if (count == 1) mat_letter = 'B';
                cout << ">>> Wrong file for Matrix " << mat_letter << " opened, the dimensions " << aux_dim_line << "x" <<
                aux_dim_col << " do not match with the arguments' dimensions: " << mat_dimension <<
                "x" << mat_dimension << endl;
                return EXIT_SUCCESS;  
            }
            file_mat.close();
        }
    }

    cout << matrix_a[mat_dimension -1][mat_dimension -1] << endl;
    cout << matrix_b[mat_dimension -1][mat_dimension -1] << endl;
}