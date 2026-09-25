#ifndef PARKING_SLOT_H
#define PARKING_SLOT_H
class ParkingSlot{int slotNumber;bool available;public:explicit ParkingSlot(int=0);int getSlotNumber()const;bool isAvailable()const;void occupy();void release();};
#endif