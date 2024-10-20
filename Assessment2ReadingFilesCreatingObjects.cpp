// Assessment2ReadingFilesCreatingObjects.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


using namespace std;
#include <vector>
#include <string>
#include <iostream>  // For std::cout
#include <fstream>   // For file input/output operations
#include "Vehicle.h" // Custom class for Vehicle objects
#include "Constant.h" // Custom class for Vehicle objects
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <tuple>
#include <iomanip>   // for setw:



// ---------------------------------------------------------------------------------------------------------------------  //
// Task 1


class ChargingStation {
public:
    int cityId = 1;
    string cityName = "Sydney";            // Declare string and initialize it 
    int distanceToLastCity = 1;
    int numberOfChargers = 1;
    int distance_to_syd = 0;
    static int displayDistanceToSydney();
    // Constructor to initialize city details
    ChargingStation() {};
    ChargingStation(int Stationid) {
        if (Stationid >= 0 && Stationid < NUM_CITIES) {
            cityId = Stationid;
            cityName = nameMap[Stationid];  // Correctly reference nameMap from Constant.h
            distanceToLastCity = distanceMap[Stationid];
            numberOfChargers = chargersMap[Stationid];
            

        }
        else {
            // Handle invalid city ID
            cout << "Invalid City ID!" << endl;
        }
    }
    // Display city information
    void displayCityID() const {
        cout << "City ID: " << cityId << endl;
    }
    void displayDistanceToLastCity() const {
        cout << "Distance to Last City: " << distanceToLastCity << " km" << endl;
    }
    void displayNumberOfChargers() const {
        cout << "Number of Chargers: " << numberOfChargers << endl;
    }
    void displayCityName() const {
        cout << "City Name: " << cityName << endl;
    }
    

    
    // Task 3
    int displayDistanceToSydney(int cityid_temp) {
        //cityid_temp;
        int distance_to_syd = 0;
        int current_cityId = 0;
        for (int i = current_cityId; i <= cityid_temp; i++) {
            distance_to_syd += distanceMap[i];
        }
        //cout << distance_to_syd;
        return distance_to_syd;
    }

    static double averageWaitingTime(int temp_charger[]) {
        double half = 0.5;
        int hour = 1;

        double totalWait = 0.0;
        int counter = 0;
        for (int i = 0; i < 12; i++) 
        {
            double avgWait = 0.5 * hour * ((temp_charger[i]) / chargersMap[i]);
            //double avgWait = temp_charger[i];
            cout << setw(20)<< "Average wait time " << nameMap[i] << ": " << static_cast<double>(avgWait)<< " Hours" << endl;
            if (avgWait > 0) 
            {
                counter++;
                totalWait += avgWait;
            }
        }
        cout << "TOTAL AVERAGE WAIT TIME ALL VEHICLES: " << totalWait / counter << " Hours" << endl<<endl;

        
        return 1.0;


    }


};
// ---------------------------------------------------------------------------------------------------------------------  //


// ---------------------------------------------------------------------------------------------------------------------  //
// Task 2
Vehicle::Vehicle(int vId, int destId, int capRange, int remRange) : vehicleId(vId), destinationId(destId), capacityRange(capRange), remainingRange(remRange) {}// constructor

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << "[" << vehicle.vehicleId << "," << vehicle.destinationId << "," << vehicle.capacityRange << "," << vehicle.remainingRange << "]" << endl;
    return os;  // Return the output stream
}





int Vehicle::getVehicleId() const { return vehicleId; }
int Vehicle::getCurrentCityId() const { return currentCityId; }
int Vehicle::getDestinationId() const { return destinationId; }
int Vehicle::getCapacityRange() const { return capacityRange; }
int Vehicle::getRemainingRange() const { return remainingRange; }

// Setters
void Vehicle::setVehicleId(int vId) { vehicleId = vId; }
void Vehicle::setCurrentCityId(int currCityId) { currentCityId = currCityId; }
void Vehicle::setDestinationId(int destId) { destinationId = destId; }
void Vehicle::setCapacityRange(int capRange) { capacityRange = capRange; }
void Vehicle::setRemainingRange(int remRange) { remainingRange = remRange; }

// Display vehicle information
void Vehicle::displayVehicleInfo() const {

    cout << "[" << vehicleId << "," << destinationId << "," << capacityRange << "," << remainingRange << "]" << "endl";
}

bool Vehicle::canReachDestination(int dei, int farc) const{
    // assumes all cars start from sydney doesnt work with recharged cars
    const int arr[12] = { 0, 57, 117, 200, 286, 385, 500, 562, 636, 723, 829, 891 };
    //int destination_length = arr[destinationdistance];
    if (farc >= dei) {
        return true;
    }
    else {
        return false;
    }
}

int Vehicle::farCity(int rem, const int* arr) {
   
    int current_city_id = 0;
    //int fd_city = 0;
    
    // assumes all cars start from sydney doesnt work with recharged cars
    //const int arr[12] = { 0, 57, 117, 200, 286, 385, 500, 562, 636, 723, 829, 891 };
    /*
    for (int i = 0; i < 12; i++)
    {
        if (rem > arr[i])
        {
            fd_city = i;
        }
        else if(rem == arr[i])
        {
            fd_city = i;
            break;
        }
        else
        {
            fd_city = i-1;
            break;
        }
        
    }
    return fd_city;
    //cout << fd_city;
    */

    // this is a much better way and works on any values
    int compoundedValue = 0;
    int fd_city = -1; // -1 is used if rem is too small 

    for (int i = 0; i < 12; i++) {
        compoundedValue += arr[i]; // Add compounded value

        if (compoundedValue >= rem) { // Check if value meets or exceeds rem
            fd_city = i; // Update the furthest city index
            break; // Exit the loop since we've found the furthest city
        }
    }

    return fd_city; // Return the index of the furthest city or -1 if none found
    
}


// ---------------------------------------------------------------------------------------------------------------------  //

// ---------------------------------------------------------------------------------------------------------------------  //
// Task 3
const int SIZE_OF_DEMAND = 200;
class DemandGenerator {
public:
    ofstream fout;
    

    void outputFunction() 
    {
        std::srand(static_cast<unsigned>(std::time(0)));
        fout.open("GeneratedDemands.txt");
        if (fout.fail()) {
            cout << "Demand Generator File Output Failed: " << endl;
            exit(1);
        }
        //int r = rand() % 10;
        cout << "Generated EV DEMANDS: " << endl;
        
        for (int i = 0; i < SIZE_OF_DEMAND; i++)
        {
            int vehicleId = i + 200;
            int destinationId = rand() % 13;
            int capacityRange = (rand() % 201) + 350;
            int remainRange = 300 + std::rand() % (capacityRange - 300 + 1);

            //int remansssssRange = 300 + std::rand() % (capacityRange - 300 + 1);

            fout << '[' << vehicleId << ','<<destinationId<<','<<capacityRange<<','<<remainRange<<']'<<endl;
            // outputs to console but we dont need it right now since the output and other stuff will be handled in the main section.
           // cout << '[' << vehicleId << ',' << destinationId << ',' << capacityRange << ',' << remainRange << ']' << endl;
        }
        fout.close();

    }
    
};





int main()
{
    DemandGenerator g;
    ChargingStation c;
    Vehicle v;

    // this shows the distance to sydney from a cityid 
    //ChargingStation::displayDistanceToSydney(12);

    // storing value of distance to syd test
    //int sdf = ChargingStation::displayDistanceToSydney(3);
    //cout << "sdf: " << sdf << endl;
    g.outputFunction();
    
 
    cout << endl;
    ifstream infile;
    
    infile.open("GeneratedDemands.txt");
    if (infile.fail()) {
        cout << "This file could not be opened";
        exit(1);
    }

    ofstream firstCharge;
    firstCharge.open("1stChargeEVs.txt");
    if (firstCharge.fail()) {
        cout << "This file could not be opened";
        exit(1);
    }

    //std::cout << "Hello World!\n";
    vector<Vehicle> demands;
    //vector<Vehicle> firstchargeDemands;
    while (!infile.eof()) 
    {
        char c;
        infile >> c;
        if (c == '[') 
        {
            int values[4];
            for (int i = 0; i < 4; i++) 
            {
                infile >> values[i];
                infile >> c;
                //currentCityId = 0;
            }
            if (c != ']') 
            {
                cout << "Problem of reading file" << endl;
                break;
            }
            Vehicle demand(values[0], values[1], values[2], values[3]);
            //demand.setLatestCharging();
            demands.push_back(demand);
        }
    }
    // works with 156 as limit for charging demands
    //cout << "Vehicle ID               Destination ID               Capacity Range               Remaining Range" << endl;
    
    // outputs the vehicle stuff in format
    int que[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

   

    int appendedSize = SIZE_OF_DEMAND;
    for (int i = 0; i < SIZE_OF_DEMAND; i++)
    {
        cout << demands[i];
        cout << "Vehicle ID: " << demands[i].getVehicleId() << endl;
        cout << "Destination ID: " << demands[i].getDestinationId() << endl;
        cout << "Capacity Range: " << demands[i].getCapacityRange() << endl;
        cout << "Remaining Range: " << demands[i].getRemainingRange() << endl;
        //cout << "Current City Id " << currentCityId;

        int destination = demands[i].getDestinationId();
        int remains = demands[i].getRemainingRange();
        cout << "farthest city can travel: " << Vehicle::farCity(remains, distanceMap) << endl;
        int farcityNum = Vehicle::farCity(remains, distanceMap);

       // v.canReachDestination(destination, remains);
        if (v.canReachDestination(destination, farcityNum) == true) {
            cout << "Reached Destination? YES" << endl << endl;
        }
        else {
            cout << "Reached Destination? NO" << endl;
            cout << "This EV is queing in city: " << farcityNum << endl<<endl;
            firstCharge << demands[i];
            appendedSize--;
            que[farcityNum]++;

        }

        
    }
    int temp_charger[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    cout << endl << "Queing Map" << "          Number of Chargers" << endl;

    for (int i = 0; i < 12; i++) {
        std::cout << std::setw(15) << nameMap[i] << ": " << que[i] << "             "<<  chargersMap[i]<< endl; // Use nameMap[i] for charger names
        temp_charger[i] = que[i];
        //cout << "TTTTTTTTTTTTTT: "<< temp_charger[i] << endl;
    }
    cout << endl;

    c.averageWaitingTime(temp_charger);
    

   // g.outputFunction();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ifstream infile2;
    infile2.open("1stChargeEVs.txt");
    if (infile2.fail()) {
        cout << "This file could not be opened";
        exit(1);
    }

    vector<Vehicle> firstchargeDemands;
    while (!infile2.eof())
    {
        char c;
        infile2 >> c;
        if (c == '[')
        {
            int values[4];
            for (int i = 0; i < 4; i++)
            {
                infile2 >> values[i];
                infile2 >> c;
                //currentCityId = 0;
            }
            if (c != ']')
            {
                cout << "Problem of reading file" << endl;
                break;
            }

            Vehicle firstCharge(values[0], values[1], values[2], values[3]);
            //demand.setLatestCharging();
            
            firstchargeDemands.push_back(firstCharge);
        }
    }
    cout << "VEHICLES THAT NEEDED RECHARGE: " << endl << endl;
    for (int i = 0; i < appendedSize; i++)
    {
        //cout << demands[i];
        cout << firstchargeDemands[i];
        cout << "Vehicle ID set: " << firstchargeDemands[i].getVehicleId() << endl;
        cout << "Destination ID: " << firstchargeDemands[i].getDestinationId() << endl;
        cout << "Capacity Range: " << firstchargeDemands[i].getCapacityRange() << endl;
        cout << "Remaining Range: " << firstchargeDemands[i].getRemainingRange() << endl<< endl;
        //cout << "Current City Id " << currentCityId;

        //int destination = demands[i].getDestinationId();
        //int remains = demands[i].getRemainingRange();
        //cout << "farthest city can travel: " << Vehicle::farCity(remains) << endl;
        //int farcityNum = Vehicle::farCity(remains);

        //// v.canReachDestination(destination, remains);
        //if (v.canReachDestination(destination, farcityNum) == true) {
        //    cout << "Reached Destination? YES" << endl << endl;
        //}
        //else {
        //    cout << "Reached Destination? NO" << endl;
        //    cout << "This EV is queing in city: " << farcityNum << endl << endl;
        //    firstCharge << demands[i];
        //    que[farcityNum]++;

        //}


    }
    infile.close();
    infile2.close();



    
    /*
    * // Already implemented in the above for loop to display furthest distance an ev can go with current remaining range
    int rr = 117;
    cout << "very far city " << Vehicle::farCity(rr) << endl;
    */
    
 
}

