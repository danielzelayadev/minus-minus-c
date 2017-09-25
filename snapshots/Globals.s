#include "screen.h"
#include "system.h"

.global main

.data

a: .word 0
b: .word 0
c: .word 0
ca: .byte 0
cb: .byte 0
cc: .byte 0
cd: .byte 0
ce: .byte 0
cf: .byte 0
d: .word 0
e: .word 0
f: .word 0

.text


main:


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4
sw $ra, 0($sp)

# global initializations
li $t1, 10
la $t0, e
sw $t1, 0($t0)
li $t1, 100
la $t0, f
sw $t1, 0($t0)
li $t1, 'U'
la $t0, ce
sw $t1, 0($t0)
li $t1, '\n'
la $t0, cf
sw $t1, 0($t0)

# screen setup
li $a0, BRIGHT_WHITE
li $a1, BLACK
jal set_color
jal clear_screen


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp



# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4

lw $ra, -4($fp)

# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4


jr $ra

