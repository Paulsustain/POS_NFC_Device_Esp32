
void Authenticate(void *pvParameters) {
  String password = "1234";
String enteredPassword = "";
String amount = "1345";
String enteredAmount = "";
bool passwordEntered = false;


  for (;;) {
  
    perform_Operation();
    //GetCardNumber();
    //getvalidatorTask();
    digitalWrite(Red,LOW);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
