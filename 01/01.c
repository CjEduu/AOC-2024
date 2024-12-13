#include <stdio.h>
#include <stdlib.h>

#define sizeof_arr(arr) sizeof(arr)/sizeof(arr[0])

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot element (last element)
    int i = low - 1;        // Index for smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {  // If current element is smaller than pivot
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // Place the pivot in the correct position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;  // Return the partition index
}

// Quicksort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Partition index

        // Recursively sort elements before and after partition
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}



int main(int argc,char* argv[]){

	printf("%d\n",argc);
	printf("%s\n",argv[1]);
	FILE* fd = fopen(argv[1],"r");
	char c;
	int* id1 = calloc(sizeof(int),1000);
	int* id2 = calloc(sizeof(int),1000); // nelms
	char* curr_num = calloc(sizeof(char),10);  // 9 cifras max
	int space = 0;
	size_t i = 0;
	size_t j = 0;

	while((c = fgetc(fd)) != EOF){
		switch(c){
			case ' ':
				if(space == 0){
					curr_num[j] = '\0';
					id1[i] = atoi(curr_num);
					space=1;
				}
				break;
			case '\n':
				curr_num[j] = '\0';
				id2[i]  = atoi(curr_num);
				i++;
				j=0;
				break;
			default:
				if(space == 1){
					j = 0;
					space = 0;
				}
				curr_num[j] = c;
				j++;
		}
	}

	quicksort(id1,0,999);
	quicksort(id2,0,999);
	
	i = 0;
	j = 0;
	for(i = 0; i<1000;i++){
		j += abs(id1[i] - id2[i]);
	}
	printf("Result Part 1 = %zu\n",j);
	
	size_t sim_score = 0;
	for(i = 0;i<1000;i++){
		j = 0;
		while(1){
			if(id1[i] == id2[j]){
				sim_score += id1[i];
			}
			if(id1[i] < id2[j]){
				break;
			}
			if(j==999){
				break;
			}
			j++;
		}
		if(j == 999) break;
	}
	printf("Result part 2 = %zu\n",sim_score);

	return 0;
}

