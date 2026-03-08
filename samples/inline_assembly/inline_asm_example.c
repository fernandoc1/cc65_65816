/*
 * Inline Assembly Example for cc65
 * 
 * This demonstrates basic inline assembly syntax with cc65.
 * Compile with: cc65 -O inline_asm_example.c
 */

#include <stdint.h>

/* Global variables for assembly access */
static unsigned char g_value;
static unsigned char g_result;

/* Example 1: Simple inline assembly to load immediate value */
void clear_with_asm(void) {
    asm("lda #$00");
    asm("sta %v", g_value);
}

/* Example 2: Inline assembly with labels for delay */
void delay_loop(unsigned char count) {
    g_value = count;
    asm("ldx %v", g_value);
label:
    asm("dex");
    asm("bne %g", label);
}

/* Example 3: Using assembly to perform arithmetic */
unsigned char add_with_carry(unsigned char a, unsigned char b) {
    g_value = a;
    g_result = b;
    asm("lda %v", g_value);
    asm("clc");
    asm("adc %v", g_result);
    asm("sta %v", g_result);
    return g_result;
}

/* Example 4: Setting processor flags */
unsigned char check_zero_flag(unsigned char value) {
    g_value = value;
    g_result = 0;
    asm("lda %v", g_value);
    asm("beq %g", is_zero);
    asm("jmp %g", end);
is_zero:
    asm("inc %v", g_result);
end:
    return g_result;
}

/* Example 5: Rotate left */
unsigned char rotate_left(unsigned char value) {
    g_value = value;
    asm("lda %v", g_value);
    asm("asl a");
    asm("sta %v", g_value);
    return g_value;
}

/* Example 6: Bit test */
unsigned char test_bit(unsigned char value, unsigned char bit) {
    g_value = value;
    g_result = (1 << bit);
    asm("lda %v", g_value);
    asm("and %v", g_result);
    asm("sta %v", g_result);
    return g_result;
}

/* Example 7: Multi-statement assembly block */
static unsigned char g_temp;

void swap_globals(void) {
    asm("lda %v", g_value);
    asm("sta %v", g_temp);
    asm("lda %v", g_result);
    asm("sta %v", g_value);
    asm("lda %v", g_temp);
    asm("sta %v", g_result);
}

int main(void) {
    unsigned char a, result;
    
    /* Clear using assembly */
    clear_with_asm();
    
    /* Add with carry */
    result = add_with_carry(100, 50);
    
    /* Check zero flag */
    result = check_zero_flag(0);
    result = check_zero_flag(5);
    
    /* Rotate left */
    a = rotate_left(0x40);
    
    /* Test bit */
    result = test_bit(0x08, 3);
    
    /* Swap globals */
    g_value = 10;
    g_result = 20;
    swap_globals();
    
    /* Delay loop */
    delay_loop(100);
    
    return 0;
}
