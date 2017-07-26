.name "Punisher"
.comment "I will Punish your foes!"

ld %0, r16 # carry = 1
trap: 
ld %72, r4 # H
ld %65, r5 # A

ld %150994944, r3 # 09 00 00 00
sti r3, %:trap, %0
aff r4
aff r5
ld %0, r3
zjmp %:jmp1
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0

##################
jmp1:
aff r4
aff r5
zjmp %:jmp2
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0

################
jmp2:
aff r4
aff r5
zjmp %:jmp3
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0

################
cycle:
ld %0, r15
sti r1, %:lap, %1
lap: live %255
zjmp %:lap
################

ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0
ld %0, r1
zjmp %0

jmp3: 
aff r4
aff r5
sti r1, %:live, %1
live:	live %255
fork %511
zjmp %:cycle
