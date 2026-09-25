#include "Vehicle.h"
#include <ctime>
Vehicle::Vehicle():parkingSlot(-1),amount(0),paid(false){}
Vehicle::Vehicle(const std::string&r,int s):registration(r),parkingSlot(s),amount(0),paid(false){std::time_t n=std::time(nullptr);entryTime=std::ctime(&n);if(!entryTime.empty()&&entryTime.back()=='\n')entryTime.pop_back();}
std::string Vehicle::getRegistration()const{return registration;}int Vehicle::getParkingSlot()const{return parkingSlot;}std::string Vehicle::getEntryTime()const{return entryTime;}std::string Vehicle::getExitTime()const{return exitTime;}double Vehicle::getAmount()const{return amount;}bool Vehicle::isPaid()const{return paid;}void Vehicle::setExitTime(const std::string&t){exitTime=t;}void Vehicle::setAmount(double v){amount=v;}void Vehicle::setPaid(bool v){paid=v;}