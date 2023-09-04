void Tag_accept(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
   display.setCursor(10, 10);
  display.println("Accepted");
  display.display();
}


void Swipe(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Swipe Card");
  display.display();
}
void oled_processing(){
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Processing...");
  display.display();
}


void Startup(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Starting...");
  display.display();
}

int clear_screen(char key){
  if(key=='C'){  
    return 1;
  } 
  else return 0;
}

void option_key(char key){
  if (!reg_card  && !logic_number && !logic_code) {
    if (key == 'A') {
     //vTaskSuspend(TaskValidator );
      vTaskSuspend(TaskBatteryBar );      
      //getvalidatorTask();
      //GetCardNumber();
      
      reg_card=true;
      //getvalidatorTask();      
      
      display.clearDisplay();            
    }
  }  
  
}

int option_1_selecttop_up(char key){
  if (amount_code) {
    if (key >= '0' && key <= '9' && amount.length() < 11) {
      amount += key;
      display.setCursor(amount.length() * 12, 20);
      } else if (key == '#') {
          if (amount != "0") {
          logic_number = false;
          logic_code = false;
          amount_code=false;
          http_post_top_up();
          //Led_processing_end();
          vTaskResume(TaskBatteryBar );
          logic_number = false;
          logic_code = false;
          amount_code=false;
          reg_card= false;
          number = "";
          code = ""; 
          amount="";
          return 1;
        } else {
            amount = "";
            display.clearDisplay();
            display.setCursor(0, 20);
            display.print("Wrong Entry");
            delay(1000);
            display.setCursor(0, 20);
            display.print("              ");
          }
          
      
        }
       vTaskDelay(pdMS_TO_TICKS(100));
       return 1;
      }
  else return 0;
}

int option_1_selectcard(char key){
  if (logic_number) {
    if (key >= '0' && key <= '9' && number.length() < 11) {
      number += key;
      display.setCursor(number.length() * 12, 20);
      } else if (key == '#') {
          if (number != "0") {
          logic_number = false;
          logic_code = false;
          amount_code=false;
          http_post_card();
          //http_register_error();
          //vTaskResume(TaskValidator);
          vTaskResume(TaskBatteryBar );
          logic_number = false;
          logic_code = false;
          amount_code=false;
          reg_card= false;
          number = "";
          code = ""; 
          amount=""; 
          return 1;
        } else {
            number = "";
            display.clearDisplay();
            display.setCursor(0, 20);
            display.print("Wrong Entry");
            delay(1000);
            display.setCursor(0, 20);
            display.print("              ");
          }
          
      
        }
       vTaskDelay(pdMS_TO_TICKS(100));
       return 1;
      }
  else return 0;
}


void reset(){
  //vTaskResume(TaskValidator);
  vTaskResume(TaskBatteryBar );
  logic_number = false;
  logic_code = false;
  amount_code=false;
  reg_card= false;
  number = "";
  code = "";
}

int Rlogic(char key){
  if (reg_card) {  
    if (key == '1') {  
      logic_number = true;
      logic_code = false;
      amount_code=false;      
      reg_card= false;
      }
if (key == '2') {  
      logic_number = false;
      logic_code = false;
      amount_code=true;      
      reg_card= false;
      }
    return 1;
    }  
  else return 0;
}

int Toplogic(char key){
  if (reg_card) {  
    if (key == '2') {  
      amount_code=true;
      logic_code = false;
      logic_number = false;
      reg_card= false;
      }
    return 1;
    }  
  else return 0;
}




void perform_Operation(){
  int i=0;
  bool clear=false;   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (!amount_code && !reg_card && !logic_number && !logic_code) {
  } else if (reg_card) {
    
    display.setCursor(0, 0);
    display.print("Selection Operation ");
    display.setCursor(0, 10);
    display.print("1.Reg Card ");
    display.setCursor(0, 20);
    display.print("2.Top up ");
    display.setCursor(60, 20);
    display.print("3.Deduction ");
  } else if (logic_number) {
    display.clearDisplay();  
    display.print("Enter Phone No: ");
    display.setCursor(0, 20);
    display.print(number);
  } else if (amount_code) {
    display.clearDisplay();  
    display.print("Enter Amount: ");
    display.setCursor(0, 20);
    display.print(amount);
  }
  display.display();

  char key = keypad.getKey();
  

  if (key != NO_KEY) {
    if(clear_screen(key)) clear=true; 
    //
    option_key(key); 
    if(Rlogic(key));     
    else if(option_1_selectcard(key));   
    else if(option_1_selecttop_up(key));
    if(clear){reset();}     
  }  
}




