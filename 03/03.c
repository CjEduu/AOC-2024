#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* input = fopen("input.txt","r");
	char pattern[4] = "mul(";
	char pattern_dont[7] = "don't()";
	char pattern_do[4] = "do()";
	char* num = malloc(10); // 9 digits max nums
	int num1,num2;
	
	int pattern_dont_index = 0;
	int pattern_do_index = 0;
	int pattern_mul = 0;
	int number_index = 0;
	size_t sum = 0;

	char c;
	while((c = fgetc(input))!=EOF){
		if(pattern_dont_index == 7){
			if(pattern_do_index == 4){
				pattern_dont_index = 0;
				pattern_do_index = 0;
				pattern_mul = 0;
				continue;
			}
			if(c == pattern_do[pattern_do_index]){
				pattern_do_index++;
				continue;
			}
			pattern_do_index = 0;
			continue;
		}
		if(pattern_mul == 4){
			if(c == ','){
				num[number_index] = '\0';
				if((num1 = atoi(num)) == 0){
					pattern_mul = 0;
				}
				else{
					pattern_mul = 5;
				}
				number_index = 0;
				continue;
			}
			if(!( c>=48 && c<=57)){
				pattern_mul = 0;
				number_index = 0;
				continue;
			}
			num[number_index] = c;
			number_index++;
			continue;
		}
		if(pattern_mul == 5){
			if(c == ')'){
				num[number_index] = '\0';
				if((num2 = atoi(num)) != 0){
					sum += num1 * num2;
				}
				pattern_mul = 0;
				number_index = 0;
				continue;

			}
			if(!( c>=48 && c<=57)){
				pattern_mul = 0;
				number_index = 0;
				continue;
			}
			num[number_index] = c;
			number_index++;
			continue;
		}
		
		// Pattern matching
		if(c == pattern[pattern_mul]){
			pattern_mul++;
			pattern_dont_index = 0;
			continue;
		}
		if(c == pattern_dont[pattern_dont_index]){
			pattern_dont_index++;
			pattern_mul = 0;
			continue;
		}
		pattern_mul = 0;
		pattern_dont_index = 0;
	}

	printf("Result %zu\n",sum);
	
}
