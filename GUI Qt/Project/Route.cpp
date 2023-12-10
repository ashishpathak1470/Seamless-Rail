#include "Route.h"

Route::Route(std::string source, std::string destination, const std::vector<std::string>& stations)
    : source(source), destination(destination), stations(stations) {
    // Constructor implementation
}

std::string Route::getSource() const {
    return source;
}

std::string Route::getDestination() const {
    return destination;
}

const std::vector<std::string>& Route::getStations() const {
    return stations;
}
