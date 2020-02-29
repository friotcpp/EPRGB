 void stage2(){
  setupGO=false;
  timeOUT=true;
  String epIp= WiFi.localIP().toString();

   Serial.println("stage 2 commencing\n ep ip on router:"+ epIp);
   String sender ="http://192.168."+ mainIP +"/epip";
    
    epIp.remove(0,8);
    fPlace2=fPlace+48;

    epIp = "epIP="+epIp+"&fp="+fPlace2;
  
  
  HTTPClient http;  //Declare an object of class HTTPClient


  http.begin(sender);  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
 int httpCode = http.POST(epIp);   //Send the request

 
  if (httpCode > 0) { //Check the returning code
 
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload

      } 
      else {Serial.println("no payload");}
 
  http.end();   //Close connection//Send the request

stage2go=false;
  }





   bool ask4setup(){


   Serial.println("asking main for set up");
   
  HTTPClient ask;  //Declare an object of class HTTPClient
IPAddress ip8 = resolver.search("espmain.local");
String mainc =toStringIp(ip8);
Serial.println(mainc);
 ask.begin("http://"+mainc+"/setupgo");  //Specify request destination
  ask.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
 int httpCode = ask.POST("auth=42");   //Send the request
  Serial.println("code:"+httpCode);

 
  if (httpCode > 0) { //Check the returning code
 
        String payload = ask.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload
        if (payload=="ok"){
          mainc.remove(0,8);
          mainIP = mainc;
              stage2go=true;
           setupGO = false;//comes out of setup 'if' in main loop
      timeOUT=true;//reset new timer  
        digitalWrite(pairIndi, 0);
      Serial.println("main is setting up");
               ask.end();   //Close connection//Send the request
              return false;
        }
    


      } 
  else {
    Serial.println("no payload from setup");
  ask.end();   //Close connection//Send the request

    return true;
      }
 
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
