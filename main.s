.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_10:
	MOV R9, #5
line_20:
	CMP R9 , R10
	BGT line_20
line_30:
line_100:

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
