#include "screen.h"
#include "system.h"

.global main

.data

str__422: .asciiz "Number [%d] = %d\n"
str__619: .asciiz "The total is %d\n"

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


lw $t0, MS_COUNTER_REG_ADDR
move $a0, $t0
jal srand
move $t0, $v0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -4
li $t0, 0
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -8
li $t0, 0
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

.while__281:

lw $t0, -8($fp)
li $t1, 3
slt $t0, $t0, $t1
beqz $t0, .while_end__225

# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4


addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -4
jal rand
move $t0, $v0
move $a0, $t0
li $t0, 100
move $a1, $t0
jal mod
move $t0, $v0
li $t1, 1
add $t0, $t0, $t1
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

la $t0, str__422
move $a0, $t0
lw $t0, 12($fp)
move $a1, $t0
lw $t0, -4($fp)
move $a2, $t0
jal printf
move $t0, $v0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, 12
lw $t0, 12($fp)
li $t1, 1
add $t0, $t0, $t1
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, 16
lw $t0, 16($fp)
lw $t1, -4($fp)
add $t0, $t0, $t1
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0


# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4

j .while__281
.while_end__225:


la $t0, str__619
move $a0, $t0
lw $t0, -4($fp)
move $a1, $t0
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

