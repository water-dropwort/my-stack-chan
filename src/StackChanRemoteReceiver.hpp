#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#define SERVICE_UUID       "c36489fd-110d-4bd5-8844-49f947fab85f"
#define CHARACTERISTIC_UUID "d2fbe672-a9c3-47d5-af29-186acfc34c21"

#include <BLEDevice.h>

namespace MyStackChan {
  class StackChanRemoteReceiver : public BLEAdvertisedDeviceCallbacks, public BLEClientCallbacks {
    public:
      StackChanRemoteReceiver();

      void scan();

      bool controllerFound();

      bool connect();

      void onResult(BLEAdvertisedDevice advertisedDevice);

      bool isConnected();

      uint32_t readCommand();

      void onConnect(BLEClient* client);

      void onDisconnect(BLEClient* client);

    private:
      bool m_controllerFound = false;
      BLEAdvertisedDevice* m_advertisedDevice = nullptr;
      BLEClient* m_client = nullptr;
      BLERemoteService* m_remoteService = nullptr;
      BLERemoteCharacteristic* m_remoteCharacteristic = nullptr;
  };

}

#endif
