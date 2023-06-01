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
       
;;;;;;;something updated here;;;;;;;;;

global _start
_start:
        call func
        mov eax, 1
        mov ebx, 0
        int 0x80
func:
        push ebp
        mov ebp, esp
        sub esp, 4
        mov [esp], byte 'o'
        mov [esp+1], byte 'h'
        mov eax, 4
        mov ebx, 1
        mov ecx, esp
        mov edx, 2
        int 0x80
        mov esp, ebp
        pop ebp
        ret          
        
        
; first, pushing then mov esp, ebo is the same as instantiating the stack of that function to perform tasks on it
; then we sub it also means we are moving esp to the top of the main stack
; as for ‘leave’, it is the opposite to what we are doing before this in order to reallocate the stack of the called function
; now, backward mov is actually updating esp from the substitution (top of the stack), popping the first element of the stack is to make it ready for next calls.
