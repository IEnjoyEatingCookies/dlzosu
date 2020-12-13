#include <visualizer/osu.h>

namespace final_project {

namespace visualizer {

Osu::Osu() {

}

void Osu::setup() {
    ci::app::setFullScreen(true);
    ci::gl::enableAlphaBlending();
    ci::gl::enableVerticalSync(false);
    ci::app::setFrameRate(240.0f);
    hideCursor();
    game_.setup(getWindowWidth(), getWindowHeight());
    game_.update(getMousePos(), held_keys_, clicked_keys_, l_mouse_held_, r_mouse_held_);
}

void Osu::update() {
    game_.update(getMousePos(), held_keys_, clicked_keys_, l_mouse_held_, r_mouse_held_);
    clicked_keys_.clear();
}

void Osu::draw() {
    game_.draw();
}

void Osu::click(ci::app::MouseEvent event) {
}

void Osu::release(ci::app::MouseEvent event) {
}

void Osu::mouseDown(ci::app::MouseEvent event) {
    if (!clicked_) {
    click(event);
    }
    clicked_ = true;
    released_ = false;

    if (event.isRight()) {
      r_mouse_held_ = true;
    }
    if (event.isLeft()) {
      l_mouse_held_ = true;
    }
}

void Osu::mouseUp(ci::app::MouseEvent event) {
    if(!released_) {
        release(event);
    }
    clicked_ = false;
    released_ = true;

    if (event.isRight()) {
        r_mouse_held_ = false;
    }
    if (event.isLeft()) {
        l_mouse_held_ = false;
    }
}

void Osu::mouseDrag(ci::app::MouseEvent event) {
}

void Osu::keyUp(ci::app::KeyEvent event) {
    held_keys_.erase(event.getChar());
}

void Osu::keyDown(ci::app::KeyEvent event) {
    if (event.getCode() == kKeyQuit) { // quit the program
        quit();
    }
    if (held_keys_.find(event.getCode()) == held_keys_.end()) {
        clicked_keys_.insert(event.getCode());
    }
    held_keys_.insert(event.getCode());
}

}  // namespace visualizer

}  // namespace final_p