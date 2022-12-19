#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// https://randomnerdtutorials.com/esp-now-many-to-one-esp32/

#define TZ_OFFSET 0
#define TZ_DST 0

struct payload {
  u8 id;
};

void on_data_recv(u8 *mac_addr, u8 *data, u8 len) {
  struct payload *r = (struct payload *)data;

  Serial.printf("%u\n", r->id);
  // Serial.printf("Data received from : %02X:%02X;%02X:%02X:%02X:%02X, id %u, of %u bytes\n",
  // mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5], r->id, len);
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  // Serial.println("ESP MAC ADDR : " + WiFi.macAddress());

  WiFi.mode(WIFI_STA);

  while (esp_now_init() != 0) {
    Serial.println("100");
    delay(500);
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(on_data_recv);
  delay(1000);
  Serial.println("200");
}

void loop() {
  delay(2000);
}
