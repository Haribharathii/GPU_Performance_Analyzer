#include <iostream>
#include <nvml.h>
#include <thread>
#include <chrono>

class GPUPerformanceMonitor
{
public:
    GPUPerformanceMonitor()
    {
        nvmlInit();
    }

    ~GPUPerformanceMonitor()
    {
        nvmlShutdown();
    }

    void getGpuInfo()
    {
        nvmlDevice_t device;
        nvmlDeviceGetHandleByIndex(0, &device);

        unsigned int temp;
        nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
        std::cout << "GPU Temperature: " << temp << "C" << std::endl;

        nvmlUtilization_t utilization;
        nvmlDeviceGetUtilizationRates(device, &utilization);
        std::cout << "GPU Utilization: " << utilization.gpu << "%" << std::endl;

        nvmlMemory_t memory;
        nvmlDeviceGetMemoryInfo(device, &memory);
        std::cout << "GPU Memory Used: " << memory.used / (1024 * 1024) << " MB" << std::endl;
        std::cout << "GPU Memory Free: " << memory.free / (1024 * 1024) << " MB" << std::endl;
    }
};

int main()
{
    GPUPerformanceMonitor monitor;

    while (true)
    {
        monitor.getGpuInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
