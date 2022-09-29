#define _USE_MATH_DEFINES
#include <math.h> 
#include <tuple>

using namespace std;

std::tuple<double, double> angles(double height, double distance) {
    double arm1 = 20.0;
    double arm2 = 15.0;

    double a1tanIn = height / distance;
    double armH = height * height + distance * distance;
    double a1cosIn = (arm1*arm1 - arm2 * arm2 + armH) / (2 * arm1 * sqrt(armH));
    double angle1 = atan(a1tanIn) + acos(a1cosIn);
    double a2cosIn = (arm1 * arm1 + arm2 * arm2 -armH) / (2 * arm1 * arm2);
    double angle2 = acos(a2cosIn) - M_PI;

    return {angle1, angle2};
}

double angleToSteps(double angle, int perRevolution) {
    double steps = angle * perRevolution / (2 * M_PI);
    return steps;
}


double distance = place[0];
double height = place[1];

double currentAngles = angles(height, distance);
double angle1 = angleToSteps(currentAngles[0], 2000);
double angle2 = angleToSteps(currentAngles[1], 200);