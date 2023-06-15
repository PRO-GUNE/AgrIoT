#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE Server variables
BLEServer *pServer;
BLECharacteristic *pNitrogenCharacteristic;
BLECharacteristic *pPottasiumCharacteristic;
BLECharacteristic *pHumidityCharacteristic;
bool deviceConnected = false;

// BLE Service UUID
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

// BLE Service Characteristics for different soil properties
#define NITROGEN_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define POTTASIUM_CHARACTERISTIC_UUID "e3d230bb-e698-4ddc-ab0a-f9391b4901d6"
#define HUMIDITY_CHARACTERISTIC_UUID "2a6889c3-3dba-4be1-800f-020d0f6ed471"

// variables to hold values read by soil sensors
static char nitrogen[6];
static char pottasium[6];
static char humidity[6];

// Callback class for BLE server events
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

void setup()
{
  // Initialize Serial Communication
  Serial.begin(115200);

  // Initialize BLE Server
  BLEServerInit();
}

void loop()
{
  if (deviceConnected)
  {
    characteristicNotify(pNitrogenCharacteristic, nitrogen);
    characteristicNotify(pPottasiumCharacteristic, pottasium);
    characteristicNotify(pHumidityCharacteristic, humidity);
    delay(1000);
  }
}

void characteristicNotify(BLECharacteristic *pCharacteristic, char *value)
{
  // Update the characteristic value with data from sensors or other sources
  pCharacteristic->setValue(value);
  // Notify/Indicate the value to the connected client
  pCharacteristic->notify();
}

void BLEServerInit()
{
  // Create the BLE Server
  BLEDevice::init("MyESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the BLE Characteristics
  pNitrogenCharacteristic = pService->createCharacteristic(
      NITROGEN_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY);

  pPottasiumCharacteristic = pService->createCharacteristic(
      POTTASIUM_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY);

  pHumidityCharacteristic = pService->createCharacteristic(
      HUMIDITY_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY);

  // Add a descriptor for the Characteristic
  pNitrogenCharacteristic->addDescriptor(new BLE2902());
  pPottasiumCharacteristic->addDescriptor(new BLE2902());
  pHumidityCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting for connections...");
}
