#include <ESP8266WiFi.h>
#include <espnow.h>
#include <DHT.h>
#include <Ultrasonic.h>
#include <Servo.h>
Servo servo;

// ========= left side motor  on robot =========
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

void setup() {


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.end();
  moveServo(servo_angle);
  dht.begin();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {

    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb(onReceive);

  esp_now_add_peer(esp32Mac, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}



void loop() {
  readDistance();
  if (run_servo) {

    moveServo(servo_angle);

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