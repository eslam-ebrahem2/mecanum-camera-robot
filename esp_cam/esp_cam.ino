#include "esp_camera.h"
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <esp_now.h>
#include "board_config.h"
#include <ArduinoJson.h>

const char* ssid = "SSRM-BOT";
const char* password = "12345678";


WebSocketsServer webSocket = WebSocketsServer(82);

// ESP8266 mac  AC:0B:FB:D0:95:BA
uint8_t esp8266Mac[] = { 0xAC, 0x0B, 0xFB, 0xD0, 0x95, 0xBA };

// Motor
#define IN1 14
#define IN2 15
#define IN3 13
#define IN4 12


#define CH_IN1 0
#define CH_IN2 1
#define CH_IN3 2
#define CH_IN4 3
#define CH_SERVO 6
// Servo
#define SERVO_PIN 2
String Moto = "stop";
uint8_t initSpeed = 180;
uint8_t direction = 0;
bool warning = false;
float max_dist = 30;
int S_angle = 90;

// Data Struct
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

// ================= CAMERA =============
void startCameraServer();



void setup() {
  Serial.begin(115200);

  // PWM
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(4, OUTPUT);

 
  ledcAttachChannel(IN1, 1000, 8, CH_IN1);
  ledcAttachChannel(IN2, 1000, 8, CH_IN2);
  ledcAttachChannel(IN3, 1000, 8, CH_IN3);
  ledcAttachChannel(IN4, 1000, 8, CH_IN4);


  // WiFi
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(200);
  WiFi.softAP(ssid, password);
  WiFi.setSleep(false);

  Serial.println(WiFi.softAPIP());


  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera Fail");
    return;
  }


  startCameraServer();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);


  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP NOW FAIL");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, esp8266Mac, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  Serial.println("READY");
}


void loop() {
  webSocket.loop();
  MoveRobot(initSpeed, direction);
}


