#include "core/input.h"

namespace final_project {
Input::Input() {

}

InputPoint* Input::update(long time, const glm::vec2& mouse_position, const std::set<int>& key_presses, bool r_mouse, bool l_mouse) {
    InputPoint* cur_action = new InputPoint(time, glm::vec2(mouse_position.x, mouse_position.y), key_presses.find(kKeyOne) != key_presses.end(), key_presses.find(kKeyTwo) != key_presses.end(), r_mouse, l_mouse);
    inputs_.push_back(cur_action);
    return cur_action;
}

const InputPoint* Input::getInput(long time) const {
    size_t index = inputs_.size() - 1;
    while (index > 0 && inputs_.at(index)->getTime() > time) {
        --index;
    }
    return inputs_.at(index);
}
const std::vector<InputPoint*> Input::getInputs(size_t num) const {
    std::vector<InputPoint*> inputs;
    size_t num_index = std::max((size_t) 0, inputs_.size() - num);
    while (num_index < inputs_.size()) {
        inputs.push_back(inputs_[num_index]);
        ++num_index;
    }
    return inputs;
}
const std::vector<InputPoint*> Input::getInputs(long time, size_t num) const {
    std::vector<InputPoint*> inputs;
    size_t index = inputs_.size() - 1;
    while (index > 0 && inputs_.at(index)->getTime() > time) {
        --index;
    }
    size_t num_index = std::max((size_t) 0, index - num + 1);
    while (num_index < inputs_.size() && num_index < num) {
        inputs.push_back(inputs_[num_index]);
        ++num_index;
    }
    return inputs;
}
const std::vector<InputPoint*>& Input::getInputs() const {
    return inputs_;
}

std::ostream& operator<<(std::ostream& out, const Input& input) {
    for (InputPoint* input_point : input.inputs_) {
        out << *input_point;
    }
    return out;
}
std::istream& operator>>(std::istream& in, Input& input) {
    std::string line;
    while (std::getline(in, line)) {
        InputPoint* input_point = new InputPoint();
        std::stringstream s(line);
        s >> *input_point;
        input.inputs_.push_back(input_point);
    }
    return in;
}

}