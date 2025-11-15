// #include "unit_tests.h"

// TestSuite(student_tests, .timeout=TEST_TIMEOUT); 
#include "../include/hw7.h"
int main() {
    printf("=== Running All Script Tests ===\n");
    
  
    for (int i = 2; i <= 11; i++) {
        char filename[50];
        sprintf(filename, "../tests_aux/script%02d.txt", i);
        
        printf("Testing %s\n", filename);
        matrix_sf *result = execute_script_sf(filename);
        if (result) {
            printf("Result: ");
            print_matrix_sf(result);
            free(result);
        }
        printf("\n");
    }
    
    printf("complete\n");
    return 0;
}