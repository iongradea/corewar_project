.name "fork.s"
.comment "fork"

sti r1, %61, %3
sti r1, %:xxx, %1
and r1, %0, r2
sti r1, %:xxx2, %1
fork %:xxx2

xxx: live %42
zjmp %:xxx

xxx2: live %42
zjmp %:xxx2
