#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/ip4_addr.h"

#include "FreeRTOS.h"
#include "task.h"

void blink_task(__unused void* params)
{
    int speed = 500;
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(speed);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(speed);
    }
}

int main()
{
    stdio_init_all();
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA)) {
        printf("failed to initialise\n");
        return 1;
    }
    printf("initialised\n");

    TaskHandle_t task;
    xTaskCreate(blink_task, "TestMainThread", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &task);
    vTaskStartScheduler();
    printf("got here somehow");
    return 0;
}