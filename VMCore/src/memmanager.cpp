#include "../include/vmcpu.hpp"

void VMCPU::memoryManager() {
    int currentFrame = 0;

    while(true) {
        #ifdef _WIN32_DEV_ENVIRONMENT
            Sleep(10);
        #else _LINUX_DEV_ENVIRONMENT
            sleep(10);
        #endif
        if(isVMcpuTurnOff) {
            return;
        }
        if(needFrame) {
            memMutex.lock();
            {
                // sth
            }
            memMutex.unlock();
        }
    }
    return;
}