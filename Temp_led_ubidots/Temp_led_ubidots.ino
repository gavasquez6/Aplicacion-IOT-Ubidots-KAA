

#include "Ubidots.h"

#define DEVICE  "esp8266_principal"  // Put here your Ubidots device label
#define VARIABLE  "var_led"  // Put here your Ubidots variable label
#define ID_TEMP "var_temperatura" 
#define TOKEN  "BBFF-Lfpv3y5JGr3QT7WdBUlUEk5I38wvgy"  // Put here your Ubidots TOKEN
#define DEVICE_LABEL "esp8266_principal"
#define WIFISSID "Red Guido 2" // Put here your Wi-Fi SSID
#define PASSWORD "Leones123" // Put here your Wi-Fi password

Ubidots ubidots(TOKEN, UBI_TCP);
float Valor_Temperatura = 0;
const byte  Pin_led = 15;
const int sensorPin= A0; 
  


void setup() {
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW);
    
    Serial.begin(115200);
    ubidots.wifiConnect(WIFISSID, PASSWORD);
   
    ubidots.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
    
    int value = analogRead(sensorPin);
    float t = (value / 1023.0) * 220;
    float Valor_Led = ubidots.get(DEVICE, VARIABLE);
    
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
      
      if (Valor_Led==1){digitalWrite(Pin_led, HIGH);}
      else{digitalWrite(Pin_led, LOW);}
      
    }else{
      Serial.println(F("Error getting Valor_Led"));
    }
    
    Valor_Temperatura=t;
    Serial.println(Valor_Temperatura);
    ubidots.add(ID_TEMP, t); 
    bool bufferSent = false;
  bufferSent = ubidots.send(DEVICE_LABEL);  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }
}
