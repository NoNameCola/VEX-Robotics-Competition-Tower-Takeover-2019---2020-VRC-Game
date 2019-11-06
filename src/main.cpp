#include "main.h"

//define the ports for the motor in the brain
const int left_wheel_front = 1;
const int right_wheel_front = 2;
const int left_wheel_back = 3;
const int right_wheel_back = 4;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(3, "I was pressed!");
	} else {
		pros::lcd::clear_line(3);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::Motor left_wheel_front(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	pros::Motor right_wheel_front(2,MOTOR_GEARSET_18,true,MOTOR_ENCODER_COUNTS);
	pros::Motor left_wheel_back(3,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	pros::Motor right_wheel_back(4,MOTOR_GEARSET_18,true,MOTOR_ENCODER_COUNTS);
	//pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
	/*
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
		*/
		pros::Motor left_wheel_front(1);
		pros::Motor right_wheel_front(2);
		pros::Motor left_wheel_back(3);
		pros::Motor right_wheel_back(4);
		pros::Controller master (pros::E_CONTROLLER_MASTER);
		int power,turn;
		while(true){
			//tank drive code
			/*
			left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
			right_wheels.move(master.gt_analog(ANALOG_RIGHT_Y));
			*/

			//arcade drive code
			power = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y);
			turn = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X);

			left_wheels.move(power + turn);
			right_wheels.move(power - turn);
			// important delay for multitasking of the brain and to avoid abnormailities.
			std::cout << left_wheels.get_voltage()*0.010583 << std::endl;
			pros::delay(10);
		}

	}
