#include "screen.h"
.global mult
.global divide
.global srand
.global rand
.global exp
.global mod
.global input
.global dbgp

.data
rnd_state: .word 0, 0, 0, 0
division:  .word 0
remainder: .word 0

.text

divide:
    move $t1, $zero
.while:
    slt $t0, $a0, $a1
    bnez $t0, .end_while
    sub $a0, $a0, $a1
    addi $t1, $t1, 1
    j .while

.end_while:
    sw $t1, 0($a2)
    sw $a0, 0($a3)
    jr $ra

mult:
    move $t0, $zero
    move $v0, $zero
.mult_loop:
    sltu $t1, $t0, $a0
    beqz $t1, .mult_end
    add $v0, $v0, $a1
    addi $t0, $t0, 1
    j .mult_loop
.mult_end:
	jr $ra

#$a0: seed
srand:
	la $t0, rnd_state
	sw $a0, 0($t0) ##rnd_state[0]
	addiu $t1, $a0, 1
	sw $t1, 4($t0) #rnd_state[1]
	addiu $t1, $a0, 2
	sw $t1, 8($t0) #rnd_state[2]
	addiu $t1, $a0, 3
	sw $t1, 12($t0) #rnd_state[3]
	jr $ra

rand:
	la $t0, rnd_state
	lw $t1, 12($t0)
	sll $t2, $t1, 11
	xor $t1, $t1, $t2
	srl $t2, $t1, 8
	xor $t1, $t1, $t2

	lw $t2, 8($t0)
	sw $t2, 12($t0)

	lw $t2, 4($t0)
	sw $t2, 8($t0)

	lw $t2, 0($t0)
	sw $t2, 4($t0)

	xor $t1, $t1, $t2
	srl $t2, $t2, 19
	xor $t1, $t1, $t2

	sw $t1, 0($t0)
	li $t0, 0x000fffff
	and $v0, $t1, $t0
	# move $v0, $t1
	jr $ra

mod:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	la $a3, remainder
	jal divide

	lw $v0, remainder
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

dbgp:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)

	move $s0, $a0
	move $s1, $a1

	li $a0, '>'
    jal put_char

	li $a0, ' '
    jal put_char

	move $a0, $s0
    jal put_char

	li $a0, ' '
    jal put_char

	li $a0, '='
    jal put_char

	li $a0, ' '
    jal put_char

	move $a0, $s1
    jal put_udecimal
     
    li $a0, '\n'
    jal put_char

	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	addi $sp, $sp, 12
	jr $ra

exp:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)

	li $s0, 1
	move $s1, $a0
	move $s2, $a1

.exp_while_start:
	beqz $s2, .exp_while_end

	move $a0, $s2
	li   $a1, 2

	jal mod
	
	li $t0, 1
	bne $v0, $t0, .exp_while_if_end

	move $a0, $s0
	move $a1, $s1
	jal mult
	move $s0, $v0

	subu $s2, $s2, 1

.exp_while_if_end:
	move $a0, $s1
	move $a1, $s1
	jal mult
	move $s1, $v0

	move $a0, $s2
	li $a1, 2
	la $a2, division
	jal divide
	lw $s2, division

	j .exp_while_start

.exp_while_end:
	move $v0, $s0

	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 16
	jr $ra

input:
	