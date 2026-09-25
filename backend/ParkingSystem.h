#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H
#include "../data_structures/ParkingSlot.h"
#include "../data_structures/Vehicle.h"
#include "../database/Database.h"
#include <vector>
#include <string>
struct ExitResult{bool success;std::string message;int slot;int durationMinutes;double amount;};
class ParkingSystem{std::vector<ParkingSlot>slots;std::vector<Vehicle>vehicles;Database database;public:explicit ParkingSystem(int=20);int getTotalSlots()const;int getAvailableSlots()const;std::vector<int>getAvailableSlotNumbers()const;bool getActiveVehicles(std::vector<VehicleRecord>&);bool registerVehicle(const std::string&,int&,std::string&);ExitResult processExit(const std::string&);bool processPayment(const std::string&,double&,int&,std::string&);double calculateFee(int)const;std::string currentTime()const;};
#endif