#include "../include/vmcpu.hpp"

void VMCPU::memoryManager() {
    std::unique_lock<std::mutex> memLock(memMutex);
    memLock.unlock();
    int currentFrame = 0;

    while(true) {
        memConditionVar.wait(lk, []{return isNewFrameNeed;});
        memLock.lock();

        if(isVMcpuTurnOff) {
            return;
        }

        //todo

        isFrameReady = true;
        memLock.unlock();
        memConditionVar.notify_all();
    }
    return;
}