#include "NVMLDeviceManager.h"

NVMLDeviceManager::NVMLDeviceManager(const NvmlWrapper& nvmlWrapper) : m_wrapper(nvmlWrapper)
{
    loadDevices();
}

NVMLDeviceManager::~NVMLDeviceManager()
{
    m_devices.clear();
}

const std::vector<NVMLDevice>::iterator NVMLDeviceManager::devicesBegin()
{
	return m_devices.begin();
}

const std::vector<NVMLDevice>::iterator NVMLDeviceManager::devicesEnd()
{
	return m_devices.end();
}

void NVMLDeviceManager::loadDevices()
{
    const unsigned int deviceCount = m_wrapper.getDeviceCount();

    if (deviceCount == 0) 
    {
        return;
    }

    for (unsigned int deviceIndex{ 0 }; deviceIndex < deviceCount; ++deviceIndex)
    {
        nvmlDevice_t handle;
        m_wrapper.getDeviceHandle(deviceIndex, handle);

        NVMLDevice device{ deviceIndex, handle, m_wrapper };
        m_devices.push_back(device);
    }
}

size_t NVMLDeviceManager::getDeviceCount() const
{
    return m_devices.size();
}