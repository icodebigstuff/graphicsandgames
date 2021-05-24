/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef BALL_H_
#define BALL_H_

#include <mingfx.h>

/// Small data structure for a ball
class Ball {
public:
    
    /// The constructor sets the radius and calls Reset() to start the ball at
    /// the center of the field
    Ball() : radius_(2.6f) {
        Reset();
    }
    
    /// Nothing special needed in the constructor
    virtual ~Ball() {}

    
    void Reset() {
        position_ = Point3(0, radius_, 0);
        accelerate_ = Vector3(0, rand() % 10 + 1, 0);
        velocity_ = Vector3(rand() % 40-20, rand() % 10, rand() % 20); //random initial velocities


    }

    float radius() { return radius_; }
    
    Point3 position() { return position_; }
    void set_position(const Point3 &p) { position_ = p; }
    
    void set_velocity(Vector3 v) { velocity_ =v;}
    Vector3 get_velocity() { return velocity_; }

    void move(double time) { position_ = (velocity_ * time) + position_;  }

    void decrease_speed() { velocity_ = velocity_ * 0.9; };
    void gravity(double time) {
        if (velocity_.y() != 0) {
            velocity_ = velocity_  + (time * Vector3(0,-15,0)); //15 set to acceleration from gravity
        }
    }
    float get_rad() { return radius_; }
    Point3 get_pos() { return position_; }
    float get_posx() { return position_.x(); }
    float get_posy() { return position_.y(); }
    float get_posz() { return position_.z(); }
    float get_velx() { return velocity_[0]; }
    float get_vely() { return velocity_[1]; }
    float get_velz() { return velocity_[2]; }

    float dot(Vector3 two) {
        float val = velocity_[0] * two[0] + velocity_[1] * two[1] + velocity_[2] * two[2];
        return val;
    }


private:
    // You will probably need to store some additional data here, e.g., velocity
    Vector3 velocity_;
    Point3 position_;
    float radius_;
    Vector3 accelerate_;

};

#endif
