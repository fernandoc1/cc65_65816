/* Example using 65C816-specific instructions */

static unsigned char g_value;
static unsigned char g_result;

/* Demonstrate REP/SEP (65C816 status register control) */
void set_16bit_mode(void) {
    asm("rep #$30");   /* 65C816: clear M and X flags -> 16-bit A/X/Y */
    asm("sep #$20");   /* set M flag -> back to 8-bit accumulator */
}

/* Demonstrate XBA (swap accumulator bytes) */
void swap_accumulator_bytes(void) {
    asm("lda #$12");
    asm("xba");        /* 65C816: swap A low/high byte */
    asm("sta %v", g_value);
}

/* Demonstrate direct page transfer instructions */
void transfer_direct_page(void) {
    asm("lda #$00");
    asm("xba");        /* ensure high byte clear */
    asm("tcd");        /* 65C816: transfer A -> Direct Page register */
}

/* Demonstrate TDC (direct page -> accumulator) */
void read_direct_page(void) {
    asm("tdc");        /* 65C816: Direct Page -> A */
    asm("sta %v", g_result);
}

/* Simple arithmetic still works as normal 6502 code */
unsigned char add_values(unsigned char a, unsigned char b) {
    g_value = a;
    g_result = b;

    asm("lda %v", g_value);
    asm("clc");
    asm("adc %v", g_result);
    asm("sta %v", g_result);

    return g_result;
}

void main(void) {
    unsigned char r;

    set_16bit_mode();
    swap_accumulator_bytes();
    transfer_direct_page();
    read_direct_page();

    r = add_values(10, 20);

    while (1) {
    }
}
