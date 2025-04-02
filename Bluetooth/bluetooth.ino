// part1
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_SPP_Device");  // Bluetooth name
  pinMode(2, OUTPUT);
  Serial.println("Classic Bluetooth SPP started!");
}

void loop() {
  if (SerialBT.available()) {
    String received = SerialBT.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(received);
    
    SerialBT.print("Echo: ");
    SerialBT.println(received);

    if (received == "ON") digitalWrite(2, HIGH);
    if (received == "OFF") digitalWrite(2, LOW);
  }
}

// part 2
// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>
// #include <BLE2902.h>

// BLECharacteristic* pCharacteristic;
// bool deviceConnected = false;

// class MyServerCallbacks : public BLEServerCallbacks {
//   void onConnect(BLEServer* pServer) {
//     deviceConnected = true;
//     Serial.println("BLE Client Connected");
//   }

//   void onDisconnect(BLEServer* pServer) {
//     deviceConnected = false;
//     Serial.println("BLE Client Disconnected");
//   }
// };

// void setup() {
//   Serial.begin(115200);
//   pinMode(2, OUTPUT);

//   BLEDevice::init("ESP32_BLE_Device");
//   BLEServer *pServer = BLEDevice::createServer();
//   pServer->setCallbacks(new MyServerCallbacks());

//   BLEService *pService = pServer->createService("180F");  // Battery Service UUID
//   pCharacteristic = pService->createCharacteristic(
//                       "2A19",  // Battery Level characteristic
//                       BLECharacteristic::PROPERTY_READ |
//                       BLECharacteristic::PROPERTY_NOTIFY |
//                       BLECharacteristic::PROPERTY_WRITE
//                     );

//   pCharacteristic->addDescriptor(new BLE2902());
//   pCharacteristic->setValue("Hello from ESP32!");
//   pService->start();

//   pServer->getAdvertising()->start();
//   Serial.println("BLE advertising started!");
// }

// void loop() {
//   if (deviceConnected) {
//     pCharacteristic->setValue("Updated at " + String(millis()));
//     pCharacteristic->notify();
//     delay(2000);
//   }
// }
