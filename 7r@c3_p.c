#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <stdio.h>
#include <sys/user.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>


const int long_size = sizeof(long);

void rev(char *str) {
    int i = 0;
    int j = strlen(str) -1;
    char tmp;
    for(; i < j; ++i, --j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

void getData(pid_t child, long addr, char *str, int len) {
    int i = 0; 
    int j = len / long_size;
    // use union to avoid "The strict aliasing rule"
    union u {
        long val;
        char chars[long_size];
    } data;
    while(i < j) {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * long_size, NULL);
        memcpy(str, data.chars, long_size);
        ++i;
        str += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * long_size, NULL);
        memcpy(str, data.chars, j);
    }
    str[len] = '\0';
}

void putData(pid_t child, long addr, char *str, int len) {
    int i = 0; 
    int j = len / long_size;
    // use union to avoid "The strict aliasing rule"
    union u {
        long val;
        char chars[long_size];
    } data;
    while(i < j) {
        memcpy(data.chars, str, long_size);
        ptrace(PTRACE_POKEDATA, child, addr + i * long_size, data.val);
        ++i;
        str += long_size;
    }
    j = len % long_size;
    if(j) {
        memcpy(data.chars, str, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * long_size, data.val);
    }
}

int main() {
    pid_t child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    } else {
        long orig_rax;
        long params[3];
        int status;
        char *str;
        int toggle = 0;
        while(1) {
            wait(&status);
            if(WIFEXITED(status)) break;
            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
            if(orig_rax == SYS_write) {
                if(toggle == 0) {
                    toggle = 1;
                    params[0] = ptrace(PTRACE_PEEKUSER, child, 8 * RDI, NULL);
                    params[1] = ptrace(PTRACE_PEEKUSER, child, 8 * RSI, NULL);
                    params[2] = ptrace(PTRACE_PEEKUSER, child, 8 * RDX, NULL);
                    str = (char *)calloc((params[2] + 1), sizeof(char));
                    getData(child, params[1], str, params[2]);
                    rev(str);
                    putData(child, params[1], str, params[2]);
                    free(str);
                } else {
                    toggle = 0;
                }
            }
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }
}
