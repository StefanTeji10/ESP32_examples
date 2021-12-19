#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"

#define TXD_PIN 4
#define RXD_PIN 5

#define RX_BUF_SIZE 1024

void app_main(void)
{
    // structure for configuring UART
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
        // flow control is interesting because, 
        // if we were going to use that, we would need some extra lines or some extra pines for
        // clear to send and ready to send.
        // Two things could basically signal to each other when they were going to be sending and receiving data. 
        // This is sometimes necessary if your buffer get very, very busy. 
    };
    // Initializing UART
    // First param takes which UART we are going to be utilizing. 
    // There are 3 UARTs that are available on the ESP32
    // Typically UART 0 is used for falshing and serial monithoring. 
    //
    // Second param is the config structure
    uart_param_config(UART_NUM_1, &uart_config);

    // Now, we need to set up the pins for our UART. 
    // We use the UART set pin in order to do this. 
    // First param, choosing UART
    // Second and third params TX and RX
    // Fourth - rts - Ready to send
    // Fifth - cts - also part of flow control as rts and it stands for Clear to Send
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // installing the UART driver
    // 1. param, choosing the UART
    // 2. param, buffer size for UART receiving information
    // 3. param, transmission buffer size
    // 4. size and 5. handler --> Queue
    // 6. interrupt flags that we can use
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE, 0, 0, NULL, 0);

    char message[] = "ping";
    printf("sending: %s\n", message);

    // Writting, sending message to UART
    // 1. param, choosing the UART
    // 2. param, message, char array
    //3. param, size of data that we want to send
    uart_write_bytes(UART_NUM_1, message, sizeof(message));


    // Receiving the message

    // buffer for incoming massage
    char incoming_message[RX_BUF_SIZE];
    memset(incoming_message, 0, sizeof(incoming_message));

    // 1. param: choosing the UART
    // 2. param: buffer in which we are receiving message, byte array
    // 3. param: buffer size
    // 4. param: ticks to wait, need to see to be ballanced
    uart_read_bytes(UART_NUM_1, (uint8_t *)incoming_message, RX_BUF_SIZE, pdMS_TO_TICKS(500));
    printf("received: %s\n", incoming_message);

}