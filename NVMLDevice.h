#pragma once
#include "NvmlWrapper.h"

struct Metrics
{
    unsigned int fanSpeed;
    unsigned int temperature;
    unsigned int powerUsage;
    unsigned int gpuUtilization;
    unsigned int memoryUtilization;
};

class NVMLDevice
{
public:

    NVMLDevice(const unsigned int index, const nvmlDevice_t handle, const NvmlWrapper& nvmlWrapper);
    Metrics refreshMetrics();

private:
    const unsigned int m_index;
    const nvmlDevice_t m_handle;
    const NvmlWrapper& m_wrapper;

    unsigned int m_fanSpeed;
    unsigned int m_temperature;
    unsigned int m_powerUsage;
    unsigned int m_gpuUtilization;
    unsigned int m_memoryUtilization;
};

