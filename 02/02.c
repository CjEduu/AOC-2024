#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* input = fopen(argv[1],"r");
	char c;
	int n_safe = 0;
	int is_safe = 1;
	int is_first = 1;
	int need_slope = 0;
	int has_error = 0;
	size_t i_str = 0;
	char* num_str = malloc(3); // We assume nums are not longer that 2 ciphers
	int slope,diff,curr,prev;
	
	while((c = fgetc(input)) != EOF){
		if(c == '\n'){
			num_str[i_str] = '\0';
			curr = atoi(num_str);
			diff = curr-prev;
			if(has_error && ( abs(diff) > 3 | abs(diff)<1 ) ){
				is_safe = 0;
			}
			if( has_error && ( (slope == 0 && diff > 0) || (slope == 1 && diff < 0)) ) {
				is_safe = 0;
			}
			n_safe += is_safe;
			is_safe = 1;
			is_first = 1;
			i_str = 0;
			continue;
		}
		if(is_safe == 0){
			continue;
		}
		if(c == ' '){
			if(is_first){
				num_str[i_str] = '\0';	
				prev = atoi(num_str);
				i_str = 0;
				is_first = 0;
				need_slope = 1;
				has_error = 0;
			}
			else if(need_slope){
				num_str[i_str] = '\0';	
				curr = atoi(num_str);
				diff = curr - prev;
				if(abs(diff) > 3 | abs(diff)<1){
					if(has_error){
						is_safe = 0;
						continue;
					}
					has_error = 1;
					i_str = 0;
					prev = curr;
					continue;
				}
				slope = diff>0 ? 1:0 ;
				need_slope = 0;
				prev = curr;
				i_str = 0;
			}
			else{
				num_str[i_str] = '\0';
				curr = atoi(num_str);
				diff = curr-prev;

				if(abs(diff) > 3 | abs(diff)<1){
					if(has_error){
						is_safe = 0;
						continue;
					}
					has_error = 1;
					i_str = 0;
					prev = curr;
					continue;
				}

				if( (slope == 0 && diff > 0) || (slope == 1 && diff < 0) ) {
					if(has_error){
						is_safe = 0;
						continue;
					}
					has_error = 1;
					i_str = 0;
					prev = curr;
					continue;
				}
				prev = curr;
				i_str = 0;
			}
			continue;
		}
		num_str[i_str] = c;
		i_str++;
	}
	printf("Result part 2 = %d\n",n_safe);
}
