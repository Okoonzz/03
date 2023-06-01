;;;;; Something I have learned. ;;;;;
section .data
     message db 'iluv', 0
section .bss
     number resb 1
section .text
     global _start
_start:
    call magic
    mov ebx, eax
    add eax, 30h ; convert Sth from magic
    mov [number], eax

    mov eax, 4
    mov ebx, 1
    mov ecx, message
    mov edx, 5
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, number
    mov edx, 2
    int 0x80

    mov eax, 1
    int 0x80

magic:
    push ebp ; Cal Magic
    mov ebp, esp
    sub esp, 8

    mov eax, 25h ; Magic num
    mov dword [ebp+10h], eax
    mov eax, dword [ebp+10h]
    add eax, eax
    mov [esp+14h], eax
    xor ecx, ecx
    mov ecx, [esp+14h]
    sar ecx, 3
    mov eax, ecx
    mov dword [esp+18h], eax
    xor eax, eax
    mov edx, dword [esp+18h]
    shl edx, 2
    mov ecx, edx
    mov [esp+8], ecx
    xor ecx, ecx
    test cl, al
    jnz chek
    mov ecx, [esp+8]
    add ecx, 1
    add edx, 8
    xor ecx, 0
    mov dword [edx+esp+4], ecx
    mov ecx, dword [edx+esp+4]
    mov eax, ecx
    
    leave
    ret
  
chek:
    mov eax, 30h
    add eax, eax
    imul eax, 12h
    nop
    mov ecx, 05h
    div ecx

;;; Nonsense or magic is up to each individual. ;;;
