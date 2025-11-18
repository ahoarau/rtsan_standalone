#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Enter real-time context.
// When in a real-time context, RTSan interceptors will error if realtime
// violations are detected. Calls to this method are injected at the code
// generation stage when RTSan is enabled.
// corresponds to a [[clang::nonblocking]] attribute.
void __rtsan_realtime_enter(void);

// Exit the real-time context.
// When not in a real-time context, RTSan interceptors will simply forward
// intercepted method calls to the real methods.
void __rtsan_realtime_exit(void);

// Disable all RTSan error reporting in an otherwise real-time context.
// Must be paired with a call to `__rtsan_enable`
void __rtsan_disable(void);

// Re-enable all RTSan error reporting.
// Must follow a call to `__rtsan_disable`.
void __rtsan_enable(void);

// Initializes rtsan if it has not been initialized yet.
// Used by the RTSan runtime to ensure that rtsan is initialized before any
// other rtsan functions are called.
void __rtsan_ensure_initialized(void);

// Allows the user to specify a function as not-real-time-safe
// Including this in the first line of a function definition is
// analogous to marking a function `[[clang::blocking]]`
void __rtsan_notify_blocking_call(const char *blocking_function_name);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus