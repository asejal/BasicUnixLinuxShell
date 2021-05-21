#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  FILE *file;
  char data[500];
  int count;
  int x;
  for(count = 0; count < argc - 1; count++) {
    if(argv[count][0] == '>'){
        //for creating file
        char name[100];
        int i;
        for(i = 0; argv[count][i+1] != '\0'; i++){
            name[i] = argv[count][i+1];
        }
        name[i] = '\0';
        // printf("Name is %s\n", name);
        file = fopen(name, "w");
        if(file == NULL){
            printf("Error %d: %s", errno, strerror(errno));
            exit(errno); 
        }
        printf("Enter contents to store in file '%s': \n", name);
        fgets(data, 500, stdin);
        fputs(data, file);
        fclose(file);
        continue;
    }
    if((file = fopen(argv[count], "r")) == NULL) {
        fprintf(stderr, "%s: %s : %s\n", argv[0], argv[count], strerror(errno)); //good thing
        exit(errno);
    }
    x = 1;
    if(argc > 1 && strcmp(argv[argc - 1],"-n") == 0){
        while(fgets(data, sizeof(data), file)){
            printf("%d\t%s", x++, data);
        }
    }
    else if(argc > 1 && strcmp(argv[argc - 1],"-b") == 0){
        while(fgets(data, sizeof(data), file)){
            if(strcmp(data, "\n") != 0)
                printf("%d\t%s", x++, data);
            else
                printf("\n");
        }
    }
    else{
        while(fgets(data, sizeof(data), file)){
            printf("%s", data);
        }
    }
    fclose(file);
  }
  exit(0);
}