#pragma once

#include "logpp/core/config.h"

#if defined(LOGPP_PLATFORM_LINUX)
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#elif defined(LOGPP_PLATFORM_DARWIN)
#include <cstdint>
#include <pthread.h>
#elif defined(LOGPP_PLATFORM_WINDOWS)
#include <windows.h>
#include <processthreadsapi.h>
#endif

namespace logpp::thread_utils
{
#if defined(LOGPP_PLATFORM_LINUX)
    using id = pid_t;

    inline id getCurrentId()
    {
        return syscall(SYS_gettid);
    }

    inline long toInteger(id id)
    {
        return static_cast<long>(id);
    }
#elif defined(LOGPP_PLATFORM_DARWIN)
    using id = uint64_t;

    inline id getCurrentId()
    {
        uint64_t tid = 0;
        pthread_threadid_np(nullptr, &tid);
        return tid;
    }

    inline uint64_t toInteger(id id)
    {
        return id;
    }
#elif defined(LOGPP_PLATFORM_WINDOWS)
    using id = DWORD;

    inline id getCurrentId()
    {
        return GetCurrentThreadId();
    }

    inline uint32_t toInteger(id id)
    {
        return static_cast<uint32_t>(id);
    }
#else
#error "Thread information not available on current platform"
#endif
}
