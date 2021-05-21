#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	DIR *p;
	struct dirent *d;
	char mydir[PATH_MAX];
	getcwd(mydir, sizeof(mydir));
	if(mydir == NULL){
		printf("Error %d: Cannot print directory. %s\n", errno, strerror(errno));
		exit(errno);
	}
	//directories not specified
	if(argc < 2){
		p = opendir(mydir);
		if(p == NULL)
		{
		  printf("Error %d: Cannot find directory. %s\n", errno, strerror(errno));
		  exit(errno);
		}
		if(strcmp(argv[argc - 1], "-a") == 0){	
			while(d = readdir(p)){
		  		printf("%s\t\t",d->d_name);
			}
			printf("\n");
		}
		else if(strcmp(argv[argc - 1], "-m") == 0){
			while(d = readdir(p)){
				if(d->d_name[0] != '.') {
		  			printf("%s, ",d->d_name);
				}
			}
			printf("\n");
		}
		else{
			while(d = readdir(p)){
				if(d->d_name[0] != '.')
		  			printf("%s\t\t",d->d_name);
			}
			printf("\n");
		}
	}
	//directories specified
	int multipledir = 0;
	if((argc > 2 && argv[argc - 1][0] != '-') || argc > 2){
		multipledir = 1;
	}
	for(int count = 0; count < argc - 1; count++) {
		getcwd(mydir, sizeof(mydir));
		strcat(mydir,"/");
		strcat(mydir, argv[count]);
		p = opendir(mydir);
		if(p == NULL)
		{
			printf("Error %d: Cannot find directory. %s\n", errno, strerror(errno));
		  	exit(errno);
		}
		if(multipledir == 1){
			printf("%s:\n", argv[count]);
		}
		if(strcmp(argv[argc - 1], "-a") == 0){	
			while(d = readdir(p)){
		  		printf("%s\t\t",d->d_name);
			}
			printf("\n");
		}
		else if(strcmp(argv[argc - 1], "-m") == 0){
			while(d = readdir(p)){
				if(d->d_name[0] != '.') {
		  			printf("%s, ",d->d_name);
				}
			}
			printf("\n");
		}
		else{
			// printf("I am here\n");
			while(d = readdir(p)){
				if(d->d_name[0] != '.')
		  			printf("%s\t\t",d->d_name);
			}
			printf("\n");
		}

	}
	free(d);
	free(p);
	exit(0);
}