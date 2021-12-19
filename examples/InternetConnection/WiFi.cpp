/*
#include <stdio.h>
#include "esp_wifi.h"  //wifi uses the event loop
#include "esp_event.h" //callbacks
#include "nvs_flash.h" //non-volatile storage
#include "esp_http_client.h" //to see how we can reach out the internet
#include "protocol_examples_common.h" //quick way how to connect to the internet, examples

esp_err_t clientEvent(esp_http_client_event_t *evt)
{
    switch(evt->event_id){
    case HTTP_EVENT_ON_DATA:
        printf("%.*s\n", evt->data_len, (char *)evt->data);
        break;
        default:
        break;
    }
    return ESP_OK;
}


void app_main() 
{
    // initializing NVS
    nvs_flash_init();
    // initializing TCP/IP adapter
    tcpip_adapter_init();
    //setting the event loop
    esp_event_loop_create_default();

    // connection to the internet using "example_connect"
    //
    //It is not intended to be used in real world applications.
    // See examples under examples/wifi/getting_started/ and examples/ethernet/
     //for more complete Wi-Fi or Ethernet initialization code.
     // 
    example_connect();
    // potrebno je da u Kconfig fajlu podesimo ssid i password to se radi kroz idf.py menuconfig


    //creating client
    esp_http_client_config_t clientConfig = {
        .url = "http://google.com",
        .event_handler = clientEvent
    };

    esp_http_client_event_handle_t client = esp_http_client_init(&clientConfig);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}*/