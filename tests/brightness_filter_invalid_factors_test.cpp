#include <assert.h>
#include <limits>
#include "../src/BrightnessFilter.h"

int main() {
    const float invalidFactors[] = {
        -1.0f,
        0.0f,
        1.1f,
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()
    };
    for (float factor : invalidFactors) {
        BrightnessFilter filter(factor);
        assert(filter.update(0) == 255);
        assert(filter.update(1023) == 204);
    }
    return 0;
}
