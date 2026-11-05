#include <assert.h>
#include "../src/BrightnessFilter.h"

int main() {
    BrightnessFilter darkToBright;
    assert(darkToBright.update(0) == 255);
    const int firstStep = darkToBright.update(1023);
    const int secondStep = darkToBright.update(1023);
    assert(firstStep < 255);
    assert(secondStep < firstStep);

    BrightnessFilter direct(1.0f);
    assert(direct.update(0) == 255);
    assert(direct.update(1023) == 0);

    BrightnessFilter smoothed(0.25f);
    assert(smoothed.update(0) == 255);
    assert(smoothed.update(1023) == 191);
    assert(smoothed.update(1023) == 143);

    BrightnessFilter clamped(1.0f);
    assert(clamped.update(-50) == 255);
    assert(clamped.update(2000) == 0);

    BrightnessFilter invalidFactor(0.0f);
    assert(invalidFactor.update(0) == 255);
    assert(invalidFactor.update(1023) == 204);

    return 0;
}
