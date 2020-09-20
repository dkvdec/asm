.name "spike"
.comment "useless"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live r1
		fork	%:f1
		zjmp %:live
f1:	ld	%4, r2
