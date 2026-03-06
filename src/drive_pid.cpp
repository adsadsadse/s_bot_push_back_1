#include "project_files/drive_pid.h"
#include "cmath"
float drive_pid::fl(float x, float curve_midpoint, float accel_jerk, float max_speed, float k){
    if (!(0 > x)&&(x<curve_midpoint)){return accel_jerk*x*x;}
    else /*((curve_midpoint <= x) && (x < 2*curve_midpoint))*/{return -accel_jerk*(x-k)*(x-k)+max_speed;}
    //else {return max_speed;}
}

float drive_pid::gl(float x, int k1, float curve_midpoint, float accel_jerk, float max_speed, float k){
    if (fl(x,curve_midpoint,accel_jerk, max_speed, k)>fl(2*k1-x,curve_midpoint,accel_jerk, max_speed, k)){return fl(2*k1-x,curve_midpoint,accel_jerk, max_speed, k);}
    else{return fl(x,curve_midpoint,accel_jerk, max_speed, k);}
}

void drive_pid::init(void){
    forward_pid.init();
}

void drive_pid::drive(float distance, float rotation, bool end, bool wait){
    //turn(rotation);

    // https://www.desmos.com/calculator/iqyqgdfwuz
    // https://www.desmos.com/calculator/t7hxzqvzc9
    float distance_to_travel = distance;

    float curve_midpoint = sqrt(fd_max_speed/(2*fd_accel_jerk));
    float k = curve_midpoint + sqrt(-(curve_midpoint*curve_midpoint)+fd_max_speed/fd_accel_jerk);

    float k2 = 0;
    int k1 = 0;

    while (k2<distance_to_travel/2)
    {
        k2 += fl(k1,curve_midpoint,fd_accel_jerk,fd_max_speed, k);
        k1 += 1;
    }

    if (abs(k2-fl(k1-1,curve_midpoint,fd_accel_jerk,fd_max_speed, k))<abs(k2)){k1 -= 1;}
    
    int n = 1;
    //while (n < 2*k1){forward_pid.target += gl(n, k1,curve_midpoint,fd_accel_jerk,fd_max_speed, k); n+= 1;}
    
    /*while (std::abs(forward_pid.sensor-distance) > 100)
    {
        pros::delay(10);
    }*/
   forward_pid.target += distance;
   if (wait){
    pros::delay((std::abs(distance)+100)*0.75);}

}

void drive_pid::turn(float rotation, bool time){

    /*float distance_to_travel = rotation;

    float curve_midpoint = sqrt(turn_max_speed/(2*turn_accel_jerk));
    float k = curve_midpoint + sqrt(-(curve_midpoint*curve_midpoint)+turn_max_speed/turn_accel_jerk);

    float k2 = 0;
    int k1 = 0;

    while (k2<distance_to_travel/2)
    {
        k2 += fl(k1,curve_midpoint,turn_accel_jerk,turn_max_speed, k);
        k1 += 1;
    }

    if (abs(k2-fl(k1-1,curve_midpoint,turn_accel_jerk,turn_max_speed, k))<abs(k2)){k1 -= 1;}
    
    int n = 1;
    while (n < 2*k1){turn_pid.target += gl(n, k1,curve_midpoint,turn_accel_jerk,turn_max_speed, k); n+= 1;}
    */ 
    rotation -= starting_heading;
    turn_pid.target = rotation;
    //while (std::abs(turn_pid.sensor-rotation) > 5 /*&& !COMPETITION_DISABLED*/)
    /*{
        pros::delay(10);
    }*/
   if (time){
    pros::delay(std::abs(rotation - turn_pid.sensor)*10+60);
   }
    

}
void drive_pid::update(void){
    const float wheel_size = 3.25*M_PI;

    float forward_voltage = forward_pid.return_voltage((((left_1.get_position()+right_1.get_position())))/*2)*wheel_size*360)*/);
    float turn_voltage = turn_pid.return_voltage(inertial_sensor.get_rotation());

    if (forward_voltage > max_volt){ forward_voltage = max_volt;}
    if (forward_voltage < -max_volt){ forward_voltage = -max_volt;}

    // x drive motor configuration
    right_1.move_voltage(forward_voltage  - turn_voltage);
    right_2.move_voltage((forward_voltage - turn_voltage));
    left_1.move_voltage(forward_voltage + turn_voltage);
    left_2.move_voltage((forward_voltage + turn_voltage));
    left_3.move_voltage((forward_voltage + turn_voltage));
    right_3.move_voltage(forward_voltage - turn_voltage);
}