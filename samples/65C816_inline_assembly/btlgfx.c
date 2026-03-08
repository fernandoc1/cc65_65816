void BtlgfxMain(void)
{
    asm(
        /* save registers and set data bank */
        "php\n"
        "phb\n"
        "phk\n"
        "plb\n"

        /* set 16-bit A/X/Y */
        "rep #$30\n"

        /* initialize battle graphics */
        "jsr InitBattleGfx\n"

        "BtlgfxMain_Loop:\n"

        /* update frame logic */
        "jsr UpdateBattleGfx\n"

        /* draw battle graphics */
        "jsr DrawBattleGfx\n"

        /* update sprite system */
        "jsr UpdateBattleSprites\n"

        /* update background layers */
        "jsr UpdateBattleBG\n"

        /* repeat forever */
        "jmp BtlgfxMain_Loop\n"

        /* restore registers */
        "plb\n"
        "plp\n"

        /* return from long call */
        "rtl\n"
    );
}
