#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include "Seat.h"

class Train {
public:
    Train(int capacity);
    int getCapacity() const;
    const Seat& getSeat(int seatNumber) const;
    bool isAvailable(int numOfSeats) const;
    bool allocateSeats(int numOfSeats, std::vector<int>& allocatedSeats);
    void deallocateSeatsTill(int preSeats, int vacantSizeTill);

private:
    int capacity;
    std::vector<Seat> seats;
};

#endif
