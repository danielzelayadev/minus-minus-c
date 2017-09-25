#include "screen.h"
#include "system.h"

.global gcd

.global main

.data

a: .word 0
b: .word 0
str__281: .asciiz "GCD(%d, %d) = %d\n"

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
addi $sp, $sp, -4


addi $sp, $sp, -4
sw $s0, 0($sp)
la $s0, a
li $t0, 10
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
la $s0, b
li $t0, 20
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -4
la $t0, a
lw $t0, 0($t0)
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -8
la $t0, b
lw $t0, 0($t0)
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -12
lw $t0, -4($fp)
move $a0, $t0
lw $t0, -8($fp)
move $a1, $t0
jal gcd
move $t0, $v0
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

la $t0, str__281
move $a0, $t0
la $t0, a
lw $t0, 0($t0)
move $a1, $t0
la $t0, b
lw $t0, 0($t0)
move $a2, $t0
lw $t0, -12($fp)
move $a3, $t0
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

gcd:


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4
sw $ra, 0($sp)

# Arg Pushing
addi $sp, $sp, -4
sw $a0, 0($sp)
addi $sp, $sp, -4
sw $a1, 0($sp)

# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp


lw $t0, 4($fp)
li $t1, 0
seq $t0, $t0, $t1
beqz $t0, .else__422

# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp


lw $t0, 12($fp)
move $v0, $t0

# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4


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


# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4

j .end_if__225
.else__422:


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

lw $t0, 8($fp)
move $a0, $t0
lw $t0, 12($fp)
addi $sp, $sp, -4
sw $a0, 0($sp)
move $a0, $t0
lw $t0, 8($fp)
move $a1, $t0
jal mod
move $t0, $v0
lw $a0, 0($sp)
move $a1, $t0
jal gcd
move $t0, $v0
move $v0, $t0

# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4


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


# epilogue
move $sp, $fp
lw $fp, 0($sp)
addi $sp, $sp, 4

.end_if__225:



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

