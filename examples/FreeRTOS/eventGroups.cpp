/**
 * EVENT GROUPS
 * 
 * Event groups are very similar to semaphores, but what's really nice about them is that they actually can operate off multiple indicators. 
 * In other words, it is not just one flag that will get a semaphore to start or stop.
 * In an event group, you can have multiple events, that will then trigger a task. 
 * 
 * 
 */ 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

// event qroup handler
EventGroupHandle_t evtGrp;
const int gotHttp = BIT0; // (1<<0)
const int gotBLE = BIT1; // (1<<1)

void listenForHTTP(void *params)
{
  while (true)
  {
      // setting bits --> 0, and 1
    xEventGroupSetBits(evtGrp, gotHttp);
    printf("got http\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void listenForBluetooth(void *params)
{
  while (true)
  {
    xEventGroupSetBits(evtGrp, gotBLE);
    printf("got BLE\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  {
      // parametri, flegovi mogu biti jako korisni true true, oni znace da resetuju bitove, pa event moze da se ponovi
    xEventGroupWaitBits(evtGrp, gotHttp | gotBLE, true, true, portMAX_DELAY);
    printf("received http and BLE\n");
  }
}

void app_main(void)
{
  evtGrp = xEventGroupCreate();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 1, NULL);
  xTaskCreate(&listenForBluetooth, "get BLE", 2048, NULL, 1, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}