#include "screen.h"
#include "system.h"

.global main

.data

str__422: .asciiz "i = %d\n"
str__619: .asciiz "End of loop\n"

.text


main:


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4
sw $ra, 0($sp)

# screen setup
li $a0, BRIGHT_WHITE
li $a1, BLACK
jal set_color
jal clear_screen


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4


addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -4
li $t0, 0
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

.for__281:

lw $t0, -4($fp)
li $t1, 10
sle $t0, $t0, $t1
beqz $t0, .end_for__225

# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp


la $t0, str__422
move $a0, $t0
lw $t0, 8($fp)
move $a1, $t0
jal printf
move $t0, $v0


# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4

addi $t0, $fp, -4
lw $t1, -4($fp)
addi $t2, $t1, 1
sw $t2, 0($t0)

j .for__281

.end_for__225:


la $t0, str__619
move $a0, $t0
jal printf
move $t0, $v0


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

