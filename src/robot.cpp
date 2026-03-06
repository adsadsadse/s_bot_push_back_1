#include "project_files/robot.h"
#include "project_files/drive_pid.h"


void robot::update(void){
    Drive_pid.update();
    intake(intake_dir);
}


void robot::intake(int pos){
    if (pos == 0){
        //descore.set_value(false);    
        intake_back.move_velocity(0);
        intake_high.move_velocity(0);
        intake_low.move_velocity(0);
    }
    if (pos == 1){
        descore.set_value(true);    
        intake_back.move_velocity(intake_back_vel);
        intake_high.move_velocity(intake_high_vel);
        intake_low.move_velocity(intake_low_vel);
        /*if (intake_back.get_actual_velocity() < 10 && intake_back_vel == 200){
            counter2 += 1;
        }
        if (intake_high.get_actual_velocity() < 10 && intake_high_vel == 200){
            counter += 1;
        }
        else
        {
            if(intake_back.get_actual_velocity() > 10){
            counter = 0;
            counter2 = 0;}
            if(intake_high.get_actual_velocity() > 10){counter = 0;}
        }

        if (counter2 > 100 && intake_back_vel == 200)
        {
            intake_back.move_velocity(0);
            intake_high.move_velocity(0);
        }
        if (counter > 100 && intake_high_vel == 200)
        {
            intake_high.move_velocity(0);
        }  */
    }
    else
    {
        counter = 0;
        counter2 = 0;
    }
    if (pos == 2){
        descore.set_value(false);   
        intake_back.move_velocity(intake_back_vel);
        intake_high.move_velocity(-intake_high_vel);
        intake_low.move_velocity(intake_low_vel);
        /*if ((intake_low.get_actual_velocity() < 10 || intake_back.get_actual_velocity() < 10) && intake_back_vel == 200 && intake_low_vel == 200){
            counter3 += 1;
        }
        else
        {
            counter3 = 0;
        }

        if (counter3 > 15){counter3 = -8;}
        if (counter3 < 0 && intake_back_vel == 200 && intake_low_vel == 200)
        {
            intake_low.move_velocity(-intake_low_vel);
            intake_back.move_velocity(-intake_back_vel);
        }*/
    }
    if (pos == 3){
        descore.set_value(false);   
        intake_back.move_velocity(intake_back_vel);
        intake_high.move_velocity(intake_high_vel);
        intake_low.move_velocity(intake_low_vel);
        if ((intake_low.get_actual_velocity() < 10 || intake_back.get_actual_velocity() < 10) && intake_back_vel == 200 && intake_low_vel == 200){
            counter3 += 1;
        }
        else
        {
            counter3 = 0;
        }

        if (counter3 > 15){counter3 = -8;}
        if (counter3 < 0 && intake_back_vel == 200 && intake_low_vel == 200)
        {
            intake_low.move_velocity(-intake_low_vel);
            intake_back.move_velocity(-intake_back_vel);
        }
    }
    if (pos == -1){
        descore.set_value(false);
        intake_back.move_velocity(-intake_back_vel);
        intake_high.move_velocity(-intake_high_vel);
        intake_low.move_velocity(-intake_low_vel);
    }
};

void robot::drive(float distance, bool wait, float rotation, bool end){
    distance = distance*360*3/(3.25*M_PI)/48*36;
    Drive_pid.drive(distance, rotation, end, wait);
}

void robot::turn_to(float heading, bool time){
    Drive_pid.turn(heading, time);
}


void robot::init(void){
    inertial_sensor.set_rotation(0);
    Drive_pid.init();
}

void robot::auton(int index){
    /*1 = left
	2 = right
	3 = solo awp
	4 = skills
	5 = drive fwd an inch*/

    if (index == 1){//left side
    intake_low_vel = 200;
    intake_back_vel = 200;
    intake_high_vel = 200;

    intake_dir = 1;
	Drive_pid.starting_heading = 333.33;
	Drive_pid.max_volt = 12000;
	drive(21,false);
	Drive_pid.max_volt = 12000;
	pros::delay(900);
	little_will.set_value(true);
	intake_back_vel = 20;
	intake_high_vel = 20;
	Drive_pid.max_volt = 6000;
    drive(-.5, false);
	turn_to(180+45);
	Drive_pid.max_volt = 12000;
	drive(-17*sqrt(2));
    intake_dir = 2;
    intake_low_vel = 200;
    intake_high_vel = 75;
	intake_back_vel = -75;
	pros::delay(200);
	intake_back_vel = (100);
	pros::delay(900);
    intake_dir = -1;
    intake_low_vel = 200;
    intake_back_vel = 200;
    intake_high_vel = 200;
	turn_to(180+85);
    intake_dir = 1;
	drive((36)*sqrt(2), false);
	pros::delay(1000);
    intake_dir = 1;
	turn_to(175);
	drive(25);
	turn_to(160, false);
    pros::delay(100);
	drive(-48, false);
	pros::delay(800);
    intake_dir = 3;
    little_will.set_value(false);
	pros::delay(1500);
	drive(30, false);
    turn_to(120, false);
    pros::delay(1000);
    turn_to(200,false);
    pros::delay(900);
    drive(-40,false);
    

    }
    if (index == 2){//right side

    }
    if (index == 3){//solo awp
	    Drive_pid.starting_heading = 270;
        intake_dir = 1;
        drive(10);
        drive(-56, false);
        pros::delay(1300);
        turn_to(185,false);
        pros::delay(700);
        intake_dir = 1;
        little_will.set_value(true);
        drive(22);
        turn_to(168,false);
        drive(-48, false);
	    pros::delay(700);
        intake_dir = 3;
	    pros::delay(900);
        intake_dir = 1;
    	//drive(30);
        turn_to(360-45,false);
        little_will.set_value(false);
        drive(25,false);
        pros::delay(900);
        drive(18, false);
        turn_to(260);
        little_will.set_value(true);
        drive(10,false);
        pros::delay(750);
        little_will.set_value(false);
        drive(26,false);
        pros::delay(650);
        little_will.set_value(true);
        pros::delay(450);
        turn_to(210);
        drive(-26,false);
        intake_dir = -1;
        pros::delay(500);
        intake_dir = 2;
        intake_back_vel = 100;
        pros::delay(900);
        turn_to(270);
        intake_back_vel = 200;
        intake_dir = 1;
        little_will.set_value(false);
        drive(52,false);
        pros::delay(700);
        little_will.set_value(true);
        turn_to(200,false);
        pros::delay(400);
        drive(22);
        turn_to(195,false);
        drive(-48, false);
	    pros::delay(700);
        intake_dir = 3;


    }
    if (index == 4){//skills
    intake_dir = 1;
	drive(25,false);
    pros::delay(900);
    little_will.set_value(true);
    drive(5,false);
    turn_to(100);
    drive(17.25,false);
    pros::delay(450);
    Drive_pid.max_volt = 3000;
    drive(-9);
    pros::delay(1150);
	Drive_pid.max_volt = 12000;
    drive(-17);
    intake_dir = 0;
    little_will.set_value(false);
    turn_to(-45);
    drive(17);
    turn_to(-87,false);
    drive(10);
    drive(24*3,false);
    pros::delay(1600);
    turn_to(-20,false);
	Drive_pid.max_volt = 6000;
    drive(-15.5);
    turn_to(-90,false);
    drive(-15);
    drive(-30,false);
	Drive_pid.max_volt = 12000;
    pros::delay(300);
    intake_dir = 3;
    little_will.set_value(true);
    pros::delay(1700);
    Drive_pid.forward_pid.target = 0;
    right_1.tare_position();
    left_1.tare_position();
    intake_dir = 1;
	Drive_pid.max_volt = 7000;
    turn_to(-125);
    drive(15,false);
    pros::delay(160);
    turn_to(-85);
    pros::delay(300);
    Drive_pid.max_volt = 5000;
    drive(35, false);
    pros::delay(450);
    Drive_pid.max_volt = 3000;
    drive(-16);
    pros::delay(1050);
    Drive_pid.max_volt = 0;
    pros::delay(750);
	Drive_pid.max_volt = 12000;
    turn_to(-110, false);
	Drive_pid.max_volt = 12000;
    drive(-35, false);
    pros::delay(700);
    turn_to(-80,false);
    pros::delay(700);
    intake_dir = 3;
    pros::delay(2500);    
    Drive_pid.forward_pid.target = 0;
    right_1.tare_position();
    left_1.tare_position();
    intake_dir = 0;
    drive(10, false);
    turn_to(-183, false);
    pros::delay(500);
    drive(10, false);
    pros::delay(1000);
    drive(63,false);
    pros::delay(1700);
    turn_to(-90);
    intake_dir = 1;
    drive(27);
    pros::delay(1500);
    drive(-9);
    pros::delay(1150);
	Drive_pid.max_volt = 12000;
    drive(-13);
    intake_dir = 0;
    little_will.set_value(false);
    turn_to(180-45);
    drive(17);
    turn_to(180-87,false);
    drive(10);
    drive(24*3,false);
    pros::delay(1600);
    turn_to(180-20,false);
	Drive_pid.max_volt = 6000;
    drive(-15.5);
    turn_to(90,false);
    drive(-15);
    drive(-30,false);
	Drive_pid.max_volt = 12000;
    pros::delay(300);
    intake_dir = 3;
    little_will.set_value(true);
    pros::delay(1700);
    Drive_pid.forward_pid.target = 0;
    right_1.tare_position();
    left_1.tare_position();
    intake_dir = 1;
	Drive_pid.max_volt = 7000;
    turn_to(125);
    drive(15,false);
    pros::delay(160);
    turn_to(85);
    pros::delay(300);
    Drive_pid.max_volt = 5000;
    drive(35, false);
    pros::delay(450);
    Drive_pid.max_volt = 3000;
    drive(-16);
    pros::delay(1050);
    Drive_pid.max_volt = 0;
    pros::delay(750);
	Drive_pid.max_volt = 12000;
    turn_to(100, false);
	Drive_pid.max_volt = 12000;
    drive(-35, false);
    pros::delay(800);
    turn_to(80,false);
    pros::delay(700);
    intake_dir = 3;
    drive(30, false);
    pros::delay(300);
    turn_to(0);
    drive(48);
    




    }
    if (index == 5){//drive forward a bit
    drive(10);
    }

}