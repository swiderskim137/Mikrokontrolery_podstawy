#include "esp_common.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/freeRTOS.h"
#include "freertos/task.h"
#include "gpio.h"

void app_main(void)
{
    GPIO_ConfigTypeDef io_conf;
    io_conf.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    io_conf.GPIO_Mode = GPIO_Mode_Output;
    io_conf.GPIO_Pin = ((1<<GPIO_Pin_2));
    //io_conf.pull_down_en = 0;
    io_conf.GPIO_Pullup = 0;
    
    gpio_config(&io_conf);
  
  
    while (1)
    {
        gpio_set_level(16, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(16, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}