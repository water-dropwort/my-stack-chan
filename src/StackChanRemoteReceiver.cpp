#include "StackChanRemoteReceiver.hpp"
#include <M5Unified.h>

using namespace MyStackChan;

StackChanRemoteReceiver::StackChanRemoteReceiver() {
  BLEDevice::init("");
  BLEScan* blescan = BLEDevice::getScan();
  blescan->setAdvertisedDeviceCallbacks(this);
  blescan->setActiveScan(true);

  m_client = BLEDevice::createClient();
  m_client->setClientCallbacks(this);
}

void StackChanRemoteReceiver::scan() {
  Serial.println("Called scan");
  BLEDevice::getScan()->stop();
  if(m_advertisedDevice != nullptr) {
    delete m_advertisedDevice;
  }
  m_advertisedDevice = nullptr;
  BLEDevice::getScan()->start(5);
}

bool StackChanRemoteReceiver::controllerFound() {
  return m_controllerFound;
}

bool StackChanRemoteReceiver::connect() {
  if(m_advertisedDevice == nullptr) {
    return false;
  }
  if(isConnected()) {
    return false;
  }

  m_client->connect(m_advertisedDevice);
  
  m_remoteService = m_client->getService(SERVICE_UUID);
  if(m_remoteService == nullptr) {
    Serial.println("NO SERVICE");
    m_client->disconnect();
    return false;
  }

  m_remoteCharacteristic = m_remoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if(m_remoteCharacteristic == nullptr) {
    Serial.println("NO CHAR");
    m_client->disconnect();
    return false;
  }

  return true;
}

void StackChanRemoteReceiver::onResult(BLEAdvertisedDevice advertisedDevice) {
  Serial.println("onResult");
  if(advertisedDevice.haveServiceUUID() 
     && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
    BLEDevice::getScan()->stop();
    m_advertisedDevice = new BLEAdvertisedDevice(advertisedDevice);
    m_controllerFound = true;
  }
}

uint32_t StackChanRemoteReceiver::readCommand() {
  return m_remoteCharacteristic->readUInt32();
}

bool StackChanRemoteReceiver::isConnected() {
  return m_client->isConnected();
}

void StackChanRemoteReceiver::onConnect(BLEClient* client) {

}

void StackChanRemoteReceiver::onDisconnect(BLEClient* client) {
  Serial.println("disconnect");
}
