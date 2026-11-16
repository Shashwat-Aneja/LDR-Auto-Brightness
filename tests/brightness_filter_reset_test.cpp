#include "../src/BrightnessFilter.h"
#include <cassert>

int main() {
    BrightnessFilter filter(0.5f);
    filter.update(1023);
    filter.reset();
    assert(filter.filteredSensorValue() == 0.0f);
    assert(filter.update(0) == 255);
    filter.update(1000);
    assert(filter.filteredSensorValue() == 500.0f);
    filter.reset();
    filter.reset();
    assert(filter.update(1023) == 0);
    return 0;
}
