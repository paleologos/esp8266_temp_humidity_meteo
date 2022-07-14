#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

// Import DHT biblioteke
#define DHTTYPE DHT22  


/*SSID i Password*/
const char* ssid = "*************";  
const char* password = "*************";  


//inicijalizacija web servera po portu 80
ESP8266WebServer server(80);

//definisanje funkcije za omogucavanje CORS-a
void setCORS(){
    server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    server.sendHeader(F("Access-Control-Max-Age"), F("600"));
    server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};
 


// DHT Sensor na pin D6
uint8_t DHTPin = D6; 
               
// Incijalizacija senzora
DHT dht(DHTPin, DHTTYPE);                


// varijable podaci sa senzora
float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //Konekcija na mrezu
  WiFi.begin(ssid, password);

  //provera da li je konektovan na wi-fi
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi konektovan..!");
  Serial.print("IP adresa: ");  Serial.println(WiFi.localIP());


  // pozivanje funkcija HTTP servera
  server.on("/", HTTP_GET, handle_OnConnect); // pozivanje funkcije konekcije koja radi


  
  
  server.onNotFound(handle_NotFound); // pozivanje funkcije neispravne konekcije 
  
  // HTTP server
  server.begin();
  Serial.println("HTTP server started");

}


void loop() {
  
  server.handleClient();
  
}

//Definisanje funkcije konekcije koja radi 
void handle_OnConnect() {
  setCORS();    //POZIVANJE setCORS funkcije
  Temperature = dht.readTemperature(); // Ocitavanje temperature
  Humidity = dht.readHumidity(); // Ocitavanje vlaznosti vazduha 

  server.send(200, "application/json", SendJSON(Temperature,Humidity)); // Pozivanje SendJSON funkcije, za renderovanje slanje JSON podata
}


//Definisanje funkcije neispravne konekcije
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}


//Definisanje SendJSON funkcije

String SendJSON(float Temperaturestat,float Humiditystat){
  
  //Definisanje response stringa, za vracanje JSON objekta
  String response = "";
  response += "{";
  response += "\"temperature\":";
  response += (int)Temperaturestat;
  response += ",\"humidity\":";
  response += (int)Humiditystat;
  response += "}";
  return response;
}
