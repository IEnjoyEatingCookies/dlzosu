#ifndef OSU_MAP_H
#define OSU_MAP_H

#include "core/circle.h"
#include "core/spinner.h"
#include "core/input.h"

namespace final_project {
enum Hitsound {
    kNormal,
    kSoft,
    kDrum
};

/**
 * Represents an osu map
 */
class Map {
public:
    /**
     * Default Constructor
     */
    Map();

    /**
     * Constructor
     * @param song_name
     */
    Map(std::string& song_name);

    /**
     * Draws the map
     * @param time
     */
    void draw(long time) const;
    /**
     * Updates the map
     * @param current_input
     */
    void update(InputPoint* current_input);

    /**
     * Returns true if map has ended
     * @return bool
     */
    bool isEnd(long time) const;

    /**
     * Returns the current accuracy
     * @return double accuracy
     */
    double getAccuracy() const;

    /**
     * Returns the current percentage of the map completed
     * @param time
     * @return double
     */
    double getPlayPercent(long time) const;

    /**
     * Resets the map
     */
    void reset();

    /**
     * Returns the score with leading zeroes
     * @return std::string
     */
    std::string getFormatedScore() const;

    /**
     * Returns the accuracy
     * @return std::string
     */
    std::string getFormatedAccuracy() const;

    /**
     * Returns the rating
     * @return std::string
     */
    std::string getRating() const;

    /**
     * Getters/Setters
     */
    size_t getCombo() const;
    size_t getMaxCombo() const;
    size_t getScore() const;
    size_t getHitMisses() const;
    size_t getHit50s() const;
    size_t getHit100s() const;
    size_t getHit300s() const;

    const std::string& getSongFileName() const;
    const std::string& getAudioFilename() const;
    const std::string& getBackgroundFilename() const;
    const std::string& getVersion() const;
    const std::string& getTitle() const;
    const std::string& getArtist() const;

    void start();
    bool isPlayed() const;

    /**
     * Operator Overloading
     */
    friend std::istream& operator>>(std::istream& in, Map& map);
private:
    /**
     * Sets variables based on argument
     * @param args
     */
    void setArgument(const std::pair<std::string, std::string>& args);
    /**
     * Creates a combo
     * @param colors
     */
    void readCombo(const std::string colors);
    /**
     * Separates a line into args (key:value pair)
     * @param string
     * @return std::pair<std::string, std::string>
     */
    std::pair<std::string, std::string> getArguments(const std::string& string);
    /**
     * Setup for difficulty values
     */
    void calculateValues();
    /**
     * Reads a hit object line
     * @param line
     */
    void readHitObject(const std::string& line);

    /*
     * Gameplay Methods
     */
    /**
      * Returns true if input is a click
      * @return bool
      */
    bool hasClicked() const;
    /**
     * Updates click variables
     * @param last_input
     */
    void updateClicks(InputPoint* last_input);

    /*
     * Circle Detection Methods
     */
    /**
     * Returns true if the input point is hitting a circle
     * @param input_point
     * @param circle
     * @return bool
     */
    bool hitCircle(InputPoint* input_point, Circle* circle) const;

    /*
     * Spinner Detection Methods
     */
    /**
     * Calculates the direction of a spin
     * @param p1
     * @param p2
     * @return bool true if clockwise, false if counterclockwise
     */
    bool calculateDirection(const glm::vec2& p1, const glm::vec2& p2) const;
    /**
     * Calculates the amount of spin
     * @param p1
     * @param p2
     * @return double radians
     */
    double calculateSpin(const glm::vec2& p1, const glm::vec2& p2) const;
    /**
     * Returns true if the input points are spinning a spinner
     * @param prev_input
     * @param current_input
     * @return bool
     */
    bool spinSpinner(InputPoint* prev_input, InputPoint* current_input);

    std::string song_name_;

    std::vector<ci::Color> combo_colors_;
    std::vector<Circle*> circles_;
    std::vector<Spinner*> spinners_;

    size_t circle_index_;
    size_t spinner_index_;

    size_t score_;
    size_t combo_;
    size_t max_combo_;
    size_t hit_misses_;
    size_t hit_50s_;
    size_t hit_100s_;
    size_t hit_300s_;

    // [General]
    std::string audio_filename_;
    std::string background_filename_;

    long audio_lead_in_;
    long preview_time_;
    Hitsound sample_set_;
    float stack_leniency_;

    // [Metadata]
    std::string title_;
    std::string artist_;
    std::string version_;

    // [Difficulty]
    float hp_drain_rate_;
    float circle_size_;
    float overall_difficulty_;
    float approach_rate_;
    float slider_multiplier_;
    float slider_tick_rate_;

    // play values
    float radius_;
    long true_approach_rate;

    // game
    long map_length_;
    InputPoint* prev_input_;
    bool first_input_;
    bool key_one_ = false;
    bool key_one_click_ = false;
    bool key_two_ = false;
    bool key_two_click_ = false;
    bool r_mouse_ = false;
    bool r_mouse_click_ = false;
    bool l_mouse_ = false;
    bool l_mouse_click_ = false;
    bool played_;
};

} // namespace final_project



#endif //IDEAL_GAS_MAP_H
