#ifndef IDEAL_GAS_INPUT_H
#define IDEAL_GAS_INPUT_H

#include "core/input_point.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a collection of inputs
 */
class Input {
public:
    /**
     * Default Constructor
     */
    Input();

    /**
     * Updates the input and returns an InputPoint
     * @param time
     * @param mouse_position
     * @param key_presses
     * @param r_mouse
     * @param l_mouse
     * @return InputPoint*
     */
    InputPoint* update(long time, const glm::vec2& mouse_position, const std::set<int>& key_presses, bool r_mouse, bool l_mouse);\

    /**
     * Returns the input at a time
     * @param time
     * @return InputPoint*
     */
    const InputPoint* getInput(long time) const;
    /**
     * Returns all inputs
     * @return std::vector<InputPoint*>
     */
    const std::vector<InputPoint*>& getInputs() const;
    /**
     * Returns the latest num inputs
     * @param num
     * @return std::vector<InputPoint*>
     */
    const std::vector<InputPoint*> getInputs(size_t num) const;
    /**
     * Returns the last num inputs at a time
     * @param time
     * @param num
     * @return std::vector<InputPoint*>
     */
    const std::vector<InputPoint*> getInputs(long time, size_t num) const;

    /**
     * Operator Overloading
     */
    friend std::ostream& operator<<(std::ostream& out, const Input& input);
    friend std::istream& operator>>(std::istream& in, Input& input);
private:
    std::vector<InputPoint*> inputs_;
};

}

#endif //IDEAL_GAS_INPUT_H
