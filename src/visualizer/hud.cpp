#include "visualizer/hud.h"

namespace final_project {
Hud::Hud() {

}

Hud::Hud(double width, double height) {
    width_ = width;
    height_ = height;
}

void Hud::draw(long time) const {
    // Text
    ci::Font massive(kFont, 100);
    ci::Font med(kFont, 60);
    ci::gl::drawStringRight(std::to_string(map_.getCombo()) + "x", glm::vec2(width_ - 50, height_ - 100), ci::Color(1, 1, 1), massive);
    ci::gl::drawStringRight(map_.getFormatedScore(), glm::vec2(width_ - 50, 40), ci::Color(1, 1, 1), massive);
    ci::gl::drawStringRight(map_.getFormatedAccuracy() + "%", glm::vec2(width_ - 50, 150), ci::Color(1, 1, 1), med);

    // Progress bar
    double play_percentage = map_.getPlayPercent(time);
    glm::vec2 top_left(width_ - kProgressDim.x - 300, 150);
    glm::vec2 bottom_right = top_left + kProgressDim;
    ci::Rectf progress_edge(top_left, bottom_right);
    glm::vec2 progress_bottom = top_left + glm::vec2(kProgressDim.x * (double) (play_percentage / 100), kProgressDim.y);
    ci::Rectf progress_bar(top_left, progress_bottom);
    ci::gl::color(ci::ColorA(1, 1, 1, 0.6f));
    if (play_percentage >= 0 && play_percentage <= 100) {
        ci::gl::drawSolidRect(progress_bar);
    }
    ci::gl::color(1, 1, 1);
    ci::gl::drawStrokedRect(progress_edge, 5);
}

void Hud::update(Map& map) {
    map_ = map;
}

}// namespace final_project