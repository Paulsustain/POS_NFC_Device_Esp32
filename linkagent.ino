void LinkAgent(){
 // vTaskSuspend(TaskLedBlink);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Enter USSD");
  display.display();

  for(;;){
    
 char key = keypad.getKey();
  
  if (key != NO_KEY) {
    if (key == '#' && enteredUSSD.length()>4) {
      if (enteredUSSD == enteredUSSD ) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        oled_processing();
        String modifiedString = removeCharacters(enteredUSSD,5,0);
        Serial.print("Modified String is : ");   
        Serial.println("Extracted number: " + modifiedString); 
        //HTTP_POST_REQUEST_AGENT(modifiedString);
        http_post_agent(modifiedString);
        break;

        delay(2000);
      } else {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Invalid USSD");
        display.display();
        delay(2000);
      }
      
      enteredUSSD = "";
    } else if (key == 'B') {
      if (enteredUSSD.length() > 0) {
        enteredUSSD.remove(enteredUSSD.length() - 1);
      }
    } else {
      enteredUSSD += key;
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Enter USSD");
    display.println(enteredUSSD);
    display.display();
  }
  
  }

}