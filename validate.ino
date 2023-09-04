
void Nfc_connect(){
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  Serial.println("Waiting for an ISO14443A card"); 
}

String convertToInternationalFormat(const String& phoneNumber) {
  if (phoneNumber.length() != 11) {
    // Invalid phone number length
    return "";
  }
  
  // Check if the phone number starts with "0"
  if (phoneNumber.startsWith("0")) {
    // Remove the leading "0" and prepend "234"
    return "234" + phoneNumber.substring(1);
  }
  
  // Phone number is already in international format
  return phoneNumber;
}

void getvalidatorTask(){ 
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength; 
   while(1){   
 
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success)
  {
    char hexStr[3];
    int offset=0;
   for (uint8_t i=0; i < uidLength; i++) 
    {
      sprintf(hexStr+offset,"%02X",uid[i]);
      offset+=2;  
    }

    HexString =  String (hexStr);
    Serial.print("The UUID is :"); 
    Serial.println(HexString); 
  }
  else
  {
    // PN532 probably timed out waiting for a card
    // Serial.println("Timed out waiting for a card");
  }
  vTaskDelay(pdMS_TO_TICKS(100));
   } 
  
}


void validatorTask(void *parameter){ 
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength; 
   while(1){   
 
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success)
  {
    char hexStr[3];
    int offset=0;
   for (uint8_t i=0; i < uidLength; i++) 
    {
      sprintf(hexStr+offset,"%02X",uid[i]);
      offset+=2;  
    }

    HexString =  String (hexStr);
    Serial.print("The UUID is :"); 
    Serial.println(HexString); 
  }
  else
  {
    // PN532 probably timed out waiting for a card
    // Serial.println("Timed out waiting for a card");
  }
  vTaskDelay(pdMS_TO_TICKS(100));
   } 
  
}
void GetDeviceID(){
  String deviceid="U10000000";
  deviceID=deviceid;
  Serial.println("device Id is :");
  Serial.println(deviceID);    
  
}

bool GetCardNumber(){
  boolean success=false;;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength; 
  Serial.println("Swipe:"); 
  Swipe();

   while(1){   
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success)
  {
    char hexStr[3];
    int offset=0;
   for (uint8_t i=0; i < uidLength; i++) 
    {
      sprintf(hexStr+offset,"%02X",uid[i]);
      offset+=2;  
    }

    HexString =  String (hexStr);
    Serial.print("The UUID is :"); 
    Serial.println(HexString); 
    break;;
  }
  else
  {
    //return 0;
    // PN532 probably timed out waiting for a card
    // Serial.println("Timed out waiting for a card");
  }
  vTaskDelay(pdMS_TO_TICKS(100));
   } 
   Serial.println("Card UUI: " + HexString);
   Serial.println("phone number entered is : " + number);
   convertedNumber = convertToInternationalFormat(number);
   Serial.println("Formatted number is : " + convertedNumber);
   Phone=convertedNumber;
   cardNumber=HexString;   

   return 0;
}
