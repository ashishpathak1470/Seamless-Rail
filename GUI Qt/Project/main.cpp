#include "Train.h"
#include "Route.h"
#include "Seat.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    Train train(72);

    std::vector<std::string> stations = { "Jabalpur", "Delhi", "Lucknow", "Jaipur", "Bilaspur" };
    std::string source, destination;
    std::vector<std::string> previousDestinations; // Keep track of previous destinations
    std::vector<int> previousGroupsize; // Last entered group size

    std::cout << "List of stations:" << std::endl;
    for (int i = 0; i < stations.size(); ++i) {
        std::cout << i + 1 << ". " << stations[i] << std::endl;
    }

    while (true) {
        int sourceIndex, destinationIndex;
        std::cout << "Enter source station (1-" << stations.size() << ") or 0 to exit: ";
        std::cin >> sourceIndex;

        if (sourceIndex == 0) {
            std::cout << "Hamara Application use karne k liye dhanyawaad!" << std::endl;
            std::cout << "Team Void" << std::endl;
            break; // Exit the loop if 0 is entered as the source station
        }

        if (sourceIndex < 1 || sourceIndex > stations.size()) {
            std::cout << "Invalid source station index. Please enter a valid index." << std::endl;
            continue; // Go back to the beginning of the loop
        }

        std::cout << "Enter destination station (1-" << stations.size() << "): ";
        std::cin >> destinationIndex;

        source = stations[sourceIndex - 1];
        destination = stations[destinationIndex - 1];

        int groupSize;
        std::cout << "Enter your group size: ";
        std::cin >> groupSize;

        std::vector<int> allocatedSeats;

        if (groupSize <= 0 || groupSize > train.getCapacity()) {
            std::cout << "Invalid group size. Please enter a valid group size." << std::endl;
            continue; // Go back to the beginning of the loop
        }

        Route route(source, destination, stations);  // Create a Route object
        std::cout << "Selected route: " << route.getSource() << " to " << route.getDestination() << std::endl;

        if (find(previousDestinations.begin(), previousDestinations.end(), source) != previousDestinations.end()) {
            std::vector<std::string>::iterator it;
            it = find(previousDestinations.begin(), previousDestinations.end(), source);
            int index = it - previousDestinations.begin();
            std::cout << " " << previousGroupsize[index] << " seats were vacated at " << source << std::endl;

            int preSeats = 0;
            for (int i = 0; i < index; i++)
                preSeats += previousGroupsize[i];

            int vacantSizeTill = preSeats + previousGroupsize[index];
            train.deallocateSeatsTill(preSeats, vacantSizeTill); // Deallocate seats
            previousDestinations[index] = destination; // Will update the destination to the current one
        }

        previousGroupsize.push_back(groupSize);

        if (train.isAvailable(groupSize)) {
            if (train.allocateSeats(groupSize, allocatedSeats)) {
                std::cout << "Seats allocated successfully: ";
                sort(allocatedSeats.begin(), allocatedSeats.end());
                for (int seatNumber : allocatedSeats) {
                    std::cout << seatNumber << " ";
                }
                std::cout << std::endl << std::endl;
                previousDestinations.push_back(destination); // Add destination to previous destinations
            }
            else {
                std::cout << "Failed to allocate contiguous seats for your group." << std::endl;
            }
        }
        else {
            std::cout << "Not enough contiguous seats available for your group." << std::endl;
        }
    }

    return 0;
}
