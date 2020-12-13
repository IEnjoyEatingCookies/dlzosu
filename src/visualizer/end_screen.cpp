#include "visualizer/end_screen.h"

namespace final_project {
EndScreen::EndScreen() {

}

EndScreen::EndScreen(double width, double height) {
    width_ = width;
    height_ = height;
}

void EndScreen::draw() const {
    ci::Color white(1, 1, 1);
    ci::ColorA banner_color(0, 0, 0, 0.8f);

    // Background
    ci::gl::Texture2dRef background_image = asset_loader.requestImage(map_.getSongFileName(), map_.getBackgroundFilename());
    ci::gl::pushModelMatrix();
    ci::gl::scale((float) (width_ / background_image->getWidth()), (float) (height_ / background_image->getHeight()));
    ci::gl::color(white);
    ci::gl::draw(background_image);
    ci::gl::popModelMatrix();

    // Title
    ci::gl::color(banner_color);
    glm::vec2 banner_top_left(0, 0);
    glm::vec2 banner_bottom_right(width_, height_ / 7);
    ci::Rectf banner(banner_top_left, banner_bottom_right);
    ci::gl::drawSolidRect(banner);

    ci::Font massive(kFont, 100);
    ci::Font big(kFont, 60);
    ci::Font med(kFont, 40);
    ci::gl::drawStringRight(map_.getVersion(), glm::vec2(width_ - 50, 35), white, big);
    ci::gl::drawStringRight(map_.getArtist(), glm::vec2(width_ - 50, 85), white, med);

    // Score
    ci::gl::color(banner_color);
    glm::vec2 score_top_left(width_ / 100, height_ / 6);
    glm::vec2 score_bottom_right(width_ / 2, height_ / 4.2);
    ci::Rectf score_rect(score_top_left, score_bottom_right);
    ci::gl::drawSolidRoundedRect(score_rect, 5);

    ci::gl::drawStringCentered("Score", glm::vec2(width_ / 100 + 50, height_ / 4.2 - 40), white, med);
    ci::gl::drawStringRight(map_.getFormatedScore(), glm::vec2(width_ / 2 - 50, height_ / 5.8), white, massive);

    // Accuracy
    ci::gl::color(banner_color);
    glm::vec2 accuracy_top_left(width_ / 100, height_ / 4);
    glm::vec2 accuracy_bottom_right(width_ / 2, height_ * 5 / 6);
    ci::Rectf accuracy_rect(accuracy_top_left, accuracy_bottom_right);
    ci::gl::drawSolidRoundedRect(accuracy_rect, 5);

    glm::vec2 top_left = accuracy_top_left + glm::vec2(50, 20);
    glm::vec2 bottom_right = accuracy_bottom_right - glm::vec2(20, 20);

    double gap = (double) (bottom_right.y - top_left.y - 3 * kIconSize.y) / 4;
    double middle = (double) (bottom_right.x - top_left.x) / 2;
    ci::gl::Texture2dRef image_300 = asset_loader.requestImage(kHit300);
    ci::gl::Texture2dRef image_100 = asset_loader.requestImage(kHit100);
    ci::gl::Texture2dRef image_50 = asset_loader.requestImage(kHit50);
    ci::gl::Texture2dRef image_0 = asset_loader.requestImage(kHit0);

    drawImage(top_left + glm::vec2(0, gap), kIconSize, image_300);
    ci::gl::drawStringCentered(std::to_string(map_.getHit300s()) + "x", top_left + glm::vec2(middle / 2, gap + kIconSize.y / 2 - 20), white, massive);

    drawImage(top_left + glm::vec2(0, 2 * gap + kIconSize.y), kIconSize, image_100);
    ci::gl::drawStringCentered(std::to_string(map_.getHit100s()) + "x", top_left + glm::vec2(middle / 2, gap * 2 + kIconSize.y * 3 / 2 - 20), white, massive);

    drawImage(top_left + glm::vec2(0, 3 * gap + 2 * kIconSize.y), kIconSize, image_50);
    ci::gl::drawStringCentered(std::to_string(map_.getHit50s()) + "x", top_left + glm::vec2(middle / 2, gap * 3 + kIconSize.y * 5 / 2 - 20), white, massive);

    drawImage(top_left + glm::vec2(middle, gap), kIconSize, image_0);
    ci::gl::drawStringCentered(std::to_string(map_.getHitMisses()) + "x", top_left + glm::vec2(middle * 3 / 2, gap + kIconSize.y / 2 - 20), white, massive);

    ci::gl::drawStringCentered("Max Combo", top_left + glm::vec2(middle * 3 / 2, gap * 2 + kIconSize.y), white, med);
    ci::gl::drawStringCentered(std::to_string(map_.getMaxCombo()) + "x", top_left + glm::vec2(middle * 3 / 2, gap * 2 + kIconSize.y + 40), white, massive);
    ci::gl::drawStringCentered("Accuracy", top_left + glm::vec2(middle * 3 / 2, gap * 3 + kIconSize.y * 2), white, med);
    ci::gl::drawStringCentered(map_.getFormatedAccuracy() + "%", top_left + glm::vec2(middle * 3 / 2, gap * 3 + kIconSize.y * 2 + 40), white, massive);

    // Rating
    std::string rating = map_.getRating();
    ci::gl::Texture2dRef rating_image = asset_loader.requestImage(kRankingX);
    if (rating == "S") {
        rating_image = asset_loader.requestImage(kRankingS);
    } else if (rating == "A") {
        rating_image = asset_loader.requestImage(kRankingA);
    } else if (rating == "B") {
        rating_image = asset_loader.requestImage(kRankingB);
    } else if (rating == "C") {
        rating_image = asset_loader.requestImage(kRankingC);
    } else if (rating == "D") {
        rating_image = asset_loader.requestImage(kRankingD);
    }
    glm::vec2 rating_dim(500, 500);
    drawImage(glm::vec2(width_ * 2 / 3, height_ / 4), rating_dim, rating_image);

    // restart
    ci::gl::color(ci::ColorA(1, 1, 1, 0.8f));
    glm::vec2 restart_top_left(width_ * 4 / 7, height_ * 2 / 3);
    glm::vec2 restart_bottom_right(width_ * 9 / 10, height_ * 7 / 9);
    ci::Rectf restart_rect(restart_top_left, restart_bottom_right);
    ci::gl::drawSolidRoundedRect(restart_rect, 5);
    ci::gl::drawStringCentered("Press Escape to Return to Menu", (restart_top_left + restart_bottom_right) / 2.0f + glm::vec2(0, -30), ci::Color(0, 0, 0), big);
}

void EndScreen::drawImage(const glm::vec2 &position, const glm::vec2 &dim, const ci::gl::Texture2dRef& image) const {
    ci::gl::pushModelMatrix();
    ci::gl::translate(position);
    ci::gl::scale(dim.x / image->getWidth(), dim.y / image->getHeight());
    ci::gl::color(1, 1, 1);
    ci::gl::draw(image);
    ci::gl::popModelMatrix();
}

void EndScreen::update(const Map& map) {
    map_ = map;
}
}