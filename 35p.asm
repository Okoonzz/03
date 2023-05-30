global _start
section .text
_start:
        sub esp, 4
        mov [esp], byte 'O'
        mov [esp+1], dword "koon"
        mov [esp+6], word "zz"
        mov eax, 4 ; call sys_write
        mov ebx, 1
        mov ecx, esp ; pointer to some bytes
        mov edx, 8 ; len
        int 0x80 ; call perform
        mov eax, 1 ; exit
        mov ebx, 0
        int 0x80
