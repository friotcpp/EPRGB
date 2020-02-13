 void stage2(){
  setupGO=false;
  String epIp= WiFi.localIP().toString();

   Serial.println("stage 2 commencing\n ep ip on router:"+ epIp);
   String sender ="http://192.168."+ mainIP +"/epip";
    
    epIp.remove(0,8);
    epIp = "epIP="+epIp;
   Serial.println("sending Post request to: \n"+ sender);
  
  HTTPClient http;  //Declare an object of class HTTPClient


  http.begin(sender);  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
 int httpCode = http.POST(epIp);   //Send the request
  Serial.println("http return code:"+httpCode);

 
  if (httpCode > 0) { //Check the returning code
 
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload

      } 
      else {Serial.println("no payload");}
 
  http.end();   //Close connection//Send the request

stage2go=false;
  }

//
//  void sendUpdated value(){
//
//    String sender ="http://192.168."+ mainIP +"/update";
//    Serial.println("sending Post request to: \n"+ sender);
//    HTTPClient http;  //Declare an object of class HTTPClient
//  
//  
//    http.begin(sender);  //Specify request destination
//    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
//   String data = "data="+ "fromdata loop"";
//    int httpCode = http.POST(epIp);   //Send the request
//    String payload = http.getString();    //Get the response payload                                                        
//    Serial.println("http return code:"+httpCode);
//    
//  if (httpCode > 0) { //Check the returning code
//    String payload = http.getString();   //Get the request response payload
//    Serial.println(payload);                     //Print the response payload 
//    } else {Serial.println("no payload");}
//   
//    http.end();   //Close connection}
//  }
