#ifndef OSU_SPINNER_H
#define OSU_SPINNER_H

#include "cinder/gl/gl.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a spinner
 */
class Spinner {
public:
    /**
     * Default Constructor
     */
    Spinner();
    /**
     * Constructor
     * @param approach_rate
     * @param start_time
     * @param end_time
     */
    Spinner(long approach_rate, long start_time, long end_time);

    /**
     * Resets the Spinner
     */
    void reset();
    /**
     * Draws the Spinner
     * @param time
     */
    void draw(long time) const;

    /**
     * Spins the Spinner
     * @param amount
     */
    void spin(double amount);

    /**
     * Returns whether the spinner is displayed on the screen
     * @param time
     * @return bool
     */
    bool inRange(long time) const;

    /**
     * Returns the score
     * @return size_t score
     */
    size_t getScore() const;

    /**
     * Returns whether the time is after the spin window of the spinner
     * @param time
     * @return bool
     */
    bool isAfter(long time) const;
    /**
     * Returns whether the spinner has been spun enough
     * @return bool
     */
    bool isMiss() const;
private:
    /**
     * Plays a hit sound
     */
    void playHitSounds();
    /**
     * Draws a marker
     * @param time
     * @param start
     * @param color
     */
    void drawMarker(long time, long start, ci::Color color) const;

    double approach_rate_;
    double rotation_;
    double spins_;
    long start_time_;
    long end_time_;
};

}

#endif //OSU_SPINNER_H
