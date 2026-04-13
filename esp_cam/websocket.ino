// ================= WEBSOCKET =================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      {

        String msg = (char*)payload;
        Serial.println(msg);


        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, msg);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }


        if (doc["dir"].is<int>()) {
          int dir = doc["dir"];
          if (dir == 0) {
            stopMotors();
          }


          direction = dir;
          sendCommand(direction, initSpeed);
        }

        if (doc["flash"].is<bool>()) {
          bool flash = doc["flash"];
          if (flash) {
            digitalWrite(4, 1);
          } else {
            digitalWrite(4, 0);
          }
        }
        if (doc["speed"].is<int>()) {
          int speed = doc["speed"];
          initSpeed = speed;
         sendCommand(direction, initSpeed);
        }
        if (doc["servo"].is<int>()) {
          int servo = doc["servo"];
          S_angle = servo;
         sendCommandsg(S_angle);
        }


        break;
      }
  }
}
