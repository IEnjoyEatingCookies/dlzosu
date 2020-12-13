#ifndef OSU_HUD_H
#define OSU_HUD_H

#include "cinder/gl/gl.h"
#include "core/map.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a HUD
 */
class Hud {
public:
    /**
     * Default Constructor
     */
    Hud();
    /**
     * Constructor
     * @param width
     * @param height
     */
    Hud(double width, double height);

    /**
     * Draws the HUD
     */
    void draw(long time) const;
    /**
     * Updates the HUD
     * @param combo
     * @param score
     */
    void update(Map& map);
private:
    double width_;
    double height_;

    Map map_;
};

} // namespace final_project

#endif //OSU_HUD_H
