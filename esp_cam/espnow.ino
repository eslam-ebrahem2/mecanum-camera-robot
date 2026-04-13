// ================= ESP-NOW SEND =================
void sendCommand(uint8_t dir, uint8_t speed) {
  DataPacket pkt;
  pkt.type = 1;
  pkt.dir = dir;
  pkt.speed = speed;
 

  esp_now_send(esp8266Mac, (uint8_t*)&pkt, sizeof(pkt));
}
void sendCommandsg(uint8_t ss) {
  DataPacket pkt;
  pkt.type = 3;

  pkt.sg = ss;


  esp_now_send(esp8266Mac, (uint8_t*)&pkt, sizeof(pkt));
}

// ================= ESP-NOW RECEIVE =================
void onDataRecv(const esp_now_recv_info* info, const uint8_t* incomingData, int len) {

  memcpy(&data, incomingData, sizeof(data));




  if (data.type == 2) {

    if (data.dist > 0 && data.dist < max_dist) {
      warning = true;

    } else {

      warning = false;
    }

    String json = "{";
    json += "\"temp\":" + String(data.temp) + ",";
    json += "\"hum\":" + String(data.hum) + ",";
    json += "\"dist\":" + String(data.dist);
    json += "}";

    // Serial.println("------------");

    webSocket.broadcastTXT(json);
  }
}
