 void stage2(){
   Serial.println("stage 2 commencing/n ep ip on router:"+WiFi.localIP().toString());
     String sender ="http://192.168."+ mainIP +"/epip";
   Serial.println("sending Post request to: \n"+ sender);
  HTTPClient http;  //Declare an object of class HTTPClient
String epIp= WiFi.localIP().toString();
epIp.remove(0,8);
epIp = "epIP="+epIp;
http.begin(sender);  //Specify request destination
 http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(epIp);   //Send the request
  String payload = http.getString();    //Get the response payload                                                             //Send the request
  Serial.println("http return code:"+httpCode);
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload
Serial.println(payload);                     //Print the response payload


 
} else {Serial.println("no payload");}
 
http.end();   //Close connection

stage2go=false;
  }
