/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef CAR_H_
#define CAR_H_

#include <mingfx.h>

/// Small data structure for a car
class Car {
public:
    
    /// The constructor sets the static properties of the car, like its size,
    /// and then calls Reset() to reset the position, velocity, and any other
    /// dynamic variables that change during game play.
    Car() : size_(3,2,4), collision_radius_(2.5) {
        Reset();
    }

    /// Nothing special needed in the constructor
    virtual ~Car() {}

    /// Resets all the dynamic variables, so if you call this after a goal, the
    /// car will go back to its starting position.
    void Reset() {
        position_ = Point3(0, size_[1]/2, 45);
        velocity_ = Vector3(10, 0, 10);
        speed_ = 50.0;
        angle_ = 30.0;
        
    }
    float get_posx() { return position_.x(); }
    float get_posy() { return position_.y(); }
    float get_posz() { return position_.z(); }
    
    float collision_radius() { return collision_radius_; }
    
    Vector3 size() { return size_; }

    void set_speed(float spe) {
        speed_ = spe;
    }

    float get_speed() {
        return speed_;
    }
    float dot(Vector3 two) {
        float val = velocity_[0] * two[0] + velocity_[1] * two[1] + velocity_[2] * two[2];
        return val;
    }
    void move(double time) { position_ = (velocity_ * time) + position_; }
    Vector3 get_velocity() { return velocity_; }
    void set_velocity(Vector3 i) { velocity_ = i; }

    Point3 position() { return position_; }
    void set_position(const Point3 &p) { position_ = p; }

    float get_velx() { return velocity_[0]; }
    float get_vely() { return velocity_[1]; }
    float get_velz() { return velocity_[2]; }
    void left() {
       velocity_ = velocity_.Cross(Vector3(0, -1,0));

    }
    void speed_up() { velocity_ = velocity_ * 1.2; };
    void slow_down() { velocity_ = velocity_ * 0.5; }

    void right() { velocity_ = velocity_.Cross(Vector3(0, 1, 0)); }
    void set_angle(float val) { angle_ = val; }
    float get_angle() { return angle_; }
    
private:
    // You will probably need to store some additional data here, e.g., speed.
    
    Vector3 size_;
    float speed_;
    float thrust_;
    float angle_;
    float drag_;
    Vector3 velocity_;
    float turn_rate_;
    float collision_radius_;
    Point3 position_;
    bool turn_left_;
    bool turn_right_;
    bool forward_;
    bool backwards_;

};

#endif
