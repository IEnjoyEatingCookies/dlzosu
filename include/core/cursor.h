#ifndef IDEAL_GAS_CURSOR_H
#define IDEAL_GAS_CURSOR_H

#include <vector>
#include "cinder/gl/gl.h"
#include "core/input.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a Cursor
 */
class Cursor {
public:
    /**
     * Default Constructor
     */
    Cursor();

    /**
     * Draws the cursor
     * @param inputs
     */
    void draw(const std::vector<InputPoint*>& inputs) const;
private:
    /**
     * Draws a cursor tail
     * @param position
     * @param expansion
     */
    void drawCursorTrail(const glm::vec2& position, bool expansion) const;
    /**
     * Draws the main cursor
     * @param position
     * @param expansion
     */
    void drawMainCursor(const glm::vec2& position, bool expansion) const;
};

}

#endif //IDEAL_GAS_CURSOR_H
