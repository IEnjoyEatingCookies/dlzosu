#include "visualizer/game.h"

namespace final_project {

Game::Game() {

}

void Game::setup(int window_width, int window_height) {
    hud_ = Hud(window_width, window_height);
    end_screen_ = EndScreen(window_width, window_height);
    menu_ = Menu(window_width, window_height);
    menu_.setup();
    cursor_ = Cursor();

    screen_ = Screen::kMenu;

    resolution_ = glm::vec2(window_width, window_height);
    osu_pixel_scale_ = resolution_.y / kOsuPixelResolution.y; // scale based on height
    double playfield_x = (resolution_.x - kPlayfieldResolution.x * osu_pixel_scale_) / 2;
    double playfield_y = resolution_.y * (kOsuPixelResolution.y - kPlayfieldResolution.y) / kOsuPixelResolution.y / 2;
    playfield_origin_ = glm::vec2(playfield_x, playfield_y);
}

void Game::start_map() {
    begin_ = getTime() + kSongStartBuffer;
}

void Game::draw() const {
    ci::Color8u background_color(0, 0, 0);  // black
    ci::gl::clear(background_color);

    // display based on the current screen
    if (screen_ == Screen::kGame) {
        long time = getTime() - begin_;

        // translate osu!pixels to screen dimensions
        ci::gl::pushModelMatrix();
        ci::gl::translate(playfield_origin_);
        ci::gl::scale((float) osu_pixel_scale_, (float) osu_pixel_scale_);
        map_.draw(time);
        cursor_.draw(input_.getInputs(kCursorTrailPoints));
        ci::gl::popModelMatrix();

        // hud is pure
        hud_.draw(time);
    } else if (screen_ == Screen::kMenu) {
        menu_.draw();
    } else if (screen_ == Screen::kEnd) {
        end_screen_.draw();
    }
}

void Game::update(const glm::vec2& mouse_position, const std::set<int>& held_keys, const std::set<int>& clicked_keys, bool r_mouse_held, bool l_mouse_held) {
    if (screen_ == Screen::kGame) {
        long time = getTime() - begin_;

        if (!map_.isPlayed() && time >= 0) {
            song_->start();
            begin_ += time;
            map_.start();
        }

        if (map_.isEnd(time)) {
            end_screen_.update(map_);
            screen_ = Screen::kEnd;
        }

        // change mouse_position to osu!pixels
        glm::vec2 mouse_osu_position = (mouse_position - playfield_origin_) / osu_pixel_scale_;
        InputPoint* current_input = input_.update(time, mouse_osu_position, held_keys, r_mouse_held, l_mouse_held);
        map_.update(current_input);
        hud_.update(map_);
    } else if (screen_ == Screen::kMenu) {

    }
    keyInput(held_keys, clicked_keys);
}

void Game::keyInput(const std::set<int> &held_keys, const std::set<int>& clicked_keys) {
    if (held_keys.find(kKeyReturn) != held_keys.end()) {
        if (song_->isPlaying()) {
            song_->stop();
        }
        menu_.reset();
        screen_ = Screen::kMenu;
    }
    if (screen_ == Screen::kMenu) {
        if (clicked_keys.find(kKeyReload) != clicked_keys.end()) {
            menu_.reset();
        }
        if (clicked_keys.find(kKeyPrevMap) != clicked_keys.end()) {
            menu_.prevMap();
        }
        if (clicked_keys.find(kKeyPrevSong) != clicked_keys.end()) {
            menu_.prevSong();
        }
        if (clicked_keys.find(kKeyNextMap) != clicked_keys.end()) {
            menu_.nextMap();
        }
        if (clicked_keys.find(kKeyNextSong) != clicked_keys.end()) {
            menu_.nextSong();
        }
        if (held_keys.find(kKeyPlaySong) != held_keys.end()) {
            map_ = menu_.getMap();
            map_.reset();
            song_ = menu_.getSong();
            if (song_->isPlaying()) {
                song_->stop();
            }
            screen_ = Screen::kGame;
            start_map();
        }
    }
}


long Game::getTime() const {
    return (long) (std::chrono::system_clock::now().time_since_epoch().count() / 10000);
}
}