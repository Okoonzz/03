section .data
   userMsg db 'Please enter Sth: ' 
   lenUserMsg equ $-userMsg
   dispMsg db 'You have entered: '
   lenDispMsg equ $-dispMsg

section .bss
   num resb 16

section .text
   global _start

_start:
   mov eax, 4
   mov ebx, 1
   mov ecx, userMsg
   mov edx, lenUserMsg
   int 0x80

   ;Read and store the user input
   mov eax, 3
   mov ebx, 2
   mov ecx, num
   mov edx, 5
   int 0x80

   ;Output the message
   mov eax, 4
   mov ebx, 1
   mov ecx, dispMsg
   mov edx, lenDispMsg
   int 0x80

   ;Output the number entered
   mov eax, 4
   mov ebx, 1
   mov ecx, num
   mov edx, 16
   int 0x80

   ; Exit
   mov eax, 1
   mov ebx, 0
   int 0x80
