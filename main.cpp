#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <stdexcept>  // За invalid_argument
#include <limits>    // За numeric_limits
#include <fstream>


using namespace std;

class Taxi{
private:
    int id;
    string brand, model;
    int year, capacity;
    double load_capacity, fuel_consumption;

public:
    Taxi(){}

    Taxi(int &id, string &brand, string &model, int &year, int &capacity, double &load_capacity, double &fuel_consumption){
        this->id = id;
        this->brand = brand;
        this->model = model;
        this->year = year;
        this->capacity = capacity;
        this->load_capacity = load_capacity;
        this->fuel_consumption = fuel_consumption;
    }

    friend ostream& operator<<(ostream& os, const Taxi& taxi){
        os << taxi.id << "\n";
        os << taxi.brand << "\n";
        os << taxi.model << "\n";
        os << taxi.year << "\n";
        os << taxi.capacity << "\n";
        os << taxi.load_capacity << "\n";
        os << taxi.fuel_consumption << "\n";

        return os;
    }

    friend istream& operator>>(istream& is, Taxi& taxi){
        int id;
        string brand, model;
        int year, capacity;
        double load_capacity, fuel_consumption;

        is >> id;
        is >> brand;
        is >> model;
        is >> year;
        is >> capacity;
        is >> load_capacity;
        is >> fuel_consumption;

        taxi.setId(id);
        taxi.setBrand(brand);
        taxi.setModel(model);
        taxi.setYear(year);
        taxi.setCapacity(capacity);
        taxi.setLoadCapacity(load_capacity);
        taxi.setFuelConsumption(fuel_consumption);

        return is;
    }

    int getId() const {
        return id;
    }

    string getBrand() const {
        return brand;
    }

    string getModel() const {
        return model;
    }

    int getCapacity() const {
        return capacity;
    }

    int getYear() const {
        return year;
    }

    double getLoadCapacity() const {
        return load_capacity;
    }

    int getFuelConsumption() const {
        return fuel_consumption;
    }

    void setId(int &id){
        this->id = id;
    }

    void setBrand(string &brand){
        this->brand = brand;
    }

     void setModel(string &model){
        this->model = model;
    }

    void setCapacity(int &capacity){
        this->capacity = capacity;
    }

    void setYear(int &year){
        this->year = year;
    }

    void setLoadCapacity(double &load_capacity){
        this->load_capacity = load_capacity;
    }

    void setFuelConsumption(double &fuel_consumption){
        this->fuel_consumption = fuel_consumption;
    }
};

class Route{
private:
    int id;
    string start_point, end_point;
    double distance;
    int daily_frequency;

public:
    Route(){}

    Route(int &id, string start_point, string end_point, double distance, int daily_frequency){
        this->id = id;
        this->start_point = start_point;
        this->end_point = end_point;
        this->distance = distance;
        this->daily_frequency = daily_frequency;
    }

    friend ostream& operator<<(ostream& os, const Route& route){
        os << route.id << "\n";
        os << route.start_point << "\n";
        os << route.end_point << "\n";
        os << route.distance << "\n";
        os << route.daily_frequency << "\n";
    }

    friend istream& operator>>(istream& is, Route& route){
        int id;
        string start_point, end_point;
        double distance;
        int daily_frequency;

        is >> id;
        is >> start_point;
        is >> end_point;
        is >> distance;
        is >> daily_frequency;

        route.setId(id);
        route.setStartPoint(start_point);
        route.setEndPoint(end_point);
        route.setDistance(distance);
        route.setDailyFrequency(daily_frequency);

        return is;
    }

    int getId() const{
        return id;
    }

    string getStartPoint() const {
        return start_point;
    }

    string getEndPoint() const {
        return end_point;
    }

    double getDistance() const {
        return distance;
    }

    int getDailyFrequency() const {
        return daily_frequency;
    }

    void setId(int &id){
        this->id = id;
    }

    void setStartPoint(string &start_point){
        this->start_point = start_point;
    }

    void setEndPoint(string &end_point){
        this->end_point = end_point;
    }

    void setDistance (double &distance){
        this->distance = distance;
    }

    void setDailyFrequency(int &daily_frequency){
        this->daily_frequency = daily_frequency;
    }

};


class TaxiApp{
private:
    vector<Taxi> taxis;
    vector<Route> routes;

public:
    //------------------------МЕНЮ--------------------------------
    int showMenu() {
        int choice;
        while (true){
            cout << "\nMenu:\n";
            cout << "0. Exit\n";
            cout << "1. Add Taxi\n";
            cout << "2. Add Route\n";
            cout << "3. Display Taxis\n";
            cout << "4. Display Routes\n";
            cout << "5. Select Taxi-Route\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addTaxiFromInput();
                    break;
                case 2:
                    addRouteFromInput();
                    break;
                case 3:
                    displayTaxis();
                    break;
                case 4:
                    displayRoutes();
                    break;
                case 5:
                    calculateRoutePrice();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    //-------------------------------------------------------------------------------------

    void displayTaxis() const {
        cout << "List of Taxis:---------------\n";
        for (const auto& taxi : taxis) {
            cout << "ID:          " << taxi.getId() << "\n";
            cout << "Brand:       " << taxi.getBrand() << "\n";
            cout << "Model        " << taxi.getModel() << "\n";
        }
        cout << "\n";
    }

    void displayRoutes() const {
        cout << "List of Routes:--------------\n";
        for (const auto& route : routes) {
            cout << "ID:          " << route.getId() << "\n";
            cout << "Start point: " << route.getStartPoint() << "\n";
            cout << "End poin:    " << route.getEndPoint() << "\n";
            cout << "Distance:    " << route.getDistance() << "\n";
        }
        cout << "\n";
    }

    void calculateFuelForRoute(int taxiIndex, int routeIndex) {
        if(taxiIndex < 0 || taxiIndex >= taxis.size()){
            cerr<< "Invalid index for taxi, try again! \n";
            return;
        }
        if(routeIndex < 0 || routeIndex >= routes.size()){
            cerr << "Invalid index for route, try again!\n";
            return;
        }

        Taxi selectedTaxi = taxis[taxiIndex];
        Route selectedRoute = routes[routeIndex];

        
    }

    void calculateRoutePrice(){
        int taxiId, routeId;
        Taxi taxi;
        Route route;

        cout << "Enter taxi ID:\n";
        cin >> taxiId;

        cout << "Enter route ID:\n";
        cin >> routeId;

        for(const Taxi &t: taxis){
            if (t.getId() == taxiId){
                taxi = t;
                break;
            }
        }
        if (taxi.getId() != taxiId ) {cout << "Taxi not found!\n"; return;}


        for(const Route &r: routes){
            if (r.getId() == routeId){
                route = r;
                break;
            }
        }
        if(route.getId() != routeId) {cout << "Route not found!\n"; return;}

        float requeredFuel = (route.getDistance() / taxi.getFuelConsumption()) * route.getDailyFrequency();
        cout << "For the selected route and taxi, you need " << requeredFuel << " liters fuel.\n";
        
    }


    void addTaxiFromInput() {
        int id;
        string brand, model;
        int year, capacity;
        double load_capacity, fuel_consumption;

        cout << "Enter Taxi Information:\n";
        cout << "Id: ";
        cin >> id;
        if(id < 100){
            cout<<"Id must be more than 100!\n";
            return;
        }

        cout << "Brand: ";
        cin >> brand;
        if(brand == ""){
            cout<<"Brand is not valid!\n";
            return;
        }
    
        cout << "Model: ";
        cin >> model;
        if(model == ""){
            cout<<"Model is not valid!\n";
            return;
        }

        cout << "Year: ";
        cin >> year;
        if(year < 1900 || year > 2023){
            cout<<"Year is not valid!\n";
            return;
        }

        cout << "Capacity: ";
        cin >> capacity;
        if (capacity > 4){
            cout<<"The car is for max four clients, not more!";
            return;
        }

        cout << "Load Capacity: ";
        cin >> load_capacity;
        if (load_capacity < 0.0){
            cout<<"Load capacity is not valid!\n";
            return;
        }
           
        
        cout << "Fuel Consumption: ";
        cin >> fuel_consumption;
        if (fuel_consumption < 0){
            cout<<"Fuel consumption is not valid!\n";
            return;
        }
        
        Taxi taxi(id, brand, model, year, capacity, load_capacity, fuel_consumption);
        taxis.push_back(taxi);
    }

    void addRouteFromInput() {
        int id;
        string start_point, end_point;
        float distance;
        int daily_frequency;

        cout << "Enter Route Information:\n";
        cout << "Id: ";
        cin >> id;
        if(id < 100){
            cout<<"Id must be more than 100!\n";
            return;
        }

        cout << "Start Point: ";
        cin >> start_point;
        if (start_point == ""){
            cout<<"Invalid start point!\n";
            return;
        }
        
        cout << "End Point: ";
        cin >> end_point;
        if(end_point == ""){
            cout<<"Invalid end point!\n";
            return;
        }

        cout << "Distance: ";
        cin >> distance;
        if(distance < 0){
            cout<<"Invalid distance, please enter a number bigger than 0!\n";
            return;
        }

        cout << "Daily Frequency: ";
        cin >> daily_frequency;
        if(daily_frequency < 0){
            cout << "Invalid input, please enter a number bigger than 0!\n";
            return;
        }

        Route route(id, start_point, end_point, distance, daily_frequency);
        routes.push_back(route);
    }


    //--------Файл---------------------------------
    void saveTaxiToFile(const string& filename) const {
        ofstream outputFile(filename);

        if (outputFile.is_open()) {
            for (const auto& taxi : taxis) {
                outputFile << taxi;
            }
            cout << "Data successfully saved to " << filename << "\n";
        } else {
            cerr << "Unable to open file: " << filename << "\n";
        }
    }

    void saveRouteToFile(const string& filename) const {
        ofstream outputFile(filename);

        if (outputFile.is_open()) {
            for (const auto& route : routes) {
                outputFile << route;
            }

            cout << "Data successfully saved to " << filename << "\n";
        } else {
            cerr << "Unable to open file: " << filename << "\n";
        }
    }

    void loadTaxiFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            taxis.clear();
            Taxi t;
            while (inputFile >> t) {
                taxis.push_back(t);
            }

            inputFile.close();
            cout << "Data successfully loaded from " << filename << "\n";
        } else {
            cerr << "Unable to open file: " << filename << "\n";
        }
    }

    void loadRouteFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            routes.clear();
            Route r;
            while (inputFile >> r) {
                routes.push_back(r);
            }
            
            inputFile.close();
            cout << "Data successfully loaded from " << filename << "\n";
        } else {
            cerr << "Unable to open file: " << filename << "\n";
        }
    }
    
}; 


int main() {
    TaxiApp taxiApp;
    int flag_escape = 1;
    while (true){
        taxiApp.loadTaxiFromFile("C:\\Users\\Айсел\\Desktop\\проект с++\\taxiData");
        taxiApp.loadRouteFromFile("C:\\Users\\Айсел\\Desktop\\проект с++\\routeData");

        flag_escape = taxiApp.showMenu();

        taxiApp.saveTaxiToFile("C:\\Users\\Айсел\\Desktop\\проект с++\\taxiData");
        taxiApp.saveRouteToFile("C:\\Users\\Айсел\\Desktop\\проект с++\\routeData");
        
        if (flag_escape == 0){
            return 0;
        }
    }
};


