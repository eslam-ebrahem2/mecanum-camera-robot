// --------------- recive data from main esp ---------------------


void onReceive(uint8_t *mac, uint8_t *incomingData, uint8_t len) {

  memcpy(&data, incomingData, sizeof(data));

  if (data.type == 1) {

    direction = data.dir;
    initSpeed = data.speed;
  }
  if (data.type == 3) {
    run_servo = true;
    servo_angle = data.sg;
  }
}


// ========= Send Sensors =========
void sendSensors() {

  DataPacket pkt;

  pkt.type = 2;


  pkt.temp = t;
  pkt.hum = h;
  pkt.dist = initdist;

  esp_now_send(esp32Mac, (uint8_t *)&pkt, sizeof(pkt));
}