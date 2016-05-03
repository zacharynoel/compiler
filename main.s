.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_1:
line_2:
line_3:
line_10:
	CMP R9, R10
	BNE line_30
line_30:
line_40:
line_50:
	MOV R0, R9
	BL print_number
line_60:
line_70:
	CMP R9, R10
	BEQ line_100
line_80:
	CMP R9, R10
line_90:
	CMP R9, R10
line_100:

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
