#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
robot Robot{};
 void initialize() {
	Robot.inertial_sensor.reset();
	delay(3000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void run_pid(){
	int c = 0;
	while (true)
	{
		c+= 1;
		Robot.update();
		pros::delay(10);
		if (c > 1500){break;}
	}
	
}
int color = 0;
bool flipper_out = 1;
void color_sorter(){
	/*int counter = -1;
	Robot.color_sort.set_led_pwm(25);
	while (true){
		int c = Robot.color_sort.get_hue();
	if (color == 1 && (c < 20)){
		if (!flipper_out){
			flipper_out = 1;
		}
		counter = 25;

	}
	else if (color == 2 &&(c < 225) && (c > 205)){
		if (!flipper_out){
			flipper_out = 1;
		}
		counter = 25;
	}
	counter -= 1;
	pros::delay(2);
	}
	if (counter == 0){flipper_out = 0;}*/
}

void autonomous() {
	Task drive{run_pid};
	Robot.intake(1);
	//Robot.intake_high.move_velocity(50);
	
	Robot.Drive_pid.starting_heading = 333.33;
	//Robot.Drive_pid.turn_pid.target = 333.33;
	Robot.Drive_pid.max_volt = 12000;
	Robot.drive(21,false);
	Robot.Drive_pid.max_volt = 12000;
	pros::delay(600);
	Robot.little_will.set_value(true);
	Robot.intake_back.move_velocity(10);
	Robot.intake_high.move_velocity(10);
	Robot.drive(9);
	pros::delay(300);
	Robot.turn_to(180+38);
	pros::delay(650);
	Robot.Drive_pid.max_volt = 12000;
	Robot.drive(-14.5*sqrt(2));
	Robot.intake(2);
	Robot.intake_high.move_velocity(-100);
	Robot.intake_back.move_velocity(-75);
	pros::delay(250);
	Robot.intake_back.move_velocity(200);
	pros::delay(700);
	Robot.intake(1);
	Robot.drive((39.5)*sqrt(2), false);
	pros::delay(1000);
	Robot.turn_to(175);
	Robot.drive(23);
	Robot.drive(-50, false);
	pros::delay(1000);
	Robot.intake(3);
	pros::delay(3000);
	Robot.drive(10);
	//Task color_sorting_task{color_sorter};
	//color_sorting_task.join();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller controller{E_CONTROLLER_MASTER};
	bool toggle_intake_check = false;
	bool toggle_descore_check = false;
	bool toggle_match_load_check = false;
	bool match_load = false;
	bool descore_active = true;	
	int intake_dir = 0;
	Task color_sorting_task{color_sorter};
	while (true) {		
		float ld = float(controller.get_analog(ANALOG_LEFT_Y))/127.0f; // Gets amount forward/backward from left joystick
		float rd = float(controller.get_analog(ANALOG_RIGHT_Y))/127.0f;
		ld = ld*std::abs(ld)*200.0f;
		rd = rd*std::abs(rd)*200.0f;


		/*if (controller.get_digital(DIGITAL_DOWN)){
			color = 1;
			controller.print(2,0,"NO RED ");
		}
		if (controller.get_digital(DIGITAL_UP)){
			color = 2;
			controller.print(2,0,"NO BLUE");
		}*/

		if ((controller.get_digital(DIGITAL_L2)||
			controller.get_digital(DIGITAL_R2))|| 
			(controller.get_digital(DIGITAL_L1)||
			controller.get_digital(DIGITAL_R1))){
			if (!toggle_intake_check){
				if (!(intake_dir == 0)){
					intake_dir = 0;
				}
				else if (controller.get_digital(DIGITAL_R1)){
					intake_dir = 1;
				}
				else if (controller.get_digital(DIGITAL_L2)){
					intake_dir = -1;
				}
				else if (controller.get_digital(DIGITAL_R2)){
					intake_dir = 2;
				}
				else if (controller.get_digital(DIGITAL_L1)){
			flipper_out = 0;	
					intake_dir = 3;
				}
			}
			toggle_intake_check = true;
		}
		else{toggle_intake_check = false;}
		
		if (controller.get_digital(DIGITAL_X)){
			if (!toggle_descore_check){
				descore_active = !descore_active;
			}
			toggle_descore_check = true;
		}
		else{toggle_descore_check = false;}

		if (controller.get_digital(DIGITAL_A)){
			if (!toggle_match_load_check){
				match_load = !match_load;
			}
			toggle_match_load_check = true;
		}
		else{toggle_match_load_check = false;}

		Robot.left_1.move_velocity(ld);
		Robot.left_2.move_velocity(ld);
		Robot.left_3.move_velocity(ld);
		Robot.right_1.move_velocity(rd);
		Robot.right_2.move_velocity(rd);
		Robot.right_3.move_velocity(rd);

		Robot.intake(intake_dir);


		Robot.little_will.set_value(match_load);
		Robot.descore.set_value(descore_active);


		pros::delay(20); // Run for 20 ms then update
	}
}