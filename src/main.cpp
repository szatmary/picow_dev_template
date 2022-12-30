
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

int main()
{
    stdio_init_all();
    cyw43_arch_init();
    TaskHandle_t blink;
    xTaskCreate(blink_task, "Blinky", configMINIMAL_STACK_SIZE, nullptr, tskIDLE_PRIORITY, &blink);
    vTaskStartScheduler();
    cyw43_arch_deinit();
    return 0;
}
