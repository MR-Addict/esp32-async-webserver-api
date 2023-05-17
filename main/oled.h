void renderOled(String name, bool status) {
  oled.clearDisplay();

  oled.setCursor(47, 25);
  oled.print("Name:" + name);
  oled.setCursor(47, 40);
  oled.print(status ? "Status:Open" : "Status:Closed");

  oled.drawBitmap(0, 8, status ? lamp_on_40x48 : lamp_off_40x48, 40, 48, WHITE);
  oled.display();
}
