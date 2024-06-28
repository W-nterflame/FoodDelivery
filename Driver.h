#ifndef DRIVER_H
#define DRIVER_H

#include <string>

using namespace std;

class Driver {
public:
    Driver(const string& name, const string& vehicle, const string& licensePlate)
        : name(name), vehicle(vehicle), licensePlate(licensePlate) {}

    string getName() const { return name; }
    string getVehicle() const { return vehicle; }
    string getLicensePlate() const { return licensePlate; }

private:
    string name;
    string vehicle;
    string licensePlate;
};

#endif
