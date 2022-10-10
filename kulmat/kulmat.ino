#define _USE_MATH_DEFINES
#include <math.h> 

void angles(double height, double distance, double depth, double* res1, double* res2, double* res3) {
    double arm1 = 20.0;
    double arm2 = 15.0;

    
    double armH = height * height + distance * distance; // armH shorthand for h^2 + d^2

    double a1tanIn = height / distance; 
    double a1cosIn = (arm1*arm1 - arm2 * arm2 + armH) / (2 * arm1 * sqrt(armH));
    double angle1 = atan(a1tanIn) + acos(a1cosIn); // lower arm angle

    double a2cosIn = (arm1 * arm1 + arm2 * arm2 - armH) / (2 * arm1 * arm2); 
    double angle2 = acos(a2cosIn) - M_PI; // upper arm angle

    
    *res1 = angle1;
    *res2 = angle2;
    *res3 = atan(distance / depth);
}

double toSteps(double angle, double perRevolution) {
    double steps = angle * perRevolution / (2 * M_PI);
    return steps;
}
