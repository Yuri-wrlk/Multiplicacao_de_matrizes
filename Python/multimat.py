import sys
import threading
import timeit
import threading
from math import pow

global_matrix_a = list()
global_matrix_b = list()
global_matrix_c = list()


class Thread_mat_mult (threading.Thread):
   def __init__(self,   row, col):
      threading.Thread.__init__(self)
      
      self.row = row
      self.col = col
   
   def run(self):
      calc_mat_value(self.row, self.col)
      

def calc_mat_value(row, col):
    result = 0
    
    
    for j in range(0, len(global_matrix_b[0])): 
        result += global_matrix_a[row][j] * global_matrix_b[j][col]
    global_matrix_c[row][col] = result
    

def valid_arguments(mat_dim, exec_type):
    valid_flag = True
    valid_range = [str(2**i) for i in range(2,12)]
    if mat_dim not in valid_range:
        print(">>> The number received is not valid! It must be a power of 2 between 4 or 2048 (such as 4, 8, 16, 32...)")
        valid_flag = False
    if exec_type != 'S' and exec_type != 'C':
        print(">>> The execution mode received is not valid! It must be either 'S' for sequential or 'C' for concurrent.")
        valid_flag = False
    return valid_flag


def multimatrix():
    zip_b = zip(*global_matrix_b)
    zip_b = list(zip_b)
    return [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) 
             for col_b in zip_b] for row_a in global_matrix_a]

def multimatrix_conc():
    threads = list()
    
    for idx_x, row in enumerate(global_matrix_a):
        for idx_y, col in enumerate(global_matrix_b):
            thread_aux = Thread_mat_mult(idx_x, idx_y)
            thread_aux.start()
            threads.append(thread_aux)

    for thread_elem in threads:
        thread_elem.join()

def read_matrix_from_file(matrix_line, matrix_col, letter):
    file_path = 'data/' + letter + matrix_line + 'x' + matrix_col + '.txt'
    file_object = open(file_path, 'r')
    dimensions = file_object.readline().split()
    if dimensions[0] != matrix_line or dimensions[1] != matrix_col:
        print(">>> Wrong file for Matrix " + letter + " opened, the dimensions " + dimensions[0] + "x" +\
            dimensions[1] + " do not match with the arguments' dimensions: " + matrix_line +\
            "x" + matrix_col)
        return None;
    else:
        matrix = list()
        
        for i in range(0,int(matrix_line)):
            string_row = file_object.readline().split()
            int_row = [int(i) for i in string_row]
            matrix.append(int_row)
        return matrix 
    
def write_matrix_to_file(matrix):
    file_path = "data/C" + str(len(matrix)) + 'x' + str(len(matrix[0])) + '.txt'
    file_output = open(file_path, "w")
    file_output.write(str(len(matrix)) + " " + str(len(matrix[0])) + "\n")
    for line in matrix:
        for value in line:
            file_output.write(str(value) + " ")
        file_output.write("\n")
    file_output.close()

def write_result_to_file(exec_type, mat_line, mat_col, mean_time):
    file_path = "data/Results.csv"
    file_output = open(file_path, "a")
    file_output.write(str(exec_type) + ", " + str(mat_line) + ", " + str(mat_col) + ", "+ str(mean_time) + "\n")

def execute_multiplications(  exec_type, number_exec):
    mean_time = 0
    time_accumulated = 0
    if exec_type == 'S':
        for i in range(0, number_exec):
            time_start = timeit.default_timer()
            matrix_c = multimatrix()
            time_end = timeit.default_timer()
            time_accumulated += time_end - time_start
        mean_time = time_accumulated/number_exec
    if exec_type == 'C':
        for i in range(0, number_exec):
            time_start = timeit.default_timer()
            multimatrix_conc()
            matrix_c = global_matrix_c
            time_end = timeit.default_timer()
            time_accumulated += time_end - time_start
        mean_time = time_accumulated/number_exec
    
    write_result_to_file(exec_type, str(len(global_matrix_a)), str(len(global_matrix_b[0])), mean_time)
    write_matrix_to_file(matrix_c)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(">>> Not enough arguments passed")
        print(">>> You should execute the program as ./multimat [number] [mode]")
        print(">>> [number] should be an integer that is 2 to the power of an integer")
        print(" higher or equal than 4 (as in 4, 8, 16, 32...).")
        print(">>> [mode] should be either the letters S or C, for sequential and concurrent ")
        print("execution, respectivelly.")
        sys.exit()
    
    mat_dim = sys.argv[1]
    exec_type = sys.argv[2]

    if valid_arguments(mat_dim, exec_type) == False:
        sys.exit()
    
    global_matrix_a = read_matrix_from_file(mat_dim, mat_dim, 'A')
    global_matrix_b = read_matrix_from_file(mat_dim, mat_dim, 'B')
    for i in range(0,int(mat_dim)):
        global_matrix_c.append(list([-1 for i in range(0,int(mat_dim))]))
    
    execute_multiplications(exec_type, 1)
    
    
    
    
