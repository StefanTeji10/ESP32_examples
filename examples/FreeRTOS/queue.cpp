/**
 *  
 * A queue is quite similar to a semaphore, but it has the extra advantage
 * that we can axtually send data with it. 
 * 
 * Queue has it size, and we can add number of elements no bigger then that size ,
 * but when we read the item from queue, we are immediatly also removing item from the queue
 * 
 * NOTE: For all tasks, if we have task with higher priority then other tasks, then we need to add vTaskDelay to put that task to sleep or
 * we can use some other option to pause or stop the task... 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// queue handler
xQueueHandle queue;

void listenForHTTP(void *params)
{
  int count = 0;
  while (true)
  {
    count++;
    printf("received http message\n");

    // 1. param --> to what queue element to send
    // 2. param --> actual item that we want to send, but we are sending the address of our item, pointer
    // 3. param --> how long I am going to wait if i am trying to basically put something onto the queue
    long ok = xQueueSend(queue, &count, 1000 / portTICK_PERIOD_MS);
    if(ok) 
    {
      printf("added message to queue\n");
    } 
    else 
    {
       printf("failed to add message to queue\n");
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  { 
    int rxInt;
    if(xQueueReceive(queue, &rxInt , 5000 / portTICK_PERIOD_MS))
    {
      printf("doing something with http %d\n", rxInt);
    }
  }
}

void app_main(void)
{
    // queue creation parameters --> 1. how long is my queue, how big one of these items within the queue are. 
  queue = xQueueCreate(3, sizeof(int));
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}