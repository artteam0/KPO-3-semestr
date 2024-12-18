.model flat,stdcall
includelib kernel32.lib
includelib user32.lib
ExitProcess PROTO :DWORD
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD
wsprintfA PROTO C :VARARG

.stack 4096

.data
    QQ BYTE "Результат: %d", 0
    BUF BYTE 256 DUP(0)
    num1 DWORD 5
    num2 DWORD 2
    MB_OK EQU 3
    STR_TITLE BYTE "Сложение 5 и 2", 0

.code
main PROC
START:
    mov EAX, num1
    mov EBX, num2
    add EAX, EBX

    push EAX
    push OFFSET QQ   
    push OFFSET BUF  
    call wsprintfA
    add ESP, 12

    push MB_OK
    push OFFSET STR_TITLE 
    push OFFSET BUF       
    push 0
    call MessageBoxA

    push 0
    call ExitProcess
main ENDP

end main
