#include "NVMLDevice.h"
#include "nvml.h"

NVMLDevice::NVMLDevice(const unsigned int index, const nvmlDevice_t handle, 
	const NvmlWrapper& nvmlWrapper) :m_wrapper(nvmlWrapper), m_index(index), m_handle(handle),
	m_fanSpeed(0), m_gpuUtilization(0), m_memoryUtilization(0), m_temperature(0), m_powerUsage(0)
{
}

Metrics NVMLDevice::refreshMetrics()
{
	m_fanSpeed = m_wrapper.getFanSpeed(m_index, m_handle);

	nvmlUtilization_t temp;
	m_wrapper.getDeviceUtilizationRates(m_index, m_handle, temp);
	m_gpuUtilization = temp.gpu;
	m_memoryUtilization = temp.memory;

	m_powerUsage = m_wrapper.getDevicePowerUsage(m_index, m_handle);
	m_temperature = m_wrapper.getDeviceTemperature(m_index, m_handle);

	return Metrics
	{
		m_fanSpeed, m_temperature, m_powerUsage, m_gpuUtilization, m_memoryUtilization
	};
}
