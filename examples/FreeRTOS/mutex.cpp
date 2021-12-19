#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

//Semaphore flag
xSemaphoreHandle mutexBus;


/**
 * Problem je u tome sto jedan task hoce da pise na Bus samo u trenutku 
 * kada je potpuno siguran da je drugi task zavrsio svoje ispisivanje.
 * Nepozeljno je ponasanje da vise taskova upisuje na jedan bus u isto vreme.
 * A to se u praksi moze dogoditi...
 * 
 * Da bi taj problem resili koristicemo MUTEX - Mutual Exclusion Object
 * MUTEX Semaphore
 */ 



/**
 * Method that can be used for writing to I2C Bus, Serial port, or anything else...
 * 
 * 
 */ 
void writeToBus(char *message)
{
  printf(message);
}

void task1(void *params)
{
  while (true)
  {
    printf("reading temperature \n");

    // Drugi parameter sluzi za timeout, tj da odredimo koliko vremena cemo cekata u slucaju ne predvidjenih okolnosti da task pusti semafor
    // logika sa if recima je, da ukoliko tasko moze da uzme semaphore onda krene u izvrsavanje do tada ceka...
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("tempratrue is 25c\n");

      // ukoliko ne bi bilo toga da taskovi predaju semaphore, on bi se mogao izvrsiti kod bi se mogao izvrsiti samo jednom 
      xSemaphoreGive(mutexBus);
    }
    else
    {
        // u slucaju da ne moze da uzme task
      printf("writing temperature timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
    printf("reading humidity\n");

    // Drugi parameter sluzi za timeout, tj da odredimo koliko vremena cemo cekata u slucaju ne predvidjenih okolnosti da task pusti semafor
    // logika sa if recima je, da ukoliko tasko moze da uzme semaphore onda krene u izvrsavanje do tada ceka...
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("humidity is 50 \n");
      // ukoliko ne bi bilo toga da taskovi predaju semaphore, on bi se mogao izvrsiti kod bi se mogao izvrsiti samo jednom 
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("writing humidity timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  // creating mutex flag  
  mutexBus = xSemaphoreCreateMutex();


  xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
}