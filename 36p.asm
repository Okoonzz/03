global _start
_start:
        call func
        mov eax, 1
        mov ebx, 0
        int 0x80
func:
        push ebp
        mov ebp,  esp
        sub esp, 4
        mov [ebp], byte 'o'
        mov [ebp+1], byte 'h'
        mov eax, 4
        mov ebx, 1
        mov ecx, ebp
        mov edx, 4
        int 0x80
        leave
        ret
