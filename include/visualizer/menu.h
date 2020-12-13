#ifndef IDEAL_GAS_MENU_H
#define IDEAL_GAS_MENU_H

#include <iostream>
#include <filesystem>
#include "cinder/app/App.h"
#include "IO/map_loader.h"
#include "cinder/audio/audio.h"
#include "IO/global_configurations.h"

namespace final_project {

const double kTitleHeight = 60;

/**
 * Represents the Main Menu
 */
class Menu {
public:
    /**
     * Default Constructor
     */
    Menu();
    /**
     * Constructor
     * @param width
     * @param height
     */
    Menu(double width, double height);

    /**
     * Setup
     */
    void setup();
    /**
     * Draws the menu
     */
    void draw() const;
    /**
     * Updates the menu
     */
    void update();
    /**
     * Resets the menu
     */
    void reset();

    /**
     * Selects the next map
     */
    void nextMap();
    /**
     * Selects the previous map
     */
    void prevMap();
    /**
     * Selects the next song
     */
    void nextSong();
    /**
     * Selects the previous song
     */
    void prevSong();

    /**
     * Getters
     */
    const std::string& song_name() const;
    const std::string& map_name() const;
    const Map getMap() const;
    const ci::audio::VoiceRef getSong() const;
private:
    /**
     * Draws a map selection
     * @param image
     * @param top_left
     * @param dimensions
     * @param draw_name
     * @param draw_title
     * @param name
     * @param title
     */
    void drawMap(const ci::gl::Texture2dRef& image, const glm::vec2& top_left, const glm::vec2& dimensions, bool draw_name, bool draw_title, const std::string& name, const std::string& title) const;
    /**
     * Updates the audio playing
     */
    void updateAudio();

    MapLoader map_loader_;

    std::vector<std::vector<std::string>> song_names_;

    size_t current_map_index_;
    size_t current_song_index_;

    std::string song_name_;
    std::string map_name_;

    Map up_map_;
    ci::gl::Texture2dRef up_image_;
    Map down_map_;
    ci::gl::Texture2dRef down_image_;
    Map current_map_;
    ci::gl::Texture2dRef current_image_;
    Map prev_map_;
    ci::gl::Texture2dRef prev_image_;
    Map next_map_;
    ci::gl::Texture2dRef next_image_;

    ci::audio::VoiceRef song_;

    double width_;
    double height_;
};

} // namespace final_project

#endif //IDEAL_GAS_MENU_H
