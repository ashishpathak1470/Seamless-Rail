#ifndef SEAT_H
#define SEAT_H

class Seat {
public:
    Seat(int seatNumber);
    int getSeatNumber() const;
    bool isOccupied() const;
    void occupy();
    void vacate();

private:
    int seatNumber;
    bool occupied;
};

#endif
