#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>

// ================= SERVO =================

const int servoPins[4] = {18, 17, 16, 15};

Servo servos[4];

const int FLAT = 10;
const int BENT = 170;

// ================= DATA =================

typedef struct struct_message {
  int fingerStates[4];
  float flexResistances[4];
  uint32_t timestamp;
} struct_message;

struct_message rxData;

// ================= TIMING =================

unsigned long lastRX = 0;
const int TIMEOUT = 1000;

// ================= CALLBACK =================

void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *data,
                int len) {

  memcpy(&rxData, data, sizeof(rxData));

  lastRX = millis();

  for (int i = 0; i < 4; i++) {

    if (i % 2 == 0) {
      servos[i].write(rxData.fingerStates[i] ? FLAT : BENT);
    } else {
      servos[i].write(rxData.fingerStates[i] ? BENT : FLAT);
    }
  }

  // Debug
  Serial.print("RX: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(rxData.fingerStates[i]);
    Serial.print(" ");
  }
  Serial.println();
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());

  // Servo init
  for (int i = 0; i < 4; i++) {

    servos[i].setPeriodHertz(50);
    servos[i].attach(servoPins[i]);

    servos[i].write(FLAT);
  }

  // ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Failed!");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver Ready!");
}

// ================= LOOP =================

void loop() {

  // Safety
  if (millis() - lastRX > TIMEOUT) {

    for (int i = 0; i < 4; i++) {
      servos[i].write(FLAT);
    }

    static unsigned long t = 0;

    if (millis() - t > 2000) {
      Serial.println("⚠️ No Signal");
      t = millis();
    }
  }

  delay(50);
}
