.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_10:
	MOV R9, #5
line_20:
	MOV R10, #6
line_30:
	CMP R10 , R9
	BLT line_10

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
