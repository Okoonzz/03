#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        puts("Error");
        return 1;
    }
    int id = fork();
    if(id == 0){
        int x;
        puts("Enter numvber");
        scanf("%i", &x);
        write(fd[1], &x, sizeof(int));
        // read(fd[0], &x, sizeof(int));
        close(fd[0]);
    }
    else if (id > 0){
        int y;
        read(fd[0], &y, sizeof(int));
        // write(fd[1], &y, sizeof(int));
        close(fd[1]);
        printf("Number u just enter is: %i\n", y);
    }
}


// Second

int main(int argc, char *argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        puts("Error");
        return 1;
    }
    int id = fork();
    if(id == 0){
        int x;
        puts("Enter numvber");
        scanf("%i", &x);
        // write(fd[1], &x, sizeof(int));
        read(fd[0], &x, sizeof(int));
        close(fd[0]);
    }
    else if (id > 0){
        int y;
        // read(fd[0], &y, sizeof(int));
        write(fd[1], &y, sizeof(int));
        close(fd[1]);
        printf("Number u just enter is: %i\n", y);
    }
}
