#include <rtsan_standalone/rtsan.hh>
#include "rtsan_standalone.hh"

namespace rtsan
{
ScopedRealtimeSanitizer::ScopedRealtimeSanitizer()
{
    __rtsan_realtime_enter();
}
ScopedRealtimeSanitizer::~ScopedRealtimeSanitizer()
{
    __rtsan_realtime_exit();
}
} // namespace rtsan