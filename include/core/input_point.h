#ifndef IDEAL_GAS_INPUT_POINT_H
#define IDEAL_GAS_INPUT_POINT_H

#include "cinder/gl/gl.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a single action
 */
class InputPoint {
public:
    /**
     * Default Constructor
     */
    InputPoint();
    /**
     * Constructor
     * @param time
     * @param position
     * @param key_one_pressed
     * @param key_two_pressed
     * @param r_mouse_pressed
     * @param l_mouse_pressed
     */
    InputPoint(long time, glm::vec2 position, bool key_one_pressed, bool key_two_pressed, bool r_mouse_pressed, bool l_mouse_pressed);

    /**
     * Getters
     */
    bool isPressed() const;
    long getTime() const;
    const glm::vec2& getPosition() const;
    bool keyOnePressed() const;
    bool keyTwoPressed() const;
    bool rMousePressed() const;
    bool lMousePressed() const;

    /**
     * Operator Overloading
     */
    friend std::ostream& operator<<(std::ostream& out, const InputPoint& input_point);
    friend std::istream& operator>>(std::istream& in, InputPoint& input_point);
private:
    long time_;

    glm::vec2 position_;
    bool key_one_pressed_;
    bool key_two_pressed_;
    bool r_mouse_pressed_;
    bool l_mouse_pressed_;

    /*
     * Bitwise:
     * 1: key one
     * 2: key two
     * 4: mouse one
     * 8: mouse two
     */
    int action_;
};

}

#endif //IDEAL_GAS_INPUT_POINT_H
