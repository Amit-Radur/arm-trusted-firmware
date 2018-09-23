/*
 * Copyright (c) 2016-2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <arch.h>
#include <asm_macros.S>
#include <assert_macros.S>
#include <console_macros.S>
#include <drivers/meson/meson_uart.h>


	/*
	 * "core" functions are low-level implementations that don't require
	 * writable memory and are thus safe to call in BL1 crash context.
	 */
	.globl console_meson_core_init
	.globl console_meson_core_putc

	.globl  console_meson_putc
	/* -----------------------------------------------
	 * int console_meson_core_init(uintptr_t base_addr)
	 * Function to initialize the console without a
	 * C Runtime to print debug information. This
	 * function will be accessed by console_init and
	 * crash reporting.
	 * We assume that the bootloader already set up
	 * the HW (baud, ...) and only enable the trans-
	 * mitter and receiver here.
	 * In: x0 - console base address
	 * Out: return 1 on success else 0 on error
	 * Clobber list : x1, x2, x3
	 * -----------------------------------------------
	 */
func console_meson_core_init
	/* Check the input base address */
	cbz	x0, core_init_fail

	/* RX/TX enabled */
	mov	w3, #(AML_UART_TX_EN | AML_UART_RX_EN)
	str	w3, [x0, #AML_UART_CONTROL]

	mov	w0, #1
	ret
core_init_fail:
	mov	w0, wzr
	ret
endfunc console_meson_core_init


#if MULTI_CONSOLE_API
        .globl console_meson_register

        /* -----------------------------------------------
         * int console_16550_register(console_16550_t *console,
                uintptr_t base, uint32_t clk, uint32_t baud)
         * Function to initialize and register a new 16550
         * console. Storage passed in for the console struct
         * *must* be persistent (i.e. not from the stack).
         * In: x0 - UART register base address
         *     w1 - UART clock in Hz
         *     w2 - Baud rate
         *     x3 - pointer to empty console_16550_t struct
         * Out: return 1 on success, 0 on error
         * Clobber list : x0, x1, x2, x6, x7, x14
         * -----------------------------------------------
         */
func console_meson_register
        mov     x7, x30
        mov     x6, x3
        cbz     x6, register_fail
        str     x0, [x6, #CONSOLE_T_MESON_BASE]

        bl      console_meson_core_init
        cbz     x0, register_fail

        mov     x0, x6
        mov     x30, x7
        finish_console_register meson

register_fail:
        ret     x7
endfunc console_meson_register
#else
#endif

	/* --------------------------------------------------------
	 * int console_meson_core_putc(int c, uintptr_t base_addr)
	 * Function to output a character over the console. It
	 * returns the character printed on success or -1 on error.
	 * In : w0 - character to be printed
	 *      x1 - console base address
	 * Out : return -1 on error else return character.
	 * Clobber list : x2
	 * --------------------------------------------------------
	 */
func console_meson_core_putc
#if ENABLE_ASSERTIONS
	cmp	x1, #0
	ASM_ASSERT(ne)
#endif /* ENABLE_ASSERTIONS */

	/* Prepend '\r' to '\n' */
	cmp	w0, #0xA
	b.ne	2f
	/* Check if the transmit FIFO is full */
1:      ldr   w2, [x1, #AML_UART_STATUS] /* status register */
        tst   w2, #(1 << 21)              /* Check TXFIFO FULL bit */
        b.ne    1b
        mov     w2, #0xD                /* '\r' */
        str     w2, [x1, #AML_UART_WFIFO]

        /* Check if the transmit FIFO is full */
2:      ldr   w2, [x1, #AML_UART_STATUS] /* status register */
        tst   w2, #(1 << 21)              /* Check TXFIFO FULL bit */
        b.ne    2b
        str     w0, [x1, #AML_UART_WFIFO]
	ret
endfunc console_meson_core_putc

func console_meson_putc
#if ENABLE_ASSERTIONS
        cmp     x1, #0
        ASM_ASSERT(ne)
#endif /* ENABLE_ASSERTIONS */
        ldr     x1, [x1, #CONSOLE_T_MESON_BASE]
        b       console_meson_core_putc
endfunc console_meson_putc



func console_core_flush
	/* Placeholder */
	mov	w0, #0
	ret
endfunc console_core_flush
