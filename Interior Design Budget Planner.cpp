// Project: Interior Design Budget Planner
// Student: Aliyah Growe
// Date: July 31, 2025
// Description: This program allows the user to track 
// and manage their budget for any interior design or 
// renovation project

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm> // for remove

using namespace std;

// Struct to represent an expense entry
struct Expense {
    string category;    // Expense category (e.g., Furniture, Paint)
    string itemName;    // Name of the item purchased
    int quantity;       // Number of items bought
    double costPerItem; // Cost for one item
    double totalCost;   // quantity * costPerItem
};

vector<Expense> expensesList; // List holding all expenses
double totalBudget = 0.0;     // User’s total budget for the project

// Function to set the total budget with optional $ sign input
void setBudget() {
    string input;
    cout << "\nEnter total budget: ";
    cin >> ws;
    getline(cin, input);

    // Remove dollar sign if present
    input.erase(remove(input.begin(), input.end(), '$'), input.end());

    stringstream ss(input);
    double value;
    ss >> value;

    if (!ss.fail() && value > 0) {
        totalBudget = value;
        cout << "\nBudget successfully set!\n";
    }
    else {
        cout << "\nInvalid budget amount.\n";
    }
}

// Function to add a new expense, cost input accepts $ sign
void addExpense() {
    Expense exp;
    string costInput;

    cout << "\nEnter category: ";
    cin >> ws;
    getline(cin, exp.category);
    cout << "Enter item name: ";
    getline(cin, exp.itemName);

    // Validate quantity input
    while (true) {
        cout << "Enter quantity: ";
        if (cin >> exp.quantity && exp.quantity > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard rest of the line
            break;
        }
        else {
            cout << "\nInvalid input. Quantity must be a positive integer.\n";
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        }
    }

    // Validate cost per item input
    while (true) {
        cout << "Enter cost per item: ";
        getline(cin, costInput);

        // Remove dollar sign if present
        costInput.erase(remove(costInput.begin(), costInput.end(), '$'), costInput.end());

        stringstream ss(costInput);
        if (ss >> exp.costPerItem && exp.costPerItem >= 0) {
            // Check if there is no trailing garbage in the input after the number
            char leftover;
            if (!(ss >> leftover)) {
                break; // valid input
            }
        }
        cout << "\nInvalid input. Cost per item must be a non-negative number.\n";
    }

    exp.totalCost = exp.quantity * exp.costPerItem;
    expensesList.push_back(exp);
    cout << "\nExpense successfully added!\n";
}

// Function to edit an existing expense selected by index
void editExpense() {
    if (expensesList.empty()) {
        cout << "No expenses to edit.\n";
        return;
    }

    // List all expenses with indices
    for (size_t i = 0; i < expensesList.size(); ++i) {
        cout << i << ": " << expensesList[i].itemName << " - $" << expensesList[i].totalCost << '\n';
    }

    int index;
    while (true) {
        cout << "\nEnter expense number to edit: ";
        if (cin >> index) {
            if (index >= 0 && index < static_cast<int>(expensesList.size())) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                break; // valid input
            }
            else {
                cout << "\nInvalid selection. Please enter a valid expense number.\n";
            }
        }
        else {
            cout << "\nInvalid selection. Please enter a valid expense number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Expense& exp = expensesList[index];
    string costInput;

    cout << "\nEnter new category: ";
    cin >> ws;
    getline(cin, exp.category);
    cout << "Enter new item name: ";
    getline(cin, exp.itemName);

    // Validate new quantity
    while (true) {
        cout << "Enter new quantity: ";
        if (cin >> exp.quantity && exp.quantity > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard rest of the line
            break;
        }
        else {
            cout << "\nInvalid input. Quantity must be a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Validate new cost per item
    while (true) {
        cout << "Enter new cost per item: ";
        getline(cin, costInput);

        // Remove dollar sign if present
        costInput.erase(remove(costInput.begin(), costInput.end(), '$'), costInput.end());

        stringstream ss(costInput);
        if (ss >> exp.costPerItem && exp.costPerItem >= 0) {
            char leftover;
            if (!(ss >> leftover)) {
                break; // valid input
            }
        }
        cout << "\nInvalid input. Cost per item must be a non-negative number.\n";
    }

    exp.totalCost = exp.quantity * exp.costPerItem;
    cout << "\nExpense successfully edited!\n";
}

// Function to delete an expense by index
void deleteExpense() {
    if (expensesList.empty()) {
        cout << "No expenses to delete.\n";
        return;
    }

    for (size_t i = 0; i < expensesList.size(); ++i) {
        cout << i << ": " << expensesList[i].itemName << " - $" << expensesList[i].totalCost << '\n';
    }

    int index;
    while (true) {
        cout << "Enter expense number to delete: ";
        if (cin >> index) {
            if (index >= 0 && index < static_cast<int>(expensesList.size())) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
                break; // valid input
            }
            else {
                cout << "\nInvalid selection. Please enter a valid expense number.\n";
            }
        }
        else {
            cout << "\nInvalid input.Please enter a valid integer.\n";
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        }
    }

    expensesList.erase(expensesList.begin() + index);
    cout << "\nExpense successfully deleted!\n";
}

// Function to display a summary of all expenses and budget status
void viewSummary() {
    if (expensesList.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    double totalSpent = 0.0;
    cout << fixed << setprecision(2);

    cout << "=====================================\n";
    cout << "           EXPENSE SUMMARY\n";
    cout << "=====================================\n";

    for (const Expense& exp : expensesList) {
        cout << "\n-------------------------------------\n";
        cout << "Category : " << exp.category << "\n";
        cout << "Item     : " << exp.itemName << "\n";
        cout << "Quantity : " << exp.quantity << "\n";
        cout << "Cost per item: $" << exp.costPerItem << "\n";
        cout << "Total    : $" << exp.totalCost << "\n";
        totalSpent += exp.totalCost;
    }

    cout << "\n=====================================\n";
    cout << "Total Spent      : $" << totalSpent << "\n";
    cout << "Total Budget     : $" << totalBudget << "\n";

    if (totalSpent > totalBudget) {
        cout << "\nOVER BUDGET by $" << totalSpent - totalBudget << "!\n";
    }
    else {
        cout << "\nRemaining Budget: $" << totalBudget - totalSpent << "\n";
    }
    cout << "=====================================\n";
}

// Function to save budget and expenses to a file
void saveToFile() {
    string filename;
    cout << "\nEnter filename to save (file can also be created if needed): ";
    getline(cin, filename);  // Use getline to read filename, so no leftover newline

    ofstream outFile(filename);
    if (!outFile) {
        cout << "\nError opening file for writing.\n";
        return;
    }

    outFile << totalBudget << '\n';
    outFile << expensesList.size() << '\n';

    for (const Expense& exp : expensesList) {
        outFile << exp.category << '\n'
            << exp.itemName << '\n'
            << exp.quantity << '\n'
            << exp.costPerItem << '\n'
            << exp.totalCost << '\n';
    }

    outFile.close();
    cout << "\nData saved successfully!\n";
}

// Function to load budget and expenses from a file
void loadFromFile() {
    string filename;
    cout << "Enter filename to load: ";
    cin >> filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

    ifstream inFile(filename);
    if (!inFile) {
        cout << "\nError opening file for reading.\n";
        return;  // Immediately return to main menu
    }

    expensesList.clear();
    size_t count;
    inFile >> totalBudget >> count;
    inFile.ignore();

    for (size_t i = 0; i < count; ++i) {
        Expense exp;
        getline(inFile, exp.category);
        getline(inFile, exp.itemName);
        inFile >> exp.quantity >> exp.costPerItem >> exp.totalCost;
        inFile.ignore();
        expensesList.push_back(exp);
    }

    inFile.close();
    cout << "\nData loaded successfully!\n";
}

// Welcome message along with the main menu of the program
int main() {
    cout << "==================================================\n";
    cout << "  Welcome to the Interior Design Budget Planner!\n";
    cout << "==================================================\n";
    cout << "  Plan, track, and manage your renovation budget\n";

    int choice;

    do {
        cout << "\n-------------------------\n";
        cout << "        MAIN MENU\n";
        cout << "-------------------------\n";
        cout << "1. Set Budget\n";
        cout << "2. Add an Expense\n";
        cout << "3. Edit an Expense\n";
        cout << "4. Delete an Expense\n";
        cout << "5. View Spending Summary\n";
        cout << "6. Save Data to File\n";
        cout << "7. Load Data from File\n";
        cout << "8. Exit Program\n";
        cout << "------------------------\n";
        cout << "\nEnter your choice: ";

        string input;
        getline(cin, input); // Read entire line to handle any characters
        stringstream ss(input);

        if (!(ss >> choice) || choice < 1 || choice > 8) {
            cout << "\nInvalid choice. Please try again.\n";
            continue; // Restart the loop without executing switch-case

        }

        switch (choice) {
        case 1: setBudget(); break;
        case 2: addExpense(); break;
        case 3: editExpense(); break;
        case 4: deleteExpense(); break;
        case 5: viewSummary(); break;
        case 6: saveToFile(); break;
        case 7: loadFromFile(); break;
        case 8:
            cout << "\nThank you for using the Budget Planner. Goodbye!\n";
            break;
        }
    } while (choice != 8);

    return 0;
}