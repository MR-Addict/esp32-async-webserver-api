// offical headers
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <esp_timer.h>

// variables
String name;
bool status;
bool updateSensor;

const uint8_t INT_PIN = 19;
const char* ssid = "your_ssid";
const char* password = "your_password";

esp_timer_handle_t timer;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// custom headers
#include "bitmap.h"
#include "store.h"
#include "oled.h"
#include "server.h"
#include "init.h"

void setup() {
  // init utils
  initUtils();
  initWifi();
  initHCTimer();

  // render Oled
  renderOled(name, status);
  // set servers
  setupServer();
}

void loop() {
  if (updateSensor) {
    status = digitalRead(INT_PIN);
    renderOled(name, status);
    updateSensor = false;
  }
}
