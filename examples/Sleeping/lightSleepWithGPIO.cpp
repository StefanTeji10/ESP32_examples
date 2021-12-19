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

#include "driver/rtc_io.h"
//rtc pin --> allow us to use pins while we are sleeping

#define INPUT_PIN GPIO_NUM_0


void app_main()
{
    gpio_pad_select_gpio(INPUT_PIN);
    gpio_set_direction(INPUT_PIN, GPIO_MODE_INPUT);
    // because we are using already build in pin, and that pin in normaly high
    gpio_wakeup_enable(INPUT_PIN, GPIO_INTR_LOW_LEVEL);

    esp_sleep_enable_gpio_wakeup();

    while (true)
    {

        if(rtc_gpio_get_level(INPUT_PIN) == 0)
        {
            printf("please release button\n");
            do{
                vTaskDelay(pdMS_TO_TICKS(10));
            } while(rtc_gpio_get_level(INPUT_PIN) == 0);
        }

        // parametar is to define how logn we want ESP32 to sleep in microseconds
        esp_sleep_enable_timer_wakeup(5000000);
        printf("goind for a nap\n");
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

        // To get how long the ESP32 has been running
        int64_t before = esp_timer_get_time();

        esp_light_sleep_start();

        int64_t after = esp_timer_get_time();

        //what caused wake up
        esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();

        printf("napped for %lld, reason was %s\n", (after-before) / 1000, reason == ESP_SLEEP_WAKEUP_TIMER? "timer":"button");

    }
    




}