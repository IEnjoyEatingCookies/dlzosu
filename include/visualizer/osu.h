#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/game.h"
#include "IO/global_configurations.h"

#include <chrono>

namespace final_project {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class Osu : public ci::app::App {
public:
    /**
    * Default Constructor
    */
    Osu();

    /**
    * Draws the current frame
    */
    void draw() override;
    /**
    * Initial setup
    */
    void setup() override;
    /**
    * Updates the current frame
    */
    void update() override;


    void shutdown();

    /**
    * Input Event Methods
    */
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseUp(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyUp(ci::app::KeyEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;

    /**
    * Runs once on initial click
    * @param event
    */
    void click(ci::app::MouseEvent event);
    /**
    * Runs once on mouse release
    * @param event
    */
    void release(ci::app::MouseEvent event);

private:
    Game game_;

    bool clicked_ = false;
    bool released_ = false;
    bool r_mouse_held_ = false;
    bool l_mouse_held_ = false;
    std::set<int> held_keys_;
    std::set<int> clicked_keys_;
};

}  // namespace visualizer

}  // namespace final_project
