#include "screen.h"
#include "system.h"

.global main

.data

anothaGlobal: .word 0, 0
globalArr: .word 0, 0, 0, 0, 0
globalChars: .byte 0, 0, 0
str__422: .asciiz "iterate[%d] = %d\n"

.text


main:


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

addi $sp, $sp, -4
sw $ra, 0($sp)

# global initializations
la $t0, anothaGlobal
li $t1, 20
sw $t1, 0($t0)
li $t1, 40
sw $t1, 4($t0)
la $t0, globalChars
li $t1, 'a'
sb $t1, 0($t0)
li $t1, 'b'
sb $t1, 1($t0)
li $t1, 'c'
sb $t1, 2($t0)

# screen setup
li $a0, BRIGHT_WHITE
li $a1, BLACK
jal set_color
jal clear_screen


# prologue
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp

# int siz
addi $sp, $sp, -4
li $t0, 6
sw $t0, -4($fp)

# int iterate[6]
addi $sp, $sp, -4
addi $t0, $sp, -4
sw $t0, 0($sp)
addi $sp, $sp, -24
li $t0, 4
sw $t0, -12($fp)
li $t0, 100
sw $t0, -16($fp)
li $t0, 12
sw $t0, -20($fp)
lw $t0, -4($fp)
sw $t0, -24($fp)

# int i
addi $sp, $sp, -4


addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -8
lw $s0, 0($s0)
li $t0, 4
move $a0, $t0
li $t0, 4
move $a1, $t0
jal mult
move $t0, $v0
sub $s0, $s0, $t0
li $t0, 20
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -8
lw $s0, 0($s0)
li $t0, 5
move $a0, $t0
li $t0, 4
move $a1, $t0
jal mult
move $t0, $v0
sub $s0, $s0, $t0
li $t0, 30
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -36
li $t0, 0
sw $t0, 0($s0)
lw $s0, 0($sp)
move $t1, $t0

.for__281:

lw $t0, -36($fp)
li $t1, 6
slt $t0, $t0, $t1
beqz $t0, .end_for__225
la $t0, str__422
move $a0, $t0
lw $t0, -36($fp)
move $a1, $t0
addi $sp, $sp, -4
sw $s0, 0($sp)
addi $s0, $fp, -8
lw $s0, 0($s0)
lw $t0, -36($fp)
addi $sp, $sp, -4
sw $a0, 0($sp)
move $a0, $t0
li $t0, 4
addi $sp, $sp, -4
sw $a1, 0($sp)
move $a1, $t0
jal mult
move $t0, $v0
lw $a0, 4($sp)
lw $a1, 0($sp)
sub $t1, $s0, $t0
lw $s0, 8($sp)
lw $t1, 0($t1)
move $a2, $t1
jal printf
move $t0, $v0
addi $t0, $fp, -36
lw $t1, -36($fp)
addi $t2, $t1, 1
sw $t2, 0($t0)

j .for__281

.end_for__225:



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

