// rgrewalassignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<stdio.h>
#include<math.h>
float AreaOfTriangle(int, int, int);
float AreaOfTriangle(int a, int b, int c) {
    float semiParameter = (a + b + c) / 2;
    float minusa = semiParameter - a;
    float minusb = semiParameter - b;
    float minusc = semiParameter - c;

    float area = semiParameter * minusa * minusb * minusc;
    if (area < 0) {
        return 0;
    }
    area = sqrt(area);
    return area;
}
int main()
{
    int a, b, c;
    float area;
    printf("Please Enter the sides of the triangle\n");
    scanf_s("%d %d %d", &a, &b, &c);
    area = AreaOfTriangle(a, b, c);
    if (area <= 0) {
        printf("Values can not form a triangle\n");
        return 0;
    }
    printf("The area of Triangle is %.2f", area);
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
