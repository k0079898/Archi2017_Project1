    addi  $sp, $sp, -4
    sw    $ra, 0($sp)
    lw    $a0, 0($0)
    lw    $a1, 4($0)
    jal   L1
    sw    $v0, 8($0)
    lw    $ra, 0($sp)
    addi  $sp, $sp, 4
    lw    $a2, 8($0)
    lw    $a3, 12($0)
    add   $t0, $a0, $a1
    sub   $t1, $a3, $a2
    and   $0, $a1, $a2
    lw    $t2, 8($0)
    or    $0, $t0, $t1
    addi  $s0, $0, 0xFFFF
    addi  $s1, $a0, 4
    beq   $s0, $s1, L2
L1: nor   $v0, $a0, $a1
    jr    $ra
L2: addu  $s2, $s0, $s1
    halt
