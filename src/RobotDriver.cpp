#include "RobotDriver.h"

RobotDriver::RobotDriver() {
}

RobotDriver::~RobotDriver() {
}

void RobotDriver::Update(double time) {
    for(auto& joint : joints_){
        joint.Update(time);
    }
}

double RobotDriver::GetAngle(int index) {
    if(index < 0 || index > joints_.size())
        return -123.456;
    return joints_[index].GetAngle();
}

std::vector<double> RobotDriver::GetAngles() {
    std::vector<double> result(joints_.size());
    for(int i=0; i<joints_.size(); i++){
        result[i] = joints_[i].GetAngle();
    }
    return result;
}

std::vector<double> RobotDriver::GetPositions() {

    // no function for position... :(
    // joint class?

}

void RobotDriver::MoveAngles(std::vector<double> dangles, double time) {
    for(int i=0; i<joints_.size(); i++){
        joints_[i].SetTarget(dangles[i], time);
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

void RobotDriver::SetAnglesTo(std::vector<double> angles) {
    
}

void RobotDriver::SetPositionTo(double x, double y, double z) {
    
}
