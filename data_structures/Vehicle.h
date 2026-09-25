#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
class Vehicle{std::string registration,entryTime,exitTime;int parkingSlot;double amount;bool paid;
public:Vehicle();Vehicle(const std::string&,int);std::string getRegistration()const;int getParkingSlot()const;std::string getEntryTime()const;std::string getExitTime()const;double getAmount()const;bool isPaid()const;void setExitTime(const std::string&);void setAmount(double);void setPaid(bool);};
#endif