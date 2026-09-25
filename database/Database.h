#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>
struct VehicleRecord{int id;std::string registration;int slot;std::string entryTime,exitTime;int durationMinutes;double amount;bool paid;};
class Database{void* db;public:Database();~Database();bool connect(const std::string& file="database/parking.db");bool createTables();bool saveVehicle(const std::string&,int);bool findActiveVehicle(const std::string&,VehicleRecord&);bool findUnpaidVehicle(const std::string&,VehicleRecord&);bool updateExit(const std::string&,const std::string&,int,double);bool markPaid(const std::string&);bool getAllActiveVehicles(std::vector<VehicleRecord>&);void close();};
#endif