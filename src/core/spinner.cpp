#include "core/spinner.h"

namespace final_project {
Spinner::Spinner() {

}

Spinner::Spinner(long approach_rate, long start_time, long end_time) {
    approach_rate_ = approach_rate;
    start_time_ = start_time;
    end_time_ = end_time;
    reset();
}

void Spinner::reset() {
    rotation_ = 0;
    spins_ = 0;
}

void Spinner::spin(double amount) {
    spins_ += std::abs(amount);
    rotation_ += amount;
    playHitSounds();
}

void Spinner::drawMarker(long time, long start, ci::Color color) const {
    if (time >= end_time_ && time <= start + kSpinnerMissLength) {
        float mult = (float) (time - start) / kSpinnerMissLength;

        ci::gl::color(color);
        ci::gl::drawStrokedCircle(kPlayfieldResolution / 2.0f, kSpinnerMiddleSize  * mult, kSpinnerMiddleSize * (1 - mult));
    }
}

void Spinner::playHitSounds() {
    if (isMiss()) {
        ci::audio::VoiceRef spin = asset_loader.requestAudio(kSpinnerSpin);
        spin->setVolume(kHitSoundVolume);
        spin->start();
    } else {
        ci::audio::VoiceRef complete = asset_loader.requestAudio(kSpinnerComplete);
        complete->setVolume(kHitSoundVolume);
        complete->start();
    }
}

bool Spinner::inRange(long time) const {
    return time >= start_time_ && time <= end_time_;
}

void Spinner::draw(long time) const {
    if (time >= start_time_ - approach_rate_ && time <= end_time_) {
        double mult = (double) (end_time_ - time) / (end_time_ - start_time_);
        glm::vec2 center = kPlayfieldResolution / 2.0f;

        // fade in
        if (time <= start_time_) {
            mult = 1;
            ci::gl::color(ci::ColorA(1, 1, 1, (float) (1 - (double) (start_time_ - time) / approach_rate_)));
        } else {
            ci::gl::color(1, 1, 1);
        }

        double radius = kSpinnerSize * mult;

        // approach
        ci::gl::Texture2dRef spinner_approach_circle = asset_loader.requestImage(kSpinnerApproachCircle);
        ci::gl::pushModelMatrix();
        ci::gl::translate(center - glm::vec2(radius, radius));
        ci::gl::scale((float) (radius * 2 / spinner_approach_circle->getWidth()), (float) (radius * 2 / spinner_approach_circle->getHeight()));
        ci::gl::draw(spinner_approach_circle);
        ci::gl::popModelMatrix();

        // middle
        ci::gl::Texture2dRef spinner_middle_circle = asset_loader.requestImage(kSpinnerMiddle);
        ci::gl::pushModelMatrix();
        ci::gl::translate(center - glm::vec2(kSpinnerMiddleSize / 2, kSpinnerMiddleSize / 2));
        ci::gl::scale((float) (kSpinnerMiddleSize / spinner_middle_circle->getWidth()), (float) (kSpinnerMiddleSize / spinner_middle_circle->getHeight()));
        ci::gl::draw(spinner_middle_circle);
        ci::gl::popModelMatrix();

        // top
        ci::gl::Texture2dRef spinner_top_circle = asset_loader.requestImage(kSpinnerTop);
        ci::gl::pushModelMatrix();
        ci::gl::translate(center);
        ci::gl::rotate((float) rotation_);
        ci::gl::translate(-glm::vec2(kSpinnerMiddleSize, kSpinnerMiddleSize));
        ci::gl::scale((float) (kSpinnerMiddleSize * 2 / spinner_top_circle->getWidth()), (float) (kSpinnerMiddleSize * 2 / spinner_top_circle->getHeight()));
        ci::gl::draw(spinner_top_circle);
        ci::gl::popModelMatrix();

        if (!isMiss()) {
            ci::gl::Texture2dRef spinner_clear = asset_loader.requestImage(kSpinnerClear);
            ci::gl::pushModelMatrix();
            ci::gl::translate(center - kSpinnerClearDim / 2.0f);
            ci::gl::scale((float) (kSpinnerClearDim.x / spinner_clear->getWidth()), (float) (kSpinnerClearDim.y / spinner_clear->getHeight()));
            ci::gl::draw(spinner_clear);
            ci::gl::popModelMatrix();
        }
    }
    if (isMiss()) {
        drawMarker(time, end_time_, kSpinnerMissColor);
    }
}

bool Spinner::isAfter(long time) const {
    return time > end_time_;
}

size_t Spinner::getScore() const {
    if (isMiss()) {
        return 0;
    } else {
        return 1000 + 1000 * (size_t) (spins_ * 10000 / (end_time_ - start_time_) / kSpinnerExtraRPM);
    }
}
bool Spinner::isMiss() const {
    return spins_ * 60000 < (end_time_ - start_time_) * 2 * M_PI * kSpinnerRPM;
}

}

