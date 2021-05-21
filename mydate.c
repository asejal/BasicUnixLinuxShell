#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<limits.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if(argc >1 && strcmp(argv[1], "-u") == 0){
	    char x[64];
	    tm->tm_hour += 7;
	    int chk = strftime(x, sizeof(x), "%a %b %d %l:%M:%S UTC %Y", tm);
	    if(chk == 0){
	    	printf("Error %d: %s\n", errno, strerror(errno));
	    	exit(errno);
	    }
	    printf("%s\n", x);
	}
	else if(argc > 2 && strcmp(argv[1], "-r") == 0){
		char mydir[PATH_MAX];
		getcwd(mydir, sizeof(mydir));
		char newdir[PATH_MAX];
		if(mydir == NULL){
			printf("Error %d: %s\n", errno, strerror(errno));
			exit(errno);
		}
		strcpy(newdir, mydir);
		strcat(newdir, "/");
		strcat(newdir, argv[2]);
		struct stat attr;
	    stat(newdir, &attr);
	    if(stat == 0){
	    	printf("Error %d: %s\n", errno, strerror(errno));
	    	exit(errno);
	    }
	    time_t tt = (time_t)ctime(&attr.st_mtime);
	    char y[64];
	    int chk = strftime(y, sizeof(y), "%a %b %d %l:%M:%S PDT %Y", tm);
	    if(chk == 0){
	    	printf("Error %d: %s\n", errno, strerror(errno));
	    	exit(errno);
	    }
	    printf("%s\n", y);
	}
	else{
	    char arr[64];
	    int chk = strftime(arr, sizeof(arr), "%a %b %d %l:%M:%S PDT %Y", tm);
	    if(chk == 0){
	    	printf("Error %d: %s\n", errno, strerror(errno));
	    	exit(errno);
	    }
	    printf("%s\n", arr);
	}
    exit(0);
}
