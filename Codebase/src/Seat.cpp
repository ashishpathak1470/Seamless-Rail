#include "Seat.h"

Seat::Seat(int seatNumber) : seatNumber(seatNumber), occupied(false) {
    // Constructor implementation
}

int Seat::getSeatNumber() const {
    return seatNumber;
}

bool Seat::isOccupied() const {
    return occupied;
}

void Seat::occupy() {
    occupied = true;
}

void Seat::vacate() {
    occupied = false;
}
