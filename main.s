.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_10:
	MOV R9, #5
line_20:
	BL print_number

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
