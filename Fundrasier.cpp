//
// Created by Rohil Shah on 10/25/24.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to hold donor details
struct Donor {
    string name;
    double amount;
};

// Function prototypes
void addDonation(vector<Donor>& donors);
void viewTotalDonations(const vector<Donor>& donors);
void showDonorList(const vector<Donor>& donors);

int main() {
    vector<Donor> donors;
    int choice;

    do {
        cout << "\n--- Fundraiser Program ---\n";
        cout << "1. Add Donation\n";
        cout << "2. View Total Donations\n";
        cout << "3. Show Donor List\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addDonation(donors);
                break;
            case 2:
                viewTotalDonations(donors);
                break;
            case 3:
                showDonorList(donors);
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void addDonation(vector<Donor>& donors) {
    Donor newDonor;
    cout << "Enter donor's name: ";
    cin >> ws; // to consume any leading whitespace
    getline(cin, newDonor.name);
    cout << "Enter donation amount: ";
    cin >> newDonor.amount;

    donors.push_back(newDonor);
    cout << "Donation added successfully!\n";
}

void viewTotalDonations(const vector<Donor>& donors) {
    double total = 0;
    for (const auto& donor : donors) {
        total += donor.amount;
    }
    cout << "Total Donations: $" << total << endl;
}

void showDonorList(const vector<Donor>& donors) {
    if (donors.empty()) {
        cout << "No donations yet.\n";
        return;
    }

    cout << "\n--- Donor List ---\n";
    for (const auto& donor : donors) {
        cout << donor.name << " donated $" << donor.amount << endl;
    }
}


