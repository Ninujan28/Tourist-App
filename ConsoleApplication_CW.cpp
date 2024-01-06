// ConsoleApplication_CW.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Base class
class Attraction {
protected:
    std::string name;
    int openingTime; // in 24-hour format
    int closingTime; // in 24-hour format

public:
    Attraction(std::string name, int openingTime, int closingTime)
        : name(name) , openingTime(openingTime), closingTime(closingTime) {}

    virtual double getAdmittancePrice() const = 0;

    bool isOpenAfter1900() const {
        return closingTime > 1900;
    }

    std::string getName() const {
        return name;
    }

    void displayInfo() const {
        std::cout << "Attraction: " << name
            << ", Opening Time: " << openingTime
            << ", Closing Time: " << closingTime << std::endl;
    }
};

// Subclass for Parks
class Park : public Attraction {
public:
    Park(std::string name,int openingTime, int closingTime)
        : Attraction(name, openingTime, closingTime) {}

    double getAdmittancePrice() const override {
        return 0.0; // Parks are free
    }
};

// Subclass for Museums
class Museum : public Attraction {
private:
    double admissionFee;

public:
    Museum(std::string name,int openingTime, int closingTime, double fee)
        : Attraction(name , openingTime, closingTime), admissionFee(fee) {}

    double getAdmittancePrice() const override {
        return admissionFee;
    }
};

// Subclass for Theatres
class Theatre : public Attraction {
private:
    double ticketPrice;

public:
    Theatre(std::string name, int openingTime, int closingTime, double price)
        : Attraction(name,openingTime, closingTime), ticketPrice(price) {}

    double getAdmittancePrice() const override {
        return ticketPrice;
    }
};

void customerMenu(const std::vector<std::shared_ptr<Attraction>>& attractions);
void viewAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions);
void searchForAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions);

void customerMenu(const std::vector<std::shared_ptr<Attraction>>& attractions) {
    int choice;

    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. View Attractions\n";
        std::cout << "2. Search for Attractions\n";
        std::cout << "3. Attractions are open after 1900 and cost less than 5GBP\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewAttractions(attractions);
            break;
        case 2:
            searchForAttractions(attractions);
            break;

        case 3:
            
            for (const auto& attraction : attractions) {
                if (attraction->isOpenAfter1900() && attraction->getAdmittancePrice() < 5.0) {
                    std::cout << attraction->getName() << " is open after 1900 and costs less than 5GBP." << std::endl;
                   
                    
                }

            }

            break;
            

        case 4:
            std::cout << "Exiting Application.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void viewAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions) {
    std::cout << "View Attractions\n";
    for (const auto& attraction : attractions) {
        attraction->displayInfo();
    }
}

void searchForAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions) {
    std::cout << "Search for Attractions (Enter keyword): ";
    std::string keyword;
    std::cin >> keyword;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

    bool found = false;
    for (const auto& attraction : attractions) {
        if (attraction->getName().find(keyword) != std::string::npos) {
            //std::cout << attraction->getName() << "\n";
            attraction->displayInfo();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No attractions found with the keyword '" << keyword << "'.\n";
    }
}
// Function prototypes
void adminMenu();
void addNewAttraction(std::vector<std::shared_ptr<Attraction>>& attractions);
//void updateExistingAttraction(std::vector<std::shared_ptr<Attraction>>& attractions);
void deleteAttraction(std::vector<std::shared_ptr<Attraction>>& attractions);
void viewAllAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions);


void adminMenu(std::vector<std::shared_ptr<Attraction>>& attractions) {
    // Modified adminMenu to take attractions as argument
    int choice;

    do {
        std::cout << "\nAdmin Menu:\n";
        std::cout << "1. Add New Attraction\n";
        std::cout << "2. Delete Attraction\n";
        std::cout << "3. View All Attractions\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addNewAttraction(attractions);
            break;
        case 2:
            deleteAttraction(attractions);
            break;
        case 3:
            viewAllAttractions(attractions);
            break;
        case 4:
            std::cout << "Exiting Admin Menu.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void addNewAttraction(std::vector<std::shared_ptr<Attraction>>& attractions) {
    std::string name;
    int openingTime, closingTime;

    std::cout << "Enter name of the attraction: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter opening time (24-hour format): ";
    std::cin >> openingTime;
    std::cout << "Enter closing time (24-hour format): ";
    std::cin >> closingTime;

    // Creating a Park instance for simplicity. You can modify this to create other types.
    auto attraction = std::make_shared<Park>(name, openingTime, closingTime);
    attractions.push_back(attraction);
    std::cout << "Attraction added successfully.\n";
    //Like this can add for Theatre & Museum
}

void updateExistingAttraction(std::vector<std::shared_ptr<Attraction>>& attractions) {
    // Implementation for updating an existing attraction
    std::cout << "Update Existing Attraction\n";
    // You will need to add specific implementation details here
}

void deleteAttraction(std::vector<std::shared_ptr<Attraction>>& attractions) {
    // Implementation for deleting an attraction
    std::cout << "Delete Attraction\n";
    std::string name;
    std::cout << "Enter name of the attraction to delete: ";
    std::getline(std::cin >> std::ws, name);

    auto it = std::remove_if(attractions.begin(), attractions.end(),
        [&name](const std::shared_ptr<Attraction>& attraction) {
            return attraction->getName() == name;
        });

    if (it != attractions.end()) {
        attractions.erase(it, attractions.end());
        std::cout << "Attraction deleted successfully.\n";
    }
    else {
        std::cout << "Attraction not found.\n";
    }
}

void viewAllAttractions(const std::vector<std::shared_ptr<Attraction>>& attractions) {
    // Implementation for viewing all attractions
    std::cout << "View All Attractions\n";
    if (attractions.empty()) {
        std::cout << "No attractions available.\n";
        return;
    }

    std::cout << "List of Attractions:\n";
    for (const auto& attraction : attractions) {
        attraction->displayInfo();
    }
}


int main() {
    std::vector<std::shared_ptr<Attraction>> attractions = {
        std::make_shared<Park>("Hyde Park", 600, 2200),
        std::make_shared<Park>("Greenwich Park", 600, 2400),
        std::make_shared<Park>("The Regent's Park", 800, 2000),
        std::make_shared<Park>("St James's Park", 600, 2200),
        std::make_shared<Park>("Kensington Gardens", 800, 1700),
        std::make_shared<Park>("Crystal Palace Park", 1000, 2200),

        std::make_shared<Museum>("British Museum", 1000, 1800, 0.0),
        std::make_shared<Museum>("Natural History Museum", 900, 1700, 4.0),
        std::make_shared<Museum>("Science Museum", 1000, 1900, 6.0),
        std::make_shared<Museum>("National Maritime Museum", 1000, 1900, 6.0),
        std::make_shared<Museum>("The National Gallery", 1600, 2100, 10.0),

        std::make_shared<Theatre>("Royal Opera House", 1200, 2300, 10.0),
        std::make_shared<Theatre>("Palace Theatre", 800, 1800, 4.0),
        std::make_shared<Theatre>("Union Theatre", 1100, 2300, 8.0),
        std::make_shared<Theatre>("Jermyn Street Theatre", 1000, 2100, 10.0),
        std::make_shared<Theatre>("Aldwych Theatre", 900, 2200, 15.0),
    };

    int choice;
    std::cout << "Welcome to the Attraction Management System" << std::endl;
    std::cout << "1. Customer Menu\n2. Admin Menu\nEnter choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        customerMenu(attractions);
        break;
    case 2:
        adminMenu(attractions); // Pass attractions to adminMenu
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
    }

    return 0;
}

    /*

    // Iterate over the list to find attractions open after 1900 and costing less than £5
    for (const auto& attraction : attractions) {
        if (attraction->isOpenAfter1900() && attraction->getAdmittancePrice() < 5.0) {
            std::cout << attraction->getName() << " is open after 1900 and costs less than £5." << std::endl;
        }
    }

    return 0;
    */





/*
#include <iostream>
#include <string>
#include <vector>

class Attraction {
public:
    Attraction(const std::string& name, int openingTime, int closingTime)
        : name(name), openingTime(openingTime), closingTime(closingTime) {}

    virtual ~Attraction() {}

    virtual float getAdmittancePrice() const = 0;
    virtual std::string getType() const = 0;

    void displayInfo() const {
        std::cout << "Attraction: " << name << std::endl;
        std::cout << "Type: " << getType() << std::endl;
        std::cout << "Admittance Price: " << getAdmittancePrice() << std::endl;
        std::cout << "Opening Time: " << openingTime << std::endl;
        std::cout << "Closing Time: " << closingTime << std::endl;
    }

    bool isOpenAfter1900() const {
        return closingTime > 1900;
    }

    bool isAffordable() const {
        return getAdmittancePrice() < 5.0;
    }

protected:
    std::string name;
    int openingTime;
    int closingTime;
};

class Park : public Attraction {
public:
    Park(const std::string& name, int openingTime, int closingTime)
        : Attraction(name, openingTime, closingTime) {}

    float getAdmittancePrice() const override {
        return 0.0; // Parks have free admittance
    }

    std::string getType() const override {
        return "Park";
    }
};

class Museum : public Attraction {
public:
    Museum(const std::string& name, int openingTime, int closingTime, float admittancePrice)
        : Attraction(name, openingTime, closingTime), admittancePrice(admittancePrice) {}

    float getAdmittancePrice() const override {
        return admittancePrice;
    }

    std::string getType() const override {
        return "Museum";
    }

private:
    float admittancePrice;
};

class Theatre : public Attraction {
public:
    Theatre(const std::string& name, int openingTime, int closingTime, float admittancePrice)
        : Attraction(name, openingTime, closingTime), admittancePrice(admittancePrice) {}

    float getAdmittancePrice() const override {
        return admittancePrice;
    }

    std::string getType() const override {
        return "Theatre";
    }

private:
    float admittancePrice;
};

int main() {
    std::vector<Attraction*> attractions;

    attractions.push_back(new Park("Hyde Park", 800, 1800));
    attractions.push_back(new Museum("British Museum", 900, 1700, 10.0));
    attractions.push_back(new Theatre("West End Theatre", 1900, 2300, 50.0));

    // Find attractions open after 1900 and costing less than £5
    for (const auto& attraction : attractions) {
        if (attraction->isOpenAfter1900() && attraction->isAffordable()) {
            std::cout << "Attraction meeting criteria:" << std::endl;
            attraction->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }

    // Clean up allocated memory
    for (const auto& attraction : attractions) {
        delete attraction;
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/