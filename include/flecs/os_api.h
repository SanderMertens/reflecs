/**
 * @file os_api.h
 * @brief Operationg system abstractions.
 *
 * This file contains the operating system abstraction API. The flecs core 
 * library avoids OS/runtime specific API calls as much as possible. Instead it
 * provides an interface that can be implemented by applications.
 *
 * Examples for how to implement this interface can be found in the 
 * examples/os_api folder.
 */

#ifndef FLECS_OS_API_H
#define FLECS_OS_API_H

#include <stdarg.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <malloc.h>
#elif defined(__FreeBSD__)
#include <stdlib.h>
#else
#include <alloca.h>
#endif

#if defined(_WIN32)
#define ECS_OS_WINDOWS
#elif defined(__linux__)
#define ECS_OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define ECS_OS_DARWIN
#else
/* Unknown OS */
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ecs_time_t {
    uint32_t sec;
    uint32_t nanosec;
} ecs_time_t;

/* Allocation counters (not thread safe) */
extern int64_t ecs_os_api_malloc_count;
extern int64_t ecs_os_api_realloc_count;
extern int64_t ecs_os_api_calloc_count;
extern int64_t ecs_os_api_free_count;

/* Use handle types that _at least_ can store pointers */
typedef uintptr_t ecs_os_thread_t;
typedef uintptr_t ecs_os_cond_t;
typedef uintptr_t ecs_os_mutex_t;
typedef uintptr_t ecs_os_dl_t;

/* Generic function pointer type */
typedef void (*ecs_os_proc_t)(void);

/* OS API init */
typedef 
void (*ecs_os_api_init_t)(void);

/* OS API deinit */
typedef 
void (*ecs_os_api_fini_t)(void);

/* Memory management */
typedef 
void* (*ecs_os_api_malloc_t)(
    ecs_size_t size);

typedef 
void (*ecs_os_api_free_t)(
    void *ptr);

typedef
void* (*ecs_os_api_realloc_t)(
    void *ptr, 
    ecs_size_t size);

typedef
void* (*ecs_os_api_calloc_t)(
    ecs_size_t size);

typedef
char* (*ecs_os_api_strdup_t)(
    const char *str);

/* Threads */
typedef
void* (*ecs_os_thread_callback_t)(
    void*);

typedef
ecs_os_thread_t (*ecs_os_api_thread_new_t)(
    ecs_os_thread_callback_t callback,
    void *param);

typedef
void* (*ecs_os_api_thread_join_t)(
    ecs_os_thread_t thread);


/* Atomic increment / decrement */
typedef
int (*ecs_os_api_ainc_t)(
    int32_t *value);


/* Mutex */
typedef
ecs_os_mutex_t (*ecs_os_api_mutex_new_t)(
    void);

typedef
void (*ecs_os_api_mutex_lock_t)(
    ecs_os_mutex_t mutex);

typedef
void (*ecs_os_api_mutex_unlock_t)(
    ecs_os_mutex_t mutex);

typedef
void (*ecs_os_api_mutex_free_t)(
    ecs_os_mutex_t mutex);

/* Condition variable */
typedef
ecs_os_cond_t (*ecs_os_api_cond_new_t)(
    void);

typedef
void (*ecs_os_api_cond_free_t)(
    ecs_os_cond_t cond);

typedef
void (*ecs_os_api_cond_signal_t)(
    ecs_os_cond_t cond);

typedef
void (*ecs_os_api_cond_broadcast_t)(
    ecs_os_cond_t cond);

typedef
void (*ecs_os_api_cond_wait_t)(
    ecs_os_cond_t cond,
    ecs_os_mutex_t mutex);

typedef 
void (*ecs_os_api_sleep_t)(
    int32_t sec,
    int32_t nanosec);

typedef
void (*ecs_os_api_get_time_t)(
    ecs_time_t *time_out);

/* Logging */
typedef
void (*ecs_os_api_log_t)(
    const char *fmt,
    va_list args);

/* Application termination */
typedef
void (*ecs_os_api_abort_t)(
    void);

/* Dynamic libraries */
typedef
ecs_os_dl_t (*ecs_os_api_dlopen_t)(
    const char *libname);

typedef
ecs_os_proc_t (*ecs_os_api_dlproc_t)(
    ecs_os_dl_t lib,
    const char *procname);

typedef
void (*ecs_os_api_dlclose_t)(
    ecs_os_dl_t lib);

typedef
char* (*ecs_os_api_module_to_path_t)(
    const char *module_id);

/* Prefix members of struct with 'ecs_' as some system headers may define 
 * macro's for functions like "strdup", "log" or "_free" */

typedef struct ecs_os_api_t {
    /* API init / deinit */
    ecs_os_api_init_t init_;
    ecs_os_api_fini_t fini_;

    /* Memory management */
    ecs_os_api_malloc_t malloc_;
    ecs_os_api_realloc_t realloc_;
    ecs_os_api_calloc_t calloc_;
    ecs_os_api_free_t free_;

    /* Strings */
    ecs_os_api_strdup_t strdup_;

    /* Threads */
    ecs_os_api_thread_new_t thread_new_;
    ecs_os_api_thread_join_t thread_join_;

    /* Atomic incremenet / decrement */
    ecs_os_api_ainc_t ainc_;
    ecs_os_api_ainc_t adec_;

    /* Mutex */
    ecs_os_api_mutex_new_t mutex_new_;
    ecs_os_api_mutex_free_t mutex_free_;
    ecs_os_api_mutex_lock_t mutex_lock_;
    ecs_os_api_mutex_lock_t mutex_unlock_;

    /* Condition variable */
    ecs_os_api_cond_new_t cond_new_;
    ecs_os_api_cond_free_t cond_free_;
    ecs_os_api_cond_signal_t cond_signal_;
    ecs_os_api_cond_broadcast_t cond_broadcast_;
    ecs_os_api_cond_wait_t cond_wait_;

    /* Time */
    ecs_os_api_sleep_t sleep_;
    ecs_os_api_get_time_t get_time_;

    /* Logging */
    ecs_os_api_log_t log_;
    ecs_os_api_log_t log_error_;
    ecs_os_api_log_t log_debug_;
    ecs_os_api_log_t log_warning_;

    /* Application termination */
    ecs_os_api_abort_t abort_;

    /* Dynamic library loading */
    ecs_os_api_dlopen_t dlopen_;
    ecs_os_api_dlproc_t dlproc_;
    ecs_os_api_dlclose_t dlclose_;

    /* Overridable function that translates from a logical module id to a
     * shared library filename */
    ecs_os_api_module_to_path_t module_to_dl_;

    /* Overridable function that translates from a logical module id to a
     * path that contains module-specif resources or assets */
    ecs_os_api_module_to_path_t module_to_etc_;    
} ecs_os_api_t;

FLECS_API
extern ecs_os_api_t ecs_os_api;

FLECS_API
void ecs_os_init(void);

FLECS_API
void ecs_os_fini(void);

FLECS_API
void ecs_os_set_api(
    ecs_os_api_t *os_api);

FLECS_API
void ecs_os_set_api_defaults(void);

/* Memory management */
#ifndef ecs_os_malloc
#define ecs_os_malloc(size) ecs_os_api.malloc_(size)
#endif
#ifndef ecs_os_free
#define ecs_os_free(ptr) ecs_os_api.free_(ptr)
#endif
#ifndef ecs_os_realloc
#define ecs_os_realloc(ptr, size) ecs_os_api.realloc_(ptr, size)
#endif
#ifndef ecs_os_calloc
#define ecs_os_calloc(size) ecs_os_api.calloc_(size)
#endif
#if defined(_MSC_VER) || defined(__MINGW32__)
#define ecs_os_alloca(size) _alloca((size_t)(size))
#else
#define ecs_os_alloca(size) alloca((size_t)(size))
#endif

/* Strings */
#ifndef ecs_os_strdup
#define ecs_os_strdup(str) ecs_os_api.strdup_(str)
#endif

#ifdef __cplusplus
#define ecs_os_strlen(str) static_cast<ecs_size_t>(strlen(str))
#define ecs_os_strncmp(str1, str2, num) strncmp(str1, str2, static_cast<size_t>(num))
#define ecs_os_memcmp(ptr1, ptr2, num) memcmp(ptr1, ptr2, static_cast<size_t>(num))
#define ecs_os_memcpy(ptr1, ptr2, num) memcpy(ptr1, ptr2, static_cast<size_t>(num))
#define ecs_os_memset(ptr, value, num) memset(ptr, value, static_cast<size_t>(num))
#define ecs_os_memmove(ptr, value, num) memmove(ptr, value, static_cast<size_t>(num))
#else
#define ecs_os_strlen(str) (ecs_size_t)strlen(str)
#define ecs_os_strncmp(str1, str2, num) strncmp(str1, str2, (size_t)(num))
#define ecs_os_memcmp(ptr1, ptr2, num) memcmp(ptr1, ptr2, (size_t)(num))
#define ecs_os_memcpy(ptr1, ptr2, num) memcpy(ptr1, ptr2, (size_t)(num))
#define ecs_os_memset(ptr, value, num) memset(ptr, value, (size_t)(num))
#define ecs_os_memmove(ptr, value, num) memmove(ptr, value, (size_t)(num))
#endif

#define ecs_os_strcmp(str1, str2) strcmp(str1, str2)

#if defined(_MSC_VER)
#define ecs_os_strcat(str1, str2) strcat_s(str1, INT_MAX, str2)
#ifndef FLECS_LEGACY
#define ecs_os_sprintf(ptr, ...) sprintf_s(ptr, INT_MAX, __VA_ARGS__)
#endif
#define ecs_os_vsprintf(ptr, fmt, args) vsprintf_s(ptr, INT_MAX, fmt, args)
#define ecs_os_strcpy(str1, str2) strcpy_s(str1, INT_MAX, str2)
#ifdef __cplusplus
#define ecs_os_strncpy(str1, str2, num) strncpy_s(str1, INT_MAX, str2, static_cast<size_t>(num))
#else
#define ecs_os_strncpy(str1, str2, num) strncpy_s(str1, INT_MAX, str2, (size_t)(num))
#endif
#else
#define ecs_os_strcat(str1, str2) strcat(str1, str2)
#ifndef FLECS_LEGACY
#define ecs_os_sprintf(ptr, ...) sprintf(ptr, __VA_ARGS__)
#endif
#define ecs_os_vsprintf(ptr, fmt, args) vsprintf(ptr, fmt, args)
#define ecs_os_strcpy(str1, str2) strcpy(str1, str2)
#ifdef __cplusplus
#define ecs_os_strncpy(str1, str2, num) strncpy(str1, str2, static_cast<size_t>(num))
#else
#define ecs_os_strncpy(str1, str2, num) strncpy(str1, str2, (size_t)(num))
#endif
#endif

/* Threads */
#define ecs_os_thread_new(callback, param) ecs_os_api.thread_new_(callback, param)
#define ecs_os_thread_join(thread) ecs_os_api.thread_join_(thread)

/* Atomic increment / decrement */
#define ecs_os_ainc(value) ecs_os_api.ainc_(value)
#define ecs_os_adec(value) ecs_os_api.adec_(value)

/* Mutex */
#define ecs_os_mutex_new() ecs_os_api.mutex_new_()
#define ecs_os_mutex_free(mutex) ecs_os_api.mutex_free_(mutex)
#define ecs_os_mutex_lock(mutex) ecs_os_api.mutex_lock_(mutex)
#define ecs_os_mutex_unlock(mutex) ecs_os_api.mutex_unlock_(mutex)

/* Condition variable */
#define ecs_os_cond_new() ecs_os_api.cond_new_()
#define ecs_os_cond_free(cond) ecs_os_api.cond_free_(cond)
#define ecs_os_cond_signal(cond) ecs_os_api.cond_signal_(cond)
#define ecs_os_cond_broadcast(cond) ecs_os_api.cond_broadcast_(cond)
#define ecs_os_cond_wait(cond, mutex) ecs_os_api.cond_wait_(cond, mutex)

/* Time */
#define ecs_os_sleep(sec, nanosec) ecs_os_api.sleep_(sec, nanosec)
#define ecs_os_get_time(time_out) ecs_os_api.get_time_(time_out)

/* Logging (use functions to avoid using variadic macro arguments) */
FLECS_API
void ecs_os_log(const char *fmt, ...);

FLECS_API
void ecs_os_warn(const char *fmt, ...);

FLECS_API
void ecs_os_err(const char *fmt, ...);

FLECS_API
void ecs_os_dbg(const char *fmt, ...);

/* Application termination */
#define ecs_os_abort() ecs_os_api.abort_()

/* Dynamic libraries */
#define ecs_os_dlopen(libname) ecs_os_api.dlopen_(libname)
#define ecs_os_dlproc(lib, procname) ecs_os_api.dlproc_(lib, procname)
#define ecs_os_dlclose(lib) ecs_os_api.dlclose_(lib)

/* Module id translation */
#define ecs_os_module_to_dl(lib) ecs_os_api.module_to_dl_(lib)
#define ecs_os_module_to_etc(lib) ecs_os_api.module_to_etc_(lib)

/* Sleep with floating point time */
FLECS_API
void ecs_sleepf(
    double t);

/* Measure time since provided timestamp */
FLECS_API
double ecs_time_measure(
    ecs_time_t *start);

/* Calculate difference between two timestamps */
FLECS_API
ecs_time_t ecs_time_sub(
    ecs_time_t t1,
    ecs_time_t t2);

/* Convert time value to a double */
FLECS_API
double ecs_time_to_double(
    ecs_time_t t);

FLECS_API
void* ecs_os_memdup(
    const void *src, 
    ecs_size_t size);

/** Are heap functions available? */
FLECS_API
bool ecs_os_has_heap(void);

/** Are threading functions available? */
FLECS_API
bool ecs_os_has_threading(void);

/** Are time functions available? */
FLECS_API
bool ecs_os_has_time(void);

/** Are logging functions available? */
FLECS_API
bool ecs_os_has_logging(void);

/** Are dynamic library functions available? */
FLECS_API
bool ecs_os_has_dl(void);

/** Are module path functions available? */
FLECS_API
bool ecs_os_has_modules(void);

#ifdef __cplusplus
}
#endif

#endif
