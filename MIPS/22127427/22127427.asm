.data
    tb1_input_array: .asciiz "Enter value: "
    tb2_output_array: .asciiz "Array: "
    tb3_input_size: .asciiz "Enter the size of array: "
    tb4_result: .asciiz "Sum of odd numbers in array = "
    tb5_error: .asciiz "The size is invalid. Try again.\n"

    separate: .asciiz " "
    end_line: .asciiz "\n"
    prompt_exit: .asciiz "Exit with code 0"

    result: .word 0
    size: .word 0
    array: .space 400

.text
main:
    jal input_array
    jal output_array
    jal sum_odd

    # Print the result of the program
    li $v0, 4
    la $a0, tb4_result
    syscall
    lw $a0, result
    li $v0, 1
    syscall
    
    # Exit the program
    li $v0, 4
    la $a0, end_line
    syscall
    li $v0, 4
    la $a0, prompt_exit
    syscall
    li $v0, 10
    syscall

input_array:
    # Storage the return address into $ra
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    # Storage the index of array into $t0
    li $t0, 0 

    # Loop to input size within the valid range
    input_size_loop:
        li $v0, 4
        la $a0, tb3_input_size
        syscall

        li $v0, 5
        syscall
        sw $v0, size
        lw $t1, size
        blt $t1, 1, input_size_error
        bge $t1, 100, input_size_error
        j continue_input_array
    
    input_size_error:
        # Print error message
        li $v0, 4
        la $a0, tb5_error
        syscall
        j input_size_loop
    
    continue_input_array:
        # Load size into $t1
        lw $t1, size
        sll $t1, $t1, 2

        # Open loop array
        loop_input_array:
            bge $t0, $t1, end_input 

            # Print prompt
            li $v0, 4
            la $a0, tb1_input_array
            syscall

            # Read input from user
            li $v0, 5
            syscall
            sw $v0, array($t0)

            # Increase the index
            addi $t0, $t0, 4
            j loop_input_array

        end_input:
        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra

output_array:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    # Storage the index of array into $t0
    li $t0, 0
    lw $t1, size
    sll $t1, $t1, 2

    # Print prompt
    li $v0, 4
    la $a0, tb2_output_array
    syscall

    # Open output loop
    loop_output_array:
        bge $t0, $t1, end_output

        # Print each element of the array
        li $v0, 1
        lw $a0, array($t0)
        syscall

        # Print space to separate
        li $v0, 4
        la $a0, separate
        syscall

        # Increase the index
        addi $t0, $t0, 4
        j loop_output_array

    end_output:
    li $v0, 4
    la $a0, end_line
    syscall
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

check_odd:
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    andi $v0, $a0, 1
    beqz $v0, not_odd
    li $v0, 1
    j end_odd

    not_odd:
    li $v0, 0

    end_odd:
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

sum_odd:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    # Storage the index of array into $t0
    li $t0, 0
    lw $t1, size
    sll $t1, $t1, 2
    li $t2, 0  # Initialize the sum to 0

    # Open loop sum 
    loop_sum_odd:
        bge $t0, $t1, end_sum
        lw $a0, array($t0)
        jal check_odd
        beqz $v0, not_odd_element

        # Add the odd number to the sum
        add $t2, $t2, $a0

        # Increase the index
        not_odd_element:
        addi $t0, $t0, 4
        j loop_sum_odd

    end_sum:
    sw $t2, result  # Store the sum in result
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra
