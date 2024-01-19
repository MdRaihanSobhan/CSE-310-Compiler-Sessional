.MODEL SMALL
.DATA
	CR EQU 0DH
	LF EQU 0AH
	number DB "00000$"
.CODE
	func PROC
		PUSH BP
		MOV BP, SP
		SUB SP,2
		PUSH W. [BP + 6]
		PUSH 0
		POP BX
		POP AX
		JE L0
			PUSH 0
		L0:
		L1:
		POP AX
		CMP AX, 0
		JE END_IF_2
		PUSH 0
		POP AX
		MOV [BP+4], AX
		ADD SP, 2
		POP BP
		RET
		END_IF_2:
		PUSH W. [BP + 6]
		POP AX
		MOV W.[BP-2], AX
;Removing redundant consecutive push and pop of the same register/address.
		PUSH W. [BP + 6]
		PUSH 1
		POP BX
		POP AX
		SUB AX, BX
		PUSH AX
		PUSH 0
		CALL func
		POP AX
		ADD SP,2
		PUSH AX
		PUSH W.[BP-2]
		POP BX
		POP AX
		ADD AX, BX
		PUSH AX
		POP AX
		MOV [BP+4], AX
		ADD SP, 2
		POP BP
		RET
		POP BP
		RET
	func ENDP
	func2 PROC
		PUSH BP
		MOV BP, SP
		SUB SP,2
		PUSH W. [BP + 6]
		PUSH 0
		POP BX
		POP AX
		JE L3
			PUSH 0
		L3:
		L4:
		POP AX
		CMP AX, 0
		JE END_IF_5
		PUSH 0
		POP AX
		MOV [BP+4], AX
		ADD SP, 2
		POP BP
		RET
		END_IF_5:
		PUSH W. [BP + 6]
		POP AX
		MOV W.[BP-2], AX
;Removing redundant consecutive push and pop of the same register/address.
		PUSH W. [BP + 6]
		PUSH 1
		POP BX
		POP AX
		SUB AX, BX
		PUSH AX
		PUSH 0
		CALL func
		POP AX
		ADD SP,2
		PUSH AX
		PUSH W.[BP-2]
		POP BX
		POP AX
		ADD AX, BX
		PUSH AX
		POP AX
		MOV [BP+4], AX
		ADD SP, 2
		POP BP
		RET
		POP BP
		RET
	func2 ENDP
	main PROC
		MOV AX, @DATA
		mov DS, AX
		MOV BP, SP
		SUB SP,2
		PUSH 7
		PUSH 0
		CALL func
		POP AX
		ADD SP,2
		PUSH AX
		POP AX
		MOV W.[BP-2], AX
;Removing redundant consecutive push and pop of the same register/address.
		MOV AX, W.[BP-2]
		CALL print_output
		CALL new_line
		PUSH 0
		L6:
		MOV AH, 4CH
		INT 21H
	main ENDP
print_output PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	MOV CX, 10
	XOR BL, BL 
	CMP AX, 0
	JGE STACK_OP 
	NEG AX
STACK_OP:
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
	POP DX
	XOR DH, DH
	ADD DL, '0'
	INT 21H
	DEC BL
	CMP BL, 0
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
