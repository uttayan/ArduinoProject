#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

#define PIN_SPI_CS 4
#define FILE_NAME "config.txt"
#define KEY_MAX_LENGTH    50 // change it if key is longer
#define VALUE_MAX_LENGTH  50 // change it if value is longer


// set pin input
#define inputLine1 A8
#define inputLine2 A9
#define inputLine3 A10
#define inputLine4 A11
#define inputLine5 A12
#define inputLine6 A13
#define inputLine7 A14
#define inputLine8 A15

// value default
int valueLine1 = 0;
int valueLine2 = 0;
int valueLine3 = 0;
int valueLine4 = 0;
int valueLine5 = 0;
int valueLine6 = 0;
int valueLine7 = 0;
int valueLine8 = 0;


byte useDhcp = false;
byte useDns = false;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(0,0,0,0);
IPAddress gateway(0,0,0,0);
IPAddress mask(255,255,255,0 );
IPAddress dns(0, 0,0,0);
IPAddress server(0,0,0,0);

int    HTTP_PORT   = 5000;
String HTTP_METHOD = "POST";
char   HOST_NAME[] = "Host: 0.0.0.0";
String PATH_NAME   = "/receive_data";
String HTTP_Content = "Content-Type: application/json;";

String queryString;
int sum = 0;
String value="";
String value1="";
EthernetClient client;
File sdFile;

void setup()
{
  Serial.begin(115200); 
    Serial.println("Initializing SD card...");
    if (!SD.begin(PIN_SPI_CS)) {
        Serial.println("ERROR - SD card initialization failed!");
       // return;    // init failed
       Ethernet.begin(mac,ip, dns, gateway, mask);
    }else{
         Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
        if (!SD.exists(FILE_NAME)) {
            Serial.println("ERROR - Can't find index.htm file!");
            //return;  // can't find index file
            Ethernet.begin(mac,ip, dns, gateway, mask);
        }else{
            Serial.print("SUCCESS - Found ");
            Serial.println(FILE_NAME);

            //read obj on SD Card
            HTTP_PORT = SD_findInt(F("HTTP_PORT"));
            HTTP_METHOD = SD_findString(F("HTTP_METHOD"));
            PATH_NAME = SD_findString(F("PATH_NAME"));
            HTTP_Content = SD_findString(F("HTTP_Content"));

            String SD_HOST_NAME = SD_findString(F("HOST_NAME"));
            String SD_Host = SD_findString(F("HOST_NAME"));
            String SD_ip = SD_findString(F("ip"));
            String SD_mask = SD_findString(F("mask"));
            String SD_gateway = SD_findString(F("gateway"));
            String SD_dns = SD_findString(F("dns"));
            String SD_server = SD_findString(F("server"));
            // read ip from string
            ip.fromString(SD_ip);
            mask.fromString(SD_mask);
            gateway.fromString(SD_gateway);
            dns.fromString(SD_dns);
            server.fromString(SD_server);
            //convert string to char
            HOST_NAME[SD_Host.length()+1];
            SD_Host.toCharArray(HOST_NAME,SD_Host.length()+1);

            Serial.println("------**************-----------");

            Ethernet.begin(mac,ip, dns, gateway, mask);
        }
    }
  delay(1000); 

   //  set status pin type INPUT/OUTPUT
  pinMode(inputLine1,INPUT);
  pinMode(inputLine2,INPUT);
  pinMode(inputLine3,INPUT);
  pinMode(inputLine4,INPUT);
  pinMode(inputLine5,INPUT);
  pinMode(inputLine6,INPUT);
  pinMode(inputLine7,INPUT);
  pinMode(inputLine8,INPUT);

}

void senddata(String data){
    client.println(HTTP_METHOD+" "+PATH_NAME+" HTTP/1.1");
    client.println(HOST_NAME);
    client.println(HTTP_Content);
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
}

void loop(){


    valueLine1 = digitalRead(inputLine1);
    valueLine2 = digitalRead(inputLine2);
    valueLine3 = digitalRead(inputLine3);
    valueLine4 = digitalRead(inputLine4);
    valueLine5 = digitalRead(inputLine5);
    valueLine6 = digitalRead(inputLine6);
    valueLine7 = digitalRead(inputLine7);
    valueLine8 = digitalRead(inputLine8);

    sum = !valueLine1+!valueLine2+!valueLine3+!valueLine4+!valueLine5+!valueLine6+!valueLine7+!valueLine8;

    value1=value;
    value = "";
    value += String(valueLine1);
    value += String(valueLine2);
    value += String(valueLine3);
    value += String(valueLine4);
    value += String(valueLine5);
    value += String(valueLine6);
    value += String(valueLine7);
    value += String(valueLine8);
 
    if (client.connect(server, 5000 )) {
        if(value1 != value){
            if(sum == 1){ 
                if(valueLine1 == LOW){
                    Serial.println("InputLine 1 "); 
                    
                    queryString = "{\"lane\":\"3\", \"dump\":\"1\"}";
                    senddata(queryString);
                    Serial.println(queryString);  
                }
                if(valueLine2 == LOW){
                    Serial.println("InputLine 2"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"2\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine3 == LOW){
                    Serial.println("InputLine 3"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"3\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine4 == LOW){
                    Serial.println("InputLine 4"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"4\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine5 == LOW){
                    Serial.println("InputLine 5"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"5\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine6 == LOW){
                    Serial.println("InputLine 6"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"6\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine7 == LOW){
                    Serial.println("InputLine 7"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"7\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
                if(valueLine8 == LOW){
                    Serial.println("InputLine 8"); 
                    queryString = "{\"lane\":\"3\", \"dump\":\"8\"}";
                    senddata(queryString);
                    Serial.println(queryString);
                }
            
            }else{
                Serial.println("Switch All OFF or Switch ON > 1");
            }
        }
    }else {
        Serial.println("connection failed");
    }
    
    delay(1000);
}


bool SD_available(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return value_length > 0;
}

int SD_findInt(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2Int(value_string, value_length);
}

float SD_findFloat(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2Float(value_string, value_length);
}

String SD_findString(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2String(value_string, value_length);
}

int SD_findKey(const __FlashStringHelper * key, char * value) {
  File configFile = SD.open(FILE_NAME);

  if (!configFile) {
    Serial.print(F("SD Card: error on opening file "));
    Serial.println(FILE_NAME);
    return;
  }

  char key_string[KEY_MAX_LENGTH];
  char SD_buffer[KEY_MAX_LENGTH + VALUE_MAX_LENGTH + 1]; // 1 is = character
  int key_length = 0;
  int value_length = 0;

  // Flash string to string
  PGM_P keyPoiter;
  keyPoiter = reinterpret_cast<PGM_P>(key);
  byte ch;
  do {
    ch = pgm_read_byte(keyPoiter++);
    if (ch != 0)
      key_string[key_length++] = ch;
  } while (ch != 0);

  // check line by line
  while (configFile.available()) {
    int buffer_length = configFile.readBytesUntil('\n', SD_buffer, 100);
    if (SD_buffer[buffer_length - 1] == '\r')
      buffer_length--; // trim the \r

    if (buffer_length > (key_length + 1)) { // 1 is = character
      if (memcmp(SD_buffer, key_string, key_length) == 0) { // equal
        if (SD_buffer[key_length] == '=') {
          value_length = buffer_length - key_length - 1;
          memcpy(value, SD_buffer + key_length + 1, value_length);
          break;
        }
      }
    }
  }

  configFile.close();  // close the file
  return value_length;
}

int HELPER_ascii2Int(char *ascii, int length) {
  int sign = 1;
  int number = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c >= '0' && c <= '9')
        number = number * 10 + (c - '0');
    }
  }

  return number * sign;
}

float HELPER_ascii2Float(char *ascii, int length) {
  int sign = 1;
  int decimalPlace = 0;
  float number  = 0;
  float decimal = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c == '.')
        decimalPlace = 1;
      else if (c >= '0' && c <= '9') {
        if (!decimalPlace)
          number = number * 10 + (c - '0');
        else {
          decimal += ((float)(c - '0') / pow(10.0, decimalPlace));
          decimalPlace++;
        }
      }
    }
  }

  return (number + decimal) * sign;
}

String HELPER_ascii2String(char *ascii, int length) {
  String str;
  str.reserve(length);
  str = "";

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    str += String(c);
  }

  return str;
}