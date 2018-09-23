#ifndef __MESON_UART_H__
#define __MESON_UART_H__

#include <console.h>

#define AML_UART_WFIFO                  0x00
#define AML_UART_RFIFO                  0x04
#define AML_UART_CONTROL                0x08
#define AML_UART_STATUS                 0x0c
#define AML_UART_MISC                   0x10
#define AML_UART_REG5                   0x14

/* UART_CONTROL bits */
#define AML_UART_TX_EN                  0x0001000
#define AML_UART_RX_EN                  0x0002000
#define AML_UART_TX_RST                 0x0400000
#define AML_UART_RX_RST                 0x0800000
#define AML_UART_CLEAR_ERR              0x1000000

#define CONSOLE_T_MESON_BASE            CONSOLE_T_DRVDATA

#ifndef __ASSEMBLY__

#include <types.h>

typedef struct {
        console_t console;
        intptr_t base;
} console_meson_t;


/*
 * Initialize a new MESON console instance and register it with the console
 * framework. The |console| pointer must point to storage that will be valid
 * for the lifetime of the console, such as a global or static local variable.
 * Its contents will be reinitialized from scratch.
 */
int console_meson_register(uintptr_t baseaddr, uint32_t clock, uint32_t baud,
                           console_meson_t *console);

#endif /*__ASSEMBLY__*/

#endif
