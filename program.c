#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "insertion.h"
#include "heap_sort.h"
#include "quick_sort.h"

#define LOW_PERCENTAGE 5
#define FILENAME1 "data1.txt"
#define FILENAME2 "data2.txt"
#define FILENAME3 "data3.txt"

/* Prototype Declarations START*/

void write_info(FILE *f, int set);
void print_array(int array[], int keys);
int randomInRange(int min, int max);
void set_A(int array[], int keys);
void set_B(int array[], int keys);
void set_C(int array[], int keys);
int int_safe_input(int *number);

/* Prototype Declarations END*/

/* Global Variables START*/

int sizes[] = {100000, 250000, 500000, 750000, 1000000, 1500000, 2000000};
int algorithm_choice = 0;
clock_t start, finish;
double elapsed;
size_t i;
char buffer[100];
FILE *f1, *f2, *f3;

/* Gloval Variables END*/
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("./program {algorithm_choice}");
        exit(EXIT_FAILURE);
    }

    algorithm_choice = atoi(argv[1]);

    if(algorithm_choice == 1){
        f1 = fopen(FILENAME1, "w");
        if(f1 == NULL){
            perror("Error opening data file");
            exit(EXIT_FAILURE);
        }
    }
    
    else if(algorithm_choice == 2){
        f2 = fopen(FILENAME2, "w");
        if(f2 == NULL){
            perror("Error opening data file");
            exit(EXIT_FAILURE);
        }
    }

    else{
        f3 = fopen(FILENAME3, "w");
        if(f3 == NULL){
            perror("Error opening data file");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < (sizeof(sizes) / sizeof(sizes[0])); i++){
        int *array = (int *)malloc(sizeof(int) * sizes[i]); 

        for(int j = 0; j < 3; j++){
            if(j == 0) set_A(array, sizes[i]);
            else if(j == 1) set_B(array, sizes[i]);
            else set_C(array, sizes[i]);
            
            if(algorithm_choice == 1){
                start = clock();
                insertion_sort(array, 0, sizes[i] - 1);
                finish = clock();
                write_info(f1, j);
            }
    
            else if(algorithm_choice == 2){
                start = clock();
                heap_sort(array, sizes[i]);
                finish = clock();
                write_info(f2, j);
            }
            
            else{
               start = clock();
                quick_sort(array, 0, sizes[i] - 1);
                finish = clock();
                write_info(f3, j); 
            }
        }
        
        free(array);
    }

    if(algorithm_choice == 1) fclose(f1);
    else if(algorithm_choice == 2) fclose(f2);
    else fclose(f3);
    
    return 0;
}

// Write which algorithm, execution time, which set and the size
void write_info(FILE *f, int set){
    elapsed = ((double) finish - start) / CLOCKS_PER_SEC;
    snprintf(buffer, sizeof(buffer), "%f %d %d", elapsed, set+1, sizes[i]);
    printf("%s\n", buffer);
    fprintf(f, "%s\n", buffer);
}

// Print each element of the array
void print_array(int array[], int keys){
    for(int i = 0; i < keys; i++){
        printf("%d\n", array[i]);
    }
}

// Random Number between min and max
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Ascending order set
void set_A(int array[], int keys){
    int num = 0;
    int index = 0;

    while(index < keys){
        array[index] = num;
        index++;
        
        if(randomInRange(1, 100) <= LOW_PERCENTAGE && index < keys){
            array[index] = num;
            index++;
        }

        num++;
    }
}

// Descending order set
void set_B(int array[], int keys){
    int num = keys - 1;
    int index = 0;

    while(index < keys){
        array[index] = num;
        index++;
        
        if(randomInRange(1, 100) <= LOW_PERCENTAGE && index < keys){
            array[index] = num;
            index++;
        }

        num--;
    }
}

// Random set
void set_C(int array[], int keys){
    int index = 0;

    while(index < keys){
        array[index] = rand() % 1000001;
        index++;
        
        if(randomInRange(1, 100) <= LOW_PERCENTAGE && index < keys){
            array[index] = array[index - 1];
            index++;
        }
    }
}