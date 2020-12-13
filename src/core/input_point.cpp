#include "core/input_point.h"

namespace final_project {

InputPoint::InputPoint() {

}
InputPoint::InputPoint(long time, glm::vec2 position, bool key_one_pressed, bool key_two_pressed, bool r_mouse_pressed,
                       bool l_mouse_pressed) {
    time_ = time;
    position_ = position;
    key_one_pressed_ = key_one_pressed;
    key_two_pressed_ = key_two_pressed;
    r_mouse_pressed_ = r_mouse_pressed;
    l_mouse_pressed_ = l_mouse_pressed;
    action_ = 0;
    if (key_one_pressed) {
        action_ += 1;
    }
    if (key_two_pressed) {
        action_ += 2;
    }
    if (r_mouse_pressed) {
        action_ += 4;
    }
    if (l_mouse_pressed) {
        action_ += 8;
    }

}

bool InputPoint::isPressed() const {
    return action_ > 0;
}

const glm::vec2 &InputPoint::getPosition() const {
    return position_;
}

long InputPoint::getTime() const {
    return time_;
}

bool InputPoint::keyOnePressed() const {
    return key_one_pressed_;
}

bool InputPoint::keyTwoPressed() const {
    return key_two_pressed_;
}

bool InputPoint::rMousePressed() const {
    return r_mouse_pressed_;
}

bool InputPoint::lMousePressed() const {
    return l_mouse_pressed_;
}

std::ostream& operator<<(std::ostream& out, const InputPoint& input_point) {
    out << input_point.time_;
    out << "," << input_point.position_.x << "," << input_point.position_.y;
    out << "," << input_point.action_;
    return out;
}

std::istream& operator>>(std::istream& in, InputPoint& input_point) {
    std::string line;
    in >> line;
    std::vector<std::string> args = delimit(line);
    if (args.size() != 4) {
        throw std::out_of_range("Incorrect lines");
    }
    input_point.time_ = std::stol(args[0]);
    input_point.position_ = glm::vec2(std::stoi(args[1]), std::stoi(args[2]));
    input_point.action_ = std::stoi(args[3]);
    int action = input_point.action_;

    input_point.key_one_pressed_ = false;
    input_point.key_two_pressed_ = false;
    input_point.r_mouse_pressed_ = false;
    input_point.l_mouse_pressed_ = false;
    if (action >= 8) {
        action -= 8;
        input_point.l_mouse_pressed_ = true;
    }
    if (action >= 4) {
        action -= 4;
        input_point.r_mouse_pressed_ = true;
    }
    if (action >= 2) {
        action -= 2;
        input_point.key_two_pressed_ = true;
    }
    if (action >= 1) {
        input_point.key_one_pressed_ = true;
    }
    return in;
}
}