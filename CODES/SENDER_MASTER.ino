#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>   // (Optional: remove if no local servo)

// ================= CONFIG =================

// Receiver MAC (PUT YOUR RECEIVER MAC HERE)
uint8_t receiverMac[] = {0x10, 0x20, 0xBA, 0x4D, 0xFB, 0xD4};

// Flex pins
const int flexPins[4] = {10, 4, 5, 6};

// Fixed resistor
const float R_FIXED = 200000.0;

// Calibration
float flexCal[4][4] = {
  {2099000, 2175000, 2150000, 2135000},
  {556000, 561000, 558000, 560000},
  {487000, 504000, 494000, 496000},
  {75000, 82000, 79000, 80000}
};

// Smoothing
const int numReadings = 10;
float readings[4][numReadings];
float totals[4];
int readIndex = 0;

// Finger states
int states[4] = {0};

// ================= DATA STRUCT =================

typedef struct struct_message {
  int fingerStates[4];
  float flexResistances[4];
  uint32_t timestamp;
} struct_message;

struct_message sendData;

// ================= CALLBACK =================

void OnDataSent(const esp_now_send_info_t *info,
                esp_now_send_status_t status) {

  Serial.print("Send: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  Serial.print("Sender MAC: ");
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed!");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Add Receiver
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer Add Failed");
    return;
  }

  // Init buffer
  for (int i = 0; i < 4; i++) {
    totals[i] = 0;

    for (int j = 0; j < numReadings; j++) {
      readings[i][j] = analogRead(flexPins[i]);
      totals[i] += readings[i][j];
    }
  }

  Serial.println("Sender Ready!");
}

// ================= LOOP =================

void loop() {

  for (int i = 0; i < 4; i++) {

    // Smooth ADC
    totals[i] -= readings[i][readIndex];
    readings[i][readIndex] = analogRead(flexPins[i]);
    totals[i] += readings[i][readIndex];

    float avg = totals[i] / numReadings;
    if (avg < 1) avg = 1;

    // Resistance
    float R = R_FIXED * ((4095.0 / avg) - 1.0);

    float R_LOW = flexCal[i][2];
    float R_HIGH = flexCal[i][3];

    // Hysteresis
    if (states[i] == 0 && R > R_HIGH)
      states[i] = 1;

    else if (states[i] == 1 && R < R_LOW)
      states[i] = 0;

    // Fill packet
    sendData.fingerStates[i] = states[i];
    sendData.flexResistances[i] = R;
  }

  sendData.timestamp = millis();

  // SEND DATA
  esp_now_send(receiverMac,
               (uint8_t *)&sendData,
               sizeof(sendData));

  // Debug
  Serial.print("TX: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(states[i]);
    Serial.print(" ");
  }
  Serial.println();

  readIndex = (readIndex + 1) % numReadings;

  delay(30);   // ~30 Hz
}
