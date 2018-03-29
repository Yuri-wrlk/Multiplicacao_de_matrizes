#include "header.h"

#define NUMTHREADS  2 

using namespace std;

phtread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *dummyPtr){
    printf("Thread number %ld\n", pthread_self());
    pthread_mutex_lock( &mutex1 );
    counter++;
    pthread_mutex_unlock( &mutex1 );
}

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

string create_file_names (char mat_letter, int mat_dim){
    stringstream stream_a;
    stream_a << "data/" << string(1, mat_letter) << mat_dim << "x" << mat_dim << ".txt";
    return stream_a.str();
}

vector<vector<unsigned long int>> create_matrix_from_files(string file_path, int mat_dimension, char mat_letter){
    
    ifstream file_mat;
    file_mat.open(file_path, ifstream::in);
    vector<vector<unsigned long int>> matrix(mat_dimension, vector<unsigned long int>(mat_dimension,1));        
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
                    
                    matrix[i][j] = stod(aux);
                }
            }
        }
        else {
            cout << ">>> Wrong file for Matrix " << mat_letter << " opened, the dimensions " << aux_dim_line << "x" <<
            aux_dim_col << " do not match with the arguments' dimensions: " << mat_dimension <<
            "x" << mat_dimension << endl;  
        }
        file_mat.close();
    }
    return matrix;
}

void write_matrix_to_file (vector<vector<unsigned long int>> matrix, char letter, int mat_dim){
    stringstream stream_a;
    stream_a << "data/" << string(1, letter) << mat_dim << "x" << mat_dim << ".txt";
    string file_name = stream_a.str();
    ofstream output_file;
    output_file.open(file_name, ofstream::trunc);
    output_file << mat_dim << " " << mat_dim << endl;

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            output_file << matrix[i][j];
            if(j != mat_dim - 1) output_file << " ";
        }
        output_file << endl;
    }
    output_file.close();
}

vector<vector<unsigned long int>> multiply_matrix_sequential (int mat_dim, vector<vector<unsigned long int>> matrix_a, vector<vector<unsigned long int>> matrix_b){
    vector<vector<unsigned long int>> matrix_c(mat_dim, vector<unsigned long int>(mat_dim,1));
    
    int aux = 0;
    for(int i = 0; i < mat_dim; i++){
        for(int j = 0; j < mat_dim; j++){
            matrix_c[i][j] = 0;
                for(int k = 0; k < mat_dim; k++){
                    aux += matrix_a[i][k] * matrix_b[k][j];
                }
            matrix_c[i][j] = aux;
            aux = 0;
        }
    }

    return matrix_c;
}

void * concurrent_calculation(void * arg){
    pthread_t thread_id[NUMTHREADS];
    
    for(int i = 0; i < NUMTHREADS; i++){
        pthread_create(&thread_id[i], NULL, thread_function, NULL);
    }
    /*for(int j = 0; j < NUMTHREADS; j++){
        pthread_join(thread_id[j], NULL);
    }*/
    struct matrix * data;
    data = (struct matrix *) arg;
    vector<unsigned long int> * matrix_a;
    matrix_a = data->matrix_a;
    vector<vector<unsigned long int>> * matrix_b;
    matrix_b = data->matrix_b;
    int aux = 0;
    
    for(int k = 0; k < data->mat_dim; k++){
        aux += matrix_a->at(k) * (matrix_b->at(k)).at(data->j);
    }
    *(data->val_c) = aux;
    //cout << "A thread da posição " << data->i << "x" << data->j <<" encerrou com valor " << aux << endl;
}

vector<vector<unsigned long int>> multiply_matrix_concurrent (int mat_dim, vector<vector<unsigned long int>> matrix_a, vector<vector<unsigned long int>> matrix_b){
    vector<pthread_t> threads(((unsigned long int)(mat_dim * mat_dim)));
    struct matrix * data = new struct matrix[(unsigned long int)(mat_dim * mat_dim)];
    vector<vector<unsigned long int>> matrix_c(mat_dim, vector<unsigned long int>(mat_dim,1));
    unsigned long int aux = 0;
    int result = 0;
    for(int i = 0; i < mat_dim; i++){
        for(int j = 0; j < mat_dim; j++){
            unsigned long int pos = (i * mat_dim) + j;
            data[pos].matrix_a = &matrix_a[i];
            data[pos].matrix_b = &matrix_b;
            data[pos].val_c = &(matrix_c[i][j]);
            data[pos].mat_dim = mat_dim;
            data[pos].j = j;
            data[pos].i = i;
            matrix_c[i][j] = 0;
            result = pthread_create(&(threads[pos]), NULL, concurrent_calculation, (void *)&(data[pos]));
            if(result){
                cout << ">>> Error: The thread of position " << i << "x" << j << "could not be created" << endl;

            }
        }
    }

    void * thread_result; 
    int * value_pos;   
    for(int i = 0; i < mat_dim; i++){
        for(int j = 0; j < mat_dim; j++){
            int pos = (i * mat_dim) + j;
            result = pthread_join(threads[pos], &thread_result);
			if (result) {
				cout << ">>> Error: incapable of joining thread " << i << "x" << j << endl;
			}
            
            value_pos = ((int *)data[pos].val_c);
            matrix_c[i][j] = *value_pos;
        }
    }
    return matrix_c;
}



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
    
    vector<vector<unsigned long int>> matrix_a;
    vector<vector<unsigned long int>> matrix_b;
    vector<vector<unsigned long int>> matrix_c;
    matrix_a = create_matrix_from_files(file_a, mat_dimension, 'A');
    matrix_b = create_matrix_from_files(file_b, mat_dimension, 'B');
    matrix_c = multiply_matrix_concurrent(mat_dimension, matrix_a, matrix_b);

    write_matrix_to_file(matrix_c, 'C', mat_dimension);
}