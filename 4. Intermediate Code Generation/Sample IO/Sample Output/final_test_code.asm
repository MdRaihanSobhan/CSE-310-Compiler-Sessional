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
L1:
	; Line No: 5
	SUB SP, 10
L2:
	; Line No: 6
	MOV AX, 0
	PUSH AX
	POP AX
	MOV [BP-2], AX
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
L4:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	PUSH AX
	POP AX
L6:
	; Line No: 8
	JMP L4
L7:
	; Line No: 9
	MOV AX, 0
	PUSH AX
	POP AX
	MOV [BP-2], AX
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
L9:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
	MOV [BP-4], AX
	PUSH AX
	POP AX
L11:
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
	PUSH AX
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
	PUSH AX
L14:
	; Line No: 13
	SUB SP, 2
L15:
	; Line No: 14
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV AX, [DI]
	PUSH AX
	POP AX
	MOV [BP-16], AX
	PUSH AX
	POP AX
L16:
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
	PUSH AX
	POP AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	PUSH AX
	POP AX
L17:
	; Line No: 16
	MOV AX, [BP-4]
	PUSH AX
	MOV AX, [BP-16]
	PUSH AX
	POP AX
	POP CX
	SHL CX, 1
	ADD CX, 6
	MOV DI, BP
	SUB DI, CX
	MOV [DI], AX
	PUSH AX
	POP AX
L18:
	; Line No: 18
L19:
	MOV AX, [BP-4]
	INC WORD PTR [BP-4]
	PUSH AX
	POP AX
L20:
	; Line No: 19
	JMP L12
L21:
	; Line No: 20
	JMP L9
L22:
	; Line No: 21
	MOV AX, 0
	PUSH AX
	POP AX
	MOV [BP-2], AX
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
L24:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L26:
	; Line No: 23
	JMP L24
L27:
	; Line No: 24
L28:
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
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L29:
	; Line No: 28
	MOV AX, 1
	PUSH AX
	MOV AX, 7
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L30:
	; Line No: 29
	MOV AX, 2
	PUSH AX
	MOV AX, 23
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L31:
	; Line No: 30
	MOV AX, 3
	PUSH AX
	MOV AX, 9
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L32:
	; Line No: 31
	MOV AX, 4
	PUSH AX
	MOV AX, 1
	PUSH AX
	POP AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV [SI], AX
	PUSH AX
	POP AX
L33:
	; Line No: 32
	CALL sort
	PUSH AX
	POP AX
L34:
	; Line No: 33
	SUB SP, 2
L35:
	; Line No: 34
	MOV AX, 0
	PUSH AX
	POP AX
	MOV [BP-2], AX
	PUSH AX
	POP AX
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
	PUSH AX
	POP AX
L37:
	MOV AX, [BP-2]
	INC WORD PTR [BP-2]
	PUSH AX
	POP AX
	JMP L36
L38:
	; Line No: 35
	SUB SP, 2
L39:
	; Line No: 36
	MOV AX, [BP-2]
	PUSH AX
	POP CX
	LEA SI, a
	SHL CX, 1
	ADD SI, CX
	MOV AX, [SI]
	PUSH AX
	POP AX
	MOV [BP-4], AX
	PUSH AX
	POP AX
L40:
	; Line No: 37
	PUSH AX
	MOV AX, [BP-4]
	CALL PRINT_OUTPUT
	CALL PRINT_NEWLINE
	POP AX
L41:
	; Line No: 38
	JMP L37
L42:
	; Line No: 39
L43:
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
