void initUtils() {
  // pinout
  pinMode(2, OUTPUT);
  pinMode(INT_PIN, INPUT_PULLUP);
  // serial
  Serial.begin(115200);
  // init global status
  readConfigFromEEPROM(&name);
}

void initWifi() {
  // init wifi
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  // indicate wifi connected
  digitalWrite(2, HIGH);
  Serial.printf("\nLocal IP: %s", WiFi.localIP().toString().c_str());

  // init oled
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    Serial.println("SSD1306 allocation failed");
  oled.setTextColor(WHITE);
}

void timerCallback(void* arg) {
  updateSensor = true;
}

void initHCTimer() {
  esp_timer_create_args_t timerConfig;
  timerConfig.callback = timerCallback;
  timerConfig.arg = NULL;
  esp_timer_create(&timerConfig, &timer);
  esp_timer_start_periodic(timer, 1000 * 1000);
}
