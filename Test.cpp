// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>

#include "NVMLDevice.h"
#include "NVMLDeviceManager.h"

int main()
{
	NvmlWrapper wrapper;
	NVMLDeviceManager manager(wrapper);
	
	while (true)
	{
		for (auto itr = manager.devicesBegin(); itr != manager.devicesEnd(); ++itr)
		{
			auto m = itr->refreshMetrics();

			std::cout << "Temperature : " << m.temperature << " degree C"
				<< " Fan speed: " << m.fanSpeed << "%"
				<< " Gpu usage: " << m.gpuUtilization << "%"
				<< " memeory usage: " << m.memoryUtilization
				<< " power usage: " << m.powerUsage
				<< " gpu clock: " << m.gpuClock << "MHz"
				<< " mem clock: " << m.memClock << "MHz" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
