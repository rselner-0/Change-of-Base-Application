//Project12.cpp - Base conversion process walk-through for C++.
//This project is a console application which converts a user-input integer to a different base (also user-specified).
/*This project also times the process by which the program is able to convert the base-10 input number and display it in console,
as well as upload the number value, the base which was used, and the time in microseconds for each run, to an external .csv file.*/

#include <iostream> //Including the module to allow console displayed text and user input.
#include <chrono> //Including the module to allow timing of the processes.
#include <fstream> //Including the module for streaming data to an external file.
using namespace std; //For the functions using the standard namespace.
using namespace std::chrono; //For the functions using the std::chrono namespace.

struct things { //Here is the struct to hold most globally-utilized variables as well as the array to store digit values.
	int number = 0, base = 0, counter = 0; //Integer variables for number, base, and counter are stored here and initialized to 0.
	int tally = 1; //A Global variable which is intended to count the number of times the user has run the program successfully.
	int digit[31]{}; //The digit array is stored here as well, initialized to an empty set.
	bool negative = false; //This boolean value will be true when the user inputs a negative value for the number variable.
}t; //The struct variable here is chosen to be 't', for "things", in quick reference to the struct name.

void input_numbers(things* t), change_base(things* t); //Both functions are prototyped before the main function.

int main() { //The main function begins here.
	ofstream file_stream; //To create and write data to an external file, an output file stream variable is declared here..
	ifstream check_file; //As well as an input file stream. This variable will be used to check whether or not the file exists yet.
	do { // <- start: do...while t.number != 0.
		input_numbers(&t); //The program asks the user to input number and base values.
		if (t.number != 0) { //This portion of the code will not run if t.number = 0.
			check_file.open("time_and_number_values.csv"); //Opening the file using input stream..
			if (!check_file.good()) { //This conditional statement checks whether or not the .csv file has been made.
				check_file.close(); //If it hasn't been made yet, it closes the input stream and...
				file_stream.open("time_and_number_values.csv"); //Creates the file..
				file_stream << "number,base,(seconds)*10^-6" << endl; //Then writes the header information to it..
				file_stream.close(); //And finally closes the output file stream.
				cout << "\n      ~File Being Made Now~" << endl;
			}
			else { check_file.close(); } //If the file exists already, the input file stream closes.
			
			file_stream.open("time_and_number_values.csv", ios::app); //Opening the output file stream to append information.
			cout << "\n======================================\n "; //This starts the display formatting for the console app.
			//These "if...else" statements will input the value of the number that had been given by the user, to the .csv file.
			if (t.negative == true) { cout << t.number * -1 << " = "; file_stream << t.number * -1 << ","; } //If negative..
			else { cout << t.number << " = "; file_stream << t.number << ","; } //Otherwise..
			if (t.negative == true) { cout << " - "; } //Here, a negative sign is displayed on the console if the flag is turned on.
			auto start = high_resolution_clock::now(); //Clock Starts Now
			change_base(&t); //The change_base function takes the input values of number and base and creates an array of digits.
			for (int i = t.counter; i > -1; i--) { cout << " " << t.digit[i]; } //Printing out the new digits..
			auto stop = high_resolution_clock::now(); //Clock Stops Now
			auto duration = duration_cast<microseconds>(stop - start); //The length of time it takes is recorded in microseconds.
			file_stream << t.base << ","; //The base number is added to the .csv file, and a comma to shift the cursor is included.
			file_stream << duration.count() << endl; //The time in microseconds is uploaded to the .csv file, and the cursor moves down.
			file_stream.close(); //Closing the output file stream.
			cout << endl << "\n Base " << t.base; //The base value is displayed again..
			cout << endl << "\n Number of digits: " << t.counter + 1 << endl; //The number of digits used in this base is shown.
			//A display that the value of the number variable is either positive or negative.
			if (t.negative == true) { cout << "\n *NEGATIVE VALUE*\n"; } //If negative.
			else { cout << "\n *POSITIVE VALUE*\n"; }  //Otherwise..

			int time = duration.count(); //The time duration in microseconds is stored inside an integer-type variable.
			int us = 0; //The microseconds variable is declared and initialized to 0.
			if (time > 999) { //This conditional "if" statement runs if the time variable is 1000 or more.
				if (time > 999999) { //This inner conditional "if" statement runs if the time variable is 1000000 or more.
					int s = (time - time % 1000000) / 1000000; //The seconds variable is created here, only when needed.
					cout << "\n Completed in " << s; //If the program takes 1 second or more, the following is displayed.
					if (s > 1) { cout << " seconds, "; } //For multiple seconds..
					else { cout << " second, "; } //For one second..
					time -= s * 1000000; //The time variable is updated to continue on with conversion to milliseconds.
				}
				else { cout << "\n Completed in "; } //If the time variable was not 1000000 or greater, this message displays.
				int ms = (time - time % 1000) / 1000; //The milliseconds variable is created here, only when needed.
				if (ms > 1) { cout << ms << " milliseconds, "; } //For multiple milliseconds..
				else { cout << ms << " millisecond, "; } //For one millisecond..
				us = time - ms * 1000; //The microseconds variable is now being set with the remainder.
			}
			else { cout << "\n Completed in "; //If the time variable was not 1000 or greater, the following message will display.
				us = time; //And the microseconds variable will be set with what is given.
			}
			cout << us << " microseconds." << endl; //The length of time to convert it is displayed.
			cout << "======================================\n"; //This ends the display for the looping portion of the console app.
			if (t.tally == 1) {
				cout << "\n ~Program has run: " << t.tally << " time~\n" << endl;
			} //The tally count (of one time) is displayed here.
			else if (t.tally > 1) {
				cout << "\n ~Program has run: " << t.tally << " times~\n" << endl;
			} //The tally count > 1 is displayed here.
			t.tally++; //The tally is incremented here.
			t.negative = false; //The boolean flag needs to be reset to false, otherwise it will remain on until the program terminates.
		} // <- end: if (t.number) != 0)
	} while (t.number != 0); //If the user inputs 0 as the number, the loop will end and the program will continue from here.
	cout << "\n\t Total Runs: " << t.tally - 1 << endl;
	cout << "\n     Thank You For Your Time!\n\t     ~ RMS ~\nTime: " << __TIME__ << "\nDate: " << __DATE__ << "\n"; //Print time and date.
	return 10; //The main function ends here, returning the value of 10: the decimal base we are all so familiar with.
}

//The fuction to get input number and base values from the user is defined below.
void input_numbers(things* t) {
	double n = 0, b = 0; //Temporary variables are used to hold values which may not be integer-type (containing decimal values).
	do {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n         Enter 0 to quit\n\t       or\n";
		cout << "         Enter an integer\n      with an absolute value\n\t    from 1 to\n";
		cout << "    2,147,483,647 (2 ^ 31 - 1)\n\n      -> number = ";
		cin >> n; //User enters the value for the number variable.
		if (n < 0) { //If the number is negative, a flag is turned on and the value is made positive.
			t->negative = true; //The flag is a boolean value within the struct "things".
			n *= -1;
		}
		//If the value is an integer, it is placed directly into the struct variable.
		if (n - floor(n) == 0) { t->number = static_cast<int>(n); }
		else if (n - floor(n) != 0) { cout << "\n      ~!Whole Numbers Only!~\n     ~!Losing Nonsense Data!~" << endl;
		//If the user inputs a non-integer value, the message will display and the value will be truncated.
			t->number = static_cast<int>(floor(n)); //The truncated value is placed into the struct variable.
		}
		//The program will repeat the prompt if the user inputs a number value greater than the limiting value.
	} while (t->number > 2147483647); //The limiting value is 2^31 - 1, since 31 is the max # of digits.
	if (t->number != 0) { //If the input value is not 0, the program will continue to ask for the base number input.
		do {
			cout << "\n   Now Enter the base to convert\n   ";  //Asking the user to input base value..
			if (t->negative == false) { cout << t->number; } //If positive..
			else { cout << t->number * -1; } //Otherwise..
			cout << " to (except for base 1)\n\n\t-> base = ";
			cin >> b; //User inputs value into a variable that can hold non-integer type values.
			//If the value is an integer, it is placed directly into the struct variable.
			if (b < 0) { //If the value is negative, a message is displayed and the absolute value is taken.
				cout << "\n      ~!Erroneous Negative!~\n     ~!Taking Absolute Value!~" << endl;
				b *= -1;
			}
			if (b - floor(b) == 0) { t->base = static_cast<int>(b); }
			else { cout << "\n      ~!Whole Numbers Only!~\n     ~!Losing Nonsense Data!~" << endl;
			//If the user inputs a non-integer value, the message will display and the value will be truncated.
				t->base = static_cast<int>(floor(b)); //The truncated value is placed into the struct variable.
			}
		} while (t->base < 2); //The program will repeat the prompt if the user inputs a base number less than 2.
	}
}

//The function to change bases from decimal to whichever base was defined be the user is defined below.
void change_base(things* t) {
	t->counter = 0; //The counter is initialized to 0, since the program repeats and a refresher statement is needed.
	int temp = t->number; //The number value from the struct is stored inside a temp variable.
	if (temp > (t->base - 1)) { //If the temp variable is larger than one less than the base, this code will run.
		while (temp > (t->base - 1)) { //This "while" loop will run until the temp variable is less than or equal b - 1.
			t->digit[t->counter] = temp % t->base; //The digit for the current place is stored in the struct array..
			temp -= t->digit[t->counter]; //The temp value is decreased by the value of the digit..
			temp /= t->base; //The temp value is divided by the base value..
			t->counter++; //The counter increments here, ensuring that each digit is stored in its rightful place.
		}
	}
	t->digit[t->counter] = temp; //The final (or only) digit is then stored in the array.
}