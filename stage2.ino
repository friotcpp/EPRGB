 void stage2(){
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
  connect = strlen(ssid) > 0; // Request WLAN connect if there is a SSID
  dnsServer.start(DNS_PORT, "*", WiFi.localIP());
  }
