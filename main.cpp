#include <iostream>

const float PI = 3.141592653589793238462643;

float degSine(float degree)
{
	return sin(degree * PI / 180);
}

float degCosine(float degree)
{
	return cos(degree * PI / 180);
}

int main()
{
	////Variables
	bool B_smaller_than_90 = false;
	char direction, facingOfST;
	int throw_distance, player_x, player_z, strh_distance, strh_x, strh_z, distToStrh_x, distToStrh_z;
	float A_angle, B_angle, C_angle, A_sine, B_sine, C_sine, B_cosine, angleOfThrow1, angleOfThrow2, tempC;

	//Variables initialising (user input)
	std::cout << "Enter first angle:" << std::endl;
	std::cin >> angleOfThrow1;

	std::cout << "\nEnter direction (L or R):" << std::endl;
	std::cin >> direction;
	if (direction == 'R' || direction == 'L') direction += 32;

	std::cout << "\nEnter distance between throws:" << std::endl;
	std::cin >> throw_distance;

	std::cout << "\nEnter second angle:" << std::endl;
	std::cin >> angleOfThrow2;

	std::cout << "\nEnter X coordinate:" << std::endl;
	std::cin >> player_x;

	std::cout << "\nEnter Z coordinate:" << std::endl;
	std::cin >> player_z;

	////Calculations

	//Angle A
	//If direction == left
	if (direction == 'l') {
		if (angleOfThrow1 >= 90) A_angle = angleOfThrow1 - 90;
		else if (angleOfThrow1 >= 0) A_angle = angleOfThrow1;
		else if (angleOfThrow1 >= -90) A_angle = angleOfThrow1 + 90;
		else if (angleOfThrow1 >= -180) A_angle = angleOfThrow1 + 180;
	}
	//If direction == right
	else if (direction == 'r') {
		if (angleOfThrow1 >= 90) A_angle = 180 - angleOfThrow1;
		else if (angleOfThrow1 >= 0) A_angle = 90 - angleOfThrow1;
		else if (angleOfThrow1 >= -90) A_angle = -angleOfThrow1;
		else if (angleOfThrow1 >= -180) A_angle = -(angleOfThrow1 + 90);
	}


	//Angle C
	tempC = angleOfThrow1 + 180 - (angleOfThrow2 + 180);
	if (tempC < 0) tempC *= -1;
	if (tempC > 180) C_angle = 360 - tempC;
	else C_angle = tempC;

	//Angle B
	B_angle = 180 - A_angle - C_angle;

	std::cout << "\n\033[93m[DEBUG]\033[0m A angle = " << A_angle << std::endl;
	std::cout << "\033[93m[DEBUG]\033[0m B angle = " << B_angle << std::endl;
	std::cout << "\033[93m[DEBUG]\033[0m C angle = " << C_angle << std::endl;

	//Sines of angles A and C
	A_sine = degSine(A_angle);
	C_sine = degSine(C_angle);

	//B_cosine = degCosine(B_angle);

	//Distance to stronghold
	strh_distance = throw_distance * A_sine / C_sine;
	std::cout << "\n\033[32m[SUCCESS]\033[0m Distance to stronghold ~ " << strh_distance << std::endl;

	//Facing of second eye throw
	/*
		-2 => x- z-
		-1 => x- z+
		 1 => x+ z-
		 2 => x+ z+
	*/
	if (angleOfThrow2 >= 0) facingOfST = -1;
	else facingOfST = 2;
	if (angleOfThrow2 > 90 || angleOfThrow2 < -90) facingOfST -= 1;

	//Stronghold coordinates (X and Z)
	if (B_angle >= 90) B_angle = 180 - B_angle;
	else B_smaller_than_90 = true;
	B_sine = degSine(B_angle);
	B_cosine = degCosine(B_angle);

	//If B angle was >= 90
	if (B_smaller_than_90 == false) {
		if (((facingOfST == 2 || facingOfST == -2) && direction == 'r') || ((facingOfST == 1 || facingOfST == -1) && direction == 'l')) {
			distToStrh_x = strh_distance * B_sine;
			distToStrh_z = strh_distance * B_cosine;
		}
		else if (((facingOfST == 2 || facingOfST == -2) && direction == 'l') || ((facingOfST == 1 || facingOfST == -1) && direction == 'r')){
			distToStrh_x = strh_distance * B_cosine;
			distToStrh_z = strh_distance * B_sine;
		}
	}
	//If B angle was < 90
	else {
		if (((facingOfST == 2 || facingOfST == -2) && direction == 'r') || ((facingOfST == 1 || facingOfST == -1) && direction == 'l')) {
			distToStrh_x = strh_distance * B_cosine;
			distToStrh_z = strh_distance * B_sine;
		}
		else if (((facingOfST == 2 || facingOfST == -2) && direction == 'l') || ((facingOfST == 1 || facingOfST == -1) && direction == 'r')) {
			distToStrh_x = strh_distance * B_sine;
			distToStrh_z = strh_distance * B_cosine;
		}
	}

	if (facingOfST == -2 || facingOfST == -1) strh_x = player_x - distToStrh_x;
	else strh_x = player_x + distToStrh_x;

	if (facingOfST == 1 || facingOfST == -2) strh_z = player_z - distToStrh_z;
	else strh_z = player_z + distToStrh_z;

	//Final result
	std::cout << "\033[32m[SUCCESS]\033[0m Stronghold coordinates ~ " << strh_x << " y " << strh_z << "\n\n" << std::endl;
	
	////Pausing program (any input to quit)
	system("pause");
}