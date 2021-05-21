#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]){
	char mydir[PATH_MAX];
	getcwd(mydir, sizeof(mydir));
	if(mydir == NULL){
		printf("Error %d: Can't print directory. %s\n", errno, strerror(errno));
		exit(errno);
	}
	for(int count = 0; count < argc - 1; count++) {
		getcwd(mydir, sizeof(mydir));
		char newdir[PATH_MAX];
		if(strcmp(argv[argc - 1], "-v") == 0){
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
				strcpy(newdir, mydir);
				strcat(newdir, "/");
				strcat(newdir, copy);	
				int state = mkdir(newdir, 0700);
				printf("mkdir: created directory '%s'\n", copy);	
			}
			else{
				strcpy(newdir, mydir);
				strcat(newdir, "/");
				strcat(newdir, argv[count]);	
				int state = mkdir(newdir, 0700);
				if(state != 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(errno);
				}
				printf("mkdir: created directory '%s'\n", argv[count]);	
			}
		}	
		else if(strcmp(argv[argc - 1], "-p") == 0){
			char **data = malloc(200 * sizeof(char*));
			char *line = strtok(argv[count], "/");
			data[0] = mydir;
			int cntr = 1;
			struct stat st = {0};
			while(line != NULL){
				data[cntr] = data[cntr-1];
				strcat(data[cntr], "/");
				strcat(data[cntr], line);
				if (stat(data[cntr], &st) == -1) {
		   			int state = mkdir(data[cntr], 0700);
		   			if(state != 0){
						printf("Error %d: %s\n", errno, strerror(errno));
						exit(errno);
					}
				}
				line = strtok(NULL, "/");
				cntr++;
			}
			data[cntr] = NULL;	
			free(data);
			free(line);
		}
		else{
			strcpy(newdir, mydir);
			strcat(newdir, "/");
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
				strcat(newdir, copy);
				int state = mkdir(copy, 0700);
				if(state != 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(errno);
				}
			}
			else{
				strcat(newdir, argv[count]);	
				int state = mkdir(newdir, 0700);
				if(state != 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(errno);
				}
			}
		}
	}
	exit(0);
}