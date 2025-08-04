// Project: Interior Design Budget Planner
// Student: Aliyah Growe
// Date: July 31, 2025
// Description: This program allows the user to track and manage their 
// budget for interior design or home renovation projects. It supports 
// expense entry by category (e.g., Furniture, Paint, Lighting), and 
// enables users to save and load their data for future planning.

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

// Struct representing an interior design expense
struct Expense {
    string category;    // e.g., Furniture, Paint, Lighting
    string itemName;    // Name of purchased item
    int quantity;       // Number of items purchased
    double costPerItem; // Cost of one item
    double totalCost;   // quantity * costPerItem
};

vector<Expense> expensesList;
double totalBudget = 0.0;

// Prompt user to set a total budget
void setBudget() {
    string input;
    cout << "\nEnter total design project budget (e.g., $3000): ";
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), '$'), input.end());

    stringstream ss(input);
    double value;
    ss >> value;

    if (!ss.fail() && value > 0) {
        totalBudget = value;
        cout << "\nBudget successfully set to $" << fixed << setprecision(2) << totalBudget << "!\n";
    }
    else {
        cout << "\nInvalid budget amount. Please enter a positive number.\n";
    }
}

// Add a new interior design expense
void addExpense() {
    Expense exp;
    string costInput;

    cout << "\nEnter category (e.g., Furniture, Paint, Lighting): ";
    getline(cin, exp.category);

    while (!exp.category.empty() && all_of(exp.category.begin(), exp.category.end(), ::isdigit)) {
        cout << "\nInvalid input. Category must be a word (e.g., Furniture): ";
        getline(cin, exp.category);
    }

    cout << "Enter item name (e.g., Sofa, Wall Paint): ";
    getline(cin, exp.itemName);

    while (true) {
        cout << "Enter quantity: ";
        if (cin >> exp.quantity && exp.quantity > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Invalid input. Quantity must be a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Enter cost per item (e.g., $150): ";
        getline(cin, costInput);
        costInput.erase(remove(costInput.begin(), costInput.end(), '$'), costInput.end());

        stringstream ss(costInput);
        if (ss >> exp.costPerItem && exp.costPerItem >= 0) {
            char leftover;
            if (!(ss >> leftover)) break;
        }
        cout << "Invalid input. Please enter a non-negative number.\n";
    }

    exp.totalCost = exp.quantity * exp.costPerItem;
    expensesList.push_back(exp);
    cout << "\nExpense successfully added!\n";
}

// Edit an existing expense
void editExpense() {
    if (expensesList.empty()) {
        cout << "\nNo design expenses to edit.\n";
        return;
    }

    for (size_t i = 0; i < expensesList.size(); ++i) {
        cout << i << ": " << expensesList[i].itemName << " - $" << expensesList[i].totalCost << '\n';
    }

    int index;
    while (true) {
        cout << "Enter the number of the expense you want to edit: ";
        if (cin >> index && index >= 0 && index < static_cast<int>(expensesList.size())) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "Invalid selection. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Expense& exp = expensesList[index];
    string costInput;

    cout << "\nEnter new category: ";
    getline(cin, exp.category);
    while (!exp.category.empty() && all_of(exp.category.begin(), exp.category.end(), ::isdigit)) {
        cout << "Invalid input. Category must be a word (e.g., Furniture): ";
        getline(cin, exp.category);
    }

    cout << "Enter new item name: ";
    getline(cin, exp.itemName);

    while (true) {
        cout << "Enter new quantity: ";
        if (cin >> exp.quantity && exp.quantity > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "Invalid quantity. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter new cost per item: ";
        getline(cin, costInput);
        costInput.erase(remove(costInput.begin(), costInput.end(), '$'), costInput.end());

        stringstream ss(costInput);
        if (ss >> exp.costPerItem && exp.costPerItem >= 0) {
            char leftover;
            if (!(ss >> leftover)) break;
        }
        cout << "Invalid input. Please enter a valid number.\n";
    }

    exp.totalCost = exp.quantity * exp.costPerItem;
    cout << "\nExpense successfully updated!\n";
}

// Delete a design expense
void deleteExpense() {
    if (expensesList.empty()) {
        cout << "\nNo design expenses to delete.\n";
        return;
    }

    for (size_t i = 0; i < expensesList.size(); ++i) {
        cout << i << ": " << expensesList[i].itemName << " - $" << expensesList[i].totalCost << '\n';
    }

    int index;
    while (true) {
        cout << "Enter the number of the expense to delete: ";
        if (cin >> index && index >= 0 && index < static_cast<int>(expensesList.size())) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "Invalid input. Please try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    expensesList.erase(expensesList.begin() + index);
    cout << "\nExpense successfully deleted!\n";
}

// View a full project summary
void viewSummary() {
    if (expensesList.empty()) {
        cout << "\nNo design expenses recorded yet.\n";
        return;
    }

    double totalSpent = 0.0;
    cout << fixed << setprecision(2);

    cout << "\n==========================================\n";
    cout << "     INTERIOR DESIGN BUDGET SUMMARY\n";
    cout << "==========================================\n";

    for (const Expense& exp : expensesList) {
        cout << "\n------------------------------------------\n";
        cout << "Category     : " << exp.category << "\n";
        cout << "Item         : " << exp.itemName << "\n";
        cout << "Quantity     : " << exp.quantity << "\n";
        cout << "Cost per item: $" << exp.costPerItem << "\n";
        cout << "Total cost   : $" << exp.totalCost << "\n";
        totalSpent += exp.totalCost;
    }

    cout << "\n==========================================\n";
    cout << "Total Spent      : $" << totalSpent << "\n";
    cout << "Total Budget     : $" << totalBudget << "\n";

    if (totalSpent > totalBudget) {
        cout << "\nOVER BUDGET by $" << totalSpent - totalBudget << "!\n";
    }
    else {
        cout << "Remaining Budget : $" << totalBudget - totalSpent << "\n";
    }

    cout << "==========================================\n";
}

// Save current data to file
void saveToFile() {
    string filename;
    cout << "\nEnter filename to save design budget (e.g., project.txt): ";
    getline(cin, filename);

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
    cout << "\nDesign project data saved successfully.\n";
}

// Load previous data from file
void loadFromFile() {
    string filename;
    cout << "\nEnter filename to load saved design budget: ";
    getline(cin, filename);

    ifstream inFile(filename);
    if (!inFile) {
        cout << "\nError opening file for reading.\n";
        return;
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
    cout << "\nDesign project data loaded successfully.\n";
}

// Main menu
int main() {
    cout << "==================================================\n";
    cout << "   Welcome to the Interior Design Budget Planner\n";
    cout << "==================================================\n";
    cout << "  Track and manage your renovation or decorating\n";
    cout << "  expenses, room by room and item by item.\n";

    int choice;

    do {
        cout << "\n--------------------------\n";
        cout << "          MAIN MENU\n";
        cout << "--------------------------\n";
        cout << "1. Set Project Budget\n";
        cout << "2. Add a Design Expense\n";
        cout << "3. Edit a Design Expense\n";
        cout << "4. Delete a Design Expense\n";
        cout << "5. View Project Summary\n";
        cout << "6. Save Project to File\n";
        cout << "7. Load Project from File\n";
        cout << "8. Exit Program\n";
        cout << "--------------------------\n";
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> choice) || choice < 1 || choice > 8) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        switch (choice) {
        case 1: setBudget(); break;
        case 2: addExpense(); break;
        case 3: editExpense(); break;
        case 4: deleteExpense(); break;
        case 5: viewSummary(); break;
        case 6: saveToFile(); break;
        case 7: loadFromFile(); break;
        case 8: cout << "\nThank you for using the Interior Design Budget Planner. Goodbye!\n"; break;
        }

    } while (choice != 8);

    return 0;
}