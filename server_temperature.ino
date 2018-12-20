#include <ESP8266WiFi.h>
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int sensorValue = 0;
int Flex_pin = 0;    // select the input pin for the potentiometer
int x,w;
WiFiServer server(80); //Initialize the server on Port 80

void setup() {

WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); . 
server.begin(); // Start the HTTP Server
Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
Serial.print("Server IP is: "); // Print the IP to the monitor window 
Serial.println(HTTPS_ServerIP);
pinMode(LED_BUILTIN, OUTPUT); //GPIO16 is an OUTPUT pin;
digitalWrite(LED_BUILTIN, LOW); //Initial state is ON

  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();

}

void loop() { 
      WiFiClient client = server.available();
        if (!client) { 
        return; 
        } 


while(1)
{
  sensors.requestTemperatures(); 
  x=sensors.getTempCByIndex(0);  
  //client.println(int(sensors.getTempCByIndex(0)));
  //client.println(" ");  
  
  
  sensorValue = analogRead(A0);
  sensorValue = map(sensorValue, 0, 1023, 0, 99);
  w = sensorValue+x*100;
  client.print(int(w));
  delay(600);  
}
delay(1);
}
