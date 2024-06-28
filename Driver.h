#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
public:
    Driver(const std::string& name, const std::string& vehicle, const std::string& licensePlate)
        : name(name), vehicle(vehicle), licensePlate(licensePlate) {}

    std::string getName() const { return name; }
    std::string getVehicle() const { return vehicle; }
    std::string getLicensePlate() const { return licensePlate; }

private:
    std::string name;
    std::string vehicle;
    std::string licensePlate;
};

#endif
