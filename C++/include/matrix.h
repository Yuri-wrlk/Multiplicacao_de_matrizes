#include "header.h"
 using namespace std;
 
struct matrix {
    vector<unsigned long int> * matrix_a;
    vector<vector<unsigned long int>> * matrix_b;
    unsigned long int * val_c;
    int mat_dim;
    int j;
    int i;
};