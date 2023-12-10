#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <string>

class Route {
public:
    Route(std::string source, std::string destination, const std::vector<std::string>& stations);
    std::string getSource() const;
    std::string getDestination() const;
    const std::vector<std::string>& getStations() const;

private:
    std::string source;
    std::string destination;
    std::vector<std::string> stations;
};

#endif
