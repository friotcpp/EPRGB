//FirebaseESP8266.h must be included before ESP8266WiFi.h
//for endpoint
//#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>//add json library
//========================EP Setup========================================//
const int interruptPin = 10;//GPIO10, pin labeled 'SD#' ESP8266-12e NodeMCU
String endPointINFO="";
String mainIP= "a";
long timeStart; //time stamp for setup time out
int inWifiKey =0;//if main is connected to wifi
int wifiPort =8080;//set port
int pairIndi = 9;
bool setupGO = false;//setupmode flag
bool timeOUT =true;//flag for timeout startpoint
bool stage2go = false;
char ssidAP[] = "ESP_main";          // SSID of your AP
String mainAP = "ESP_main"; 
char pass[] = "12345678";         // password of your AP
String ssidM = "";//router ssid
String passwordM = "";//router pass
IPAddress server(192,168,4,1);     // IP address of the Main AP
WiFiClient client;



ICACHE_RAM_ATTR void setupISR() {
  noInterrupts();  
  Serial.println("Interrupt service routine ");
  setupGO = true;
    
}
//=========================================================================//


//===Firebase===//
//#define FIREBASE_HOST "use different host"
//#define FIREBASE_AUTH "2"

/* Set these to your desired softAP credentials. They are not configurable at runtime */
//#define APSSID "ESP_main"
//#define APPSK  "12345678"
//More definition
#define ColorNum 14               //total amount of colors
#define Device1 "led1"            //we can create device here
#define Device2 "led3"
#define AllDevice "All led"

const int led = 13;           //led pin
String ColorNames[ColorNum] = { "off","on/white","blue","lightblue","red",
                            "pink","magenta","lightmagenta","green",
                            "lightgreen","cyan","lightcyan","yellow","lightyellow"};
            
//const char *softAP_ssid = APSSID;
//const char *softAP_password = APPSK;

/* hostname for mDNS. Should work at least on windows. Try http://esp8266.local */
const char *myHostname = "RGBEP";

/* Don't set this wifi credentials. They are configurated at runtime and stored on EEPROM */
char ssid[32] = "";
char password[32] = "";

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;

// Web server
ESP8266WebServer epserver(80);

/* Soft AP network parameters */
//IPAddress apIP(192, 168, 4, 1);
//IPAddress netMsk(255, 255, 255, 0);

/** Should I connect to WLAN asap? */
boolean connect;

/** Last time I tried to connect to WLAN */
unsigned long lastConnectTry = 0;

/** Current WLAN status */
unsigned int status = WL_IDLE_STATUS;

//Define FirebaseESP8266 data object
//FirebaseData firebaseData;
//FirebaseJson json;

//====setup===//
void setup() {
    delay(1500);
  //output setup
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(led, 0); //indication led
  
  pinMode(pairIndi, OUTPUT);//anti interrupt attempt
  digitalWrite(pairIndi, 0); //starts low
  //
    //========================================================================//

 // pinMode(LED_BUILTIN, OUTPUT); //led turns on while client is connected
  Serial.begin(115200);//changed from example baud rate
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), setupISR, FALLING);
  
  Serial.println();
  //ClearCredentials();
//  Serial.println("Configuring access point...");
//  /* You can remove the password parameter if you want the AP to be open. */
//  WiFi.softAPConfig(apIP, apIP, netMsk);
//  //WiFi.softAP(softAP_ssid, softAP_password);
//  WiFi.softAP(softAP_ssid);
//  delay(500); // Without delay I've seen the IP address blank
//  Serial.print("AP IP address: ");
//  Serial.println(WiFi.softAPIP());

// wifiserver.begin();
//   Serial.print("Started wifiserver on port: ");
//   Serial.println(wifiPort);
  /* Setup the DNS server redirecting all the domains to the apIP */
  WiFi.begin(ssidAP, pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
      digitalWrite(LED_BUILTIN, 0); //indication led
    delay(500);
    Serial.print(".");
          digitalWrite(LED_BUILTIN, 1); //indication led
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  setupGO = true;
      dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
 // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  
  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  //server.on("/", handleRoot);
//  epserver.on("/", handleWifi);
//  epserver.on("/wifi", handleWifi);
//  epserver.on("/wifisave", handleWifiSave);
//  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
//  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
//new
  epserver.on("/getip", HTTP_GET, handleGetIP);
  epserver.on("/receive", HTTP_POST, handleCommand);
//
//  epserver.onNotFound(handleNotFound);
  
  epserver.begin(); // Web server start
  Serial.println("HTTP server started");
  //loadCredentials(); // Load WLAN credentials from network
  dnsServer.start(DNS_PORT, "*", WiFi.localIP());

}

void loop() {
  if (connect) {                                                       //addd stage 2 flag
    Serial.println("Connect requested");
    connect = false;
    connectWifi();
    lastConnectTry = millis();
  }
  {
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000)) {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      connect = true;
    }
    if (status != s) { // WLAN status change
      Serial.print("Status: ");
      Serial.println(s);
      status = s;
      if (s == WL_CONNECTED) {
        /* Just connected to WLAN */
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address on local connection: ");
        Serial.println(WiFi.localIP());
          inWifiKey =1;     //boolean true if connect to wifi 
        // Setup MDNS responder
        if (!MDNS.begin(myHostname)) {
          Serial.println("Error setting up MDNS responder!");
        } else {
          Serial.println("mDNS responder started");
          // Add service to MDNS-SD

          MDNS.addService("http", "tcp", 80);
        }

//        //====FireBase===//
//        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//        Firebase.reconnectWiFi(true);
//
//        //Set database read timeout to 1 minute (max 15 minutes)
//        Firebase.setReadTimeout(firebaseData, 1000 * 60);
//        //tiny, small, medium, large and unlimited.
//        //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
//        Firebase.setwriteSizeLimit(firebaseData, "tiny");
//        
//        //set IP with debug info in serial output
//        if (Firebase.setString(firebaseData,  "/Wifi_IP" , toStringIp(WiFi.localIP())))
//        {
//          Serial.println("PASSED");
//          Serial.println("PATH: " + firebaseData.dataPath());
//          Serial.println("TYPE: " + firebaseData.dataType());
//          Serial.println("ETag: " + firebaseData.ETag());
//          Serial.print("VALUE: ");
//          printResult(firebaseData);
//          Serial.println("------------------------------------");
//          Serial.println();
//         }
//         else
//         {
//            Serial.println("FAILED");
//            Serial.println("REASON: " + firebaseData.errorReason());
//            Serial.println("------------------------------------");
//            Serial.println();
//           }
//        //===FireBase==//
        
        
      } else if (s == WL_NO_SSID_AVAIL) {
        inWifiKey =0;//no connection flag
        WiFi.disconnect();
      }
    }
    if (s == WL_CONNECTED) {
      MDNS.update();
    }
  }//'if connect' end
    if(stage2go)      stage2();
  if (setupGO)
  {//if in setting up mode, may modify to a while loop

      if(endPointINFO=="")
      {//fills out wifi json info only once
          loadEPInfo();//goes to json void for wifi info
      }
      
      setupMode();
   }//end setup mode if statement
  // Do work:
  //DNS

//  if(inWifiKey ==0)
//  return;
  dnsServer.processNextRequest();
  //HTTP
  epserver.handleClient();
}
