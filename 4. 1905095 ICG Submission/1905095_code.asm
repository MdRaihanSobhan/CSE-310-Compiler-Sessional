.MODEL SMALL
.STACK 100h
.DATA
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
	
.CODE
; line no: 1 , Definition of Function func begins

	func PROC
		PUSH BP
		MOV BP, SP
		SUB SP,2
		PUSH W. [BP + 6]
; line no: 3 , n stored

; line no: 3 , Store 0

		PUSH 0
; line no: 3 , n == 0

		POP BX
; line no: 3 , 0 loaded

		POP AX
; line no: 3 , n loaded

		CMP AX, BX
		JE L0
			PUSH 0
			JMP L1
		L0:
			PUSH 1
		L1:

		POP AX
; line no: 3 , n == 0 loaded

		CMP AX, 0
; line no: 3 , If block begins

		JE END_IF_2
; line no: 3 , Store 0

		PUSH 0
		POP AX
; line no: 3 , 0 loaded

		MOV [BP+4], AX
; line no: 3 , Removing all internal variables from stack

		ADD SP, 2
		POP BP
		RET
; line no: 3 , If block ends

		END_IF_2:

		PUSH W. [BP + 6]
; line no: 4 , n stored

; line no: 4 , i = n

		POP AX
; line no: 4 , n loaded

		MOV W.[BP-2], AX
		PUSH AX
		POP AX
; line no: 4 , evaluated expression: i = n;


		PUSH W. [BP + 6]
; line no: 5 , n stored

; line no: 5 , Store 1

		PUSH 1
; line no: 5 , n - 1

		POP BX
; line no: 5 , 1 loaded

		POP AX
; line no: 5 , n loaded

		SUB AX, BX
		PUSH AX
; line no: 5 , n stored

; line no: 5 , For return value

		PUSH 0
; line no: 5 , Calling function func

		CALL func
		POP AX
; line no: 5 , Return value loaded

; line no: 5 , Now removing function parameters from the stack

		ADD SP,2
; line no: 5 , Return value stored 

		PUSH AX
		PUSH W.[BP-2]
; line no: 5 , i stored

; line no: 5 , func(n - 1) + i

		POP BX
; line no: 5 , i loaded

		POP AX
; line no: 5 , func(n - 1) loaded

		ADD AX, BX
		PUSH AX
; line no: 5 , func(n - 1) stored

		POP AX
; line no: 5 , func(n - 1) + i loaded

		MOV [BP+4], AX
; line no: 5 , Removing all internal variables from stack

		ADD SP, 2
		POP BP
		RET
		POP BP
		RET
	func ENDP

; line no: 6 , Definition of Function func ends

; line no: 8 , Definition of Function func2 begins

	func2 PROC
		PUSH BP
		MOV BP, SP
		SUB SP,2
		PUSH W. [BP + 6]
; line no: 10 , n stored

; line no: 10 , Store 0

		PUSH 0
; line no: 10 , n == 0

		POP BX
; line no: 10 , 0 loaded

		POP AX
; line no: 10 , n loaded

		CMP AX, BX
		JE L3
			PUSH 0
			JMP L4
		L3:
			PUSH 1
		L4:

		POP AX
; line no: 10 , n == 0 loaded

		CMP AX, 0
; line no: 10 , If block begins

		JE END_IF_5
; line no: 10 , Store 0

		PUSH 0
		POP AX
; line no: 10 , 0 loaded

		MOV [BP+4], AX
; line no: 10 , Removing all internal variables from stack

		ADD SP, 2
		POP BP
		RET
; line no: 10 , If block ends

		END_IF_5:

		PUSH W. [BP + 6]
; line no: 11 , n stored

; line no: 11 , i = n

		POP AX
; line no: 11 , n loaded

		MOV W.[BP-2], AX
		PUSH AX
		POP AX
; line no: 11 , evaluated expression: i = n;


		PUSH W. [BP + 6]
; line no: 12 , n stored

; line no: 12 , Store 1

		PUSH 1
; line no: 12 , n - 1

		POP BX
; line no: 12 , 1 loaded

		POP AX
; line no: 12 , n loaded

		SUB AX, BX
		PUSH AX
; line no: 12 , n stored

; line no: 12 , For return value

		PUSH 0
; line no: 12 , Calling function func

		CALL func
		POP AX
; line no: 12 , Return value loaded

; line no: 12 , Now removing function parameters from the stack

		ADD SP,2
; line no: 12 , Return value stored 

		PUSH AX
		PUSH W.[BP-2]
; line no: 12 , i stored

; line no: 12 , func(n - 1) + i

		POP BX
; line no: 12 , i loaded

		POP AX
; line no: 12 , func(n - 1) loaded

		ADD AX, BX
		PUSH AX
; line no: 12 , func(n - 1) stored

		POP AX
; line no: 12 , func(n - 1) + i loaded

		MOV [BP+4], AX
; line no: 12 , Removing all internal variables from stack

		ADD SP, 2
		POP BP
		RET
		POP BP
		RET
	func2 ENDP

; line no: 13 , Definition of Function func2 ends

; line no: 15 , Definition of Function main begins

	main PROC
		MOV AX, @DATA
		mov DS, AX
		MOV BP, SP
		SUB SP,2
; line no: 17 , Store 7

		PUSH 7
; line no: 17 , For return value

		PUSH 0
; line no: 17 , Calling function func

		CALL func
		POP AX
; line no: 17 , Return value loaded

; line no: 17 , Now removing function parameters from the stack

		ADD SP,2
; line no: 17 , Return value stored 

		PUSH AX
; line no: 17 , a = func(7)

		POP AX
; line no: 17 , func(7) loaded

		MOV W.[BP-2], AX
		PUSH AX
		POP AX
; line no: 17 , evaluated expression: a = func(7);


; line no: 18 , println(a)

		MOV AX, W.[BP-2]
; line no: 18 , a loaded

		CALL print_output
		CALL new_line
; line no: 19 , Store 0

		PUSH 0

		L6:
		MOV AH, 4CH
		INT 21H
	main ENDP

; line no: 20 , Definition of Function main ends

; line no: 22 , Functions for printing new line and value of integer variables

print_output PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	MOV CX, 10
	XOR BL, BL 
	CMP AX, 0
	JGE STACK_OP 
	MOV BH, 1
	NEG AX
STACK_OP:
	XOR DX, DX
	DIV CX
	PUSH DX
	INC BL 
	CMP AX, 0
	JG STACK_OP
	MOV AH, 02
	CMP BH, 1 
	JNE PRINT_LOOP
	MOV DL, '-'
	INT 21H
PRINT_LOOP:
	POP DX
	XOR DH, DH
	ADD DL, '0'
	INT 21H
	DEC BL
	CMP BL, 0
	JG PRINT_LOOP
	POP DX
	POP CX
	POP BX
	POP AX
	RET
	print_output ENDP

	new_line PROC
	PUSH AX
	PUSH DX
	MOV AH, 02
	MOV DL, 0DH
	INT 21H
	MOV DL, 0AH
	INT 21H
	POP DX
	POP AX
	RET
	new_line ENDP

	END main
