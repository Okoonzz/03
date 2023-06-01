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
    add eax, '0' ; convert Sth from func
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

    mov eax, 37 ; Magic num
    mov dword [ebp+16], eax
    mov eax, dword [ebp+16]
    add eax, eax
    mov [esp+20], eax
    mov ecx, [esp+20]
    sar ecx, 3
    mov eax, ecx
    mov [esp+24], eax
    mov edx, [esp+24]
    shl edx, 2
    mov ecx, edx
    mov [esp+8], ecx
    mov ecx, [esp+8]
    add ecx, 1
    add edx, 8
    xor ecx, 0
    mov dword [edx+esp+4], ecx
    mov ecx, dword [edx+esp+4]
    mov eax, ecx
    
    leave
    ret
;;; Nonsense or magic is up to each individual. ;;;
