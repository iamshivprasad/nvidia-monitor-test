#pragma once
#include "nvml.h"
#include <string>


class NvmlWrapper
{
public:
	explicit NvmlWrapper();
	~NvmlWrapper();
	unsigned int getFanSpeed(const unsigned int index, const nvmlDevice_t& handle) const;
	unsigned int getDeviceCount() const;
	unsigned int getDeviceTemperature(const unsigned int index, const nvmlDevice_t& handle) const;
	unsigned int getDevicePowerUsage(const unsigned int index, const nvmlDevice_t& handle) const;
	unsigned int getClockInfo(nvmlClockType_t type, const nvmlDevice_t& handle) const;
	//void getPsuInfo(const unsigned int index, nvmlPSUInfo_t& psu) const;
	void getDeviceUtilizationRates(const unsigned int index, const nvmlDevice_t& handle, nvmlUtilization_t& utilization) const;
	void getDeviceHandle(const unsigned int index, nvmlDevice_t& handle)const;
	std::string getDeviceName(const unsigned int index, const nvmlDevice_t& handle) const;

	std::string getDriverVersion() const;
	std::string getNVMLVersion() const;

private:
	std::string m_driverVersion;
	std::string m_nvmlVersion;

};