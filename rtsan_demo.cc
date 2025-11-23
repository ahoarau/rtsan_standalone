#include <rtsan_standalone/rtsan_standalone.h>
#include <vector>

int process()
{
    __rtsan::ScopedSanitizeRealtime srs;
    auto vec = std::vector<int>(3);
    vec.push_back(42);
    return 0;
}

int main()
{
    __rtsan::Initialize();
    return process();
}