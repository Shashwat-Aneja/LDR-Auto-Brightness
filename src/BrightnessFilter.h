#ifndef LDR_BRIGHTNESS_FILTER_H
#define LDR_BRIGHTNESS_FILTER_H

class BrightnessFilter {
public:
    enum { ADC_MAX = 1023, PWM_MAX = 255 };

    explicit BrightnessFilter(float smoothingFactor = 0.2f)
        : smoothingFactor_(isValidFactor(smoothingFactor) ? smoothingFactor : 0.2f),
          filteredSensorValue_(0.0f),
          initialized_(false) {}

    int update(int rawSensorValue) {
        if (rawSensorValue < 0) {
            rawSensorValue = 0;
        } else if (rawSensorValue > ADC_MAX) {
            rawSensorValue = ADC_MAX;
        }

        if (!initialized_) {
            filteredSensorValue_ = static_cast<float>(rawSensorValue);
            initialized_ = true;
        } else {
            filteredSensorValue_ += smoothingFactor_
                * (static_cast<float>(rawSensorValue) - filteredSensorValue_);
        }

        const float scaled = (ADC_MAX - filteredSensorValue_) * PWM_MAX / ADC_MAX;
        int brightness = static_cast<int>(scaled + 0.5f);
        if (brightness < 0) {
            brightness = 0;
        } else if (brightness > PWM_MAX) {
            brightness = PWM_MAX;
        }
        return brightness;
    }

    float filteredSensorValue() const {
        return filteredSensorValue_;
    }

private:
    static bool isValidFactor(float factor) {
        return factor > 0.0f && factor <= 1.0f;
    }

    float smoothingFactor_;
    float filteredSensorValue_;
    bool initialized_;
};

#endif
