#include "NvmlWrapper.h"
#include <stdexcept>

NvmlWrapper::NvmlWrapper()
{
	auto nv_status = nvmlInit();
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlInit() failed, " + std::string(nvmlErrorString(nv_status)));

	char valueDriverVersion[NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE];
	nv_status = nvmlSystemGetDriverVersion(valueDriverVersion, NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlSystemGetDriverVersion() failed, " + std::string(nvmlErrorString(nv_status)));

	m_driverVersion = std::string(valueDriverVersion);

	char valueNVMLVersion[NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE];
	nv_status = nvmlSystemGetNVMLVersion(valueNVMLVersion, NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlSystemGetNVMLVersion() failed, " + std::string(nvmlErrorString(nv_status)));
	m_nvmlVersion = std::string(valueNVMLVersion);
}

NvmlWrapper::~NvmlWrapper() 
{
	auto nv_status = nvmlShutdown();
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlShutdown() failed, " + std::string(nvmlErrorString(nv_status)));
}

unsigned int NvmlWrapper::getFanSpeed(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value = 0;
	auto nv_status = nvmlDeviceGetFanSpeed(handle, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetFanSpeed() failed");

	return value;
}

unsigned int NvmlWrapper::getDeviceCount() const
{
	unsigned int device_count{ 0 };
	auto nv_status = nvmlDeviceGetCount(&device_count);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetCount() failed, " + std::string(nvmlErrorString(nv_status)));
	
	return device_count;
}

unsigned int NvmlWrapper::getDeviceTemperature(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value;
	auto nv_status = nvmlDeviceGetTemperature(handle, nvmlTemperatureSensors_t::NVML_TEMPERATURE_GPU, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetTemperature() failed, " + std::string(nvmlErrorString(nv_status)));

	return value;
}

unsigned int NvmlWrapper::getDevicePowerUsage(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value = 0;
	auto nv_status = nvmlDeviceGetPowerUsage(handle, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetPowerUsage() failed, " + std::string(nvmlErrorString(nv_status)));
	
	return value;
}

void NvmlWrapper::getDeviceUtilizationRates(const unsigned int index, const nvmlDevice_t& handle, nvmlUtilization_t& utilization) const
{
	auto nv_status = nvmlDeviceGetUtilizationRates(handle, &utilization);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetUtilizationRates() failed, " + std::string(nvmlErrorString(nv_status)));
}

void NvmlWrapper::getDeviceHandle(const unsigned int index, nvmlDevice_t& handle) const
{
	auto nv_status = nvmlDeviceGetHandleByIndex(index, &handle);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetHandleByIndex() failed, " + std::string(nvmlErrorString(nv_status)));
}

std::string NvmlWrapper::getDeviceName(const unsigned int index, const nvmlDevice_t& handle) const
{
	char value[NVML_DEVICE_NAME_BUFFER_SIZE];
	auto nv_status = nvmlDeviceGetName(handle, value, NVML_DEVICE_NAME_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		throw std::runtime_error("nvmlDeviceGetName() failed, " + std::string(nvmlErrorString(nv_status)));
	return std::string(value);
}

std::string NvmlWrapper::getDriverVersion() const
{
	return m_driverVersion;
}

std::string NvmlWrapper::getNVMLVersion() const
{
	return m_nvmlVersion;
}
