#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_SORT_SIZE 10000000

void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void printArrayToFile(int* arr, int size, const char* filename); 
int generateRandomNumber(int min, int max);
void fillArrayRandom(int* arr, long size);
double timeBetween (clock_t s, clock_t e);
double sortEvent();

int main(int argc, char* argv[]) {
    srand(time(NULL));

	int sampleSize;
	sscanf(argv[2] ,"%d", &sampleSize);

	double totalTime = 0.0;
	for(int i=0; i<sampleSize; i++){
		totalTime += sortEvent();	
	}
	
	printf("Average time of %s optimization: %f\n", argv[1], (totalTime / (double) sampleSize));
    return 0;
}

double sortEvent(){
	int* arr = malloc(ARRAY_SORT_SIZE*sizeof(int));
	
	for(long i=0; i<ARRAY_SORT_SIZE; i++){
		arr[i] = rand();
	}

	clock_t start = clock();
    quickSort(arr, 0, ARRAY_SORT_SIZE - 1);
    clock_t end = clock();
	return timeBetween(start, end);
}

double timeBetween (clock_t s, clock_t e) {
    return ((double)(e - s)) / CLOCKS_PER_SEC * 1000;
}

void fillArrayRandom(int* arr, long size){
    for(long i = 0; i < size; i++){
        arr[i] = rand();
    }   
}


// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}


// Function to print an array
void printArrayToFile(int* arr, int size, const char* filename) {
    FILE* file = fopen(filename, "w");

    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
     
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

// Partition function for Quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i+1] and arr[high] (or pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Quicksort algorithm
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
