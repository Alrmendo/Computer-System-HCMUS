.data 
    inputA: .asciiz "Input integer A: "
    inputB: .asciiz "Input integer B: "
    add: .asciiz "A + B: "
    sub: .asciiz "\nA - B: "
    mul: .asciiz "\nA * B: "
    div: .asciiz "\nA / B: "
    mod: .asciiz "\nA % B: "
    error: .asciiz "\nCan not calculate"

.text
    # Print input A
    la $a0, inputA
    li $v0, 4
    syscall
    
    # Read input A
    li $v0, 5
    syscall
    move $s0, $v0
    
    # Print input B
    la $a0, inputB
    li $v0, 4
    syscall
    
    # Read input B
    li $v0, 5
    syscall
    move $s1, $v0

main:
    # Calculate Add
    add $t0, $s0, $s1
    la $a0, add
    li $v0, 4
    syscall
    # Print the result
    li $v0, 1
    move $a0, $t0
    syscall 
    
    
    # Calculate Subtract
    sub $t0, $s0, $s1
    la $a0, sub
    li $v0, 4
    syscall
    # Print the result
    li $v0, 1
    move $a0, $t0
    syscall
    

    # Exit the program
    li $v0, 10
    syscall
