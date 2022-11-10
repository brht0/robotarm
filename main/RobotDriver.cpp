#include "RobotDriver.h"

RobotDriver::RobotDriver() {
}

RobotDriver::~RobotDriver() {
}

void RobotDriver::Update(double time) {
    for(int i=0; i<joints_.size(); i++){
        joints_[i].Update(time);
    }
}

double RobotDriver::GetAngle(int index) {
    if(index < 0 || index > joints_.size())
        return -123.456;
    return joints_[index].GetAngle();
}

Vector<double> RobotDriver::GetAngles() {
    Vector<double> result;
    for(int i=0; i<joints_.size(); i++){
        result.push_back(joints_[i].GetAngle());
    }
    return result;
}

Vector<double> RobotDriver::GetPositions() {

    // no function for position... :(
    // joint class?

}

void RobotDriver::MoveAngles(Vector<double> dangles, double targetTime, double time) {
    for(int i=0; i<joints_.size(); i++){
        joints_[i].SetTarget(dangles[i], targetTime, time);
    }
}

void RobotDriver::MoveAngle(int index, double dangle) {
    
}

void RobotDriver::MovePosition(double dx, double dy, double dz) {
    
}

void RobotDriver::MoveX(double dx) {
    
}

void RobotDriver::MoveY(double dy) {
    
}

void RobotDriver::MoveZ(double dz) {
    
}

void RobotDriver::SetAnglesTo(Vector<double> angles) {
    
}

void RobotDriver::SetPositionTo(double x, double y, double z) {
    
}

void RobotDriver::AddJoint(Joint joint) {
    joints_.push_back(joint);
}
