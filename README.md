# esp8266_meteostation_temp_humidity

(SRB) - Serbian language
(EN) - English language

(SRB)
Jednostavna meteo stanica
Jednostavna meteorolska stanica koja preuzima podatke sa DHT22 senzora vlaznosti i temperature vazduha i prikazuje 
ih koricenjem biblioteke web server, nodemcu ESP8266.

Realizovano je na dva nacina:
1. Renderovanjem HTML stranice na strani servera (nodemcu ESP8266)
2. Renderovanje stranice na klijentskoj strani (/temp_humidity_api/meteo.html), koji podatke preuzima koriscenjem AXIOS CDN biblioteke, posredstvom GET request-a na IP adresi. podaci su u formi JSON objekta.


Staticka IP adresa
Postoji nacin da se staticka IP adresa naznaci u sketch-u, koriscenjem sledecih linija koda, koje je potrebno dodati ispred bloka "void setup() { ...":

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 87);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 255,255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

Nakon ovog koraka potrebno je na ruteru rezervisati IP adresu (izbaciti je iz dinamicke dodele) 

U slucaju mog rutera, staticku IP adresu sam resio rezervacijom IP adrese koja je povezana sa nodemcu ESP8266 MAC adresom na kucnom ruteru.

(EN)
Simple meteo station
Simple meteo station wich gets weather data (temperature and air humidity) from DHT22 sensor, and displays the data using nodemcu ESP8266 web server library.

It is realized on two ways:
1. Server side rendering of the HTML page
2. Client side rendering of the HTNL page (/temp_humidity_api/meteo.html),which fetching data using Axios CDN library, with  GET request. Data are in form of JSON.


Static IP address:
There are an option to specify static IP adress in sketch, by using this lines of code, just before "void setup() { ..." block of code :

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 87);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 255,255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

After this step you should create IP reservation on your router(remove from dynamic leases this IP address)


In case of my home router it is enough to create only IP reservations (providing nodemcu ESP8266 MAC address), because of that, i did not added this lines in my sketch.

