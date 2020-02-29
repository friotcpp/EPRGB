//======Wifi conneting functino=====//
void connectWifi() {
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);
  Serial.println("connected to:"+WiFi.SSID());
}

//=================check color function========//
String checkColor(String device, String command)
{
  String error_color = "error";
  int color_num = strtol( command.c_str(), NULL, 2 ); //convert string to int in base 2;
  if (device.charAt(3) == fPlace2)
  {
    Serial.println("in first if");
    digitalWrite(greenPin, int(command[0])-'0'); //change string to int with ascii correction
    digitalWrite(redPin, int(command[1])-'0');
    digitalWrite(bluePin, int(command[2])-'0'); 
    digitalWrite(whitePin, int(command[3])-'0');
    //===Firebase update===//
//    Firebase.setString(firebaseData,  "/Device2" , ColorNames[color_num]);
    return ColorNames[color_num];
   }
  else if (device.charAt(3) == fPlace2)
  {Serial.println("in else if");
    digitalWrite(greenPin, int(command[0])-'0'); //change string to int with ascii correction
    digitalWrite(redPin, int(command[1])-'0');
    digitalWrite(bluePin, int(command[2])-'0'); 
    digitalWrite(whitePin, int(command[3])-'0');
    //===Firebase update===//
//    Firebase.setString(firebaseData,  "/Device2" , ColorNames[color_num]);
    return ColorNames[color_num];
  }
  else if (device == AllDevice)
  {
    
    digitalWrite(greenPin, int(command[0])-'0'); //change string to int with ascii correction
    digitalWrite(redPin, int(command[1])-'0');
    digitalWrite(bluePin, int(command[2])-'0'); 
    digitalWrite(whitePin, int(command[3])-'0');
//    //===Firebase update===//
//    Firebase.setString(firebaseData,  "/Device1" , ColorNames[color_num]);
//    Firebase.setString(firebaseData,  "/Device2" , ColorNames[color_num]);
    return ColorNames[color_num];
  }
  return error_color;
}

//==========color command response
void handleCommand() {
//  digitalWrite(led, 1);
  String device = epserver.arg("OutputDevice");
  String command = epserver.arg("Command");
  String color = checkColor(device,command);
  epserver.send(200, "text/plain", "Successfully Received Code: [" + command + "]\nColor: [" + color + "]");

  Serial.println("Handling Command: {" + command + "} For: {" + device + "}...");
  Serial.println("The Led is now: " + color + "!");
//digitalWrite(led, 0);
}

////====Firebase Print debug tool
//void printResult(FirebaseData &data)
//{
//
//    if (data.dataType() == "int")
//        Serial.println(data.intData());
//    else if (data.dataType() == "float")
//        Serial.println(data.floatData(), 5);
//    else if (data.dataType() == "double")
//        printf("%.9lf\n", data.doubleData());
//    else if (data.dataType() == "boolean")
//        Serial.println(data.boolData() == 1 ? "true" : "false");
//    else if (data.dataType() == "string")
//        Serial.println(data.stringData());
//    else if (data.dataType() == "json")
//    {
//        Serial.println();
//        FirebaseJson &json = data.jsonObject();
//        //Print all object data
//        Serial.println("Pretty printed JSON data:");
//        String jsonStr;
//        json.toString(jsonStr,true);
//        Serial.println(jsonStr);
//        Serial.println();
//        Serial.println("Iterate JSON data:");
//        Serial.println();
//        size_t len = json.iteratorBegin();
//        String key, value = "";
//        int type = 0;
//        for (size_t i = 0; i < len; i++)
//        {
//            json.iteratorGet(i, type, key, value);
//            Serial.print(i);
//            Serial.print(", ");
//            Serial.print("Type: ");
//            Serial.print(type == JSON_OBJECT ? "object" : "array");
//            if (type == JSON_OBJECT)
//            {
//                Serial.print(", Key: ");
//                Serial.print(key);
//            }
//            Serial.print(", Value: ");
//            Serial.println(value);
//        }
//        json.iteratorEnd();
//    }
//    else if (data.dataType() == "array")
//    {
//        Serial.println();
//        //get array data from FirebaseData using FirebaseJsonArray object
//        FirebaseJsonArray &arr = data.jsonArray();
//        //Print all array values
//        Serial.println("Pretty printed Array:");
//        String arrStr;
//        arr.toString(arrStr,true);
//        Serial.println(arrStr);
//        Serial.println();
//        Serial.println("Iterate array values:");
//        Serial.println();
//        for (size_t i = 0; i < arr.size(); i++)
//        {
//            Serial.print(i);
//            Serial.print(", Value: ");
//
//            FirebaseJsonData &jsonData = data.jsonData();
//            //Get the result data from FirebaseJsonArray object
//            arr.get(jsonData, i);
//            if (jsonData.typeNum == JSON_BOOL)
//                Serial.println(jsonData.boolValue ? "true" : "false");
//            else if (jsonData.typeNum == JSON_INT)
//                Serial.println(jsonData.intValue);
//            else if (jsonData.typeNum == JSON_DOUBLE)
//                printf("%.9lf\n", jsonData.doubleValue);
//            else if (jsonData.typeNum == JSON_STRING ||
//                     jsonData.typeNum == JSON_NULL ||
//                     jsonData.typeNum == JSON_OBJECT ||
//                     jsonData.typeNum == JSON_ARRAY)
//                Serial.println(jsonData.stringValue);
//        }
//    }
//}
