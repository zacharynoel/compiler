.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_10:
	MOV R9, #5
line_20:
<<<<<<< HEAD
	MOV R10, #6
line_30:
	CMP R10 , R9
	BLT line_10
=======
	CMP R9 , R10
	BGT line_20
line_30:
line_100:
>>>>>>> e5f7318ff95376c6f37f6918be4b701553bcc480

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
