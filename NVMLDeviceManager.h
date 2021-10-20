#pragma once
#include "NvmlWrapper.h"
#include <vector>
#include "NVMLDevice.h"

class NVMLDeviceManager 
{
public:
    NVMLDeviceManager(const NvmlWrapper& wrapper);
    ~NVMLDeviceManager();

    size_t getDeviceCount() const;
    const std::vector<NVMLDevice>::iterator devicesBegin();
    const std::vector<NVMLDevice>::iterator devicesEnd();

private:
    void loadDevices();

    const NvmlWrapper& m_wrapper;
    std::vector<NVMLDevice> m_devices;
};

