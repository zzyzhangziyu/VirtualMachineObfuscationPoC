#include "../include/vmcpu.hpp"

void VMCPU::memoryManager() 
{
    // std::unique_lock<std::mutex> memLock(memMutex);
    // memLock.unlock();
    // int currentFrame = 0;

    // while(true) {
    //     memConditionVar.wait(memLock, []{ return isNewFrameNeed; });
    //     memLock.lock();

    //     if(isVMcpuTurnOff) {
    //         return;
    //     }

    //     // TODO: memory swap

    //     isFrameReady = true;
    //     memLock.unlock();
    //     memConditionVar.notify_all();
    // }
    std::cout << "NOT IMPLEMENTED YET!" << std::endl;
    return;
}