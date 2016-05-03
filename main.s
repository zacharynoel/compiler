.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_10:
line_20:
	MOV R9, #1
	MOV R1, R9
	BL print_number

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
