#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

#include <time.h>

using namespace std;

void InputIntoArray(int(&input)[4][4], ifstream &infile); //function reads values from text file and places them into array
//N.B. infile needs to be passed by reference as fstream objects are not copyable

void PrintNumbers(const int(&input)[4][4]); // function that prints all the numbers in the array

void MainShift(int(&input)[4][4]); // This function will have the shift and add Num together to complete teh shifting
void AddNum(int(&input)[4][4], int n, int i); // This will be adding the numbers
void Shift(int(&input)[4][4], int i, int  n); //this will be shifting the numbers left/right

void CopyArray(const int(&input)[4][4], int(&copy)[4][4]); // copies array
void RotateS(int(&input)[4][4]); //Shift S
void RotateW(int(&input)[4][4]); //Shifts w
void RotateD(int(&input)[4][4]); //Shifts D

void Direction(int(&input)[4][4], string Direction); //Determines which rotate to call (wasd)

int CheckArrayChanged(int(&input)[4][4], int(&copy)[4][4]); // Check if array has changed

int EndCase(int (&input)[4][4]); //pass by value as we do not want to save the changed values
int CheckZero(int(&input)[4][4]);// check if array contains a zero


void Rand2(int(&input)[4][4]); //Randomly generate



int main() {
	int Changed = 0; //This is the value that will determine if the code has changed
	string wasd; //string to determine the input direction
	int exit = 1; //if exit 
	int found; //determines if array has changed

	// we will do this using a 2 dimensional 4x4 array

	int input[4][4]{}; //set all elements to 0
	int inputCopy[4][4]{};

	//Check if elements in array matchces

   //First we need to open the file, and ask the user for the file name

   string FileName;
   cout << "Please input file name" << endl;
   cin >> FileName;

//setup reading from text file
	ifstream infile;
	infile.open(FileName.c_str());

	//if cant open then set array 
	if (!infile.is_open()) {
		cout << "File not found, using default starting configuration " << endl; // need to modify
		input[3][3] = 2;

	}

	//now we need to output the contents of the file if we can find the file
	else
	{
		InputIntoArray(input, infile);
	}
	// now we need to read from the file the set of integers


	//print the array
	PrintNumbers(input);

	//now we need to shift the values right, left up and down
	//we will need 2 functions, shifting right and left will be the same function	


	cout << "Please input shifts now " << endl;
	//shift right test



	
	do {
		
		CopyArray(input, inputCopy); //Copy input into inputcopy

		exit = EndCase(inputCopy); // if there is zero exit = 1 , no zero means there are no zeroes and we should exit
		if (exit == 0) {
			found = 0;
			cout << " " << endl;
			cout << "End Game" << endl;
			wasd = "end";
		}
		cin >> wasd; //input values


		CopyArray(input, inputCopy); //Copy again to ensure no changes occur
		//Check which direction
		Direction(input, wasd); //we have to do check if anything has shifted, if nothing shifted we have to not output anything

		found = CheckArrayChanged(input, inputCopy); //found 1 means array has changed
		
		if (found == 1) {
			Rand2(input);
			// now we need to randomize and add 2 -use function ra
				//Rand2(input);
			PrintNumbers(input);
		}



	} while (!(wasd == "end"));


	return 0;
}


void InputIntoArray(int(&input)[4][4], ifstream &infile) {
	//this function will take the read from the file the values and place them into the array

	for (int i = 0; i < 4; i++) //read the values from text file
		for (int j = 0; j < 4; j++)
			infile >> input[i][j];

}

void PrintNumbers(const int(&input)[4][4]) { // print numbers from array, using const and pass by reference to save memory and ensure no changes are made to arrray
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << input[i][j] << "   \t";

		}
		cout << endl;
	}


}


void MainShift(int(&input)[4][4]) { //This function will shift the array left or right 


	 //shift left


	for (int i = 0; i < 4; i++) {//i is the column
		for (int n = 0; n < 3; n++) { //n is the variable, starting from right/left

			AddNum(input, n, i);


		}

		for (int n = 0; n < 3; n++) { //shift direct
			Shift(input, i, n);
		}



	}





}


void Rand2(int(&input)[4][4]) {
	//this function will randomly generate a 2 in the array
	int randNumi, randNumj = 0;
	bool found = false;
	srand(time(NULL));//initialize random seed

	do {
		randNumi = rand() % 4;
		randNumj = rand() % 4;

		if (input[randNumi][randNumj] == 0) {
			input[randNumi][randNumj] = 2;
			found = true;

		}

	} while (found == !true);



}

void AddNum(int(&input)[4][4], int n, int i) { // this function will combine the values if they are equal
	for (int z = 1; z < 4 - n; z++) {
		if (!(input[i][n + z] == 0)) {
			if (input[i][n] == input[i][n + z]) {
				//if the value does not match move on to next value in array 
				//if value matches add number , and replace original by 0

				input[i][n] = input[i][n] + input[i][n + z];
				input[i][n + z] = 0;
				z = 4;
			}
			else
			{
				z = 4; //z=4 exit condition
			}
		}


	}
}



void Shift(int(&input)[4][4], int i, int  n) { //k is the offset for D, p is the offset for S

	int temp = 0;

	int found = 0;
	int k = 0;

	//n is starting position
	do {

		if (input[i][n + k] == 0) { //find position where item is 0 (k) for 0th position

			k++;
		}

		else
		{
			found = 1;
			temp = k;
			k = 4;
			//need to exit loop if all 0 
		} // if does not equal 0




	} while (!(found == 1) && (n + k < 4));



	if (!(temp == 0)) { // if not checking first term with itself

		if (found == 1) {
			input[i][n] = input[i][n + temp]; // if found = true  
			input[i][n + temp] = 0;

		}
	}
	//reset variables
	found = 0;
	temp = 0;
	k = 0;


}


void CopyArray(const int(&input)[4][4], int(&copy)[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy[i][j] = input[i][j];
		}
	}
}

void RotateS(int(&input)[4][4]) {
	int copy[4][4];

	CopyArray(input, copy); //copy input into copy

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy[i][j] = input[3 - j][i]; //rotate array
		}
	}

	MainShift(copy); //perform shifts on copy of array


	CopyArray(copy, input); //copy copy into input (this is the shifted version is S form


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			input[3 - j][i] = copy[i][j]; // rotate array back
		}
	}

}
void RotateW(int(&input)[4][4]) {
	int copy[4][4];

	CopyArray(input, copy); //copy input into copy

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy[i][j] = input[j][i]; //rotate array
		}
	}

	MainShift(copy); //perform shifts on copy of array


	CopyArray(copy, input); //copy copy into input (this is the shifted version is S form


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			input[j][i] = copy[i][j]; // rotate array back
		}
	}
}

void RotateD(int(&input)[4][4]) {
	int copy[4][4];

	CopyArray(input, copy); //copy input into copy

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy[i][j] = input[i][3 - j]; //rotate array
		}
	}

	MainShift(copy); //perform shifts on copy of array


	CopyArray(copy, input); //copy copy into input (this is the shifted version is S form


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			input[i][3 - j] = copy[i][j]; // rotate array back
		}
	}
}
void Direction(int(&input)[4][4], string Direction) {

	if (Direction == "a") {
		MainShift(input);
	}
	else if (Direction == "d") {

		RotateD(input);
	}
	else if (Direction == "w") {
		RotateW(input);
	}
	else if (Direction == "s") {
		RotateS(input);
	}
}

int CheckArrayChanged(int(&input)[4][4], int(&copy)[4][4]) {
	int found = 0; //this is to check if array has changed
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!(input[i][j] == copy[i][j])) {
				found = 1;
				i = 4;
				j = 4;
			}


		}
	}
	return found;
}

int CheckZero(int(&input)[4][4]) {
	int exit = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((input[i][j] == 0)) {
				exit = 1; //set exit to 1
				i = 4;
				j = 4; //set i and j to exit loop

			}
		}
	}
	return exit;
}

int EndCase(int (&input) [4][4]) {
	//Check if elements are non zero
	int exit = 0;
	exit = CheckZero(input); // if there is zero exit = 1
	
	if (!(exit == 1)) {
		
		MainShift(input);
		RotateD(input);
		RotateS(input);
		RotateW(input);

		exit = CheckZero(input); // if there is zero exit = 1
	}
	return exit; 
}
