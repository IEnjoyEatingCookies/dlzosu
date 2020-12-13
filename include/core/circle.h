#ifndef IDEAL_GAS_CIRCLE_H
#define IDEAL_GAS_CIRCLE_H

#include "cinder/gl/gl.h"
#include "IO/global_configurations.h"

namespace final_project {

/**
 * Represents a Circle
 */
class Circle {
public:
    /**
     * Default Constructor
     */
    Circle();
    /**
     * Constructor
     * @param position
     * @param time
     * @param radius
     * @param approach_rate
     * @param overall_difficulty
     * @param color
     */
    Circle(glm::vec2 position, long time, float radius, int approach_rate, float overall_difficulty, const ci::Color& color);

    /**
     * Resets the circle
     */
    void reset();
    /**
     * Draws the Circle
     * @param time
     */
    void draw(long time) const;
    /**
     * Returns whether the circle is displayed on the screen
     * @param time
     * @return bool
     */
    bool inRange(long time) const;
    /**
     * Returns whether the time is after the hit window of the circle
     * @param time
     * @return bool
     */
    bool isAfter(long time) const;
    /**
     * Returns whether the circle has been assigned a hit
     * @param time
     * @return bool
     */
    bool isHit(long time) const;
    /**
     * Returns whether the hit on the circle is a miss
     * @return bool
     */
    bool isMiss() const;

    /**
     * Getters/Setters
     */
    const glm::vec2& getPosition() const;
    float getRadius() const;
    size_t getScore() const;
    bool correctHit() const;
    void hit(long time);
private:
    /**
     * Sets the hit window according to difficulty
     * @param overall_difficulty
     */
    void setHitWindow(float overall_difficulty);
    /**
     * Draws the approach circle
     * @param time
     */
    void drawApproachCircle(long time) const;
    /**
     * Draws the actual circle
     * @param time
     */
    void drawCircle(long time) const;
    /**
     * Draws hit markers
     * @param time
     * @param start
     * @param color
     */
    void drawMarker(long time, long start, const ci::Color& color) const;
    /**
     * Draws the circle when its hit
     * @param time
     */
    void drawHit(long time) const;
    /**
     * Plays a hitsound
     */
    void playHitSound() const;

    long hit_;
    glm::vec2 position_;
    long time_;
    int approach_rate_;
    long hit_window_early_;
    long hit_window_50_;
    long hit_window_100_;
    long hit_window_300_;
    float radius_;
    float outer_radius_;
    ci::Color color_;
};

} // namespace final_project

#endif //IDEAL_GAS_CIRCLE_H
