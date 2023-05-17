void storeConfigToEEPROM(String name) {
  DynamicJsonDocument doc(50);
  doc["name"] = name;

  int startAddress = 0;
  String jsonString;
  serializeJson(doc, jsonString);
  int length = jsonString.length();

  EEPROM.begin(length + 1);
  for (int i = 0; i < length; i++) {
    EEPROM.write(startAddress + i, jsonString[i]);
  }
  EEPROM.write(startAddress + length, '\0');  // Null-terminate the string
  EEPROM.commit();
  EEPROM.end();
}

void readConfigFromEEPROM(String* name) {
  int startAddress = 0;
  String jsonString;
  char c;
  EEPROM.begin(4096);
  while ((c = EEPROM.read(startAddress++)) != '\0') {
    jsonString += c;
  }
  EEPROM.end();

  DynamicJsonDocument doc(100);
  deserializeJson(doc, jsonString);

  // parse and store data
  if (doc.containsKey("name")) {
    *name = doc["name"].as<String>();
  }
}
