.model flat,stdcall;
includelib kernel32.lib;
	ExitProcess PROTO : DWORD;
	MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096;

.DATA;
	MB_OK	EQU 0
	STR1 BYTE "Моя первая программа", 0
	STR2 BYTE "Hello World", 0
	HW DWORD ?

.code;

main PROC;
START :
		PUSH MB_OK
		PUSH OFFSET STR1
		PUSH OFFSET STR2
		PUSH HW
		CALL MessageBoxA

		Invoke MessageboxA, MB_OK, OFFSET STR1, OFFSET STR2, HW
	push -1;
	call ExitProcess;
main ENDP;

end main;