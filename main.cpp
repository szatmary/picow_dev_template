
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#ifndef SSID
#define SSID "default"
#endif

#ifndef PASSWD
#define PASSWD "default"
#endif

void blink(int speed, int count)
{
    while (count--) {
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
    cyw43_arch_enable_sta_mode();

    int wait = 0; // seconds
    while (true) {
        int status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
        if (CYW43_LINK_UP == status) {
            printf("CYW43_LINK_UP\n");
            blink(500, 2);
            continue;
        }

        if (wait > 0 && (CYW43_LINK_NOIP == status || CYW43_LINK_JOIN == status)) {
            --wait;
            sleep_ms(1000);
            continue;
        }

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        switch (status) {
        case CYW43_LINK_NOIP:
            printf("CYW43_LINK_NOIP\n");
            break;
        case CYW43_LINK_JOIN:
            printf("CYW43_LINK_JOIN\n");
            break;
        case CYW43_LINK_FAIL:
            printf("CYW43_LINK_FAIL\n");
            break;
        case CYW43_LINK_NONET:
            printf("CYW43_LINK_NONET\n");
            break;
        case CYW43_LINK_BADAUTH:
            printf("CYW43_LINK_BADAUTH\n");
            break;
        case CYW43_LINK_DOWN:
            printf("CYW43_LINK_DOWN\n");
            break;
        default:
            printf("UNKNOWN\n");
            break;
        }

        printf("Connecting\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        auto err = cyw43_arch_wifi_connect_async(SSID, PASSWD, CYW43_AUTH_WPA2_AES_PSK);
        if (err >= 0) {
            wait = 30; // seconds
        } else {
            printf("cyw43_arch_wifi_connect_async %d\n", err);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
        sleep_ms(1000);
    }

    cyw43_arch_deinit();
}
