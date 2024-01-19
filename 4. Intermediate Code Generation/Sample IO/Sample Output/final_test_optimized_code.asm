.MODEL SMALL
.STACK 1000H

.DATA
	a DW 5 DUP (0000H)

.CODE
	; Line No: 3
sort PROC
	PUSH BP
	MOV BP, SP
	; Line No: 4
	SUB SP, 4
	; Line No: 5
	SUB SP, 10
	; Line No: 6
	MOV AX, 0
	MOV [BP-2], AX
L3:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, 5
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JL L5
	JMP L7
L4:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	JMP L3
L5:
	; Line No: 7
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV AX, [SI]
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	; Line No: 8
	JMP L4
L7:
	; Line No: 9
	MOV AX, 0
	MOV [BP-2], AX
L8:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, 5
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JL L10
	JMP L22
L9:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	JMP L8
L10:
	; Line No: 10
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, 1
	PUSH AX
	POP BX
	POP AX
	ADD AX, BX
	MOV [BP-4], AX
	; Line No: 11
L12:
	MOV AX, [BP-4]
	PUSH AX
	MOV AX, 5
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JL L13
	JMP L9
L13:
	; Line No: 12
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JG L14
	JMP L19
L14:
	; Line No: 13
	SUB SP, 2
	; Line No: 14
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	MOV [BP-16], AX
	; Line No: 15
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-4]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	; Line No: 16
	MOV AX, [BP-4]
	PUSH AX
	MOV AX, [BP-16]
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	; Line No: 18
L19:
	MOV AX, [BP-4]
	INC WORD PTR [BP-4]
	; Line No: 19
	JMP L12
	; Line No: 20
L22:
	; Line No: 21
	MOV AX, 0
	MOV [BP-2], AX
L23:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, 5
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JL L25
	JMP L27
L24:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	JMP L23
L25:
	; Line No: 22
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 23
	JMP L24
L27:
	; Line No: 24
	MOV SP, BP
	POP BP
	RET
sort ENDP
	; Line No: 26
main PROC
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	; Line No: 27
	MOV AX, 0
	PUSH AX
	MOV AX, 69
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 28
	MOV AX, 1
	PUSH AX
	MOV AX, 7
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 29
	MOV AX, 2
	PUSH AX
	MOV AX, 23
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 30
	MOV AX, 3
	PUSH AX
	MOV AX, 9
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 31
	MOV AX, 4
	PUSH AX
	MOV AX, 1
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	; Line No: 32
	CALL sort
	; Line No: 33
	SUB SP, 2
	; Line No: 34
	MOV AX, 0
	MOV [BP-2], AX
L36:
	MOV AX, [BP-2]
	PUSH AX
	MOV AX, 5
	PUSH AX
	POP BX
	POP AX
	CMP AX, BX
	JL L38
	JMP L42
L37:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	JMP L36
L38:
	; Line No: 35
	SUB SP, 2
	; Line No: 36
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV AX, [SI]
	MOV [BP-4], AX
	; Line No: 37
	PUSH AX
	MOV AX, [BP-4]
	CALL PRINT_OUTPUT
	CALL PRINT_NEWLINE
	POP AX
	; Line No: 38
	JMP L37
L42:
	; Line No: 39
	MOV SP, BP
	POP BP
	MOV AX, 4CH
	INT 21H
main ENDP

PRINT_OUTPUT PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	; dividend has to be in DX:AX
	; divisor in source, CX
	MOV CX, 10
	XOR BL, BL ; BL will store the length of number
	CMP AX, 0
	JGE STACK_OP ; number is positive
	MOV BH, 1; number is negative
	NEG AX
STACK_OP:
	XOR DX, DX
	DIV CX
	; quotient in AX, remainder in DX
	PUSH DX
	INC BL ; len++
	CMP AX, 0
	JG STACK_OP
	MOV AH, 02
	CMP BH, 1 ; if negative, print a '-' sign first
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
PRINT_OUTPUT ENDP

PRINT_NEWLINE PROC
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
PRINT_NEWLINE ENDP

END main
