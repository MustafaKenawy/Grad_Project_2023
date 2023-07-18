#include <String.h>
#include <Arduino.h>
#if defined(ESP32)  
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
// #define WIFI_SSID "admin"
// #define WIFI_PASSWORD "JBF07352"
// #define WIFI_SSID "Infinix ZERO 8"
// #define WIFI_PASSWORD "123456780"
// #define WIFI_SSID "#_._#"
// #define WIFI_PASSWORD "***we***  "
#define WIFI_SSID "HONOR 8X"
#define WIFI_PASSWORD "AaaaaaaAA"
// #define WIFI_SSID "OPPO A52"
// #define WIFI_PASSWORD "fatma12345@#"
// #define WIFI_SSID "Omar Omar"
// #define WIFI_PASSWORD "2512011@#"
// #define WIFI_SSID "MUSTAFA_KENAWY"
// #define WIFI_PASSWORD "12345678"



#define API_KEY "AIzaSyDozLoAqVkZUW4BjCoTOjXT_omLtRsuK2M"
#define DATABASE_URL "https://nodemcu-691e1-default-rtdb.firebaseio.com/"
//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
char input[5];
int value = 0;
char c = 'a';
char prev;
String data = "m ";
char read;
char arr[8] = { '0', '1', '2', '3', '4', '5', '6', '7' };



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK) {
    if (Firebase.RTDB.getString(&fbdo, "/test/data")) {
      if (fbdo.dataType() == "string") {
        data = fbdo.stringData();
        //digitalWrite(LED_BUILTIN,value);
        if ((prev == c))
          c = data[0];
        else {
          c = data[0];
          prev = c;
          c = data[0];
          Serial.write(c);
        }
      }
    }
    if (Serial.available()) {
      read = Serial.read();
      Serial.println(read);
      switch (read) {
        case 'E':
          sendToDB('E', "test/empty");
          break;
        case 'F':
          sendToDB('F', "test/empty");
          break;
        case 'C':
          sendToDB('C', "test/park");
          break;
        case 'N':
          sendToDB('N', "test/ret");
          break;
        case 'Y':
          sendToDB('Y', "test/ret");
          getIndex();
          reset();
          break;
        case 'R':
          reset(); 
          break;
        default:
          for (int i = 0; i < 8; i++) {
            if (i == (read-48)) {
              Serial.println("Entered.......");
              sendToDB(arr[i], "test/park");
              sendToDB('Y', "test/ret");
              reset();
              break;
            }
          }
          break;
      }
    }
  }
}



void sendToDB (char k,String s){
    data[0] = k;
    if (Firebase.ready() && signupOK) {
          // Write an String data on the database path test/avr
          if (Firebase.RTDB.setString(&fbdo, s, data)) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
        }
}


void getIndex()
{
  delay(3000);  // Wait for the app to get the index from user data and put it in CarIndex on the data section
  if (Firebase.ready() && signupOK){
  if (Firebase.RTDB.getString(&fbdo, "/test/carIndex")) {
      if (fbdo.dataType() == "string") {
        data = fbdo.stringData();
        //digitalWrite(LED_BUILTIN,value);
            c = data[0];
            Serial.println("Index------> ");
            Serial.write(c);
        }
      // Serial.write('\n');
      }}
    c = prev;  
}


void reset (){
   data[0] = 'R';
    if (Firebase.ready() && signupOK) {
          // Write an String data on the database path test/avr
          if (Firebase.RTDB.setString(&fbdo, "test/data", data)) {
            Serial.println("DATA RESET");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
        }
}
