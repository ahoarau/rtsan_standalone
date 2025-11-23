#pragma once

namespace rtsan
{

class ScopedRealtimeSanitizer
{
  public:
    ScopedRealtimeSanitizer();
    ~ScopedRealtimeSanitizer();

  private:
#if __cplusplus >= 201103L
    ScopedRealtimeSanitizer(const ScopedRealtimeSanitizer &) = delete;
    ScopedRealtimeSanitizer &operator=(const ScopedRealtimeSanitizer &) = delete;
    ScopedRealtimeSanitizer(ScopedRealtimeSanitizer &&) = delete;
    ScopedRealtimeSanitizer &operator=(ScopedRealtimeSanitizer &&) = delete;
#else
    ScopedRealtimeSanitizer(const ScopedRealtimeSanitizer &);
    ScopedRealtimeSanitizer &operator=(const ScopedRealtimeSanitizer &);
#endif // __cplusplus >= 201103L
};

} // namespace rtsan