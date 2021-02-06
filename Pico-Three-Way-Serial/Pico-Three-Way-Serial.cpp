/**
 * Pico Serial port pass through example
 * You can setup any combination of connections
 * 
 * As an example, you can have USB for your debug / monitoring
 * And then two serial ports for real serial things like GPS etc
 * 
 * By Nick McCloud, HeadBoffin, 3rd Feb 2021, Unlicensed
 */

// Just because this is a C++ file doesn't mean you should go wild with all of C++


#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"


// UART0
#define UART0_ID        uart0
#define UART0_BAUD_RATE 115200
#define UART0_TX_GP    0
#define UART0_RX_GP    1
// UART1
#define UART1_ID        uart1
#define UART1_BAUD_RATE 115200
#define UART1_TX_GP    8
#define UART1_RX_GP    9

// Pico LED
#define LED_GP 25


void delay(uint32_t ms) {
    busy_wait_us(ms * 1000);
}

void flash(uint8_t times, uint8_t on = 25, uint8_t off = 100) {
    for (uint8_t c = 0; c < times; c++) {
        gpio_put(LED_GP, 1);
        delay(on);
        gpio_put(LED_GP, 0);
        delay(off);
    }
}


int main() {
    
    // GPIO init
    gpio_init(LED_GP);
    gpio_set_dir(LED_GP, GPIO_OUT);
    flash(1);       // Let the world know we are alive

    // Setup the USB as as a serial port
    stdio_usb_init();
    // Setup the UART0 port as a seperate item
    uart_init(UART0_ID, UART0_BAUD_RATE);
    gpio_set_function(UART0_TX_GP, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_GP, GPIO_FUNC_UART);
    // Setup the UART1 port
    uart_init(UART1_ID, UART1_BAUD_RATE);
    gpio_set_function(UART1_TX_GP, GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_GP, GPIO_FUNC_UART);

    
    delay(1000);    // Give time for the USB to be setup
    flash(3);       // Time to connect that USB port
    delay(2000);    // Give time for the USB to be connected by the user clicking things

    puts("USB with debug");
    uart_puts(UART0_ID, "UART0 with debug\n");
    //uart_puts(UART1_ID, "UART1\n");

    delay(1000);    // Give time for the USB to be setup

    while (true) {
        // USB serial to UART0 + UART1
        int16_t ch = getchar_timeout_us(100);
        while (ch != PICO_ERROR_TIMEOUT) {
            uart_putc_raw(UART0_ID, ch);    // Send to UART0
            uart_putc_raw(UART1_ID, ch);    // Send to UART1
            printf("%c", ch);               // Echo back so you can see what you've done
            ch = getchar_timeout_us(100);
        }
        
        // UART0 to UART1 & USB
        while (uart_is_readable_within_us(UART0_ID, 100)) {
            uint8_t ch = uart_getc(UART0_ID);
            uart_putc_raw(UART1_ID, ch);    // Send to UART1
            printf("%c", ch);               // Echo to USB
            // If you are using this port to communicate with the module, then  
            // uncomment this to echo back so you can see what you've sent        
            //uart_putc_raw(UART0_ID, ch);    
        }

        //  UART1 to UART0 & USB
        while (uart_is_readable_within_us(UART1_ID, 100)) {
            uint8_t ch = uart_getc(UART1_ID);
            uart_putc_raw(UART0_ID, ch);    // Send to UART0
            printf("%c", ch);               // Echo to USB
        }
    }

    return 0;
}
