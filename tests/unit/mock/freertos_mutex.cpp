#include "freertos_mutex.hpp"

// uncomment this to get buffer size ass compile time error message
// char (*__give_me_buffere_size)[sizeof( StaticSemaphore_t )] = 1;
// use that size in header as buffer_size

void FreeRTOS_Mutex::unlock() {}
bool FreeRTOS_Mutex::try_lock() { return true; }
void FreeRTOS_Mutex::lock() { return; }
FreeRTOS_Mutex::FreeRTOS_Mutex() noexcept // ctor should be constexpr, but cannot due C code
    : xSemaphore(nullptr) {}
FreeRTOS_Mutex::FreeRTOS_Mutex(FreeRTOS_Mutex &&mutex)
    : xSemaphore(mutex.xSemaphore) {};
void buddy::lock(std::unique_lock<FreeRTOS_Mutex> &l1, std::unique_lock<FreeRTOS_Mutex> &l2) {
    if (&l1 < &l2) {
        l1.lock();
        l2.lock();
    } else {
        l2.lock();
        l1.lock();
    }
}
