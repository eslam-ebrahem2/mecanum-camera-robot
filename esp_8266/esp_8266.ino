#include <ESP8266WiFi.h>
#include <espnow.h>
#include <DHT.h>
#include <Ultrasonic.h>
#include <Servo.h>
Servo servo;

// ========= left side motor  =========
#define IN1 12
#define IN2 14
#define IN3 4
#define IN4 5

#define DHTPIN 13
#define TRIG 16
#define ECHO 15
Ultrasonic ultrasonic(TRIG, ECHO);
#define DHTTYPE DHT11
#define MAX_DISTANCE 200

DHT dht(DHTPIN, DHTTYPE);

uint8_t servo_angle = 90;
bool run_servo = true;


typedef struct {
  uint8_t type;
  uint8_t dir;
  uint8_t speed;
  uint8_t sg;
  float temp;
  float hum;
  float dist;
} DataPacket;

DataPacket data;


float t;
float h;
uint8_t direction = 0;
uint8_t initSpeed = 180;
float initdist = 0;
float max_dist = 30;
unsigned long lastSend = 0;
bool warning = false;






// esp32 cam  MAC Address: 8C:4F:00:D1:1B:B8
uint8_t esp32Mac[] = { 0x8C, 0x4F, 0x00, 0xD1, 0x1B, 0xB8 };





// ---------- ultrasonic ---------------
void readDistance() {
  float distance = ultrasonic.read(CM);
  if (distance <= 0) {
    return;
  }


  initdist = distance;
}

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
void readDH() {

  float tt = dht.readTemperature();
  float hh = dht.readHumidity();

  if (isnan(tt)) {

  } else {
    t = tt;
  }
  if (isnan(hh)) {

  } else {
    h = hh;
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

// ========= Setup =========
void setup() {


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.end();
  servo.attach(1, 500, 2500);
  servo.write(servo_angle);
  dht.begin();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    // Serial.println("ESP NOW FAIL");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb(onReceive);

  esp_now_add_peer(esp32Mac, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  // Serial.println("ESP8266 READY");
}

// ========= Loop =========

void loop() {
  readDistance();
  if (run_servo) {
    servo.write(servo_angle);
    delay(60);
    run_servo = false;
  }

  bool inRange = (initdist > 1 && initdist < max_dist);

  if (inRange && !warning) {

    sendSensors();
    warning = true;

  } else if (!inRange && warning) {

    sendSensors();
    warning = false;
  }


  static long lastreadtt = 0;


  if (millis() - lastreadtt > 2000) {
    readDH();

    lastreadtt = millis();
  }

  if (millis() - lastSend > 1500) {

    sendSensors();
    lastSend = millis();
  }
  MoveRobot(initSpeed, direction);
}