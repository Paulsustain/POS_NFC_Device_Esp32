
void error001(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("No Response");
  Led_failed();
  display.display();
}

void error002(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("Success");
 // Led_failed();
 Led_success();
  display.display();
}

void error003(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("Card Alrdy Exist");
  Led_failed();
  display.display();
}

void error004(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("User not found");
  Led_failed();
  display.display();
}

void error005(){
  display.clearDisplay();
  display.setCursor(20, 10);
  display.print("Device linked Already");
  Led_failed();
  display.display();
}

void error006(){
  display.clearDisplay();
  display.setCursor(20, 10);
  display.print("Device linked");
  Led_failed();
  display.display();
}

void error007(){
  display.clearDisplay();
  display.setCursor(20, 10);
  display.print("user_not_found");
  Led_failed();
  display.display();
}
void error008(){
  display.clearDisplay();
  display.setCursor(20, 10);
  display.print("Invalid");
  Led_failed();
  display.display();
}





