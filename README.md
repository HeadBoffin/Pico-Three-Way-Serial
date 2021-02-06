# Pico-Three-Way-Serial
Serial communications example/starter for the Raspberry Pi Pico board


The setup splits out the two hardware UARTs plus the USB-over-Serial.

This allows you (me) to have a debug port on USB and two serial devices, send setup commands via the USB and see what's going on.

For me, the application is for a comms module on a UART like ESP8266 for Wifi or a LoRa/LoRaWAN AT based module and have a GPS on another UART.

In the main loop you can choose which serial port relays traffic to the other (two) serial ports.

