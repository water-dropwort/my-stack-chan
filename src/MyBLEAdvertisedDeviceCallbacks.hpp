#ifndef MYBLEADVERTISEDDEVICECALLBACKS_HPP_
#define MYBLEADVERTISEDDEVICECALLBACKS_HPP_

#include <BLEUUID.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>

class MyBLEAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  private:
    BLEUUID m_targetUUID;
    BLEAdvertisedDevice* m_advDevice = nullptr;
  
  public:
    MyBLEAdvertisedDeviceCallbacks(BLEUUID target) {
      m_targetUUID = target;
    }

    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if(advertisedDevice.haveServiceUUID()) {
        BLEUUID servUUID = advertisedDevice.getServiceUUID();
        if (servUUID.equals(m_targetUUID)) {
          m_advDevice = new BLEAdvertisedDevice(advertisedDevice);
          BLEDevice::getScan()->stop();
        }
      }
    }

    BLEAdvertisedDevice* getAdvDevice() {
      return m_advDevice;
    }
};

#endif
