#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// binary semaphore is useful is to indicate that something has happened.
// in this example we are pretending that we are listening for HTTP socket
// 
// here in this example we are trying to indicate form one task to another task to do something
// 


// semaphore handler
xSemaphoreHandle binSemaphore;



void listenForHTTP(void *params)
{
  while (true)
  {
    printf("received http message\n");
    xSemaphoreGive(binSemaphore);
    printf("processed http message\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{ 
  while (true)
  {
      // it goes true this loop once every time when some task give semaphore...
    xSemaphoreTake(binSemaphore, portMAX_DELAY);
    printf("doing something with http\n");
  }
}

void app_main(void)
{
    //creating binary semaphore, same handler as mutex but different creation
  binSemaphore = xSemaphoreCreateBinary();
  
  // trebalo bi promeniti prioritete, da bi se videlo kako to sve funkcionise
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}