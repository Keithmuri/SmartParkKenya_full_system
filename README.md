# SmartPark Kenya - Full System

SmartPark Kenya is a small parking operations dashboard backed by a C++ HTTP API and SQLite. The frontend is a static HTML/CSS/JavaScript control room with live space availability, vehicle entry, exit calculation, and payment workflows.

## What it does when used

- Shows live availability for all parking spaces
- Assigns the next available space when a vehicle enters
- Calculates parking duration and fees when a vehicle exits
- Records payment and reports the barrier as open
- Persists vehicle activity in SQLite
- Refreshes the parking map every five seconds

## Requirements (Windows)

Install the MSYS2 UCRT64 toolchain and make sure `g++` is available in PowerShell. Install the SQLite development package once from an MSYS2 terminal or PowerShell:

```powershell
C:\msys64\usr\bin\pacman.exe -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sqlite3
```

Python 3 is also required to serve the static frontend. VS Code Live Server can be used instead if preferred.

## Start the backend API

Open PowerShell in the project root, the folder containing `backend`, `frontend`, and `database`:

```powershell
g++ backend/Server.cpp backend/ParkingSystem.cpp data_structures/Vehicle.cpp data_structures/ParkingSlot.cpp database/Database.cpp -Ibackend -lsqlite3 -lws2_32 -pthread -o SmartParkServer.exe
.\SmartParkServer.exe
```

The API starts at `http://localhost:8080`.

## Start the frontend

Keep the backend terminal running. Open a second PowerShell window in the project root and serve the frontend directory:

```powershell
python -m http.server 5500 --directory frontend
```

Open `http://localhost:5500` in a browser. The frontend calls the backend at `http://localhost:8080/api`.

Alternatively, install VS Code's Live Server extension, right-click `frontend/index.html`, and choose **Open with Live Server**.

## API routes

| Method | Route | Purpose |
| --- | --- | --- |
| GET | `/api/slots` | Read current space availability |
| POST | `/api/entry` | Register a vehicle and assign a space |
| POST | `/api/exit` | Calculate duration and amount due |
| POST | `/api/payment` | Record payment and open the barrier |

POST requests use JSON in this shape:

```json
{"registration":"KCA 123A"}
```

## Fee schedule

| Parking time | Fee |
| --- | ---: |
| 0-30 minutes | KSh 0 |
| 31-120 minutes | KSh 50 |
| 121-240 minutes | KSh 100 |
| 241-360 minutes | KSh 300 |
| Over 360 minutes | KSh 500 |

## Project layout

```text
backend/          HTTP server and parking business logic
connection/       API helper and route notes
data_structures/  Vehicle and parking-slot models
database/         SQLite connection and schema
frontend/         Static dashboard assets
```
