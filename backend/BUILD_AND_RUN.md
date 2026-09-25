# VS Code - Run the Full System
1. Open the SmartParkKenya folder in VS Code.
2. Ensure the terminal is at the project root (the folder containing frontend, backend, database).
3. Put `httplib.h` and `json.hpp` in `backend/`.
4. Compile:
`g++ backend/Server.cpp backend/ParkingSystem.cpp data_structures/Vehicle.cpp data_structures/ParkingSlot.cpp database/Database.cpp -Ibackend -lsqlite3 -lws2_32 -pthread -o SmartParkServer.exe`
5. Run:
`.\SmartParkServer.exe`
6. Keep that terminal open.
7. Install VS Code's Live Server extension.
8. Right-click `frontend/index.html` -> Open with Live Server.
9. Test: register a vehicle, check occupied slot, calculate exit, pay, confirm barrier OPEN and slot availability.
