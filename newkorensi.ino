#include <Wire.h>
#include <Adafruit_PN532.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <HardwareSerial.h>

HardwareSerial SIM800(2); // RX = 16, TX = 17

String serialmessage="1678hd78 ";
String APN = "web.gprs.mtnnigeria.net";
String API_URL = "http://api.dev2.korensi.com/api/v1/wallet/cards/";
String Agent_URL="http://api.dev2.korensi.com/api/v1/auth/devices/link-to-agent/";
String Top_up="http://api.dev2.korensi.com/api/v1/wallet/cards/top-up/";
String Phone = "2348126631893";
String cardNumber = "";
const  String errornum="User with this phone number does not exist or is not verified";
const String error_card_already_exist="card with this card number already exists";
const String created="created_at";
const String status_device_already_linked="Device already linked";
const String status_device_linked_success="Device linked successfully";
const String user_not_found="User with this phone number not found";
const String Invalid_number="This field may not be blank";
const String Top_up_success="Wallet topped up successfully";
String deviceID="";



const byte ROWS = 4;
const byte COLS = 4;
TaskHandle_t TaskLedBlink= NULL;
TaskHandle_t TaskBatteryBar = NULL;
SemaphoreHandle_t xSemaphorehttp = NULL;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[ROWS] = {13, 12, 14, 27};
byte rowPins[COLS] = {32, 33, 25, 26};

//byte colPins[ROWS]= {27,14,12,13};
//byte rowPins[COLS]= {32, 33, 25, 26};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define PN532_IRQ   (26)
#define PN532_RESET (27)
#define Yellow 15
#define Red 2
#define Green 23

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
const int sensorPin = 34;  //ADC input for battery level and percentage monitoring
const float k = 0.66;     // Constant conversion

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

String enteredUSSD = "";
// Battery bar variables
const int barHeight = 10;
const int barWidth = 20;
const int barX = 100;
const int barY = 0;
const int barSpacing = 2;
const int numBars = 5;
SemaphoreHandle_t xSemaphoreOled=NULL;
String convertedNumber="";
String number = "";
String amount = "";
String code = "";   

boolean logic_number = false; 
boolean logic_code = false;   

String HexString="";
String phone_number = "";
bool reg_card = false; // flag to check if the user selected register card option
bool agent_logic = false;
bool top_card = false;
boolean amount_code = false;  
bool clear=false; 

void setup(void) {
  Serial.begin(9600);
  SIM800.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);
 
  Serial.println("Starting SIM800...");
   
 
 Serial.println("Hello!");
 
  //Indicator_initialize();
 // while (!Serial) delay(10); // Wait for serial port to connect
  
  nfc.begin();
 Nfc_connect();
 
 xSemaphoreOled = xSemaphoreCreateBinary();
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.display();
 Indicator_initialize();
 Initialize_GPRS(APN);
 LinkAgent();
//LinkAgent(); 
  //Indicator_initialize();
  
  //xTaskCreatePinnedToCore(validatorTask, "validatorTask", 10000, NULL, 1, &TaskValidator, 1);
  //xTaskCreatePinnedToCore(LedBlink, "LedBlink", 1000, NULL, 1, &TaskLedBlink, 1);
  xTaskCreatePinnedToCore(batteryBarTask, "batteryBarTask", 8096, NULL, 1, &TaskBatteryBar, 1);
  xTaskCreatePinnedToCore(Authenticate, "Authenticate", 8096, NULL, 1, NULL, 1);
 
}



void loop(void) {
  //LinkAgent(); 
//Indicator_initialize();
}

 
  
