#include "Event.hpp"

Event::Event() {
    
}

Event::~Event() {
    
}

void Event::AddEvent(MotorDriver* driver, double target) {
    targets.push_back(target);
    drivers.push_back(driver);
}

void Event::SetEvents(double time, double targetTime) {
    for(int i=0; i<drivers.size(); i++){
        drivers[i]->SetTarget(targets[i], targetTime, time);
    }
}

bool Event::IsDone() const {
    bool result = true; 

    for(int i=0; i<drivers.size(); i++){
        result &= drivers[i]->IsDone();
    }

    return result;    
}
