.data # Lu tru bien
    inputA: .asciiz "Nhap so nguyen A: "
    inputB: .asciiz "Nhap so nguyen B: "
    cong: .asciiz "A + B = "
    tru: .asciiz "\nA - B = "
    nhan: .asciiz "\nA * B = "
    chia: .asciiz "\nA / B = "
    du: .asciiz "\nA % B = "
    warn: .asciiz "\nKhong tinh duoc = "
    
.text # Ham
    # cout A
    la $a0, inputA
    li $v0, 4
    syscall
    
    # cin A
    li $v0, 5
    syscall
    move $s0, $v0
    
    # cout B
    la $a0, inputB
    li $v0, 4
    syscall
    
    # cin B
    li $v0, 5
    syscall
    move $s1, $v0
    
main:
    # Phep cong
    add  $t0, $s0, $s1
    la $a0, cong
    li $v0, 4
    syscall
    # in kq
    li $v0, 1
    move $a0, $t0
    syscall
    
    # Phep tru
    sub $t0, $s0, $s1
    la $a0, tru
    li $v0, 4
    syscall
    # in kq
    li $v0, 1
    move $a0, $t0
    syscall
    
    # Phep nhan
    mult $s0, $s1
    mflo $t0
    la $a0, nhan
    li $v0, 4
    syscall
    #in kq
    li $v0, 1
    move $a0, $t0
    syscall
    
    # Phep chia
    blez $s1, error
    div $s0, $s1
    mflo $t0
    la $a0, chia
    li $v0, 4
    syscall
    # in kq
    li $v0, 1
    move $a0, $t0
    syscall
    
    # du
    mfhi $t1
    la $a0, du
    li $v0, 4
    syscall
    # in kq
    li $v0, 1
    move $a0, $t1
    syscall
    
    #LO (phan thap), HI (phan cao)
    
    # return 0
    li $v0, 10
    syscall

error:
    la $a0, warn
    li $v0, 4
    syscall

