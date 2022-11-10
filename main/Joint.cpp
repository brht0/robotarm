#include "Joint.h"

Joint::Joint(double length, MotorDriver* driver):
    length_(length), driver_(driver)
{
}

Joint::~Joint(){
}

void Joint::Update(double time){
    driver_->Update(time);
}

double Joint::GetLength() const{
    return length_;
}

double Joint::GetAngle() const{
    return driver_->GetAngle();
}

void Joint::SetTarget(double angle, double targetTime, double time){
    driver_->SetTarget(angle, targetTime, time);
}

void Joint::SetAngle(double angle){
    driver_->SetAngle(angle);
}
