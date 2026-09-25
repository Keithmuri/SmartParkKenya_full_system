#include "ParkingSystem.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
ParkingSystem::ParkingSystem(int n){for(int i=1;i<=n;i++)slots.emplace_back(i);database.connect("database/parking.db");std::vector<VehicleRecord>a;if(database.getAllActiveVehicles(a))for(auto&r:a)if(r.slot>=1&&r.slot<=getTotalSlots())slots[r.slot-1].occupy();}
int ParkingSystem::getTotalSlots()const{return (int)slots.size();}int ParkingSystem::getAvailableSlots()const{int n=0;for(auto&s:slots)if(s.isAvailable())n++;return n;}
std::vector<int>ParkingSystem::getAvailableSlotNumbers()const{std::vector<int>r;for(auto&s:slots)if(s.isAvailable())r.push_back(s.getSlotNumber());return r;}
bool ParkingSystem::getActiveVehicles(std::vector<VehicleRecord>&records){return database.getAllActiveVehicles(records);}
bool ParkingSystem::registerVehicle(const std::string&r,int&slot,std::string&m){if(r.empty()){m="Vehicle registration is required.";return false;}VehicleRecord x;if(database.findActiveVehicle(r,x)){m="Vehicle is already inside the parking area.";return false;}slot=-1;for(auto&s:slots)if(s.isAvailable()){slot=s.getSlotNumber();s.occupy();break;}if(slot==-1){m="Parking is full.";return false;}if(!database.saveVehicle(r,slot)){slots[slot-1].release();m="Could not save vehicle.";return false;}vehicles.emplace_back(r,slot);m="Vehicle registered successfully.";return true;}
std::string ParkingSystem::currentTime()const{std::time_t n=std::time(nullptr);std::tm t{};
#ifdef _WIN32
localtime_s(&t,&n);
#else
t=*std::localtime(&n);
#endif
std::ostringstream o;o<<std::put_time(&t,"%Y-%m-%d %H:%M:%S");return o.str();}
double ParkingSystem::calculateFee(int m)const{if(m<=30)return 0;if(m<=120)return 50;if(m<=240)return 100;if(m<=360)return 300;return 500;}
ExitResult ParkingSystem::processExit(const std::string&r){ExitResult z{false,"",-1,0,0};VehicleRecord v;if(!database.findActiveVehicle(r,v)){z.message="No active vehicle found with that registration.";return z;}std::tm t{};std::istringstream in(v.entryTime);in>>std::get_time(&t,"%Y-%m-%d %H:%M:%S");if(in.fail()){z.message="Invalid entry time.";return z;}std::time_t e=std::mktime(&t),n=std::time(nullptr);int m=(int)(std::difftime(n,e)/60.0);if(m<0)m=0;double fee=calculateFee(m);if(!database.updateExit(r,currentTime(),m,fee)){z.message="Could not update exit.";return z;}if(v.slot>=1&&v.slot<=getTotalSlots())slots[v.slot-1].release();z={true,"Exit calculated. Payment required before barrier opens.",v.slot,m,fee};return z;}
bool ParkingSystem::processPayment(const std::string&r,double&a,int&slot,std::string&m){VehicleRecord v;if(!database.findUnpaidVehicle(r,v)){m="No unpaid exit record found for this vehicle.";return false;}a=v.amount;slot=v.slot;if(!database.markPaid(r)){m="Payment could not be recorded.";return false;}m="Payment successful. Barrier OPEN.";return true;}