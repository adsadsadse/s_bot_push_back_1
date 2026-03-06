#ifndef ROBOT_H
#define ROBOT_H
#include "PID.h"
#include "api.h"
#include "drive_pid.h"

class robot{
    public:

    void init(void);

    //6 motor drive configuration
    pros::v5::Motor right_1{6};
    pros::v5::Motor right_2{5};
    pros::v5::Motor right_3{-4};
    pros::v5::Motor left_1{3};
    pros::v5::Motor left_2{-2};
    pros::v5::Motor left_3{-1};

    pros::v5::IMU inertial_sensor{19};

    //pros::v5::Optical color_sort{4};

    drive_pid Drive_pid{right_1, right_2, 
                        right_3,  
                        left_1, left_2,
                        left_3, 
                        inertial_sensor};
    
    void drive(float distance, bool wait = true, float rotation = (0.0F), bool end = true);
    void turn_to(float heading, bool time = true);
    int intake_dir = 0;
    void intake(int pos);
    pros::v5::Motor intake_high{-8}; 
    pros::v5::Motor intake_back{12}; 
    pros::v5::Motor intake_low{10}; 

    pros::adi::DigitalOut little_will{'g'};
    pros::adi::DigitalOut descore{'h'};

    void update(void);

    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;

    int intake_low_vel = 200;
    int intake_back_vel = 200;
    int intake_high_vel = 200;

    void auton(int index);

};



#endif