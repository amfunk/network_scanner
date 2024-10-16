#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"

void blinkLed ()
{
  // Refactor this to process incoming ICMP packets
  while (true)
  {
    cyw43_arch_gpio_put(0, 1);
    sleep_ms(2000);
    cyw43_arch_gpio_put(0, 0);
    sleep_ms(1000);
  }
}

int main ()
{
  stdio_init_all();
  lwip_nosys_init();

  if (cyw43_arch_init())
  {
    printf("Failed to initialize\n");
    return -1;
  }

  if (cyw43_arch_wifi_connect_blocking(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK))
  {
    printf("Failed to connect\n");
    return -1;
  }
  else
  {
    multicore_launch_core1(blinkLed);
  }

#if 1
  // Send ICMP packets here
  struct pbuf *packet = pbuf_alloc(PBUF_IP, 74, PBUF_RAM);
  //cyw43_cb_tcpip_init(&cyw43_state, CYW43_ITF_STA); // Not sure if I need this after cyw43_arch_init()
  while (true)
  {
    cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, 74, &packet, true);
  }
#endif

  return 0;
}
