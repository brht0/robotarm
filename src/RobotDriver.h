#ifndef __ROBOTDRIVER_H__
#define __ROBOTDRIVER_H__

#include "Joint.h"
// works in arduino?
#include <vector>

/*
RobotDriver is a high level class handling the entire motion of
the robot. This class calculates the angles from global positions
and handle all motor drivers.

This class assumes that all motors are placed sequentially (like in
a robotic arm) and will store them ordered in "drivers_" container.
*/

class RobotDriver{
public:
    RobotDriver();
    ~RobotDriver();

    // returns current position of tool end
    std::initializer_list<double> GetPosition();

    void Update(double time);

    double GetAngle(int index);
    std::vector<double> GetAngles();
    std::vector<double> GetPositions();

    // moves single motor with specified index to angle
    void MoveAngles(std::vector<double> dangles, double time);

    // moves single motor with specified index to angle
    void MoveAngle(int index, double dangle);

    // move in relative co-ordinates
    void MovePosition(double dx, double dy, double dz);

    double GetEstimatedTimeForMotion(double x, double y, double z);

    // move specific co-ordinates 
    void MoveX(double dx);
    void MoveY(double dy);
    void MoveZ(double dz);

    // move in global space
    void SetAnglesTo(std::vector<double> angles);
    void SetPositionTo(double x, double y, double z);

private:
    std::vector<Joint> joints_;

    // angle logic here i think?
    // Jacobian Matrix to generalize ?
};

#endif // __ROBOTDRIVER_H__