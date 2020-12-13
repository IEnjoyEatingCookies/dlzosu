#include "visualizer/menu.h"

namespace final_project {
Menu::Menu() {

}

Menu::Menu(double width, double height) {
    width_ = width;
    height_ = height;
    current_map_index_ = 0;
    current_song_index_ = 0;
    setup();
}

void Menu::setup() {
    map_loader_ = MapLoader();
    song_names_ = map_loader_.getSongList();
    update();
    updateAudio();
}

void Menu::reset() {
    asset_loader.reload();
    map_loader_.reload();
    song_names_ = map_loader_.getSongList();
    current_map_index_ = 0;
    current_song_index_ = 0;
    update();
    updateAudio();
}

void Menu::draw() const {
    // check for songs
    if (song_names_.empty()) {
        ci::gl::drawStringCentered("No Available Maps", glm::vec2(width_ / 2, height_ / 2));
    } else { // draw current songs
        /*
         * Consider the layout
         *             Up
         * Prev  <<  Current   >>  Next
         *            Down
         */
        if (current_song_index_ > 0) { // prev
            glm::vec2 top_left(width_ / 4 - kMapWidth / 2, height_ / 2 - kMapHeight / 2);
            glm::vec2 dim(kMapWidth, kMapHeight);
            drawMap(prev_image_, top_left, dim, false, true, "", prev_map_.getTitle());
        }

        if (current_map_index_ > 0) { // up
            glm::vec2 top_left(width_ / 2 - kMapWidth / 2, height_ / 6 - kMapHeight / 2);
            glm::vec2 dim(kMapWidth, kMapHeight);
            drawMap(up_image_, top_left, dim, true, false, up_map_.getVersion(), "");
        }

        // current
        glm::vec2 top_left(width_ / 2 - kMapWidth * kSelectedMult / 2, height_ / 2 - kMapHeight * kSelectedMult / 2);
        glm::vec2 dim(kMapWidth * kSelectedMult, kMapHeight * kSelectedMult);
        drawMap(current_image_, top_left, dim, true, true, current_map_.getVersion(), current_map_.getTitle());

        if (current_map_index_ < song_names_.at(current_song_index_).size() - 2) { // down
            glm::vec2 top_left(width_ / 2 - kMapWidth / 2, height_ * 5 / 6 - kMapHeight / 2);
            glm::vec2 dim(kMapWidth, kMapHeight);
            drawMap(down_image_, top_left, dim, true, false, down_map_.getVersion(), "");
        }

        if (current_song_index_ < song_names_.size() - 1) { // next
            glm::vec2 top_left(width_ * 3 / 4 - kMapWidth / 2, height_ / 2 - kMapHeight / 2);
            glm::vec2 dim(kMapWidth, kMapHeight);
            drawMap(next_image_, top_left, dim, false, true, "", next_map_.getTitle());
        }
    }
}

void Menu::drawMap(const ci::gl::Texture2dRef &image, const glm::vec2 &top_left, const glm::vec2 &dimensions,
                   bool draw_name, bool draw_title, const std::string &name, const std::string &title) const {
    ci::gl::pushModelMatrix();
    ci::gl::translate(top_left);
    ci::gl::scale(dimensions.x / image->getWidth(), dimensions.y / image->getHeight());
    // image
    ci::gl::color(1, 1, 1);
    ci::gl::draw(image);
    ci::gl::popModelMatrix();

    ci::Font font("arial", 30);
    if (draw_title) { // title
        glm::vec2 title_c1(0, dimensions.y / 2 - kTitleHeight / 2);
        glm::vec2 title_c2(dimensions.x, dimensions.y / 2 + kTitleHeight / 2);
        ci::Rectf title_box(top_left + title_c1, top_left + title_c2);
        ci::gl::color(0, 0, 0);
        ci::gl::drawSolidRect(title_box);
        ci::gl::drawStringCentered(title, top_left + glm::vec2(dimensions.x / 2, dimensions.y / 2 - 14), ci::Color(1, 1, 1), font);
    }
    if (draw_name) { // version name
        ci::gl::drawStringCentered(name, top_left + glm::vec2(dimensions.x / 2, dimensions.y + 20), ci::Color(1, 1, 1), font);
    }
}


void Menu::update() {
    if (!song_names_.empty()) {
        if (current_song_index_ > 0) { // previous song
            prev_map_ = map_loader_.requestMap(current_song_index_ - 1, 0);
            prev_image_ = asset_loader.requestImage(current_song_index_ - 1, prev_map_.getBackgroundFilename());
        }
        // current map chosen
        if (song_names_.at(current_song_index_).size() > 1) {
            // up map
            if (current_map_index_ > 0) {
                up_map_ = map_loader_.requestMap(current_song_index_, current_map_index_ - 1);
                up_image_ = asset_loader.requestImage(current_song_index_, up_map_.getBackgroundFilename());
            }
            // current map
            song_name_ = song_names_.at(current_song_index_).at(0);
            map_name_ = song_names_.at(current_song_index_).at(current_map_index_ + 1);
            current_map_ = map_loader_.requestMap(song_name_, map_name_);
            current_image_ = asset_loader.requestImage(song_name_, current_map_.getBackgroundFilename());

            // down map
            if (current_map_index_ < song_names_.at(current_song_index_).size() - 2) {
                down_map_ = map_loader_.requestMap(current_song_index_, current_map_index_ + 1);
                down_image_ = asset_loader.requestImage(current_song_index_, down_map_.getBackgroundFilename());
            }
        }
        // next song
        if (current_song_index_ < song_names_.size() - 1) {
            next_map_ = map_loader_.requestMap(current_song_index_ + 1, 0);
            next_image_ = asset_loader.requestImage(current_song_index_ + 1, next_map_.getBackgroundFilename());
        }
    }
}

void Menu::updateAudio() {
    if (!song_names_.empty()) {
        song_ = asset_loader.requestAudio(song_name_, current_map_.getAudioFilename());
        song_->setVolume(kSongVolume);
        song_->start();
    }
}

void Menu::prevMap() {
    if (current_map_index_ > 0) {
        --current_map_index_;
    }
    update();
    if (!song_->isPlaying()){
        song_->start();
    }
}

void Menu::nextMap() {
    if (current_map_index_ < song_names_.at(current_song_index_).size() - 2) {
        ++current_map_index_;
    }
    update();
    if (!song_->isPlaying()){
        song_->start();
    }
}

void Menu::prevSong() {
    if (current_song_index_ > 0) {
        --current_song_index_;
        current_map_index_ = 0;
    }
    if (song_->isPlaying()) {
        song_->stop();
    }
    update();
    updateAudio();
}

void Menu::nextSong() {
    if (current_song_index_ < song_names_.size() - 1) {
        ++current_song_index_;
        current_map_index_ = 0;
    }
    if (song_->isPlaying()) {
        song_->stop();
    }
    update();
    updateAudio();
}

const std::string& Menu::map_name() const {
    return map_name_;
}

const std::string& Menu::song_name() const {
    return song_name_;
}

const Map Menu::getMap() const {
    return current_map_;
}

const ci::audio::VoiceRef Menu::getSong() const {
    return song_;
}

} // namespace final_project