/* version 0.01a
 * added some new tabs
    * Documentation - each time when we update some thing we need to note it down/unused code and potential useful code can also be put in here
    * Function List - function should go there so that our main is clean
 * changed CaptivePortalAdvanced to Froit
 * added Firebase library
  */




//original example description
/*
   This example serves a "hello world" on a WLAN and a SoftAP at the same time.
   The SoftAP allow you to configure WLAN parameters at run time. They are not setup in the sketch but saved on EEPROM.

   Connect your computer or cell phone to wifi network ESP_ap with password 12345678. A popup may appear and it allow you to go to WLAN config. If it does not then navigate to http://192.168.4.1/wifi and config it there.
   Then wait for the module to connect to your wifi and take note of the WLAN IP it got. Then you can disconnect from ESP_ap and return to your regular WLAN.

   Now the ESP8266 is in your network. You can reach it through http://192.168.x.x/ (the IP you took note of) or maybe at http://esp8266.local too.

   This is a captive portal because through the softAP it will redirect any http request to http://192.168.4.1/
*/

//unused code//
//========colors========//

/* String to Int Example
String s = "11110000";
int i = strtol( s.c_str(), NULL, 2 ); //convert string to int in base 2;
String val = “1234”;
int result = val.toInt();  //Converts string to integer(base 10)
*/

/*parts being replaced
const int led = 13;
String checkColor(String device, String command)
{
  String color = "error";
  if (device == "led1")
  {
    if (command == "0000") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 0);return "off";}
  else if (command == "0001") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 1);return "on/white";}
  else if (command == "0010") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 0);return "blue";}
  else if (command == "0011") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 1);return "light blue";}
  else if (command == "0100") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 0);return "red";}
  else if (command == "0101") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 1);return "pink";}
  else if (command == "0110") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 1); digitalWrite(5, 0);return "magenta";}
  else if (command == "0111") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 1); digitalWrite(5, 1);return "light magenta";}
  else if (command == "1000") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 0);return "green";}
  else if (command == "1001") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 1);return "light green";}
  else if (command == "1010") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 0);return "cyan";}
  else if (command == "1011") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 1);return "light cyan";}
  else if (command == "1100") {digitalWrite(2, 1); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 0);return "yellow";}
  else if (command == "1101") {digitalWrite(2, 1); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 1);return "light yellow";}
  }
  else if (device == "led3")
  {
    if (command == "0000") {digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 0);return "off";}
  else if (command == "0001") {digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 1);return "on/white";}
  else if (command == "1000") {digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 0);return "green";}
  else if (command == "0100") {digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 0);return "red";}
  else if (command == "0010") {digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 0);return "blue";}
  else if (command == "1100") {digitalWrite(15, 0); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 0);return "yellow";}
  else if (command == "0110") {digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 0); digitalWrite(14, 0);return "magenta";}
  else if (command == "1010") {digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 0);return "cyan";}
  else if (command == "1001") {digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 1);return "light green";}
  else if (command == "0101") {digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 1);return "pink";}
  else if (command == "0011") {digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 1);return "light blue";}
  else if (command == "1101") {digitalWrite(15, 0); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 1);return "light yellow";}
  else if (command == "0111") {digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 0); digitalWrite(14, 1);return "light magenta";}
  else if (command == "1011") {digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 1);return "light cyan";}
  }
  else if (device == "All led")
  {
    if (command == "0000") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 0);return "off";}
  else if (command == "0001") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 1); digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 1);return "on/white";}
  else if (command == "1000") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 0);return "green";}
  else if (command == "0100") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 0);return "red";}
  else if (command == "0010") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 0); digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 0);return "blue";}
  else if (command == "1100") {digitalWrite(2, 1); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(15, 0); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 0);return "yellow";}
  else if (command == "0110") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 1); digitalWrite(5, 0); digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 0); digitalWrite(14, 0);return "magenta";}
  else if (command == "1010") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 0); digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 0);return "cyan";}
  else if (command == "1001") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 0); digitalWrite(5, 1); digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 1); digitalWrite(14, 1);return "light green";}
  else if (command == "0101") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 1); digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 1);return "pink";}
  else if (command == "0011") {digitalWrite(2, 0); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 1); digitalWrite(15, 1); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 1);return "light blue";}
  else if (command == "1101") {digitalWrite(2, 1); digitalWrite(0, 1); digitalWrite(4, 0); digitalWrite(5, 1); digitalWrite(15, 0); digitalWrite(16, 0); digitalWrite(12, 1); digitalWrite(14, 1);return "light yellow";}
  else if (command == "0111") {digitalWrite(2, 0); digitalWrite(0, 1); digitalWrite(4, 1); digitalWrite(5, 1); digitalWrite(15, 1); digitalWrite(16, 0); digitalWrite(12, 0); digitalWrite(14, 1);return "light magenta";}
  else if (command == "1011") {digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 1); digitalWrite(15, 0); digitalWrite(16, 1); digitalWrite(12, 0); digitalWrite(14, 1);return "light cyan";}
  }
  return color;
}
*/
//digitalWrite(2, 1); digitalWrite(0, 0); digitalWrite(4, 1); digitalWrite(5, 1);
//digitalWrite(7, 1); digitalWrite(11, 0); digitalWrite(8, 1); digitalWrite(9, 1);

/** Handle root or redirect to captive portal */
/*not needed at this moment
void handleRoot() {
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  String Page;
  Page += F(
            "<html><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><head></head><body>"
            "<h1>HELLO WORLD!!</h1>");
  if (server.client().localIP() == apIP) {
    Page += String(F("<p>You are connected through the soft AP: ")) + softAP_ssid + F("</p>");
  } else {
    Page += String(F("<p>You are connected through the wifi network: ")) + ssid + F("</p>");
  }
  Page += F(
            "<p>You may want to <a href='/wifi'>config the wifi connection</a>.</p>"
            "</body></html>");

  server.send(200, "text/html", Page);
}
*/
