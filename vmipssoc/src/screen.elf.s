
screen.elf:     file format elf32-bigmips


Disassembly of section .text:

00400000 <start>:
  400000:	3c1d7fff 	lui	sp,0x7fff
  400004:	0c1001d1 	jal	400744 <main>
  400008:	37bdfffc 	ori	sp,sp,0xfffc
  40000c:	08100003 	j	40000c <start+0xc>
  400010:	00000000 	nop

00400014 <divide>:
  400014:	00004825 	move	t1,zero

00400018 <.while>:
  400018:	0085402a 	slt	t0,a0,a1
  40001c:	15000004 	bnez	t0,400030 <.end_while>
  400020:	00000000 	nop
  400024:	00852022 	sub	a0,a0,a1
  400028:	08100006 	j	400018 <.while>
  40002c:	21290001 	addi	t1,t1,1

00400030 <.end_while>:
  400030:	acc90000 	sw	t1,0(a2)
  400034:	03e00008 	jr	ra
  400038:	ace40000 	sw	a0,0(a3)

0040003c <mult>:
  40003c:	00004025 	move	t0,zero
  400040:	00001025 	move	v0,zero

00400044 <.mult_loop>:
  400044:	0104482b 	sltu	t1,t0,a0
  400048:	11200004 	beqz	t1,40005c <.mult_end>
  40004c:	00000000 	nop
  400050:	00451020 	add	v0,v0,a1
  400054:	08100011 	j	400044 <.mult_loop>
  400058:	21080001 	addi	t0,t0,1

0040005c <.mult_end>:
  40005c:	03e00008 	jr	ra
  400060:	00000000 	nop

00400064 <rand_seed>:
  400064:	3c081001 	lui	t0,0x1001
  400068:	25080000 	addiu	t0,t0,0
  40006c:	ad040000 	sw	a0,0(t0)
  400070:	24890001 	addiu	t1,a0,1
  400074:	ad090004 	sw	t1,4(t0)
  400078:	24890002 	addiu	t1,a0,2
  40007c:	ad090008 	sw	t1,8(t0)
  400080:	24890003 	addiu	t1,a0,3
  400084:	03e00008 	jr	ra
  400088:	ad09000c 	sw	t1,12(t0)

0040008c <rand>:
  40008c:	3c081001 	lui	t0,0x1001
  400090:	25080000 	addiu	t0,t0,0
  400094:	8d09000c 	lw	t1,12(t0)
  400098:	00000000 	nop
  40009c:	000952c0 	sll	t2,t1,0xb
  4000a0:	012a4826 	xor	t1,t1,t2
  4000a4:	00095202 	srl	t2,t1,0x8
  4000a8:	012a4826 	xor	t1,t1,t2
  4000ac:	8d0a0008 	lw	t2,8(t0)
  4000b0:	00000000 	nop
  4000b4:	ad0a000c 	sw	t2,12(t0)
  4000b8:	8d0a0004 	lw	t2,4(t0)
  4000bc:	00000000 	nop
  4000c0:	ad0a0008 	sw	t2,8(t0)
  4000c4:	8d0a0000 	lw	t2,0(t0)
  4000c8:	00000000 	nop
  4000cc:	ad0a0004 	sw	t2,4(t0)
  4000d0:	012a4826 	xor	t1,t1,t2
  4000d4:	000a54c2 	srl	t2,t2,0x13
  4000d8:	012a4826 	xor	t1,t1,t2
  4000dc:	ad090000 	sw	t1,0(t0)
  4000e0:	3c08000f 	lui	t0,0xf
  4000e4:	3508ffff 	ori	t0,t0,0xffff
  4000e8:	03e00008 	jr	ra
  4000ec:	01281024 	and	v0,t1,t0

004000f0 <mod>:
  4000f0:	23bdfffc 	addi	sp,sp,-4
  4000f4:	afbf0000 	sw	ra,0(sp)
  4000f8:	3c071001 	lui	a3,0x1001
  4000fc:	0c100005 	jal	400014 <divide>
  400100:	24e70014 	addiu	a3,a3,20
  400104:	3c021001 	lui	v0,0x1001
  400108:	8c420014 	lw	v0,20(v0)
  40010c:	8fbf0000 	lw	ra,0(sp)
  400110:	23bd0004 	addi	sp,sp,4
  400114:	03e00008 	jr	ra
  400118:	00000000 	nop

0040011c <dbgp>:
  40011c:	23bdfff4 	addi	sp,sp,-12
  400120:	afbf0000 	sw	ra,0(sp)
  400124:	afb00004 	sw	s0,4(sp)
  400128:	afb10008 	sw	s1,8(sp)
  40012c:	00808025 	move	s0,a0
  400130:	00a08825 	move	s1,a1
  400134:	0c1000a6 	jal	400298 <put_char>
  400138:	2404003e 	li	a0,62
  40013c:	0c1000a6 	jal	400298 <put_char>
  400140:	24040020 	li	a0,32
  400144:	0c1000a6 	jal	400298 <put_char>
  400148:	02002025 	move	a0,s0
  40014c:	0c1000a6 	jal	400298 <put_char>
  400150:	24040020 	li	a0,32
  400154:	0c1000a6 	jal	400298 <put_char>
  400158:	2404003d 	li	a0,61
  40015c:	0c1000a6 	jal	400298 <put_char>
  400160:	24040020 	li	a0,32
  400164:	0c1000fc 	jal	4003f0 <put_udecimal>
  400168:	02202025 	move	a0,s1
  40016c:	0c1000a6 	jal	400298 <put_char>
  400170:	2404000a 	li	a0,10
  400174:	8fbf0000 	lw	ra,0(sp)
  400178:	8fb00004 	lw	s0,4(sp)
  40017c:	8fb10008 	lw	s1,8(sp)
  400180:	03e00008 	jr	ra
  400184:	23bd000c 	addi	sp,sp,12

00400188 <exp>:
  400188:	23bdfff0 	addi	sp,sp,-16
  40018c:	afbf0000 	sw	ra,0(sp)
  400190:	afb00004 	sw	s0,4(sp)
  400194:	afb10008 	sw	s1,8(sp)
  400198:	afb2000c 	sw	s2,12(sp)
  40019c:	24100001 	li	s0,1
  4001a0:	00808825 	move	s1,a0
  4001a4:	00a09025 	move	s2,a1

004001a8 <.exp_while_start>:
  4001a8:	12400019 	beqz	s2,400210 <.exp_while_end>
  4001ac:	00000000 	nop
  4001b0:	02402025 	move	a0,s2
  4001b4:	0c10003c 	jal	4000f0 <mod>
  4001b8:	24050002 	li	a1,2
  4001bc:	24080001 	li	t0,1
  4001c0:	14480006 	bne	v0,t0,4001dc <.exp_while_if_end>
  4001c4:	00000000 	nop
  4001c8:	02002025 	move	a0,s0
  4001cc:	0c10000f 	jal	40003c <mult>
  4001d0:	02202825 	move	a1,s1
  4001d4:	00408025 	move	s0,v0
  4001d8:	2652ffff 	addiu	s2,s2,-1

004001dc <.exp_while_if_end>:
  4001dc:	02202025 	move	a0,s1
  4001e0:	0c10000f 	jal	40003c <mult>
  4001e4:	02202825 	move	a1,s1
  4001e8:	00408825 	move	s1,v0
  4001ec:	02402025 	move	a0,s2
  4001f0:	24050002 	li	a1,2
  4001f4:	3c061001 	lui	a2,0x1001
  4001f8:	0c100005 	jal	400014 <divide>
  4001fc:	24c60010 	addiu	a2,a2,16
  400200:	3c121001 	lui	s2,0x1001
  400204:	8e520010 	lw	s2,16(s2)
  400208:	0810006a 	j	4001a8 <.exp_while_start>
  40020c:	00000000 	nop

00400210 <.exp_while_end>:
  400210:	02001025 	move	v0,s0
  400214:	8fb2000c 	lw	s2,12(sp)
  400218:	8fb10008 	lw	s1,8(sp)
  40021c:	8fb00004 	lw	s0,4(sp)
  400220:	8fbf0000 	lw	ra,0(sp)
  400224:	23bd0010 	addi	sp,sp,16
  400228:	03e00008 	jr	ra
  40022c:	00000000 	nop

00400230 <input>:
  400230:	00052900 	sll	a1,a1,0x4
  400234:	3084000f 	andi	a0,a0,0xf
  400238:	00a44025 	or	t0,a1,a0
  40023c:	3c011001 	lui	at,0x1001
  400240:	03e00008 	jr	ra
  400244:	a0280018 	sb	t0,24(at)

00400248 <get_color>:
  400248:	3c081001 	lui	t0,0x1001
  40024c:	81080018 	lb	t0,24(t0)
  400250:	00000000 	nop
  400254:	3109000f 	andi	t1,t0,0xf
  400258:	a0890000 	sb	t1,0(a0)
  40025c:	00084102 	srl	t0,t0,0x4
  400260:	03e00008 	jr	ra
  400264:	a0a80000 	sb	t0,0(a1)

00400268 <set_cursor>:
  400268:	2c88001e 	sltiu	t0,a0,30
  40026c:	11000008 	beqz	t0,400290 <.end_if>
  400270:	00000000 	nop
  400274:	2ca80050 	sltiu	t0,a1,80
  400278:	11000005 	beqz	t0,400290 <.end_if>
  40027c:	00000000 	nop
  400280:	3c011001 	lui	at,0x1001
  400284:	a024001a 	sb	a0,26(at)
  400288:	3c011001 	lui	at,0x1001
  40028c:	a0250019 	sb	a1,25(at)

00400290 <.end_if>:
  400290:	03e00008 	jr	ra
  400294:	00000000 	nop

00400298 <put_char>:
  400298:	2408000a 	li	t0,10
  40029c:	1488000d 	bne	a0,t0,4002d4 <.else>
  4002a0:	00000000 	nop
  4002a4:	3c081001 	lui	t0,0x1001
  4002a8:	8108001a 	lb	t0,26(t0)
  4002ac:	00000000 	nop
  4002b0:	2d09001d 	sltiu	t1,t0,29
  4002b4:	11200004 	beqz	t1,4002c8 <.cursor_zero>
  4002b8:	00000000 	nop
  4002bc:	25080001 	addiu	t0,t0,1
  4002c0:	3c011001 	lui	at,0x1001
  4002c4:	a028001a 	sb	t0,26(at)

004002c8 <.cursor_zero>:
  4002c8:	3c011001 	lui	at,0x1001
  4002cc:	03e00008 	jr	ra
  4002d0:	a0200019 	sb	zero,25(at)

004002d4 <.else>:
  4002d4:	3c081001 	lui	t0,0x1001
  4002d8:	8108001a 	lb	t0,26(t0)
  4002dc:	00000000 	nop
  4002e0:	00084980 	sll	t1,t0,0x6
  4002e4:	00085100 	sll	t2,t0,0x4
  4002e8:	012a5020 	add	t2,t1,t2
  4002ec:	3c081001 	lui	t0,0x1001
  4002f0:	81080019 	lb	t0,25(t0)
  4002f4:	00000000 	nop
  4002f8:	01484020 	add	t0,t2,t0
  4002fc:	3c091001 	lui	t1,0x1001
  400300:	81290018 	lb	t1,24(t1)
  400304:	00000000 	nop
  400308:	00094a00 	sll	t1,t1,0x8
  40030c:	01244825 	or	t1,t1,a0
  400310:	340ab800 	li	t2,0xb800
  400314:	00084040 	sll	t0,t0,0x1
  400318:	010a5020 	add	t2,t0,t2
  40031c:	ad490000 	sw	t1,0(t2)
  400320:	3c081001 	lui	t0,0x1001
  400324:	81080019 	lb	t0,25(t0)
  400328:	00000000 	nop
  40032c:	2909004f 	slti	t1,t0,79
  400330:	11200005 	beqz	t1,400348 <.else_cursor>
  400334:	00000000 	nop
  400338:	21080001 	addi	t0,t0,1
  40033c:	3c011001 	lui	at,0x1001
  400340:	081000da 	j	400368 <.end_if_cursor>
  400344:	a0280019 	sb	t0,25(at)

00400348 <.else_cursor>:
  400348:	3c011001 	lui	at,0x1001
  40034c:	a0200019 	sb	zero,25(at)
  400350:	3c081001 	lui	t0,0x1001
  400354:	8108001a 	lb	t0,26(t0)
  400358:	00000000 	nop
  40035c:	21080001 	addi	t0,t0,1
  400360:	3c011001 	lui	at,0x1001
  400364:	a028001a 	sb	t0,26(at)

00400368 <.end_if_cursor>:
  400368:	03e00008 	jr	ra
  40036c:	00000000 	nop

00400370 <puts>:
  400370:	27bdfff8 	addiu	sp,sp,-8
  400374:	afbf0000 	sw	ra,0(sp)
  400378:	afb00004 	sw	s0,4(sp)
  40037c:	00808025 	move	s0,a0

00400380 <.while_begin>:
  400380:	82090000 	lb	t1,0(s0)
  400384:	00000000 	nop
  400388:	11200006 	beqz	t1,4003a4 <.while_end>
  40038c:	00000000 	nop
  400390:	01202025 	move	a0,t1
  400394:	0c1000a6 	jal	400298 <put_char>
  400398:	22100001 	addi	s0,s0,1
  40039c:	081000e0 	j	400380 <.while_begin>
  4003a0:	00000000 	nop

004003a4 <.while_end>:
  4003a4:	8fbf0000 	lw	ra,0(sp)
  4003a8:	8fb00004 	lw	s0,4(sp)
  4003ac:	03e00008 	jr	ra
  4003b0:	27bd0008 	addiu	sp,sp,8

004003b4 <clear_screen>:
  4003b4:	3c081001 	lui	t0,0x1001
  4003b8:	81080018 	lb	t0,24(t0)
  4003bc:	00000000 	nop
  4003c0:	00084200 	sll	t0,t0,0x8
  4003c4:	35080020 	ori	t0,t0,0x20
  4003c8:	3409b800 	li	t1,0xb800

004003cc <.for_begin>:
  4003cc:	2d2acac0 	sltiu	t2,t1,-13632
  4003d0:	11400004 	beqz	t2,4003e4 <.for_end>
  4003d4:	00000000 	nop
  4003d8:	a5280000 	sh	t0,0(t1)
  4003dc:	081000f3 	j	4003cc <.for_begin>
  4003e0:	25290002 	addiu	t1,t1,2

004003e4 <.for_end>:
  4003e4:	00002025 	move	a0,zero
  4003e8:	0810009a 	j	400268 <set_cursor>
  4003ec:	00002825 	move	a1,zero

004003f0 <put_udecimal>:
  4003f0:	23bdffe8 	addi	sp,sp,-24
  4003f4:	afbf0000 	sw	ra,0(sp)
  4003f8:	afb00004 	sw	s0,4(sp)
  4003fc:	afb10008 	sw	s1,8(sp)
  400400:	00808025 	move	s0,a0
  400404:	16000005 	bnez	s0,40041c <.pu_else>
  400408:	23b1000c 	addi	s1,sp,12
  40040c:	0c1000a6 	jal	400298 <put_char>
  400410:	24040030 	li	a0,48
  400414:	0810011f 	j	40047c <.epilogo>
  400418:	00000000 	nop

0040041c <.pu_else>:
  40041c:	2231000b 	addi	s1,s1,11
  400420:	23bdfff8 	addi	sp,sp,-8
  400424:	a2200000 	sb	zero,0(s1)
  400428:	2231ffff 	addi	s1,s1,-1

0040042c <.pu_while>:
  40042c:	0010402b 	sltu	t0,zero,s0
  400430:	1008000e 	beq	zero,t0,40046c <.pu_end_while>
  400434:	00000000 	nop
  400438:	02002025 	move	a0,s0
  40043c:	2405000a 	li	a1,10
  400440:	23a60000 	addi	a2,sp,0
  400444:	0c100005 	jal	400014 <divide>
  400448:	23a70004 	addi	a3,sp,4
  40044c:	8fa90004 	lw	t1,4(sp)
  400450:	00000000 	nop
  400454:	25290030 	addiu	t1,t1,48
  400458:	a2290000 	sb	t1,0(s1)
  40045c:	2231ffff 	addi	s1,s1,-1
  400460:	8fb00000 	lw	s0,0(sp)
  400464:	0810010b 	j	40042c <.pu_while>
  400468:	00000000 	nop

0040046c <.pu_end_while>:
  40046c:	23bd0008 	addi	sp,sp,8
  400470:	22310001 	addi	s1,s1,1
  400474:	0c1000dc 	jal	400370 <puts>
  400478:	02202025 	move	a0,s1

0040047c <.epilogo>:
  40047c:	8fbf0000 	lw	ra,0(sp)
  400480:	8fb00004 	lw	s0,4(sp)
  400484:	8fb10008 	lw	s1,8(sp)
  400488:	03e00008 	jr	ra
  40048c:	23bd0018 	addi	sp,sp,24

00400490 <draw_rect>:
  400490:	8c880000 	lw	t0,0(a0)
  400494:	8c890004 	lw	t1,4(a0)
  400498:	8c8b0008 	lw	t3,8(a0)
  40049c:	8c8a000c 	lw	t2,12(a0)
  4004a0:	00086180 	sll	t4,t0,0x6
  4004a4:	00086900 	sll	t5,t0,0x4
  4004a8:	018d6020 	add	t4,t4,t5
  4004ac:	01896020 	add	t4,t4,t1
  4004b0:	000c6040 	sll	t4,t4,0x1
  4004b4:	340db800 	li	t5,0xb800
  4004b8:	018d6020 	add	t4,t4,t5
  4004bc:	010b7020 	add	t6,t0,t3
  4004c0:	21ceffff 	addi	t6,t6,-1
  4004c4:	000e7980 	sll	t7,t6,0x6
  4004c8:	000e7100 	sll	t6,t6,0x4
  4004cc:	01cf7020 	add	t6,t6,t7
  4004d0:	01c97020 	add	t6,t6,t1
  4004d4:	000e7040 	sll	t6,t6,0x1
  4004d8:	01cd7020 	add	t6,t6,t5
  4004dc:	012a6820 	add	t5,t1,t2
  4004e0:	01207825 	move	t7,t1

004004e4 <.dw_for1>:
  4004e4:	01edc02a 	slt	t8,t7,t5
  4004e8:	1300000c 	beqz	t8,40051c <.dw_end_for1>
  4004ec:	00000000 	nop
  4004f0:	3c181001 	lui	t8,0x1001
  4004f4:	83180018 	lb	t8,24(t8)
  4004f8:	00000000 	nop
  4004fc:	0018c200 	sll	t8,t8,0x8
  400500:	371800c4 	ori	t8,t8,0xc4
  400504:	a5980000 	sh	t8,0(t4)
  400508:	a5d80000 	sh	t8,0(t6)
  40050c:	218c0002 	addi	t4,t4,2
  400510:	21ce0002 	addi	t6,t6,2
  400514:	08100139 	j	4004e4 <.dw_for1>
  400518:	21ef0001 	addi	t7,t7,1

0040051c <.dw_end_for1>:
  40051c:	00086180 	sll	t4,t0,0x6
  400520:	00086900 	sll	t5,t0,0x4
  400524:	018d6020 	add	t4,t4,t5
  400528:	01896020 	add	t4,t4,t1
  40052c:	000c6040 	sll	t4,t4,0x1
  400530:	340db800 	li	t5,0xb800
  400534:	018d6020 	add	t4,t4,t5
  400538:	012a7020 	add	t6,t1,t2
  40053c:	21ceffff 	addi	t6,t6,-1
  400540:	0008c180 	sll	t8,t0,0x6
  400544:	00087900 	sll	t7,t0,0x4
  400548:	030f7820 	add	t7,t8,t7
  40054c:	01ee7820 	add	t7,t7,t6
  400550:	000f7840 	sll	t7,t7,0x1
  400554:	01ed7820 	add	t7,t7,t5
  400558:	010b7020 	add	t6,t0,t3
  40055c:	01006825 	move	t5,t0

00400560 <.dw_for2>:
  400560:	01aec02a 	slt	t8,t5,t6
  400564:	1300000c 	beqz	t8,400598 <.dw_end_for2>
  400568:	00000000 	nop
  40056c:	3c181001 	lui	t8,0x1001
  400570:	83180018 	lb	t8,24(t8)
  400574:	00000000 	nop
  400578:	0018c200 	sll	t8,t8,0x8
  40057c:	371800b3 	ori	t8,t8,0xb3
  400580:	a5980000 	sh	t8,0(t4)
  400584:	a5f80000 	sh	t8,0(t7)
  400588:	218c00a0 	addi	t4,t4,160
  40058c:	21ef00a0 	addi	t7,t7,160
  400590:	08100158 	j	400560 <.dw_for2>
  400594:	21ad0001 	addi	t5,t5,1

00400598 <.dw_end_for2>:
  400598:	23bdffec 	addi	sp,sp,-20
  40059c:	afbf0000 	sw	ra,0(sp)
  4005a0:	afb00004 	sw	s0,4(sp)
  4005a4:	afb10008 	sw	s1,8(sp)
  4005a8:	afb2000c 	sw	s2,12(sp)
  4005ac:	afb30010 	sw	s3,16(sp)
  4005b0:	01008025 	move	s0,t0
  4005b4:	01208825 	move	s1,t1
  4005b8:	01409025 	move	s2,t2
  4005bc:	01609825 	move	s3,t3
  4005c0:	02002025 	move	a0,s0
  4005c4:	0c10009a 	jal	400268 <set_cursor>
  4005c8:	02202825 	move	a1,s1
  4005cc:	0c1000a6 	jal	400298 <put_char>
  4005d0:	240400da 	li	a0,218
  4005d4:	02002025 	move	a0,s0
  4005d8:	02512821 	addu	a1,s2,s1
  4005dc:	0c10009a 	jal	400268 <set_cursor>
  4005e0:	24a5ffff 	addiu	a1,a1,-1
  4005e4:	0c1000a6 	jal	400298 <put_char>
  4005e8:	240400bf 	li	a0,191
  4005ec:	02132021 	addu	a0,s0,s3
  4005f0:	2484ffff 	addiu	a0,a0,-1
  4005f4:	0c10009a 	jal	400268 <set_cursor>
  4005f8:	02202825 	move	a1,s1
  4005fc:	0c1000a6 	jal	400298 <put_char>
  400600:	240400c0 	li	a0,192
  400604:	02132021 	addu	a0,s0,s3
  400608:	2484ffff 	addiu	a0,a0,-1
  40060c:	02512821 	addu	a1,s2,s1
  400610:	0c10009a 	jal	400268 <set_cursor>
  400614:	24a5ffff 	addiu	a1,a1,-1
  400618:	0c1000a6 	jal	400298 <put_char>
  40061c:	240400d9 	li	a0,217
  400620:	8fbf0000 	lw	ra,0(sp)
  400624:	8fb00004 	lw	s0,4(sp)
  400628:	8fb10008 	lw	s1,8(sp)
  40062c:	8fb2000c 	lw	s2,12(sp)
  400630:	8fb30010 	lw	s3,16(sp)
  400634:	03e00008 	jr	ra
  400638:	23bd0014 	addi	sp,sp,20

0040063c <fill_rect>:
  40063c:	8c880000 	lw	t0,0(a0)
  400640:	8c890004 	lw	t1,4(a0)
  400644:	8c8a0008 	lw	t2,8(a0)
  400648:	8c8b000c 	lw	t3,12(a0)
  40064c:	340cb800 	li	t4,0xb800
  400650:	00086980 	sll	t5,t0,0x6
  400654:	00087100 	sll	t6,t0,0x4
  400658:	01ae7020 	add	t6,t5,t6
  40065c:	01c97020 	add	t6,t6,t1
  400660:	000e7040 	sll	t6,t6,0x1
  400664:	01cc7021 	addu	t6,t6,t4
  400668:	3c0c1001 	lui	t4,0x1001
  40066c:	818c0018 	lb	t4,24(t4)
  400670:	00000000 	nop
  400674:	000c6200 	sll	t4,t4,0x8
  400678:	01856025 	or	t4,t4,a1
  40067c:	240d0000 	li	t5,0

00400680 <.fill_rect_for>:
  400680:	01aa782b 	sltu	t7,t5,t2
  400684:	11e0000d 	beqz	t7,4006bc <.end_fill_rect>
  400688:	00000000 	nop
  40068c:	01c07825 	move	t7,t6
  400690:	24180000 	li	t8,0

00400694 <.fill_rect_inner_for>:
  400694:	030bc82b 	sltu	t9,t8,t3
  400698:	13200005 	beqz	t9,4006b0 <.fill_rect_inner_for_end>
  40069c:	00000000 	nop
  4006a0:	a5ec0000 	sh	t4,0(t7)
  4006a4:	25ef0002 	addiu	t7,t7,2
  4006a8:	081001a5 	j	400694 <.fill_rect_inner_for>
  4006ac:	27180001 	addiu	t8,t8,1

004006b0 <.fill_rect_inner_for_end>:
  4006b0:	25ce00a0 	addiu	t6,t6,160
  4006b4:	081001a0 	j	400680 <.fill_rect_for>
  4006b8:	25ad0001 	addiu	t5,t5,1

004006bc <.end_fill_rect>:
  4006bc:	03e00008 	jr	ra
  4006c0:	00000000 	nop

004006c4 <keypad_init>:
  4006c4:	3c081001 	lui	t0,0x1001
  4006c8:	03e00008 	jr	ra
  4006cc:	ad00001c 	sw	zero,28(t0)

004006d0 <keypad_getkey>:
  4006d0:	3c08ffff 	lui	t0,0xffff
  4006d4:	81080004 	lb	t0,4(t0)
  4006d8:	24090008 	li	t1,8
  4006dc:	240b0001 	li	t3,1
  4006e0:	00005025 	move	t2,zero

004006e4 <.gk_loop>:
  4006e4:	11490015 	beq	t2,t1,40073c <.gk_end_loop>
  4006e8:	00000000 	nop
  4006ec:	010b6024 	and	t4,t0,t3
  4006f0:	11800010 	beqz	t4,400734 <.gk_inc_loop>
  4006f4:	000b5840 	sll	t3,t3,0x1
  4006f8:	3c081001 	lui	t0,0x1001
  4006fc:	8d08001c 	lw	t0,28(t0)
  400700:	3c09ffff 	lui	t1,0xffff
  400704:	8d290008 	lw	t1,8(t1)
  400708:	00000000 	nop
  40070c:	0128582b 	sltu	t3,t1,t0
  400710:	11600002 	beqz	t3,40071c <.set_key>
  400714:	00000000 	nop
  400718:	00001025 	move	v0,zero

0040071c <.set_key>:
  40071c:	252900c8 	addiu	t1,t1,200
  400720:	3c081001 	lui	t0,0x1001
  400724:	ad09001c 	sw	t1,28(t0)
  400728:	01401025 	move	v0,t2
  40072c:	03e00008 	jr	ra
  400730:	24420001 	addiu	v0,v0,1

00400734 <.gk_inc_loop>:
  400734:	081001b9 	j	4006e4 <.gk_loop>
  400738:	254a0001 	addiu	t2,t2,1

0040073c <.gk_end_loop>:
  40073c:	03e00008 	jr	ra
  400740:	00001025 	move	v0,zero

00400744 <main>:
  400744:	23bdfffc 	addi	sp,sp,-4
  400748:	2408000a 	li	t0,10
  40074c:	afa80000 	sw	t0,0(sp)
  400750:	23bdffff 	addi	sp,sp,-1
  400754:	2408006a 	li	t0,106
  400758:	a3a80004 	sb	t0,4(sp)
  40075c:	03e00008 	jr	ra
  400760:	23bd0005 	addi	sp,sp,5

Disassembly of section .data:

10010000 <rnd_state>:
	...

10010010 <division>:
10010010:	00000000 	nop

10010014 <remainder>:
10010014:	00000000 	nop

10010018 <chr_attr>:
	...

10010019 <cursor_col>:
	...

1001001a <cursor_row>:
	...

1001001c <next_key_time>:
1001001c:	00000000 	nop

10010020 <hi>:
10010020:	00000000 	nop

10010024 <lo>:
10010024:	00000000 	nop

10010028 <str0>:
10010028:	69203d20 	0x69203d20
1001002c:	00000000 	nop

10010030 <i>:
10010030:	00000000 	nop

10010034 <str2>:
10010034:	456e6420 	0x456e6420
10010038:	6f66206c 	0x6f66206c
1001003c:	6f6f7000 	0x6f6f7000

Disassembly of section .gnu.attributes:

00000000 <.gnu.attributes>:
   0:	41000000 	bc0f	4 <_gp+0x4>
   4:	0f676e75 	jal	d9db9d4 <main+0xd5db290>
   8:	00010000 	sll	zero,at,0x0
   c:	00070401 	0x70401
