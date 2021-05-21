#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<limits.h>
#include<errno.h>

#define mypath "/home/aditisejal/Documents/Cfiles/Assignment1/Task/"
char temppath[PATH_MAX];
int exstat = 1;
int wantexit = 0;

char *reader(){
	char *str;
	str = readline(">> "); 
    if (strlen(str) != 0 && str[0]!='\0') { //strlen != 0
    	strcpy(temppath, mypath);
    	strcat(temppath, "myhistory.txt");
    	FILE *fptr = fopen(temppath, "a");
    	if(fptr == NULL){
    		printf("Error %d: %s\n", errno, strerror(errno));
    		return NULL;
    	}
		fprintf(fptr,"%s\n",str);
		fclose(fptr);
        return str; 
    } 
    else {
        return NULL; 
    }
}

char **parser(char *toparse){
	if(strlen(toparse) > 200){
		printf("Error: Unrecognized Input. Acceptable length of commands <200 characters\n");
		return NULL;
	}
	char **data = malloc(200 * sizeof(char*));
	char *line = strtok(toparse, " \n\t\r");
	int cntr = 0;
	while(line != NULL){
		data[cntr++] = line;
		line = strtok(NULL, " \n\t\r");
	}
	data[cntr] = NULL;
	return data;
}

int doexit(char **tokens){
	if(tokens[1] != NULL){
		for(int i = 0; tokens[1][i] != '\0'; i++){
			if(!isdigit(tokens[1][i])){
				printf("Error: Enter valid integer argument (0 - 255) in exit\n");
				wantexit = 0;
				return 1;
			}
		}
		// printf("%d\n", atoi(tokens[1]));
		if(atoi(tokens[1]) < 256 && atoi(tokens[1]) >= 0)
			return atoi(tokens[1]);
		else{
			printf("Error: Enter valid integer argument (0 -255) in exit\n");
			wantexit = 0;
			return 1;
		}

	}
	else{
		return 0;
	}
}

int dopwd(char **tokens){
	char mydir[PATH_MAX];
	getcwd(mydir, sizeof(mydir));
	if(mydir == NULL){
		printf("Error %d: Can't print directory. %s\n", errno, strerror(errno));
		return errno;
	}
	if(tokens[1] == NULL || ((strcmp(tokens[1], "-L") == 0) && tokens[2] == NULL))
		printf("Current working directory: %s\n", mydir);
	else if(strcmp(tokens[1], "--help") == 0){
		FILE *fptr; 
		char c; 
		strcpy(temppath, mypath);
    	strcat(temppath, "pwdhelp.txt");
		fptr = fopen(temppath, "r");
		if (fptr == NULL) { 
        	printf("Error %d: Can't show help. %s\n", errno, strerror(errno));
    		return errno;
    	} 
    	c = fgetc(fptr); 
    	while (c != EOF) { 
		    printf ("%c", c); 
			c = fgetc(fptr); 
		}
		printf("\n"); 
  		fclose(fptr); 
  		return 1;
	}
	else{
		printf("Error: Unrecognized Input\n");
		return 1;
	}
	return 1;
}

int docd(char **tokens){
	if(tokens[1] == NULL || ((strcmp(tokens[1], "-L") == 0) && tokens[2] == NULL)){
		char mydir[PATH_MAX];
		getcwd(mydir, sizeof(mydir));
		while(strcmp(mydir, "/") != 0){
			int stat = chdir("..");
			if(stat < 0){
			printf("Error %d: Enter valid directory. %s\n", errno, strerror(errno));
			return errno;
			}
			getcwd(mydir, sizeof(mydir));
		}
		return 1;
	}
	else {
		if((strcmp(tokens[1], "-L") == 0) && tokens[2] != NULL){
			if(strchr(tokens[2], '\\') != NULL){
				char copy[200];
				int i;
				for(i = 0; tokens[2][i]!='\0'; i++){
					if((int)(strchr(tokens[2], '\\') - tokens[2]) == i){
						copy[i] = ' ';
					}
					else{
						copy[i] = tokens[2][i];
					}
				}
				copy[i] = '\0';
				int stat = chdir(copy);
				if(stat < 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					return errno;
				}
				return 1;	
			}
			int stat = chdir(tokens[2]);
			if(stat < 0){
				printf("Error %d: Enter valid directory. %s\n", errno, strerror(errno));
				return errno;
			}
			return 1;
		}
		else if(strcmp(tokens[1], "--help") == 0){
			FILE *fptr; 
			char c; 
			strcpy(temppath, mypath);
    		strcat(temppath, "cdhelp.txt");
			fptr = fopen(temppath, "r");
			if (fptr == NULL) { 
        		printf("Error %d: %s\n", errno, strerror(errno));
        		return errno; 
    		} 
    		c = fgetc(fptr); 
    		while (c != EOF) { 
		        printf ("%c", c); 
		        c = fgetc(fptr); 
		    } 
		    printf("\n");
  		    fclose(fptr); 
  		    return 1;
		}
		else{
			if(strchr(tokens[1], '\\') != NULL){
				char copy[200];
				int i;
				for(i = 0; tokens[1][i]!='\0'; i++){
					if((int)(strchr(tokens[1], '\\') - tokens[1]) == i){
						copy[i] = ' ';
					}
					else{
						copy[i] = tokens[1][i];
					}
				}
				copy[i] = '\0';
				int stat = chdir(copy);
				if(stat < 0){
					printf("Error %d: %s\n", errno, strerror(errno));
					return errno;
				}
				return 1;	
			}
			int stat = chdir(tokens[1]);
			if(stat < 0){
				printf("Error %d: %s\n", errno, strerror(errno));
				return errno;
			}
			return 1;
		}
	}
}

int dohistory(char **tokens){
	if(tokens[1] != NULL && strcmp(tokens[1], "!!") == 0){	
		HIST_ENTRY *entry = history_get(where_history());
		printf("history %s\n", entry->line);
		free_history_entry(entry);		
	}
	else if(tokens[1] != NULL && strcmp(tokens[1], "-c") == 0){
		strcpy(temppath, mypath);
    	strcat(temppath, "myhistory.txt");
		remove(temppath);
	}
	else if(tokens[2] != NULL && (tokens[1] != NULL && strcmp(tokens[1], "-d") == 0)){
		int y;
		sscanf(tokens[2], "%d", &y);
		strcpy(temppath, mypath);
    	strcat(temppath, "myhistory.txt");
    	FILE *fptr1 = fopen(temppath, "r");
        if (!fptr1) 
		{	printf("Error %d: %s\n", errno, strerror(errno));
    		return errno; 
        }
        char tp[PATH_MAX];
        strcpy(tp, mypath);
    	strcat(tp, "newhistory.txt");
        FILE *fptr2 = fopen(tp, "w");
        if (!fptr2) 
		{
               printf("Error %d: %s\n", errno, strerror(errno));
                return errno;
        }
        int ctr = 1;
        char str1[200];
        str1[0] = 0;
         while ((fgets(str1, 200, fptr1)) != NULL) {
        	if(ctr != y){
        		fputs(str1, fptr2);
        	}
        	ctr++;
        }
        if(ctr < y){
        	printf("Error 1: Invalid offset\n");
        	return 1;
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(temppath);
        rename(tp, temppath);
	}
	else{
		strcpy(temppath, mypath);
    	strcat(temppath, "myhistory.txt");
    	FILE *fptr = fopen(temppath, "r");
    	if (!fptr) 
		{
               printf("Error %d: %s\n", errno, strerror(errno));
                return errno;
        }
		char str[200];
		rewind(fptr);
		int n = 0;
		while(fgets(str, 200, fptr))
			printf("%d\t%s", ++n, str);
		fclose(fptr);
	}
	return 1;
}

int doecho(char **tokens){
	if(tokens[1] == NULL){
		printf("\n");
		return 1;
	}
	else if(strcmp(tokens[1], "-n") == 0 && tokens[2] == NULL){
		return 1;
	}
	else{
		int flag = 25;
		int i = 1;
		if(strcmp(tokens[1], "-n") == 0){
			flag = 99;
			i = 2;
		}
		else if(strcmp(tokens[1], "-E") == 0){
			flag = 75;
			i = 2;
		}
		int quotes;		
		while(tokens[i] != NULL){
			quotes = 0;
			for(int j = 0; tokens[i][j]!='\0'; j++){
				if((tokens[i][j] == '\\' && tokens[i][j+1] != ' ') && quotes == 0){
					continue;
				}
				if(j == 0 && tokens[i][j] == '"'){
					quotes = 1;
					continue;
				}
				else if(j == strlen(tokens[i])-1 && tokens[i][j] == '"'){
					continue;
				}
				else{
					printf("%c", tokens[i][j]);
				}
			}
			printf(" ");
			i++;
		}
		if(flag != 99)
			printf("\n");
		return 1;
	}
}

int dols(char **tokens){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		//error ocurred
		fprintf(stderr, "Fork Failed");
		return errno;
	}
	else if(pid == 0){
		//child process
		char **args = malloc(200 * sizeof(char*));
		int numargs = 0;
		char *flag;
		for(int i = 1; tokens[i]!=NULL; i++){
			if(strcmp(tokens[i], "-a") == 0){
				flag = "-a";
			}
			else if(strcmp(tokens[i], "-m") == 0){
				flag = "-m";
			}
			else{
				args[numargs++] = tokens[i];
			}
		}
		args[numargs] = flag;
		strcpy(temppath, mypath);
    	strcat(temppath, "myls");
		int state = execv(temppath, args);
		if(state < 0){
			printf("Error %d: %s\n", errno, strerror(errno));
    		exit(errno);
		}
	}
	else{
		// parent process
		int status;
		wait(&status);
		if(WIFEXITED(status))
        	printf("Child exited with exit code %d\n",WEXITSTATUS(status));
	}
	return 1;
}

int domkdir(char **tokens){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		//error ocurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		//child process
		//for space in dir name, use backslash for -v and defualt options
		char **args = malloc(200 * sizeof(char*));
		int numargs = 0;
		char *flag;
		for(int i = 1; tokens[i]!=NULL; i++){
			if(strcmp(tokens[i], "-v") == 0){
				flag = "-v";
			}
			else if(strcmp(tokens[i], "-p") == 0){
				flag = "-p";
			}
			else{
				args[numargs++] = tokens[i];
			}
		}
		args[numargs] = flag;
		strcpy(temppath, mypath);
    	strcat(temppath, "mymkdir");
		int state = execv(temppath, args);
		if(state < 0){
			printf("Error %d: %s\n", errno, strerror(errno));
    		exit(errno);
		}
		exit(0);
	}
	else{
		// parent process
		int status;
		wait(&status);
		if(WIFEXITED(status))
        	printf("Child exited with exit code %d\n",WEXITSTATUS(status));
	}
	return 1;
}

int docat(char **tokens){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		//error ocurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		//child process
		char **args = malloc(200 * sizeof(char*));
		int numargs = 0;
		char *flag;
		for(int i = 1; tokens[i]!=NULL; i++){
			if(strcmp(tokens[i], "-n") == 0){
				flag = "-n";
			}
			else if(strcmp(tokens[i], "-b") == 0){
				flag = "-b";
			}
			else{
				args[numargs++] = tokens[i];
			}
		}
		args[numargs] = flag;
		strcpy(temppath, mypath);
    	strcat(temppath, "mycat");
		int state = execv(temppath, args);
		if(state < 0){
			printf("Error %d: %s\n", errno, strerror(errno));
    		exit(errno);
		}
		exit(0);
	}
	else{
		// parent process
		int status;
		wait(&status);
		if(WIFEXITED(status))
        	printf("Child exited with exit code %d\n",WEXITSTATUS(status));
	}
	return 1;
}

int dorm(char **tokens){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		//error ocurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		//child process
		char **args = malloc(200 * sizeof(char*));
		int numargs = 0;
		char *flag;
		for(int i = 1; tokens[i]!=NULL; i++){
			printf("%s\n", tokens[i]);
			if(strcmp(tokens[i], "-i") == 0){
				flag = "-i";
			}
			else if(strcmp(tokens[i], "-v") == 0){
				flag = "-v";
			}
			else{
				args[numargs++] = tokens[i];
			}
		}
		args[numargs] = flag;
		strcpy(temppath, mypath);
    	strcat(temppath, "myrm");
		int state = execv(temppath, args);
		if(state < 0){
			printf("Error %d: %s\n", errno, strerror(errno));
    		exit(errno);
		}
		exit(0);
	}
	else{
		// parent process;
		int status;
		wait(&status);
		if(WIFEXITED(status))
        	printf("Child exited with exit code %d\n",WEXITSTATUS(status));
	}
	return 1;
}

int dodate(char **tokens){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		//error ocurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		//child process
		strcpy(temppath, mypath);
    	strcat(temppath, "mydate");
		if(tokens[1] != NULL && strcmp(tokens[1], "-u") == 0){
			int state = execlp(temppath, "mydate", tokens[1], NULL);
			if(state < 0){
				printf("Error %d: %s\n", errno, strerror(errno));
	    		exit(errno);
			}
		}
		if(tokens[2] != NULL && (tokens[1] != NULL && strcmp(tokens[1], "-r") == 0)){
			int state = execlp(temppath, "mydate", tokens[1], tokens[2], NULL);
			if(state < 0){
				printf("Error %d: %s\n", errno, strerror(errno));
	    		exit(errno);
			}
		}
		else{
			int state = execlp(temppath, "mydate", NULL);
			if(state < 0){
				printf("Error %d: %s\n", errno, strerror(errno));
	    		exit(errno);
			}
		}
		exit(0);
	}
	else{
		// parent process
		int status;
		wait(&status);
		if(WIFEXITED(status))
        	printf("Child exited with exit code %d\n",WEXITSTATUS(status));
	}
	return 1;
}

int docommand(char **tokens){
	if(tokens[0] == NULL){
		printf("Error: Unrecognised Input\n");
		return 1;
	}
	else{
		if(strcmp(tokens[0], "exit") == 0){	//should implement number wala return exit[1]
			wantexit = 1;
			return doexit(tokens);
		}
		else if(strcmp(tokens[0], "pwd") == 0){
			return dopwd(tokens);
		}
		else if(strcmp(tokens[0], "cd") == 0){	
			return docd(tokens);
		}
		else if(strcmp(tokens[0], "history") == 0){	
			return dohistory(tokens);
		}
		else if(strcmp(tokens[0], "echo") == 0){ 
			return doecho(tokens);
		}
		else if(strcmp(tokens[0], "ls") == 0){	
			return dols(tokens);
		}
		else if(strcmp(tokens[0], "mkdir") == 0){
			return domkdir(tokens);
		}
		else if(strcmp(tokens[0], "cat") == 0){
			return docat(tokens);
		}
		else if(strcmp(tokens[0], "rm") == 0){
			return dorm(tokens);
		}
		else if(strcmp(tokens[0], "date") == 0){
			return dodate(tokens);
		}
		else{
			printf("Error: Enter valid command\n");
			return 1;
		}
	}
}

int main(){
	printf("Starting shell...\n");
	char *input;
	char **tokdeets;
	while(exstat){
		input = reader();
		if(input == NULL){
			printf("Error: Enter valid input\n");
			continue;
		}
		add_history(input);
		tokdeets = parser(input);
		if(tokdeets == NULL){
			printf("Error: Enter valid input\n");
			continue;
		}
		exstat = docommand(tokdeets);
		if(exstat == 0 || wantexit == 1){
			goto _exit;
		}
	}
	_exit: free(input);
	free(tokdeets);
	printf("Exit status: %d\n", exstat);
	printf("Terminating shell...\n");
	return 0;
}
