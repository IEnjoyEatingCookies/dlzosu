#ifndef OSU_END_SCREEN_H
#define OSU_END_SCREEN_H

#include "core/map.h"

namespace final_project {

class EndScreen {
public:
    EndScreen();
    EndScreen(double width, double height);

    void draw() const;
    void update(const Map& map);
private:
    void drawImage(const glm::vec2& position, const glm::vec2& dim, const ci::gl::Texture2dRef& image) const;

    double width_;
    double height_;

    Map map_;
};

}

#endif //OSU_END_SCREEN_H
