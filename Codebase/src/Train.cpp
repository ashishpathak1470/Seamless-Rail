#include "Seat.h"
#include "Train.h"
#include <algorithm>

Train::Train(int capacity) : capacity(capacity) {
    for (int i = 1; i <= capacity; ++i) {
        seats.push_back(Seat(i)); // Associate seat numbers with seat objects
    }
}

int Train::getCapacity() const {
    return capacity;
}

const Seat& Train::getSeat(int seatNumber) const {
    return seats[seatNumber - 1];
}

bool Train::isAvailable(int numOfSeats) const {
    int contiguousEmptySeats = 0;
    for (const Seat& seat : seats) {
        if (!seat.isOccupied()) {
            contiguousEmptySeats++;
            if (contiguousEmptySeats == numOfSeats) {
                return true;
            }
        } else {
            contiguousEmptySeats = 0;
        }
    }
    return false;
}

bool Train::allocateSeats(int numOfSeats, std::vector<int>& allocatedSeats) {
    int contiguousEmptySeats = 0;
    for (int i = (numOfSeats % 2 == 0) ? 0 : capacity - 1; (numOfSeats % 2 == 0) ? (i < capacity) : (i >= 0); (numOfSeats % 2 == 0) ? ++i : --i) {
        if (!seats[i].isOccupied()) {
            contiguousEmptySeats++;
            allocatedSeats.push_back(seats[i].getSeatNumber());
            if (contiguousEmptySeats == numOfSeats) {
                if (numOfSeats % 2 != 0) {
                    std::reverse(allocatedSeats.begin(), allocatedSeats.end());
                }
                for (int seatNumber : allocatedSeats) {
                    seats[seatNumber - 1].occupy();
                }
                return true;
            }
        } else {
            contiguousEmptySeats = 0;
            allocatedSeats.clear();
        }
    }
    return false;
}

void Train::deallocateSeatsTill(int preSeats, int vacantSizeTill) {
    for (int i = preSeats; i < vacantSizeTill; ++i) {
        seats[i].vacate();
    }
}