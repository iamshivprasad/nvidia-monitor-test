#include "NvmlWrapper.h"
#include <stdexcept>
#include <iostream>
#include <iostream>

NvmlWrapper::NvmlWrapper()
{
	auto nv_status = nvmlInit();
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlInit() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
		return;
	}
		

	char valueDriverVersion[NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE];
	nv_status = nvmlSystemGetDriverVersion(valueDriverVersion, NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlSystemGetDriverVersion() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
		return;
	}

	m_driverVersion = std::string(valueDriverVersion);

	char valueNVMLVersion[NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE];
	nv_status = nvmlSystemGetNVMLVersion(valueNVMLVersion, NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlSystemGetNVMLVersion() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
		return;
	}
	m_nvmlVersion = std::string(valueNVMLVersion);

}

NvmlWrapper::~NvmlWrapper() 
{
	auto nv_status = nvmlShutdown();
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
		std::cout << "nvmlShutdown() failed";
}

unsigned int NvmlWrapper::getFanSpeed(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value = 0;
	auto nv_status = nvmlDeviceGetFanSpeed(handle, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetFanSpeed() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}

	return value;
}

unsigned int NvmlWrapper::getDeviceCount() const
{
	unsigned int device_count{ 0 };
	auto nv_status = nvmlDeviceGetCount(&device_count);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetCount() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}
	
	return device_count;
}

unsigned int NvmlWrapper::getDeviceTemperature(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value;
	auto nv_status = nvmlDeviceGetTemperature(handle, nvmlTemperatureSensors_t::NVML_TEMPERATURE_GPU, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetTemperature() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}

	return value;
}

unsigned int NvmlWrapper::getClockInfo(nvmlClockType_t type, const nvmlDevice_t& handle) const
{
	unsigned int value = 0;
	auto nv_status = nvmlDeviceGetClockInfo(handle, type, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetClockInfo() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}

	return value;
}

unsigned int NvmlWrapper::getDevicePowerUsage(const unsigned int index, const nvmlDevice_t& handle) const
{
	unsigned int value = 0;
	auto nv_status = nvmlDeviceGetPowerUsage(handle, &value);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetPowerUsage() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}
	
	return value;
}

//void NvmlWrapper::getPsuInfo(const unsigned int index, nvmlPSUInfo_t& psu) const
//{
//	nvmlUnit_t temp = new nvmlUnit_st();
//	auto nv_status = nvmlUnitGetHandleByIndex(index, &temp);
//	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
//	{
//		std::cout << "nvmlUnitGetHandleByIndex() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
//		return;
//	}
//
//	nv_status = nvmlUnitGetPsuInfo(temp, &psu);
//	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
//	{
//		std::cout << "nvmlUnitGetPsuInfo() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
//	}
//}

void NvmlWrapper::getDeviceUtilizationRates(const unsigned int index, const nvmlDevice_t& handle, nvmlUtilization_t& utilization) const
{
	auto nv_status = nvmlDeviceGetUtilizationRates(handle, &utilization);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetUtilizationRates() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}
}

void NvmlWrapper::getDeviceHandle(const unsigned int index, nvmlDevice_t& handle) const
{
	auto nv_status = nvmlDeviceGetHandleByIndex(index, &handle);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetHandleByIndex() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}
}

std::string NvmlWrapper::getDeviceName(const unsigned int index, const nvmlDevice_t& handle) const
{
	char value[NVML_DEVICE_NAME_BUFFER_SIZE];
	auto nv_status = nvmlDeviceGetName(handle, value, NVML_DEVICE_NAME_BUFFER_SIZE);
	if (nv_status != nvmlReturn_t::NVML_SUCCESS)
	{
		std::cout << "nvmlDeviceGetName() failed, " << std::string(nvmlErrorString(nv_status)) << std::endl;
	}
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
