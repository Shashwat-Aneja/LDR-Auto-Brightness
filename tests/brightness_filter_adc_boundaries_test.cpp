#include <assert.h>
#include "../src/BrightnessFilter.h"

int main() {
    BrightnessFilter filter(1.0f);
    assert(filter.update(-2147483647) == 255);
    assert(filter.filteredSensorValue() == 0.0f);
    assert(filter.update(2147483647) == 0);
    assert(filter.filteredSensorValue() == 1023.0f);
    assert(filter.update(512) >= 0);
    assert(filter.update(512) <= 255);
    return 0;
}
