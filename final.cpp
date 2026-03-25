#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Colors for terminal text on white background
#define PINK "\033[95m"
#define GREEN "\033[92m"
#define RESET "\033[0m"
#define WHITE_BG "\033[107m" // White background

struct BillEntry {
    string customer;
    double hours;
    double total;
};

vector<BillEntry> billHistory;
const double RATE_PER_HOUR = 50.0; // Fixed rate per hour

// Function to save bills to file
void saveBillsToFile() {
    ofstream file("bills.txt");
    if (!file.is_open()) {
        cout << GREEN << "Error saving to file!" << RESET << endl;
        return;
    }
    double grandTotal = 0;
    int count = 1;
for (auto &b : billHistory){
        file << count << ". " << b.customer << ": " << b.hours 
             << " hrs x KES " << RATE_PER_HOUR << " = KES " << fixed << setprecision(2) << b.total << endl;
        grandTotal += b.total;
        count++;
    }
    file << "Grand Total: KES " << fixed << setprecision(2) << grandTotal << endl;
    file.close();
    cout << GREEN << "Bills saved to bills.txt 💾" << RESET << endl;
}

// Add a new bill
void addBill(const string& customer, double hours) {
    double total = hours * RATE_PER_HOUR;
    billHistory.push_back({customer, hours, total});
    cout << PINK << WHITE_BG << "Added Bill: " << customer 
         << " - " << hours << " hrs, Total: KES " 
         << fixed << setprecision(2) << total << RESET << endl;
}

// Rollback last bill
void rollbackBill() {
    if (!billHistory.empty()) {
        BillEntry last = billHistory.back();
        billHistory.pop_back();
        cout << GREEN << WHITE_BG << "Rolled back last bill: " << last.customer 
             << " - KES " << fixed << setprecision(2) << last.total << RESET << endl;
    } else {
        cout << GREEN << WHITE_BG << "No bills to rollback!" << RESET << endl;
    }
}

// Show all bills
void showBills() {
    cout << PINK << WHITE_BG << "\n--- BILL HISTORY ---" << RESET << endl;
    if (billHistory.empty()) {
        cout << GREEN << WHITE_BG << "No bills yet!" << RESET << endl;
        return;
    }

    double grandTotal = 0;
    int count = 1;
    for (auto &b : billHistory) {
        cout << GREEN << WHITE_BG << count << ". " << b.customer << ": " 
             << b.hours << " hrs x KES " << RATE_PER_HOUR 
             << " = KES " << fixed << setprecision(2) << b.total << RESET << endl;
        grandTotal += b.total;
        count++;
    }
    cout << PINK << WHITE_BG << "Grand Total: KES " << fixed << setprecision(2) << grandTotal << RESET << endl;
}

int main() {
    int choice;
    string name;
    double hours;

    cout << PINK << WHITE_BG << "💖 Welcome to the Billing System 💚" << RESET << endl;

    do {
        cout << PINK << WHITE_BG << "\n1. Add Bill\n2. Rollback Last Bill\n3. Show Bills\n4. Save Bills to File\n5. Exit\nChoose: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << GREEN << WHITE_BG << "Customer Name: " << RESET;
                cin.ignore();
                getline(cin, name);
                cout << GREEN << WHITE_BG << "Hours spent: " << RESET;
                cin >> hours;
                addBill(name, hours);
                break;
            case 2:
                rollbackBill();
                break;
            case 3:
                showBills();
                break;
            case 4:
                saveBillsToFile();
                break;
            case 5:
                cout << PINK << WHITE_BG << "Goodbye! 💖" << RESET << endl;
                break;
            default:
                cout << GREEN << WHITE_BG << "Invalid choice!" << RESET << endl;
        }
    } while (choice != 5);

    return 0;
}7