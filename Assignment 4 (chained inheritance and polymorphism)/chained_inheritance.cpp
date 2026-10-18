

#include <iostream>
#include <string>

using namespace std;

class Device {
protected:                     
    string deviceId;
    string location;
    bool   powered;

public:
    Device(const string& id, const string& loc)
        : deviceId(id), location(loc), powered(false) {
        cout << "  [Device]            constructor ran for " << deviceId << endl;
    }

    ~Device() {
        cout << "  [Device]            destructor ran for " << deviceId << endl;
    }

    void powerOn() {
        powered = true;
        cout << deviceId << " powered ON" << endl;
    }

    void powerOff() {
        powered = false;
        cout << deviceId << " powered OFF" << endl;
    }

    bool isPoweredOn() const { return powered; }

    void showDeviceInfo() const {
        cout << "Device ID : " << deviceId << endl;
        cout << "Location  : " << location << endl;
        cout << "Power     : " << (powered ? "ON" : "OFF") << endl;
    }
};


class Sensor : public Device {
protected:
    string unit;               
    double lastReading;

public:
    Sensor(const string& id, const string& loc, const string& measurementUnit)
        : Device(id, loc), unit(measurementUnit), lastReading(0.0) {
        cout << "  [Sensor]            constructor ran for " << deviceId << endl;
    }

    ~Sensor() {
        cout << "  [Sensor]            destructor ran for " << deviceId << endl;
    }

    void recordReading(double value) {
        
        if (!powered) {
            cout << deviceId << ": cannot record, sensor is OFF" << endl;
            return;
        }
        lastReading = value;
        cout << deviceId << " recorded " << value << " " << unit << endl;
    }

    double getLastReading() const { return lastReading; }

    void showSensorInfo() const {
        showDeviceInfo();       
        cout << "Unit      : " << unit << endl;
        cout << "Last read : " << lastReading << " " << unit << endl;
    }
};


class TemperatureSensor : public Sensor {
private:
    double maxSafeTemp;

public:
    TemperatureSensor(const string& id, const string& loc, double maxTemp)
        : Sensor(id, loc, "degC"), maxSafeTemp(maxTemp) {
        cout << "  [TemperatureSensor] constructor ran for " << deviceId << endl;
    }

    ~TemperatureSensor() {
        cout << "  [TemperatureSensor] destructor ran for " << deviceId << endl;
    }


    bool isOverheating() const { return lastReading > maxSafeTemp; }

    double toFahrenheit() const { return lastReading * 9.0 / 5.0 + 32.0; }

    void showStatus() const {
        showSensorInfo();       
        cout << "Max safe  : " << maxSafeTemp << " " << unit << endl;
        cout << "In degF   : " << toFahrenheit() << endl;
        cout << "Status    : " << (isOverheating() ? "WARNING - OVERHEATING!" : "Normal") << endl;
    }
};

int main() {
    cout << "=== 1. Creating a TemperatureSensor (watch the constructor order) ===" << endl;
    TemperatureSensor serverRoom("TS-01", "Server Room", 35.0);

    cout << "\n=== 2. Using members inherited from Device (Level 1) ===" << endl;
    serverRoom.recordReading(28.5);     
    serverRoom.powerOn();               

    cout << "\n=== 3. Using members inherited from Sensor (Level 2) ===" << endl;
    serverRoom.recordReading(28.5);

    cout << "\n=== 4. Using members defined in TemperatureSensor (Level 3) ===" << endl;
    serverRoom.showStatus();

    cout << "\n--- Temperature rises ---" << endl;
    serverRoom.recordReading(38.2);
    serverRoom.showStatus();

    cout << "\n=== 5. Power off, then try to record again ===" << endl;
    serverRoom.powerOff();
    serverRoom.recordReading(40.0);

    cout << "\n=== 6. A Level 2 object on its own ===" << endl;
    Sensor humidity("HS-01", "Greenhouse", "%");
    humidity.powerOn();
    humidity.recordReading(64.0);
    humidity.showSensorInfo();

    cout << "\n=== 7. End of main: objects are destroyed in reverse order ===" << endl;
    return 0;
}
