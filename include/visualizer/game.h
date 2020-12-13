#ifndef IDEAL_GAS_GAME_H
#define IDEAL_GAS_GAME_H

#include <windows.h>
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"

#include "core/map.h"
#include "core/input.h"
#include "core/cursor.h"
#include "cinder/app/App.h"
#include "visualizer/menu.h"
#include "visualizer/hud.h"
#include "visualizer/end_screen.h"
#include "IO/global_configurations.h"

namespace final_project {
enum Screen {
    kMenu,
    kReplay,
    kGame,
    kEnd
};

/**
 * Represents the Game
 */
class Game {
public:
    /**
     * Default Constructor
     */
    Game();

    /**
     * Sets up the game
     * @param window_width
     * @param window_height
     */
    void setup(int window_width, int window_height);

    /**
     * Plays the current map
     */
    void start_map();

    /**
     * Draws the current frame
     */
    void draw() const;
    /**
     * Updates the current frame with input
     * @param mouse_position
     * @param held_keys
     * @param clicked_keys
     * @param r_mouse_held
     * @param l_mouse_held
     */
    void update(const glm::vec2& mouse_position, const std::set<int>& held_keys, const std::set<int>& clicked_keys, bool r_mouse_held, bool l_mouse_held);
private:
    /**
     * Updates the current frame's key input
     * @param held_keys
     * @param clicked_keys
     */
    void keyInput(const std::set<int>& held_keys, const std::set<int>& clicked_keys);
    /**
     * Returns the current time
     * @return double time
     */
    long getTime() const;

    Screen screen_;
    glm::vec2 resolution_;
    glm::vec2 playfield_origin_;
    float osu_pixel_scale_;

    std::string map_name_;
    std::string audio_path_;
    ci::audio::VoiceRef song_;
    long begin_;

    EndScreen end_screen_;
    Menu menu_;
    Hud hud_;
    Cursor cursor_;
    Input input_;
    Map map_;
};

}

#endif //IDEAL_GAS_GAME_H
