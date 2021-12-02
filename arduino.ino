#include <SPI.h>
#include <WiFiNINA_Generic.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>

String inputString = "";         // a String to hold incoming data
String buff;
bool stringComplete = false;  // whether the string is complete
bool id;
int f,buf;
char x;

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting...");
 }
 inputString.reserve(200);
}
void loop() {
 // Check WiFi Status
 if (WiFi.status() == WL_CONNECTED) {
     //Object of class HTTPClient
   WiFi.begin("http://yourip/api/Home/GetAllApp");
   WiFi.end();   //Close connection
 }
 if (stringComplete) {
   while (f < 100)
   { if (inputString.substring(f) == "id")
     {
       id = true;
       break;
     } f++;
   }
   if (id == true)
   {
     x = inputString.charAt(f + 4);
   }
   if (x == '4')
   { f = 0;
     while (f < 100)
     { if (inputString.substring(f) == "number")
       { f += 9;
         for (int i = 0; i < 3; i++)
         { if (inputString.charAt(f + i) == '"') i = 3;
           else buff += inputString.charAt(f + i);
         }
         buf = buff.toInt();
         analogWrite(9, buf);
         break;
       }
       f++;
     }
   }
   // clear the string:
   inputString = "";
   stringComplete = false;
 }
}

void serialEvent() {
 while (Serial.available()) {
   // get the new byte:
   char inChar = (char)Serial.read();
   // add it to the inputString:
   inputString += inChar;
   // if the incoming character is a newline, set a flag so the main loop can
   // do something about it:
   if (inChar == '\n') {
     stringComplete = true;
   }
 }
}
