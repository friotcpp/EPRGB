void setupMode(){//set up mode
    if(timeOUT==true){//if timeout bool true
      //ClearCredentials();
      timeOUT=false;//boolean so time is not set again
      timeStart=millis();//timestamp
      Serial.println("Time out timer begins");
          Serial.println("epinfo:");
              digitalWrite(pairIndi, 1);//io turns on when in pairing mode
              Serial.println(endPointINFO);
              
     if(mainAP != WiFi.SSID()& ask4setup ())//checks to connect to main ap if no response over router
     {
        Serial.println("Connecting to main device during pair:");
        WiFi.disconnect(true);
        delay(500);
          Serial.println(WiFi.SSID());
        WiFi.begin(ssidAP, pass);
      while (WiFi.status() != WL_CONNECTED)
        {
      
          delay(500);
          Serial.print(".");
         if( timeStart+45000<millis()){
                  Serial.println("\nCould not connect to Main AP");
          return;
          
          }
      
        }
   //   }//if !mainap
//       if(WiFi.status() == WL_CONNECTED){
//          Serial.println();
//          Serial.print("Connected to Main, AP IP address: ");
//          Serial.println(WiFi.localIP());}
//            Serial.println(WiFi.SSID());
      }
  }

          
    if((timeStart+45000<millis()) )
    {//times out after 120sec
      setupGO = false;//comes out of setup 'if' in main loop
      timeOUT=true;//reset new timer  
        digitalWrite(pairIndi, 0);
      Serial.println("Setup time out");
      return; //comes out if endpoint setup loop    
    }
      endpointSetup();//checks for client in a void, if no timeout

      
//     if(!setupEndpointGO){ //this is just a loop simulating an ISR
// Serial.println("Restarting setup mode");
// delay(2500);
// setupEndpointGO=true;  }
}







void endpointSetup(){//endpoint setup function

  client.connect(server, wifiPort);//matching server point
//  Serial.println("*********Wifi server printing to Main AP**************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print(endPointINFO+"\r"));//station sends "\r"
  String payload = client.readStringUntil('\r');//ap sends '\r'
  Serial.println("From the AP: " + payload);
  client.flush();

  if(payload==""||payload==NULL) return;//only processes json package if not empty
//json payload from ap
const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonDocument jsonBuff(capacity);
  
   // Parse JSON object
    auto error = deserializeJson(jsonBuff, payload);
    if (error) {
      Serial.println(F("Parsing failed!"));
      //setupGO =false;
      return;
    }
    // Decode JSON/Extract values
    Serial.println("Response:");
    Serial.println(jsonBuff["SSID"].as<char*>());
    Serial.println(jsonBuff["PASS"].as<char*>());
    Serial.println(jsonBuff["MIP"].as<char*>());
    Serial.println(jsonBuff["KEY"].as<int>());

  ///   if (jsonBuff["KEY"].as<int>()==1){//if key from main is on   ///json save logic
  passwordM = jsonBuff["PASS"].as<String>();
  ssidM = jsonBuff["SSID"].as<String>();
    mainIP = jsonBuff["MIP"].as<String>();
//  timeStart +=120000;
  stage2go=true;

           digitalWrite(pairIndi, 0);//returns button gnd to low
 if(passwordM!=password  || ssidM!=ssid){//only saves credential if they are not mathing
      Serial.println("wifi save");
      delay(5);
     strcpy(ssid,ssidM.c_str());
     delay(5);
     strcpy(password,passwordM.c_str());
    saveCredentials();
    
    }
  connectWifi();//tries to connect to wifi with new credentials
  //connect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
 //eeprom call to save info
   
 // }                                             ////////////// ///json save logic
  //notice only stops entering setup mode if "Key" ==1
//  digitalWrite(LED_BUILTIN, HIGH);
  client.stop();

}//end setup mode function





//===================================

void loadEPInfo() {//creates a json package
loadFamPlace();//loads fam place
     // need to add info payload void outside of setupmode
         
  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<500> jsonBuffer;
 
  // Create the root object
  DynamicJsonDocument root(1024);
//bool doorsensor = digitalread(pin0)
//root["type"] = "sensor" ; 
//root["data"] = doorsensor ; 
//if (doorsensor==1){
//string status = "open";}
//else string status = "closed";

//if (tempsensor=>75){
//string status = "warm: turn on AC?";}
//if (tempsensor>75&<65){
//string status = "manageable";}
//if (tempsensor>100&<30){
//string status = "automatically turning on ac";}

//  root["status"] = status; 
//  root["dependencies"] = ; 
 // root["IPonAP"] = ThisIP; 

  root["type"] = "relay" ;
  root["Name"] = "rgb"; 
  root["fp"] = fPlace2-48;
  root["ESPAUTH"] = "42"; //auth variable
    Serial.println("endpoint info updated"); 
  serializeJson(root,endPointINFO);  //Store JSON in String variable
  }
//===================================================================//
