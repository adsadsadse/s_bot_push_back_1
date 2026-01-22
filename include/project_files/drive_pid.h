#ifndef DRIVE_PID
#define DRIVE_PID
#include "api.h"
#include "PID.h"

class drive_pid{
    public:
    drive_pid(pros::v5::Motor & right1, pros::v5::Motor & right2,
              pros::v5::Motor & right3,
              pros::v5::Motor & left1, pros::v5::Motor & left2,
              pros::v5::Motor & left3,
              pros::v5::IMU & inertial):
    right_1{right1},
    right_2{right2},
    right_3{right3},
    left_1{left1},
    left_2{left2},
    left_3{left3},
    inertial_sensor{inertial}
    {}

    pros::v5::Motor & right_1;
    pros::v5::Motor & right_2;
    pros::v5::Motor & right_3;
    pros::v5::Motor & left_1;
    pros::v5::Motor & left_2;
    pros::v5::Motor & left_3;
    
    pros::v5::IMU & inertial_sensor;

    float drive_kp = 4;
    float drive_kd = 0;
    float drive_ki = 0;
    float drive_integral_threshold = 0;

    float turn_kp = 60;
    float turn_kd = -20;
    float turn_ki = 0;
    float turn_integral_threshold = 0;

    pid forward_pid{drive_kp, drive_kd, drive_ki, drive_integral_threshold};
    pid turn_pid{turn_kp, turn_kd, turn_ki, turn_integral_threshold};

    const float fd_accel_jerk = .0000000000250f;
    const float turn_accel_jerk = 1.0f;

    int max_volt = 12000;

    const float fd_max_speed = (950*sqrt(2)*3.25)/(3*60*100);
    const float turn_max_speed = 36;

    float fl(float x, float curve_midpoint, float accel_jerk, float max_speed, float k);
    float gl(float x, int k1, float curve_midpoint, float accel_jerk, float max_speed, float k);

    int time_counter = 0;

    void init(void);

    float starting_heading = 0;
    void turn(float rotation);
    void drive(float distance, float rotation = 0, bool end = true, bool wait = true);

    void update(void);

};


#endif