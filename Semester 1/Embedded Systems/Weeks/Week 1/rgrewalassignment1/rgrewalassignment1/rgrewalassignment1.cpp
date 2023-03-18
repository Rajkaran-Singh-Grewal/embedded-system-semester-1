// rgrewalassignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
float celsiusToFarhenheit(int);
float celsiusToKelvin(int);
float celsiusToFarhenheit(int celsius) {
	float temperature = (float)celsius * 9 / 5;
	temperature = temperature +32;
	return(temperature);
}
float celsiusToKelvin(int celsius) {
	float temperature = (float)celsius + 273.15;
	return(temperature);
}
int main()
{
	int celsius;
	float farhenheit;
	float kelvin;
	printf("Enter the current temperature in Celsius\n");
	scanf_s("%d", &celsius);
	farhenheit = celsiusToFarhenheit(celsius);
	kelvin = celsiusToKelvin(celsius);
	printf("The temperature in Celsius is %d C\n", celsius);
	printf("The temperature in Farhenheit is %.2f F\n", farhenheit);
	printf("The temperature in Kelvin is %.2f K\n", kelvin);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
