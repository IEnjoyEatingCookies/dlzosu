#include "core/circle.h"

namespace final_project {
Circle::Circle() {

}

Circle::Circle(glm::vec2 position, long time, float radius, int approach_rate, float overall_difficulty, const ci::Color& color) {
    position_ = position;
    time_ = time;
    radius_ = radius;
    approach_rate_ = approach_rate;
    outer_radius_ = (float) (radius_ - kCircleWidth / 2);
    color_ = color;
    hit_ = -1;
    setHitWindow(overall_difficulty);
}

void Circle::reset() {
    hit_ = -1;
}

bool Circle::isAfter(long time) const {
    return time >= time_ + hit_window_50_;
}

bool Circle::inRange(long time) const {
    // Not hit and in the time window
    return time >= time_ - approach_rate_ && time <= time_ + hit_window_50_;
}

bool Circle::isHit(long time) const {
    return hit_ != -1 && inRange(hit_) && hit_ <= time;
}

size_t Circle::getScore() const {
    if (hit_ >= time_ - hit_window_300_ && hit_ <= time_ + hit_window_300_) { // 300 hit
        return 300;
    } else if (hit_ >= time_ - hit_window_100_ && hit_ <= time_ + hit_window_100_) { // 100 hit
        return 100;
    } else if (hit_ >= time_ - hit_window_50_ && hit_ <= time_ + hit_window_50_) { // 50 hit
        return 50;
    }
    return 0;
}

bool Circle::correctHit() const {
    return getScore() > 0;
}

bool Circle::isMiss() const {
    return hit_ != -1 && hit_ >= time_ - hit_window_early_ && hit_ <= time_ - hit_window_50_ || hit_ == -1 || hit_ >= time_ + hit_window_50_;
}

void Circle::setHitWindow(float overall_difficulty) {
    hit_window_300_ = (long) (80 - 6 * overall_difficulty);
    hit_window_100_ = (long) (140 - 8 * overall_difficulty);
    hit_window_50_ = (long) (200 - 10 * overall_difficulty);
    hit_window_early_ = (long) (260 - 12 * overall_difficulty);
}

void Circle::drawApproachCircle(long time) const {
    if (time <= time_) {
        ci::gl::drawStrokedCircle(position_, outer_radius_ * (kCircleApproach - (kCircleApproach - 1) * (float) (time - time_ + approach_rate_) / approach_rate_), (float) radius_ / kCircleWidth);
    }
}

void Circle::drawCircle(long time) const {
    // alpha is transparency
    float alpha = (float) (approach_rate_ - std::abs(time - time_)) / approach_rate_;

    // draw the actual circle
    ci::gl::color(ci::ColorA(1, 1, 1, alpha)); // white
    ci::gl::drawStrokedCircle(position_, outer_radius_, (float) radius_ / kCircleWidth);
    ci::ColorA color(color_.r, color_.g, color_.b, alpha);
    ci::gl::color(color);
    ci::gl::drawStrokedCircle(position_, outer_radius_ * ((2 * kCircleWidth - 3) / (2 * kCircleWidth)), (float) radius_ / kCircleWidth);
}

void Circle::drawHit(long time) const {
    if (time <= hit_ + hit_window_50_) {
        // alpha is transparency
        float alpha = (float) 0.5 * (1 - (time - hit_) / hit_window_50_);
        float radius_mult = (float) (1 + kCircleDissipate * (time - hit_) / hit_window_50_);

        // draw the actual circle
        ci::gl::color(ci::ColorA(1, 1, 1, alpha)); // white
        ci::gl::drawStrokedCircle(position_, outer_radius_ * radius_mult, (float) radius_ / kCircleWidth);
        ci::ColorA color(color_.r, color_.g, color_.b, alpha);
        ci::gl::color(color);
        ci::gl::drawStrokedCircle(position_, outer_radius_ * ((2 * kCircleWidth - 3) / (2 * kCircleWidth)) * radius_mult, (float) radius_ / kCircleWidth);
    }
}

void Circle::drawMarker(long time, long start, const ci::Color& color) const {
    if (time >= start && time <= start + kCircleMarkerLength * hit_window_50_) {
        float mult = (float) ((time - start) / kCircleMarkerLength / hit_window_50_);

        ci::gl::color(color);
        ci::gl::drawStrokedCircle(position_, radius_ * kCircleMarkerSize * mult, radius_ * kCircleMarkerSize * (1 - mult));
    }
}

void Circle::draw(long time) const {
    if (isHit(time)) {
        if (hit_ >= time_ - hit_window_300_ && hit_ <= time_ + hit_window_300_) { // 300 hit
            drawHit(time);
        } else if (hit_ >= time_ - hit_window_100_ && hit_ <= time_ + hit_window_100_) { // 100 hit
            drawHit(time);
            drawMarker(time, hit_, kCircle100Color);
        } else if (hit_ >= time_ - hit_window_50_ && hit_ <= time_ + hit_window_50_) { // 50 hit
            drawHit(time);
            drawMarker(time, hit_, kCircle50Color);
        } else if (hit_ >= time_ - hit_window_early_) { // too early or too late (miss)
            drawMarker(time, hit_, kCircleMissColor);
        } else { // was hit too early to be considered a hit
            drawCircle(time);
            drawApproachCircle(time);
        }
    } else { // if has not been hit yet, just draw the circle
        if (inRange(time)) {
            drawCircle(time);
            drawApproachCircle(time);
        }   else if (time > time_ + hit_window_50_) { // circle was not hit (too late)
            drawMarker(time, time_ + hit_window_50_, kCircleMissColor);
        }
    }

}
void Circle::hit(long time) {
    if (time > time_ - hit_window_early_ && hit_ == -1) {
        hit_ = time;
        playHitSound();
    }
}

void Circle::playHitSound() const {
    ci::audio::VoiceRef& hit_sound = asset_loader.requestAudio(kHitSoundAudio, false);
    if (hit_sound->isPlaying()) {
        hit_sound->stop();
    }
    hit_sound->setVolume(kHitSoundVolume);
    hit_sound->start();
}

const glm::vec2& Circle::getPosition() const {
    return position_;
}
float Circle::getRadius() const {
    return radius_;
}

}