#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h" // to have uart_tx_wait_idle, function that make a esp32 to finish uart task and then go to sleep

void app_main()
{
    // parametar is to define how logn we want ESP32 to sleep in microseconds
    esp_sleep_enable_timer_wakeup(5000000);
    printf("goind for a nap\n");
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

    // To get how long the ESP32 has been running
    int64_t before = esp_timer_get_time();

    esp_light_sleep_start();

    int64_t after = esp_timer_get_time();

    printf("napped for %lld\n", (after-before) / 1000);

}