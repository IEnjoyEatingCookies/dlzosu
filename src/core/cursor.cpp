#include "core/cursor.h"

namespace final_project {
Cursor::Cursor() {

}

void Cursor::drawCursorTrail(const glm::vec2 &position, bool expansion) const {
    double dim = kCursorSize;
    if (expansion) {
        dim *= kCursorExpansionMultiplier;
    }

    ci::gl::Texture2dRef cursor_trail_image = asset_loader.requestImage(kCursorTrailImage);
    ci::gl::color(1, 1, 1);
    ci::gl::pushModelMatrix();
    ci::gl::translate(position - glm::vec2(dim / 2, dim / 2));
    ci::gl::scale((float) (dim / cursor_trail_image->getWidth()), (float) (dim / cursor_trail_image->getHeight()));
    ci::gl::draw(cursor_trail_image);
    ci::gl::popModelMatrix();
}
void Cursor::drawMainCursor(const glm::vec2& position, bool expansion) const {
    double dim = kCursorSize;
    if (expansion) {
        dim *= kCursorExpansionMultiplier;
    }

    ci::gl::Texture2dRef cursor_image = asset_loader.requestImage(kCursorImage);
    ci::gl::color(1, 1, 1);
    ci::gl::pushModelMatrix();
    ci::gl::translate(position - glm::vec2(dim / 2, dim / 2));
    ci::gl::scale((float) (dim / cursor_image->getWidth()), (float) (dim / cursor_image->getHeight()));
    ci::gl::draw(cursor_image);
    ci::gl::popModelMatrix();
}

void Cursor::draw(const std::vector<InputPoint*>& inputs) const {
    for (size_t i = 0; i < inputs.size(); i++) {
        if (i == inputs.size() - 1) {
            drawMainCursor(inputs.at(i)->getPosition(), inputs.at(i)->isPressed());
        } else {
            drawCursorTrail(inputs.at(i)->getPosition(), inputs.at(i)->isPressed());
        }
    }
}

}