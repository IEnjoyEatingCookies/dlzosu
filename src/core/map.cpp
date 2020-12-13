#include "core/map.h"

namespace final_project {
Map::Map() {
    reset();
}

Map::Map(std::string& song_name) {
    song_name_ = song_name;
    reset();
}

void Map::reset() {
    score_ = 0;
    combo_ = 0;
    max_combo_ = 0;
    hit_misses_ = 0;
    hit_50s_ = 0;
    hit_100s_ = 0;
    hit_300s_ = 0;
    circle_index_ = 0;
    spinner_index_ = 0;
    first_input_ = true;
    played_ = false;

    for (Circle* circle : circles_) {
        circle->reset();
    }
    for (Spinner* spinner : spinners_) {
        spinner->reset();
    }
}

void Map::draw(long time) const {
    for (Circle* circle : circles_) {
        circle->draw(time);
    }
    for (Spinner* spinner : spinners_) {
        spinner->draw(time);
    }
}

void Map::updateClicks(InputPoint *last_input) {
    key_one_click_ = false;
    key_two_click_ = false;
    r_mouse_click_ = false;
    l_mouse_click_ = false;
    if (!key_one_ && last_input->keyOnePressed()) {
        key_one_click_ = true;
    }
    if (!key_two_ && last_input->keyTwoPressed()) {
        key_two_click_ = true;
    }
    if (!r_mouse_ && last_input->rMousePressed()) {
        r_mouse_click_ = true;
    }
    if (!l_mouse_ && last_input->lMousePressed()) {
        l_mouse_click_ = true;
    }
    key_one_ = last_input->keyOnePressed();
    key_two_ = last_input->keyTwoPressed();
    r_mouse_ = last_input->rMousePressed();
    l_mouse_ = last_input->lMousePressed();
}

const std::string & Map::getAudioFilename() const {
    return audio_filename_;
}

const std::string & Map::getBackgroundFilename() const {
    return background_filename_;
}

const std::string & Map::getVersion() const {
    return version_;
}

const std::string & Map::getTitle() const {
    return title_;
}

std::string Map::getFormatedScore() const {
    std::string score = std::to_string(score_);
    return std::string(kScoreLength - score.length(), '0') + score;
}

size_t Map::getMaxCombo() const {
    return max_combo_;
}

bool Map::isPlayed() const {
    return played_;
}

const std::string & Map::getSongFileName() const {
    return song_name_;
}

const std::string & Map::getArtist() const {
    return artist_;
}

void Map::start() {
    played_ = true;
}

bool Map::hasClicked() const {
    return key_one_click_ || key_two_click_ || r_mouse_click_ || l_mouse_click_;
}

void Map::update(InputPoint* current_input) {
    long time = current_input->getTime();
    if (first_input_) {
        prev_input_ = current_input;
        first_input_ = false;
    }
    while (circle_index_ < circles_.size() && (circles_.at(circle_index_)->isHit(time) || circles_.at(circle_index_)->isAfter(time))) {
        if(circles_.at(circle_index_)->isMiss()) {
            combo_ = 0;
            ++hit_misses_;
        } else {
            ++combo_;
            max_combo_ = std::max(max_combo_, combo_);
            size_t score = circles_.at(circle_index_)->getScore();
            if (score == 50) {
                ++hit_50s_;
            } else if (score == 100) {
                ++hit_100s_;
            } else if (score == 300) {
                ++hit_300s_;
            }
            score_ += combo_ * score;
        }
        ++circle_index_;
    }
    while (spinner_index_ < spinners_.size() && spinners_.at(spinner_index_)->isAfter(time)) {
        if(spinners_.at(spinner_index_)->isMiss()) {
            combo_ = 0;
        } else {
            ++combo_;
            max_combo_ = std::max(max_combo_, combo_);
            score_ += spinners_.at(spinner_index_)->getScore();
        }
        ++spinner_index_;
    }

    updateClicks(current_input);
    if (circle_index_ < circles_.size() && hitCircle(current_input, circles_.at(circle_index_))) {
        circles_.at(circle_index_)->hit(current_input->getTime());
    }

    if (spinner_index_ < spinners_.size() && spinners_.at(spinner_index_)->inRange(time) && spinSpinner(prev_input_, current_input)) {
        spinners_.at(spinner_index_)->spin(calculateSpin(prev_input_->getPosition(), current_input->getPosition()));
    }
    prev_input_ = current_input;
}

bool Map::hitCircle(InputPoint *input_point, Circle *circle) const {
    return hasClicked() && glm::length(input_point->getPosition() - circle->getPosition()) <= circle->getRadius();
}

bool Map::calculateDirection(const glm::vec2& p1, const glm::vec2& p2) const {
    return p1.x * (p1.y - p2.y) + p1.y * (p2.x - p1.x) >= 0;
}

double Map::calculateSpin(const glm::vec2& p1, const glm::vec2& p2) const {
    glm::vec2 current_prime = p1 - (kPlayfieldResolution / 2.0f);
    glm::vec2 prev_prime = p2 - (kPlayfieldResolution / 2.0f);
    double dot = (double) (glm::dot(current_prime, prev_prime)) /
            (glm::length(current_prime) * glm::length(prev_prime));
    if (dot > 1) {
        dot =  1;
    } else if (dot < -1) {
        dot = -1;
    }
    if (calculateDirection(prev_prime, current_prime)) {
        return std::acos(dot);
    } else {
        return -std::acos(dot);
    }
}

double Map::getPlayPercent(long time) const {
    return 100 * (double) time / map_length_;
}

size_t Map::getHitMisses() const {
    return hit_misses_;
}

size_t Map::getHit50s() const {
    return hit_50s_;
}

size_t Map::getHit100s() const {
    return hit_100s_;
}

size_t Map::getHit300s() const {
    return hit_300s_;
}

double Map::getAccuracy() const {
    if (hit_300s_ + hit_100s_ + hit_50s_ + hit_misses_ == 0) {
        return 100;
    }
    return 100 * ((double) hit_300s_ + (double) hit_100s_ / 3 + (double) hit_50s_ / 6) / (hit_300s_ + hit_100s_ + hit_50s_ + hit_misses_);
}

std::string Map::getRating() const {
    double accuracy = getAccuracy();
    if (hit_misses_ == 0) {
        if (hit_50s_ == 0 && hit_100s_ == 0) {
            return "X";
        } else if (accuracy >= 93) {
            return "S";
        } else if (accuracy >= 85) {
            return "A";
        } else if (accuracy >= 80) {
            return "B";
        } else if (accuracy >= 70) {
            return "C";
        } else {
            return "D";
        }
    } else {
        if (accuracy >= 90) {
            return "A";
        } else if (accuracy >= 80) {
            return "B";
        } else if (accuracy >= 70) {
            return "C";
        } else {
            return "D";
        }
    }
}

std::string Map::getFormatedAccuracy() const {
    int value = (int) getAccuracy();
    int decimal = (int) (getAccuracy() * 100) - value * 100;
    return std::to_string(value) + "." + std::to_string(decimal);
}

bool Map::spinSpinner(InputPoint *prev_input, InputPoint *current_input) {
    return prev_input->isPressed() && current_input->isPressed();
}

std::pair<std::string, std::string> Map::getArguments(const std::string& string) {
    size_t colon = string.find(':');
    if (colon == std::string::npos) {
        throw std::out_of_range("Not an argument");
    }
    std::string key = string.substr(0, colon);
    std::string value;
    if (colon == string.size() - 1) {
        value = "";
    } else {
        value = string.substr(colon + 1);
    }
    value = string.substr(colon);
    std::pair<std::string, std::string> args(key, value);
    return args;
}

void Map::setArgument(const std::pair<std::string, std::string>& args) {
    std::string key = args.first;
    std::string val = args.second;

    // [General]
    if (key == "AudioFilename") {
        audio_filename_ = val.substr(2);
    } else if (key == "AudioLeadIn") {
        audio_lead_in_ = std::stoi(val.substr(2));
    } else if (key == "PreviewTime") {
        preview_time_ = std::stoi(val.substr(2));
    } else if (key == "SampleSet") {
        if (val == " Soft") {
            sample_set_ = Hitsound::kSoft;
        } else if (val == " Drum") {
            sample_set_ = Hitsound::kDrum;
        } else {
            sample_set_ = Hitsound::kNormal;
        }
    } else if (key == "StackLeniency") {
        stack_leniency_ = std::stof(val.substr(1));
    } else if (key == "BackgroundFileName") {
        background_filename_ = val.substr(2);
    }
    // [Metadata]
    else if (key == "Title") {
        title_ = val.substr(1);
    } else if (key == "Artist") {
        artist_ = val.substr(1);
    } else if (key == "Version") {
        version_ = val.substr(1);
    }
    // [Difficulty]
    else if (key == "HPDrainRate") {
        hp_drain_rate_ = std::stof(val.substr(1));
    } else if (key == "CircleSize") {
        circle_size_ = std::stof(val.substr(1));
    } else if (key == "OverallDifficulty") {
        overall_difficulty_ = std::stof(val.substr(1));
    } else if (key == "ApproachRate") {
        approach_rate_ = std::stof(val.substr(1));
    } else if (key == "SliderMultiplier") {
        slider_multiplier_ = std::stof(val.substr(1));
    } else if (key == "SliderTickRate") {
        slider_tick_rate_ = std::stof(val.substr(1));
    }
    // [Colours]
    else if (key.substr(0, 5) == "Combo") {
        readCombo(val.substr(2));
    }
}

void Map::readCombo(std::string colors) {
    size_t comma1 = colors.find(',');
    size_t comma2 = colors.rfind(',');

    int r = std::stoi(colors.substr(0, comma1));
    int g = std::stoi(colors.substr(comma1 + 1, comma2 - comma1 - 1));
    int b = std::stoi(colors.substr(comma2 + 1));

    combo_colors_.push_back(ci::Color((float) r / 255, (float) g / 255, (float) b / 255));
}

void Map::calculateValues() {
    radius_ = (109 - 9 * circle_size_) / 2;

    /*  Approach rate chart:
        AR11 – 300ms (+150)
        AR10 – 450ms (+150)
        AR9 – 600ms (+150)
        AR8 – 750ms (+150)
        AR7 – 900ms (+150)
        AR6 – 1050ms (+150)
        AR5 – 1200ms (+150)
        AR4 – 1320ms (+120)
        AR3 – 1440ms (+120)
        AR2 – 1560ms (+120)
        AR1 – 1680ms (+120)
        AR0 – 1800ms (+120)
     */
    if (approach_rate_ <= 5) {
        true_approach_rate = (long) (1800 - 120 * approach_rate_);
    } else {
        true_approach_rate = (long) (1200 - 150 * (approach_rate_ - 5));
    }
}

bool Map::isEnd(long time) const {
    return time >= map_length_;
}

void Map::readHitObject(const std::string &line) {
    std::vector<std::string> hit_object = delimit(line);

    size_t type = std::stoi(hit_object.at(3));
    // type is a bitwise representation
    if (type >= 128) { // osu mania (useless)
        type -= 128;
    }

    size_t combo_skip = 0;
    if (type >= 64) {
        type -= 64;
        combo_skip += 4;
    }
    if (type >= 32) {
        type -= 32;
        combo_skip += 2;
    }
    if (type >= 16) {
        type -= 16;
        combo_skip += 1;
    }

    bool spinner = false;
    if (type >= 8) {
        type -= 8;
        spinner = true;
    }

    bool new_combo = false;
    if (type >= 4) {
        type -= 4;
        new_combo = true;
    }

    bool slider = false;
    if (type >= 2) {
        type -= 2;
        slider = true;
    }

    bool circle = false;
    if (type >= 1) {
        circle = true;
    }

    glm::vec2 position(std::stoi(hit_object.at(0)), std::stoi(hit_object.at(1)));
    long time = std::stol(hit_object.at(2));

    if (new_combo) {
        if (combo_ == combo_colors_.size() - 1) {
            combo_ = 0;
        } else {
            ++combo_;
        }
    }

    if (spinner) {
        long end_time = std::stol(hit_object.at(5));
        Spinner* spinner = new Spinner(kSpinnerApproachRate, time, end_time);
        spinners_.push_back(spinner);
        map_length_ = std::max(map_length_, end_time + kSongEnd);
    }

    if (circle) {
        Circle* circle = new Circle(position, time, radius_, true_approach_rate, 5, combo_colors_[combo_]);
        circles_.push_back(circle);
        map_length_ = std::max(map_length_, time + kSongEnd);
    }

    if (slider) {
        Circle* circle = new Circle(position, time, radius_, true_approach_rate, 5, combo_colors_[combo_]);
        circles_.push_back(circle);
        map_length_ = std::max(map_length_, time + kSongEnd);
    }
}

std::istream& operator>>(std::istream& in, Map& map) {
    std::string line;
    std::getline(in, line);

    if (line != "osu file format v14") {
        throw std::invalid_argument("Not the right file format (osu file format v14)");
    }

    while (line != "[Events]") {
        std::getline(in, line);
        if (!line.empty() && line[0] != '[') {
            std::pair<std::string, std::string> args = map.getArguments(line);
            map.setArgument(args);
        }
    }

    map.calculateValues();

    // skip to timing points
    while (line != "[TimingPoints]") {
        if (line.substr(0, 4) == "0,0,") { // background
            std::pair<std::string, std::string> args("BackgroundFileName",line.substr(3, line.rfind('"') - 3));
            map.setArgument(args);
        }
        std::getline(in, line);
    }

    while (line != "[Colours]") { // skip to colors
        std::getline(in, line);
    }

    while (line != "[HitObjects]") {
        if (!line.empty() && line[0] != '[') {
            std::pair<std::string, std::string> args = map.getArguments(line);
            map.setArgument(args);
        }
        std::getline(in, line);
    }

    while (std::getline(in, line)) {
        if (!line.empty()) {
            map.readHitObject(line);
        }
    }

    return in;
}

size_t Map::getScore() const {
    return score_;
}

size_t Map::getCombo() const {
    return combo_;
}

}