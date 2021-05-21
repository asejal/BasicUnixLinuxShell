#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]){
	int state;
	char reply;
	for(int count = 0; count < argc - 1; count++) {
		if(strcmp(argv[argc - 1], "-v") == 0){
			state = remove(argv[count]);
			if(state == 0){
                printf("removed '%s'\n", argv[count]);
	        }
	        else{
	            printf("Error %d: Cannot remove '%s'. %s\n", errno, argv[count], strerror(errno));
	            exit(errno);
	        }
		}
		else if(strcmp(argv[argc - 1], "-i") == 0){
			printf("remove file '%s'?\n", argv[count]);
			scanf(" %c", &reply);
			if(reply == 'Y' || reply == 'y'){
				state = remove(argv[count]);	
			}
		}
		else{
			if(strchr(argv[count], '\\') != NULL){
				char copy[200];
				int i;
				for(i = 0; argv[count][i]!='\0'; i++){
					if((int)(strchr(argv[count], '\\') - argv[count]) == i){
						copy[i] = ' ';
					}
					else{
						copy[i] = argv[count][i];
					}
				}
				copy[i] = '\0';
				state = remove(copy);
				if(state < 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(errno);
				}	
			}
			state = remove(argv[count]);
	        if(state != 0) {
	            printf("Error %d: Cannot remove '%s'. %s\n", errno, argv[count], strerror(errno));
	            exit(errno);
	        }
		}        
	}
	exit(0);
}