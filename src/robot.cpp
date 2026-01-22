#include "project_files/robot.h"
#include "project_files/drive_pid.h"


void robot::update(void){
    Drive_pid.update();
}


void robot::intake(int pos){
    if (pos == 0){
        intake_back.move_velocity(0);
        intake_high.move_velocity(0);
        intake_low.move_velocity(0);
    }
    if (pos == 1){
        descore.set_value(true);    
        intake_back.move_velocity(200);
        intake_high.move_velocity(200);
        intake_low.move_velocity(200);
        if (intake_back.get_actual_velocity() < 10){
            counter2 += 1;
        }
        if (intake_high.get_actual_velocity() < 10){
            counter += 1;
        }
        else
        {
            if(intake_back.get_actual_velocity() > 10){
            counter = 0;
            counter2 = 0;}
            if(intake_high.get_actual_velocity() > 10){counter = 0;}
        }

        if (counter2 > 100)
        {
            intake_back.move_velocity(0);
            intake_high.move_velocity(0);
        }
        if (counter > 100)
        {
            intake_high.move_velocity(0);
        }  
    }
    else
    {
        counter = 0;
        counter2 = 0;
    }
    if (pos == 2){
        descore.set_value(false);   
        intake_back.move_velocity(200);
        intake_high.move_velocity(-200);
        intake_low.move_velocity(200);
    }
    if (pos == 3){
        descore.set_value(false);   
        intake_back.move_velocity(200);
        intake_high.move_velocity(200);
        intake_low.move_velocity(200);
    }
    if (pos == -1){
        descore.set_value(false);
        intake_back.move_velocity(-200);
        intake_high.move_velocity(-200);
        intake_low.move_velocity(-200);
    }
};

void robot::drive(float distance, bool wait, float rotation, bool end){
    distance = distance*360*3/(3.25*M_PI)/48*36;
    Drive_pid.drive(distance, rotation, end, wait);
}

void robot::turn_to(float heading){
    Drive_pid.turn(heading);
}


void robot::init(void){
    inertial_sensor.set_rotation(0);
    Drive_pid.init();
}