
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

void blink_task(__unused void* params)
{
    const static int speed = 500;
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(speed);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(speed);
    }
}

void main_task(__unused void* params)
{
    cyw43_arch_init();
    TaskHandle_t blink;
    xTaskCreate(blink_task, "Blinky", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &blink);
    while (true) {
        vTaskDelay(1000);
    }
}

int main()
{
    stdio_init_all();
    TaskHandle_t main;
    xTaskCreate(main_task, "main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &main);
    vTaskStartScheduler();
    return 0;
}
