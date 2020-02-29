/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  EEPROM.begin(511);//changed to 511 from 512
  EEPROM.get(1, ssid);
  EEPROM.get(1 + sizeof(ssid), password);
  char ok[2 + 1];
  EEPROM.get(1 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssid[0] = 0;
    password[0] = 0;
  }
  Serial.println("Recovered credentials:");
  Serial.println(ssid);
  Serial.println(strlen(password) > 0 ? "********" : "<no password>");
}

/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  Serial.println("Saving credentials");
  EEPROM.begin(511);//changed to 511 from 512
  EEPROM.put(1, ssid);
  EEPROM.put(1 + sizeof(ssid), password);
  char ok[2 + 1] = "OK";
  EEPROM.put(1 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}

void saveFamPlace(int fp) {
  Serial.println("Saving device place in family");
  EEPROM.begin(1);//changed to 511 from 512
  EEPROM.put(0, fp);
  EEPROM.commit();
  EEPROM.end();
  fPlace=fp;
  fPlace2=48+fPlace;
}
void loadFamPlace() {
  EEPROM.begin(1);//changed to 511 from 512
  EEPROM.get(0, fPlace);
  EEPROM.end();
  fPlace2=48+fPlace;
  Serial.println("FamPlace");
  Serial.println(fPlace2);


}


//clear any data in the epprom for debug purpose
void ClearCredentials(){
  EEPROM.begin(512);
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.end();
  Serial.println("\"All Credentials cleared for debug purpose\"");
  }
