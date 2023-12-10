#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Seat {
public:
    Seat(int seatNumber) : seatNumber(seatNumber), occupied(false) {}

    int getSeatNumber() const {
        return seatNumber;
    }

    bool isOccupied() const {
        return occupied;
    }

    void occupy() {
        occupied = true;
    }

    void vacate() {
        occupied = false;
    }

private:
    int seatNumber;
    bool occupied;
};

class Train {
public:
    Train(int capacity) : capacity(capacity) {
        for (int i = 0; i <= capacity; ++i) {
            seats.push_back(Seat(i)); // Associate seat numbers with seat objects
        }
    }

    int getCapacity() const {
        return capacity;
    }

    const Seat& getSeat(int seatNumber) const {
        return seats[seatNumber - 1];
    }

    bool isAvailable(int numOfSeats) const {
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

    bool allocateSeats(int numOfSeats, vector<int>& allocatedSeats) {
        int contiguousEmptySeats = 0;
        for (int i = 1; i<capacity; ++i) {
            if (!seats[i].isOccupied()) {
                contiguousEmptySeats++;
                allocatedSeats.push_back(seats[i].getSeatNumber());
                if (contiguousEmptySeats == numOfSeats) {
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

    void deallocateSeatsTill(int preSeats, int vacantSizeTill) {
        for (int i = preSeats; i < vacantSizeTill; ++i) {
            seats[i].vacate();
        }
    }

private:
    int capacity;
    vector<Seat> seats;
};

class Route {
public:
    Route(string source, string destination, vector<QString> stations)
        : source(source), destination(destination), stations(stations) {}

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    const vector<QString>& getStations() const {
        return stations;
    }

private:
    string source;
    string destination;
    vector<QString> stations;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a Qt main window
    QWidget window;
    window.setWindowTitle("Train Seat Reservation System");

    QLabel sourceLabel("Source Station:", &window);
    QLabel destinationLabel("Destination Station:", &window);
    QLabel groupSizeLabel("Group Size:", &window);

    QComboBox sourceComboBox(&window);
    QComboBox destinationComboBox(&window);
    QLineEdit groupSizeInput(&window);

    QPushButton allocateButton("Allocate Seats", &window);
    QLabel outputLabel("Output will be displayed here", &window);

    vector<QString> stations = {"Jabalpur", "Delhi", "Lucknow", "Jaipur", "Bilaspur"};

    for (const QString& station : stations) {
        sourceComboBox.addItem(station);
        destinationComboBox.addItem(station);
    }

    Train train(72);
    string source, destination;
    vector<QString> previousDestinations;
    vector<int> previousGroupsize;

    QVBoxLayout layout(&window);
    layout.addWidget(&sourceLabel);
    layout.addWidget(&sourceComboBox);
    layout.addWidget(&destinationLabel);
    layout.addWidget(&destinationComboBox);
    layout.addWidget(&groupSizeLabel);
    layout.addWidget(&groupSizeInput);
    layout.addWidget(&allocateButton);
    layout.addWidget(&outputLabel);

    window.show();

    QObject::connect(&allocateButton, &QPushButton::clicked, [&outputLabel, &sourceComboBox, &destinationComboBox, &groupSizeInput, &train, &stations, &source, &destination, &previousDestinations, &previousGroupsize]() {
        QString source = sourceComboBox.currentText();
        QString destination = destinationComboBox.currentText();
        int groupSize = groupSizeInput.text().toInt();

        int sourceIndex = sourceComboBox.currentIndex();
        if (sourceIndex == -1) {
            outputLabel.setText("Invalid source station selected");
            return;
        }

        int destinationIndex = destinationComboBox.currentIndex();
        if (destinationIndex == -1) {
            outputLabel.setText("Invalid destination station selected");
            return;
        }

        stations[sourceIndex].toStdString();
        stations[destinationIndex].toStdString();


        vector<int> allocatedSeats;

        if (groupSize <= 0 || groupSize > train.getCapacity()) {
            outputLabel.setText("Invalid group size. Please enter a valid group size.");
            return;
        }

        if (find(previousDestinations.begin(), previousDestinations.end(), source) != previousDestinations.end()) {

            vector<QString>::iterator it;

            it = find(previousDestinations.begin(), previousDestinations.end(), source);
            int index = it - previousDestinations.begin();
            //cout <<" " <<previousGroupsize[index]<<" seats were vacated at "<< source << endl;

            int preSeats=0;
            for(int i=0; i<index; i++)
                preSeats += previousGroupsize[i];

            int vacantSizeTill = preSeats + previousGroupsize[index];
            train.deallocateSeatsTill(preSeats , vacantSizeTill); // Deallocate seats
            previousDestinations[index]= destination; // Will update the destination to current one
        }

        previousGroupsize.push_back(groupSize);


        // Your logic for seat allocation and deallocation
        if (train.isAvailable(groupSize)) {
            if (train.allocateSeats(groupSize, allocatedSeats)) {
                // Successful allocation
                string outputText = "Seats allocated successfully: ";
                sort(allocatedSeats.begin(), allocatedSeats.end());
                for (int seatNumber : allocatedSeats) {
                    outputText += to_string(seatNumber) + " ";
                }
                outputLabel.setText(outputText.c_str());

                // Track previous destinations and group sizes
                previousDestinations.push_back(destination);
                previousGroupsize.push_back(groupSize);
            } else {
                outputLabel.setText("Failed to allocate contiguous seats for your group.");
            }
        } else {
            outputLabel.setText("Not enough contiguous seats available for your group.");
        }
    });

    return app.exec();
}
