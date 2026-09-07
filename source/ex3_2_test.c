/*
 * ex3_2_test.c - bring-up / verification helper for TTK4155 exercise 3.2
 * (Address decoding and external RAM)
 *
 * Covers:
 *   - Step 1  : address-latch test        -> test_address_latch()
 *   - Step 4-5: address-decoder CS test   -> test_address_decoder()
 *   - SRAM verification (Fig. 21 in the manual, reused as-is) -> SRAM_test()
 *
 * Assumes the recommended memory map from Figure 20 (single-bit decode):
 *   ADC  : 0x1000 - 0x17FF
 *   SRAM : 0x1800 - 0x1FFF   (2 KiB used)
 * Went for the 3 KiB "challenge" mapping instead? Change the four #defines
 * below (ADC 0x1000-0x13FF, SRAM 0x1400-0x1FFF, SRAM_SIZE 0xC00) - nothing
 * else in the file needs to change.
 *
 * Assumes printf() is already wired to your UART driver from exercise 3.1.
 */

#define F_CPU 4915200UL     /* crystal from ex. 3.1.4 - must come before delay.h */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* ---- Memory map (Figure 20, "Recommended") ---- */
#define ADC_BASE   0x1000u
#define ADC_END    0x17FFu
#define SRAM_BASE  0x1800u
#define SRAM_SIZE  0x0800u

/* ---- Pick what this build runs ---- */
#define RUN_LATCH_TEST      1
#define RUN_SRAM_TEST       1
#define RUN_DECODER_TEST    1
#define DECODER_TEST_CYCLES 30

static void enable_external_memory(void)
{
    /* Routes PORTA/PORTC/PE1/PD6/PD7 to the external bus, see tip 3.2.8 */
    MCUCR |= (1 << SRE);
}

#if RUN_LATCH_TEST
/* Step 1.
 * The 74ALS573 only ever shows the LOW byte of the last address that hit
 * the bus, so neither the data written nor anything behind the decoder
 * matters here - only the address does.
 *   Pass 1: a walking single bit, so each LED can be matched to its own
 *           latch pin/wire one at a time.
 *   Pass 2: a slow 0x00..0xFF count, as a general "does this look right"
 *           check across all 8 lines at once.
 */
static void test_address_latch(void)
{
    printf("\n[latch] pass 1: walking bit - one LED at a time\n");
    for (uint8_t bit = 0; bit < 8; bit++) {
        uint8_t pattern = (uint8_t)(1u << bit);
        volatile uint8_t *p = (volatile uint8_t *)(ADC_BASE | pattern);
        printf("[latch] expect 0x%02X\n", pattern);
        *p = 0x00;
        _delay_ms(600);
    }

    printf("[latch] pass 2: 0x00..0xFF count\n");
    for (uint16_t low = 0; low <= 0xFF; low++) {
        volatile uint8_t *p = (volatile uint8_t *)(ADC_BASE | low);
        *p = 0x00;
        _delay_ms(120);
    }
    printf("[latch] done\n");
}
#endif

#if RUN_DECODER_TEST
static void hammer(uint16_t addr, uint16_t reps)
{
    volatile uint8_t *p = (volatile uint8_t *)addr;
    for (uint16_t i = 0; i < reps; i++) {
        *p = 0xAA;
    }
}

/* Step 4-5.
 * CS_ADC/CS_SRAM aren't wired back to the AVR, so there's nothing for
 * software to check - this just parks the bus in one region at a time,
 * long enough that you can put the scope on CS_ADC and CS_SRAM and
 * confirm only the right one pulses while its region is being hit.
 * Using the two addresses right at the boundary (0x17FF / 0x1800) also
 * catches an off-by-one in the decode logic that a mid-range address
 * wouldn't.
 */
static void test_address_decoder(void)
{
    printf("\n[decoder] probe CS_ADC / CS_SRAM now\n");
    for (uint16_t cycle = 0; cycle < DECODER_TEST_CYCLES; cycle++) {
        printf("[decoder] accessing ADC region (0x%04X)\n", ADC_END);
        hammer(ADC_END, 20000);
        _delay_ms(800);

        printf("[decoder] accessing SRAM region (0x%04X)\n", SRAM_BASE);
        hammer(SRAM_BASE, 20000);
        _delay_ms(800);
    }
    printf("[decoder] done\n");
}
#endif

#if RUN_SRAM_TEST
/* SRAM_test(), reproduced from the manual's Figure 21.
 * Only change: 0x1800 / 0x800 now reference the #defines above instead of
 * being hardcoded a second time. Logic (including the "retreived_value"
 * spelling) is untouched.
 */
void SRAM_test(void)
{
    volatile char *ext_ram = (char *) SRAM_BASE;
    uint16_t ext_ram_size = SRAM_SIZE;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;

    printf("Starting SRAM test...\n");

    uint16_t seed = rand();

    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n",
                   i, retreived_value, some_value);
            write_errors++;
        }
    }

    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",
                   i, retreived_value, some_value);
            retrieval_errors++;
        }
    }

    printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors in retrieval phase\n\n",
           write_errors, retrieval_errors);
}
#endif

int main(void)
{
    /* your UART init + stdout redirection from exercise 3.1 goes here -
       everything below assumes printf() already reaches the terminal */

    enable_external_memory();

#if RUN_LATCH_TEST
    test_address_latch();
#endif

#if RUN_SRAM_TEST
    SRAM_test();
#endif

#if RUN_DECODER_TEST
    test_address_decoder();
#endif

    printf("\nAll enabled tests finished.\n");
    for (;;) {
        /* park here - reset the board to run again */
    }
}
