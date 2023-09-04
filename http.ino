
String HTTP_post_request_link_agent(String api_url,String phoneNumber,String serialmessage){
  
  SIM800.println("AT+HTTPINIT");
  delay(5);
  SIM800.println("AT+HTTPPARA=\"CID\",1");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"URL\",\"" + api_url + "\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  String body = "{\"serial\":\"" + serialmessage + "\",\"phone\":\"" + phoneNumber + "\"}";

  SIM800.println("AT+HTTPDATA=" + String(body.length()) + ",10000");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println(body);
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPACTION=1");
  delay(5000);

  char save[160];
  int counter=0;
  SIM800.println("AT+HTTPREAD");
  delay(500);
   int i=0;
   String ntn="";
  for(;;){

  if (SIM800.available()) {
    
    char c  = SIM800.read();
      save[i]=c;
      //Serial.println(save[i]);
      
    }
     if(i>=157){
       save[i] = '\0';
        String savedString(save);
        int len=savedString.length(); 
       Serial.println(len);
        i=0;
        SIM800.println("AT+HTTPTERM");
        return (savedString);
      }  

      else if(counter>=2000){
       goto end;
        
      }      
      i++;
   }
   end:
  SIM800.println("AT+HTTPTERM");
  delay(1000);

}


int HTTP_POST_REQUEST_AGENT(String number){
bool found;
 String resp= HTTP_post_request_link_agent(Agent_URL,number,serialmessage);
 Serial.print("phone number is : "); 
 Serial.println(number); 
 Serial.print("serial message is "); 
Serial.println(serialmessage);  
 //String modifiedString = removeCharacters(resp,48,6); // card already exist
 String modifiedString = removeCharacters(resp,50,3); // phone does not exist
 
 Serial.print("Modified String is : "); 
 Serial.print("Result len : "); 
 Serial.println(modifiedString.length()); 
 Serial.println("Extracted Message: " + modifiedString);
 found = searchString(modifiedString,status_device_linked_success);
 if(found){
  Serial.println("found error :" + status_device_linked_success); 
  goto err1;
 }

 found = searchString(modifiedString,status_device_already_linked);
 if(found){
  Serial.println("found error :" + status_device_already_linked);  //error007()
  goto err2;
 } 

 found = searchString(modifiedString, user_not_found);
 if(found){
  Serial.println("found error :" +  user_not_found);  //error007()
  goto err3;
 } 
 
err1: 
error006();
return 1;
err3:
error007();
return -1;
err2: 
error005();
return -1;

}

void http_post_card(){
  int i=0;
  GetCardNumber();
  oled_processing();
  Led_processing1();

  HTTP_POST_REQUEST_Card();
 Led_processing_end();  
 
}

void http_post_agent(String number){
  int i=0;
   oled_processing();  
   Led_processing1();
   //vTaskResume(TaskLedBlink);
  while(!HTTP_POST_REQUEST_AGENT(number));
  Led_processing_end();
   //vTaskSuspend(TaskLedBlink);
}




void http_post_top_up(){
  int i=0;
  GetDeviceID();
  GetCardNumber();
  oled_processing();
  Led_processing1();
  HTTP_POST_REQUEST_Topup();
  while(i<40){
    //getvalidatorTask();
   // Led_failed();
    
    //Led_processing1();
    vTaskDelay(pdMS_TO_TICKS(100));
    i++;
  }
  Led_processing_end();
}

void http_register_error(){
  int i=0;
  while(i<50){
    //error600();    
    i++;
  }
}


bool searchString(const String& str, String target) {
  //String target = "User with this phone number does not exist or is not verified";
  return str.indexOf(target) != -1;
}


String removeCharacters(String inputString, int start, int end) {
  if (inputString.length() >= start + end) {
    return inputString.substring(start, inputString.length() - end);
  }
  return "";
}

String extractErrorMessage(const String& response) {
  int startIndex = response.indexOf("phone\": ") + 9;
  int endIndex = response.indexOf("\"", startIndex);
  String errorMessage = response.substring(startIndex, endIndex);
  return errorMessage;
}


int getTotalStringLength(const String& str) {
  return str.length();
}

void Initialize_GPRS(String apn){
  Startup();
  for(int i=0;i<3;i++){
  SIM800.println("AT"); // Check if SIM800 is responding
  delay(1000);
  SIM800.println("ATE0"); // Check if SIM800 is responding
  delay(1000);

  SIM800.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+SAPBR=3,1,\"APN\",\"" + apn + "\"");// Network provider APN 
  delay(1000);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+SAPBR=1,1");
  delay(1000);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPINIT");
  delay(1000);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  }
}


String HTTP_post_request_Topup(String api_url,String Amount,String card_id,String deviceid){
  SIM800.println("AT+HTTPINIT");
  delay(5);
  SIM800.println("AT+HTTPPARA=\"CID\",1");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"URL\",\"" + Top_up + "\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  String body = "{\"card_number\":\"" + card_id + "\",\"amount\":\"" + Amount + "\",\"device\":\"" + deviceid + "\"}";

  SIM800.println("AT+HTTPDATA=" + String(body.length()) + ",10000");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println(body);
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPACTION=1");
  delay(5000);

  char save[160];
  int counter=0;
  SIM800.println("AT+HTTPREAD");
  delay(500);
   int i=0;
   String ntn="";
  for(;;){

  if (SIM800.available()) {
    
    char c  = SIM800.read();
      save[i]=c;
      //Serial.println(save[i]);
      
    }
     if(i>=157){
       save[i] = '\0';
        String savedString(save);
        int len=savedString.length(); 
       Serial.println(len);
        i=0;
        SIM800.println("AT+HTTPTERM");
        return (savedString);
      }  

      else if(counter>=2000){
       goto end;
        
      }      
      i++;
   }
   end:
  SIM800.println("AT+HTTPTERM");
  delay(1000);




}

int HTTP_POST_REQUEST_Topup(){
bool found;
 String resp= HTTP_post_request_Topup(Top_up,amount,cardNumber,deviceID);
 //String modifiedString = removeCharacters(resp,48,6); // card already exist
 String modifiedString = removeCharacters(resp,50,3); // phone does not exist
 
 Serial.print("Modified String is : "); 
 Serial.print("Result len : "); 
 Serial.println(modifiedString.length()); 
 Serial.println("Extracted Message: " + modifiedString);
 found = searchString(modifiedString,errornum);
 if(found){
  Serial.println("found error :" + errornum); 
  goto err4;
 }

 found = searchString(modifiedString,error_card_already_exist);
 if(found){
  Serial.println("found error :" + error_card_already_exist);  
  goto err3;
 } 
 
 found = searchString(modifiedString,created);
 if(found){
  Serial.println("found error :" + created); 
  goto err2;
 } 
 if(!found){
 goto err1;
   
 }
err1: 
error001();
return 1;
err2: 
error002();
return 1;
err3: 
error003();
return 1;
err4: 
error004();
return 1;



  return 0;
}




String HTTP_post_request_Card_Registration(String api_url,String phoneNumber,String card_id){
  
  SIM800.println("AT+HTTPINIT");
  delay(5);
  SIM800.println("AT+HTTPPARA=\"CID\",1");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"URL\",\"" + api_url + "\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  String body = "{\"phone\":\"" + phoneNumber + "\",\"card_number\":\"" + card_id + "\"}";

  SIM800.println("AT+HTTPDATA=" + String(body.length()) + ",10000");
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println(body);
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPACTION=1");
  delay(5000);

  char save[160];
  int counter=0;
  SIM800.println("AT+HTTPREAD");
  delay(500);
   int i=0;
   String ntn="";
  for(;;){

  if (SIM800.available()) {
    
    char c  = SIM800.read();
      save[i]=c;
      //Serial.println(save[i]);
      
    }
     if(i>=157){
       save[i] = '\0';
        String savedString(save);
        int len=savedString.length(); 
       Serial.println(len);
        i=0;
        SIM800.println("AT+HTTPTERM");
        return (savedString);
      }  

      else if(counter>=2000){
       goto end;
        
      }      
      i++;
   }
   end:
  SIM800.println("AT+HTTPTERM");
  delay(1000);

}

int HTTP_POST_REQUEST_Card(){
 bool found;
 String resp= HTTP_post_request_Card_Registration(API_URL,Phone,cardNumber);
 //String modifiedString = removeCharacters(resp,48,6); // card already exist
 String modifiedString = removeCharacters(resp,50,3); // phone does not exist
 
 Serial.print("Modified String is : "); 
 Serial.print("Result len : "); 
 Serial.println(modifiedString.length()); 
 Serial.println("Extracted Message: " + modifiedString);
 found = searchString(modifiedString,errornum);
 if(found){
  Serial.println("found error :" + errornum); 
  goto err4;
 }

 found = searchString(modifiedString,error_card_already_exist);
 if(found){
  Serial.println("found error :" + error_card_already_exist);  
  goto err3;
 } 
 
 found = searchString(modifiedString,created);
 if(found){
  Serial.println("found error :" + created); 
  goto err2;
 } 
 if(!found){
 goto err1;
   
 }
err1: 
error001();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
err2: 
error002();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
err3: 
error003();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
err4: 
error004();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;

}
