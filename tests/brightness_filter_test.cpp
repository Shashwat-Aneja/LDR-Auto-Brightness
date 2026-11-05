#include <assert.h>
#include "../src/BrightnessFilter.h"

int main() {
    BrightnessFilter darkToBright;
    assert(darkToBright.update(0) == 255);
    assert(darkToBright.update(1023) < 255);
    assert(darkToBright.update(1023) < 255);

    BrightnessFilter direct(1.0f);
    assert(direct.update(0) == 255);
    assert(direct.update(1023) == 0);

    BrightnessFilter smoothed(0.25f);
    assert(smoothed.update(0) == 255);
    assert(smoothed.update(1023) == 191);
    assert(smoothed.update(1023) == 143);

    BrightnessFilter clamped;
    assert(clamped.update(-50) == 255);
    assert(clamped.update(2000) == 0);

    BrightnessFilter invalidFactor(0.0f);
    assert(invalidFactor.update(0) == 255);
    assert(invalidFactor.update(1023) == 204);

    return 0;
}
