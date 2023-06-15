#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>
#include <BLE2902.h>

// BLE Client variables
BLEClient* pClient;
bool deviceConnected = false;

// Server MAC Address
#define SERVER_MAC_ADDR  "3C:61:05:2F:F1:0A"

// BLE Service UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

// BLE Service Characteristics for different soil properties
#define NITROGEN_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define POTTASIUM_CHARACTERISTIC_UUID "e3d230bb-e698-4ddc-ab0a-f9391b4901d6"
#define HUMIDITY_CHARACTERISTIC_UUID "2a6889c3-3dba-4be1-800f-020d0f6ed471"

// Callback class for BLE client events
class MyClientCallbacks : public BLEClientCallbacks {
  void onConnect(BLEClient* pClient) {
    deviceConnected = true;
  }

  void onDisconnect(BLEClient* pClient) {
    deviceConnected = false;
  }
};

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);

  // Initialize BLE Client
  BLEClientInit();

}

void loop() {
  if (deviceConnected) {
    // Perform any desired actions with the connected server
    delay(1000);
  }
}

void BLEClientInit(){
  // Create the BLE Client
  BLEDevice::init("MyESP32");
  pClient = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallbacks());

  // Connect to the server
  pClient->connect(BLEAddress(SERVER_MAC_ADDR));

  // Get the service and characteristic
  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  BLERemoteCharacteristic* pNitrogenCharacteristic = pRemoteService->getCharacteristic(NITROGEN_CHARACTERISTIC_UUID);
  BLERemoteCharacteristic* pPottasiumCharacteristic = pRemoteService->getCharacteristic(POTTASIUM_CHARACTERISTIC_UUID);
  BLERemoteCharacteristic* pHumidityCharacteristic = pRemoteService->getCharacteristic(HUMIDITY_CHARACTERISTIC_UUID);

  // Enable notifications/indications
  pNitrogenCharacteristic->registerForNotify([](BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("Received Nitrogen data: ");
    Serial.write(pData, length);
    Serial.println();
  });

  pPottasiumCharacteristic->registerForNotify([](BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("Received Pottasium data: ");
    Serial.write(pData, length);
    Serial.println();
  });

  pHumidityCharacteristic->registerForNotify([](BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("Received Humidity data: ");
    Serial.write(pData, length);
    Serial.println();
  });


  delay(1000);
}
