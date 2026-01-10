#ifndef ROBOT_H
#define ROBOT_H
#include "PID.h"
#include "api.h"
#include "drive_pid.h"

class robot{
    public:

    void init(void);

    //6 motor drive configuration
    pros::v5::Motor right_1{18};
    pros::v5::Motor right_2{-14};
    pros::v5::Motor right_3{19};
    pros::v5::Motor left_1{11};
    pros::v5::Motor left_2{-12};
    pros::v5::Motor left_3{-13};

    pros::v5::IMU inertial_sensor{14};

    //pros::v5::Optical color_sort{4};

    drive_pid Drive_pid{right_1, right_2, 
                        right_3,  
                        left_1, left_2,
                        left_3, 
                        inertial_sensor};
    
    void drive(float distance, float rotation = (0.0F), bool end = true);
    void turn_to(float heading);
    void intake(int pos);
    pros::v5::Motor intake_high{15}; 
    pros::v5::Motor intake_back{-16}; 
    pros::v5::Motor intake_low{17}; 

    pros::adi::DigitalOut little_will{'c'};
    pros::adi::DigitalOut descore{'b'};

    void update(void);

    int counter = 0;
    int counter2 = 0;


};



#endif