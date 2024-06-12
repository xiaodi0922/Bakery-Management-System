#define NOMINMAX

#include <iostream>
#include <iomanip>
#include <cctype>
#include <regex>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <mysql.h> //libmysql
#include <ctime> // Include this header for date and time functions
#include <chrono>
#include <thread>
#include <limits>
#include <fstream>


using namespace std;
void MainMenu();
void AdminMainMenu();
void AdminLogin();

void AdminRegistration();
void AdminMenu();


void AdminRecord();
void UpdateAdmin();
void DeleteAdmin();
void DisplayAdmin();
void SearchAdmin();

void EmployeeRecord();
void AddEmployee();
void DeleteEmployee();
void SearchEmployee();
void UpdateEmployee();
void DisplayEmployee();

void CustomerRecord() {
    cout << "k";
}
void CustomerMenu();
void AddCustomer();
void UpdateCustomer();
void DeleteCustomer();
void SearchCustomer();
void DisplayCustomer();

void SupplierRecord();
void SupplierMenu();
void AddSupplier();
void UpdateSupplier();
void DeleteSupplier();
void SearchSupplier();
void DisplaySupplier();
void SupplierRecord();

void ProductRecord() {
    cout << "s";
}
void ProductMenu();

void AddProduct();
void UpdateProduct();
void UpdateProductQuantity(const std::string& productId);
void UpdateProductPrice(const std::string& productId);
void DeleteProduct();
void SearchProduct();
void StockInformation();

void DisplayAllProducts();

void FilterLowStock();
void CalculateTotalInventoryValue();




void OrderRecord();
void OrderMenu();
void AddOrder();
void UpdateOrder();
void DeleteOrder();
void SearchOrder();
void DisplayOrder();

void Report();
void ProductSales();
void SalesMenu();
void YearlySales();
void MonthlySales();
void ViewTopSellingProducts();
void ViewLowSellingProducts();


void EmployeeMainMenu();


void EmployeeLogin();

void EmployeeRegistration();
void EmployeeMenu();
// Function to clear the current input line
void ClearLastLine() {
    cout << "\033[F\033[K";  // Move cursor up one line and clear line
}
void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}







bool Email_check(string emailAddress) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(emailAddress, pattern);
}
// Function to validate the date format
bool isValidDateFormat(const std::string& date) {
    std::regex dateFormat("^(\\d{4})-(0?[1-9]|1[0-2])-(0?[1-9]|[1-2][0-9]|3[0-1])$");
    return std::regex_match(date, dateFormat);
}




int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;



class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "bakerymanagement", 3306, NULL, 0);
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};


int main() {
    system("cls");
    system("title My Project");
    db_response::ConnectionFunction();
    MainMenu();


    return 0;
}


void ExecuteSearchQuery(const string& query) {
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        // Display column headers with horizontal lines
        cout << left << setw(20) << "Product ID"
            << setw(30) << "Product Name"
            << setw(20) << "Price"
            << setw(15) << "Quantity"
            << setw(15) << "Supplier ID" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;

        // Display product data with horizontal lines
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0]
                << setw(35) << row[1]
                << setw(24) << row[2]
                << setw(15) << row[3]
                << setw(15) << row[4] << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
    }

}
bool CheckAdminExistence(const std::string& adminId) {
    // Your SQL query to check the existence of the product in the database
    string query = "SELECT COUNT(*) AS count FROM admin WHERE AdminID = '" + adminId + "'";

    // Execute the query and fetch the result to determine product existence
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (product exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckProductExistence(const std::string& productId) {
    // Your SQL query to check the existence of the product in the database
    string query = "SELECT COUNT(*) AS count FROM product WHERE ProductID = '" + productId + "'";

    // Execute the query and fetch the result to determine product existence
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (product exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckCustomerExistence(const std::string& customerId) {
    // SQL query to check if the customer exists in the database
    string query = "SELECT COUNT(*) AS count FROM customer WHERE CustomerID = '" + customerId + "'";

    // Execute the query and determine the existence of the customer
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (customer exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckEmployeeExistence(const std::string& employeeID) {
    // SQL query to check if the employee exists in the database
    std::string query = "SELECT COUNT(*) AS count FROM employee WHERE EmployeeID = '" + employeeID + "'";

    // Execute the query and determine the existence of the employee
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (employee exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckOrderExistence(const std::string& orderID) {
    // SQL query to check if the order exists in the database
    std::string query = "SELECT COUNT(*) AS count FROM `order` WHERE OrderID = '" + orderID + "'";

    // Execute the query and determine the existence of the order
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (order exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckSupplierExistence(const std::string& supplierID) {
    // SQL query to check if the order exists in the database
    std::string query = "SELECT COUNT(*) AS count FROM `supplier` WHERE supplierID = '" + supplierID + "'";

    // Execute the query and determine the existence of the order
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = atoi(row[0]);  // Convert count to an integer

            // Free the result set
            mysql_free_result(result);

            return (count > 0);  // Return true if count > 0 (supplier exists), false otherwise
        }
    }
    return false;  // Return false by default (if an error occurs or count <= 0)
}
bool CheckStockAvailability(const string& productID, int orderQuantity) {
    string checkQuery = "SELECT ProductQuantity FROM product WHERE ProductID = '" + productID + "'";
    if (mysql_query(conn, checkQuery.c_str()) == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        if (row) {
            int availableQuantity = atoi(row[0]);
            mysql_free_result(res);

            if (orderQuantity <= availableQuantity) {
                return true;  // There is sufficient stock
            }
            else {
                cout << "Insufficient stock for the order." << endl;
                return false;
            }
        }
        else {
            cout << "Failed to fetch product details: " << mysql_error(conn) << endl;
            return false;
        }
    }
    else {
        cout << "Failed to check stock availability: " << mysql_error(conn) << endl;
        return false;
    }
}


void UpdateAdminQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void DeleteAdminQuery(const string& deleteQuery) {
    if (mysql_query(conn, deleteQuery.c_str()) == 0) {
        cout << "Admin deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete order: " << mysql_error(conn) << endl;
    }
}
void DeleteEmployeeQuery(const string& deleteQuery) {
    if (mysql_query(conn, deleteQuery.c_str()) == 0) {
        cout << "Employee deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete : " << mysql_error(conn) << endl;
    }
}
void UpdateProductQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << "Product updated successfully!" << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void UpdateCustomerQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << "Customer updated successfully!" << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void UpdateEmployeeQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << endl;
        cout << "Update Successful!" << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void UpdateOrderQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << "Order updated successfully!" << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void UpdateSupplierQuery(const string& updateQuery) {
    qstate = mysql_query(conn, updateQuery.c_str());
    if (!qstate) {
        cout << endl;
        cout << "Supplier updated successfully!" << endl;
    }
    else {
        cout << "Failed to update: " << mysql_error(conn) << endl;
    }
}
void DeleteOrderQuery(const std::string& deleteQuery) {
    if (mysql_query(conn, deleteQuery.c_str()) == 0) {
        cout << "Order deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete order: " << mysql_error(conn) << endl;
    }
}

void DeleteSupplierQuery(const std::string& deleteQuery) {
    if (mysql_query(conn, deleteQuery.c_str()) == 0) {
        cout << "Supplierr deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete order: " << mysql_error(conn) << endl;
    }
}
void DeleteProductQuery(const string& deleteQuery) {
    qstate = mysql_query(conn, deleteQuery.c_str());
    if (!qstate) {
        cout << "Product deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete product: " << mysql_error(conn) << endl;
    }
}
void DeleteCustomerQuery(const string& deleteQuery) {
    qstate = mysql_query(conn, deleteQuery.c_str());
    if (!qstate) {
        cout << "Customer deleted successfully!" << endl;
    }
    else {
        cout << "Failed to delete customer: " << mysql_error(conn) << endl;
    }
}
// Function to get the product price based on product ID
double GetProductPrice(const string& productID) {
    string query = "SELECT ProductPrice FROM product WHERE ProductID = '" + productID + "'";
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (row = mysql_fetch_row(res)) {
            return stod(row[0]); // Convert the retrieved price to double
        }
        else {
            cout << "Product not found." << endl;
            return 0; // Return 0 if the product is not found
        }
    }
    else {
        cout << "Failed to fetch product price: " << mysql_error(conn) << endl;
        return 0; // Return 0 if there's an error in the query
    }
}
void UpdateStockLevels(const string& productID, int soldQuantity) {
    // Assuming you have a table named 'product' with columns 'ProductID' and 'ProductQuantity'
    string updateQuery = "UPDATE product SET ProductQuantity = ProductQuantity - " + to_string(soldQuantity) + " WHERE ProductID = '" + productID + "'";
    if (mysql_query(conn, updateQuery.c_str()) != 0) {
        cout << "Failed to update stock levels: " << mysql_error(conn) << endl;
    }
}
void ExecuteQueryAndDisplayResult(const string& query) {
    // Common function to execute a query and display the result
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        // Display column headers with horizontal lines
        cout << left << setw(20) << "Product ID"
            << setw(30) << "Product Name"
            << setw(20) << "Price"
            << setw(15) << "Quantity"
            << setw(15) << "Supplier ID" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;

        // Display product data with horizontal lines
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0]
                << setw(35) << row[1]
                << setw(24) << row[2]
                << setw(15) << row[3]
                << setw(15) << row[4] << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
    }

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    StockInformation(); // Return to the View Stock Level menu
}
// Function to display product details with formatting





void MainMenu() {
    
    string choice;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "   Bakery Management System" << endl;
        cout << "===============================" << endl;
        cout << "Main Menu" << endl;
        cout << endl;
        cout << "1. Admin" << endl;
        cout << endl;
        cout << "2. Employee" << endl;
        cout << endl;
        cout << "3. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            AdminMainMenu();  // Call AdminMainMenu() function
        }
        else if (choice == "2") {
            EmployeeMainMenu();  // Call EmployeeMainMenu() function
        }
        else if (choice == "3") {
            exit(0);  // Exit the program
            cout << "------BYE BYE------";
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
        cin.clear();
        cin.sync();


        cout << endl;
    } while (choice != "1" && choice != "2" && choice != "3");
}

void AdminMainMenu() {
    string choice;
    
    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tAdmin Main Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Admin Login" << endl;
        cout << endl;
        cout << "2. Admin Registration" << endl;
        cout << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            AdminLogin();  // Call AdminLogin() function
        }
        else if (choice == "2") {
            AdminRegistration();  // Call AdminRegistration() function
        }
        else if (choice == "3") {
            MainMenu();  // Go back to the main menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }

    } while (choice != "1" && choice != "2" && choice != "3");
}
void EmployeeMainMenu() {
    string choice;
    
    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "      Employee Main Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Employee Login" << endl;
        cout << endl;
        cout << "2. Employee Registration" << endl;
        cout << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "1") {
            EmployeeLogin();  // Call EmployeeLogin() function
        }
        else if (choice == "2") {
            EmployeeRegistration();  // Call EmployeeRegistration() function
        }
        else if (choice == "3") {
            MainMenu();  // Call MainMenu() function
        }
        else {
            cout << "Invalid choice. Please choose 1 to 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press

        }

    } while (choice != "1" && choice != "2" && choice != "3");
    
    
}


void AdminRegistration() {
    system("cls");
    cout << "-----------------------------------" << endl;
    cout << "\tAdmin Registration" << endl;
    cout << "-----------------------------------" << endl;
    string  adminIC, adminID, adminName, phoneNumber, emailAddress, password;

    cout << "Please follow the example given for registration." << endl;
    cout << endl;
    cout << "IC (e.g. 021016070716 [only 12 numbers included]): ";

    cin.ignore(1, '\n'); // Clear the newline character from previous input

    while (true) {
        getline(cin, adminIC);

        if (adminIC.length() == 12) {
            bool isValid = true;

            for (char ch : adminIC) {
                if (!isdigit(ch)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                break; // Exit the loop when input is valid
            }
        }

        cout << "IC should contain exactly 12 digits and only numbers. Please try again: ";
    }
    cout << endl;
    // Auto-generate the AdminID in the format 'A0001', 'A0002', etc.
    string lastIDQuery = "SELECT AdminID FROM admin ORDER BY AdminID DESC LIMIT 1";
    qstate = mysql_query(conn, lastIDQuery.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (row) {
            // Extract the numeric part of the existing AdminID and increment
            int lastID = atoi(row[0] + 1);
            stringstream nextID;
            nextID << "A" << setfill('0') << setw(4) << (lastID + 1); // Increment lastID
            adminID = nextID.str();
        }
        else {
            // If no existing records, start from A0001
            adminID = "A0001";
        }

        mysql_free_result(res);
    }
    else {
        cout << "Error generating AdminID: " << mysql_error(conn) << endl;
        cout << endl;
        cout << "Press any key to continue...";
        _getch();
        AdminMainMenu(); // Return to the Admin Main Menu
        return;
    }


    // Check if an admin with the same adminIC already exists in the database
    string checkQueryIC = "SELECT COUNT(*) FROM admin WHERE AdminIC = '" + adminIC + "'";
    qstate = mysql_query(conn, checkQueryIC.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        int adminCountIC = atoi(row[0]);
        mysql_free_result(res);

        if (adminCountIC > 0) {
            cout << "Admin with this IC already exists. Registration failed." << endl;
            cout << "Press any key to continue...";
            _getch();
            AdminRegistration();  // Return to the Admin Main Menu
            return;
        }
    }
    else {
        cout << "Error checking adminIC: " << mysql_error(conn) << endl;
        cout << "Press any key to continue...";
        _getch();
        AdminMainMenu();  // Return to the Admin Main Menu
        return;
    }

    cout << "Admin Name: ";
    getline(cin, adminName);
    cout << endl;
    cout << "Phone Number (e.g. 0124286675): ";

    while (true) {
        getline(cin, phoneNumber);

        bool isValid = true;

        for (char ch : phoneNumber) {
            if (!isdigit(ch)) {
                isValid = false;
                break;
            }
        }

        if (isValid && phoneNumber.length() >= 10 && phoneNumber.length() <= 11) {
            break; // Exit the loop when input is valid
        }

        cout << "Phone Number should contain only 10 to 11 digits. Please try again: ";
    }
    cout << endl;
    cout << "Email Address (e.g. limXXXXXX@gmail.com):  ";
    while (true) {
        getline(cin, emailAddress);
        if (Email_check(emailAddress)) {
            break; // Exit the loop when input is valid
        }

        cout << "Invalid email address. Please try again: ";
    }

    string inputPassword;
    password.clear();  // Clear the 'password' variable
    bool hasLetter = false;
    bool hasDigit = false;
    cout << endl;

    do {
        cout << "Password (e.g.abc123, maximum 20 characters ): ";

        inputPassword = ""; // Clear the input password string

        char ch;
        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && inputPassword.length() > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                inputPassword.pop_back(); // Remove the last character
            }
            else if (inputPassword.length() < 20) {
                inputPassword += ch; // Add the character to the inputPassword string
                cout << '*'; // Display asterisk for each character
            }
        }

        // Check for password requirements
        hasLetter = false;
        hasDigit = false;

        if (inputPassword.length() > 20) {
            cout << "\nPassword must be at most 20 characters. Please try again." << endl;
        }
        else {
            for (size_t i = 0; i < inputPassword.length(); ++i) {
                if (isalpha(inputPassword[i])) {
                    hasLetter = true;
                }
                if (isdigit(inputPassword[i])) {
                    hasDigit = true;
                }
            }

            if (!(hasLetter && hasDigit)) {
                cout << "\nPassword must contain a mix of letters and numbers. Please try again." << endl;
            }
            else {
                // Store the password in the 'password' variable
                password = inputPassword;
            }
        }
    } while (inputPassword.length() > 20 || !(hasLetter && hasDigit));
    cout << endl;
    cout << "\nPassword accepted." << endl;

    // MySQL query to insert data into the admin table
    string query = "INSERT INTO admin (AdminIC ,AdminID, AdminName,PhoneNumber, EmailAddress, Password) VALUES ('" + adminIC + "','" +
        adminID + "', '" + adminName + "', '" + phoneNumber + "', '" + emailAddress + "', '" + password + "')";

    // Execute the query
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        cout << "------------------------------" << endl;
        cout << "Admin Registration Successful!" << endl;
        cout << "------------------------------" << endl;
    }
    else {
        cout << "------------------------------" << endl;
        cout << "Admin Registration Failed: " << mysql_error(conn) << endl;
        cout << "------------------------------" << endl;
    }

    cout << "Press any key to continue...";
    _getch();  // Wait for a key press
    AdminMainMenu();  // Return to the Admin Main Menu
}
void AdminLogin() {

    string adminID, password;
    char retryChoice;
    int invalidAttempts = 0;
    const int maxAttempts = 3;

    do {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "\tWelcome to admin login" << endl;
        cout << "---------------------------------------" << endl;
        bool loginSuccessful = false;

        // Validate Admin ID
        cout << "Admin ID (e.g. A0001): ";
        while (true) {
            cin >> adminID;

            if (adminID.length() == 5 && adminID[0] == 'A') {
                bool isValid = true;

                for (int i = 1; i < 4; ++i) {
                    if (!isdigit(adminID[i])) {
                        isValid = false;
                        break;
                    }
                }

                if (isdigit(adminID[4])) {
                    break; // Exit the loop when input is valid
                }
            }
            cout << endl;
            cout << "Invalid format for Admin ID. Please use 'A0001' format. Please try again: ";

        }

        // Validate Password
        char inputPassword[21];
        char ch;
        int index = 0;
        cout << endl;
        cout << "Password (e.g.abc123, maximum 20 characters ): ";

        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && index > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                index--;
            }
            else if (index < 20) {
                inputPassword[index++] = ch;
                cout << '*'; // Display asterisk for each character
            }
        }

        inputPassword[index] = '\0'; // Null-terminate the password

        // Check if the provided admin ID and password match an entry in the database
        string checkQuery = "SELECT COUNT(*) FROM admin WHERE AdminID = '" + adminID + "' AND Password = '" + inputPassword + "'";
        qstate = mysql_query(conn, checkQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            int adminCount = atoi(row[0]);
            mysql_free_result(res);

            if (adminCount == 1) {
                cout << "-------------------------------" << endl;
                cout << "\nAdmin Login Successful!" << endl;
                cout << "-------------------------------" << endl;
                loginSuccessful = true;
                // You can add code here to perform admin tasks
                AdminMenu();
                break;
            }
            else {
                invalidAttempts++;
                cout << endl;
                cout << "\nInvalid admin ID or password. Login failed." << endl;
                if (invalidAttempts >= maxAttempts) {
                    cout << "\nMaximum invalid attempts reached. Exiting..." << endl;
                    exit(0);
                }
                else {
                    cout << endl;
                    cout << "Attempts left: " << maxAttempts - invalidAttempts << endl;
                    cout << endl;
                    cout << "Do you want to try again? (y/n): ";
                    cin >> retryChoice;
                }
            }
        }
        else {
            cout << "\nError checking login: " << mysql_error(conn) << endl;
            cout << "Do you want to try again? (y/n): ";
            cin >> retryChoice;
        }
    } while (retryChoice == 'y' || retryChoice == 'Y');
    cout << endl;
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    AdminMainMenu(); // Return to the Admin Record menu
}




void EmployeeRegistration() {
    system("cls");

    cout << "-----------------------------------" << endl;
    cout << "\tEmployee Registration" << endl;
    cout << "-----------------------------------" << endl;

    string employeeIC, employeeID, employeeName, phoneNumber, emailAddress, password;

    cout << "Please follow the example given for registration." << endl;
    cout << endl;
    cout << "IC (e.g. 021016070716 [only 12 numbers included]): ";

    cin.ignore(1, '\n'); // Clear the newline character from previous input

    while (true) {
        getline(cin, employeeIC);

        if (employeeIC.length() == 12) {
            bool isValid = true;

            for (char ch : employeeIC) {
                if (!isdigit(ch)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                break; // Exit the loop when input is valid
            }
        }

        cout << "IC should contain exactly 12 digits and only numbers. Please try again: ";
    }
    cout << endl;
    // Check if an employee with the same employeeIC already exists in the database
    string checkQueryIC = "SELECT COUNT(*) FROM employee WHERE EmployeeIC = '" + employeeIC + "'";
    qstate = mysql_query(conn, checkQueryIC.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        int employeeCountIC = atoi(row[0]);
        mysql_free_result(res);

        if (employeeCountIC > 0) {
            cout << "Employee with this IC already exists. Registration failed." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();
            EmployeeRegistration();
            return;
        }
    }
    else {
        cout << "Error checking employeeIC: " << mysql_error(conn) << endl;
        cout << "Press any key to continue...";
        _getch();
        EmployeeMainMenu();  // Return to the employee Main Menu
        return;
    }

    // Auto-generate the EmployeeID in the format 'E0001', 'E0002', etc.
    string lastIDQuery = "SELECT EmployeeID FROM employee ORDER BY EmployeeID DESC LIMIT 1";
    qstate = mysql_query(conn, lastIDQuery.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (row) {
            // Extract the numeric part of the existing EmployeeID and increment
            int lastID = atoi(row[0] + 1);
            stringstream nextID;
            nextID << "E" << setfill('0') << setw(4) << (lastID + 1); // Increment lastID
            employeeID = nextID.str();
        }
        else {
            // If no existing records, start from E0001
            employeeID = "E0001";
        }

        mysql_free_result(res);
    }
    else {
        cout << "Error generating EmployeeID: " << mysql_error(conn) << endl;
        cout << "Press any key to continue...";
        _getch();
        EmployeeMainMenu();  // Return to the employee Main Menu
        return;
    }

    cout << "Employee Name: ";
    getline(cin, employeeName);
    cout << endl;
    cout << "Phone Number (e.g. 0124286675): ";

    while (true) {
        getline(cin, phoneNumber);

        bool isValid = true;

        for (char ch : phoneNumber) {
            if (!isdigit(ch)) {
                isValid = false;
                break;
            }
        }

        if (isValid && phoneNumber.length() >= 10 && phoneNumber.length() <= 11) {
            break; // Exit the loop when input is valid
        }

        cout << "Phone Number should contain only 10 to 11 digits. Please try again: ";
    }
    cout << endl;
    cout << "Email Address (e.g. limXXXXXX@gmail.com): ";
    while (true) {
        getline(cin, emailAddress);
        if (Email_check(emailAddress)) {
            break; // Exit the loop when input is valid
        }

        cout << "Invalid email address. Please try again: ";
    }
    cout << endl;
    string inputPassword;
    password.clear();  // Clear the 'password' variable
    bool hasLetter = false;
    bool hasDigit = false;



    do {
        cout << "Password (e.g.abc123, maximum 20 characters ): ";

        inputPassword = ""; // Clear the input password string

        char ch;
        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && inputPassword.length() > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                inputPassword.pop_back(); // Remove the last character
            }
            else if (inputPassword.length() < 20) {
                inputPassword += ch; // Add the character to the inputPassword string
                cout << '*'; // Display asterisk for each character
            }
        }

        // Check for password requirements
        hasLetter = false;
        hasDigit = false;

        if (inputPassword.length() > 20) {
            cout << "\nPassword must be at most 20 characters. Please try again." << endl;
        }
        else {
            for (size_t i = 0; i < inputPassword.length(); ++i) {
                if (isalpha(inputPassword[i])) {
                    hasLetter = true;
                }
                if (isdigit(inputPassword[i])) {
                    hasDigit = true;
                }
            }

            if (!(hasLetter && hasDigit)) {
                cout << "\nPassword must contain a mix of letters and numbers. Please try again." << endl;
            }
            else {
                // Store the password in the 'password' variable
                password = inputPassword;
            }
        }
    } while (inputPassword.length() > 20 || !(hasLetter && hasDigit));

    cout << endl;
    cout << "\nPassword accepted." << endl;

    // Include 'EmployeeID' in the column list since it's generated manually
    string query = "INSERT INTO employee (EmployeeIC, EmployeeID, EmployeeName, PhoneNumber, EmailAddress, Password) VALUES ('" +
        employeeIC + "', '" + employeeID + "', '" + employeeName + "', '" + phoneNumber + "', '" + emailAddress + "', '" + password + "')";

    // Execute the query
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        cout << "-------------------------------------" << endl;
        cout << "Employee Registration Successful!" << endl;
        cout << "-------------------------------------" << endl;
    }
    else {
        cout << "-------------------------------------" << endl;
        cout << "Employee Registration Failed: " << mysql_error(conn) << endl;
        cout << "-------------------------------------" << endl;
    }

    cout << "Press any key to continue...";
    _getch();  // Wait for a key press
    EmployeeMainMenu();  // Return to the employee Main Menu
}


void EmployeeLogin() {
    string employeeID, password;
    char retryChoice;
    int invalidAttempts = 0;
    const int maxAttempts = 3;

    do {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "\tWelcome to Employee Login" << endl;
        cout << "---------------------------------------" << endl;

        bool loginSuccessful = false;

        // Validate Employee ID
        cout << "Employee ID (e.g. E0001): ";
        while (true) {
            cin >> employeeID;

            if (employeeID.length() == 5 && employeeID[0] == 'E') {
                bool isValid = true;

                for (int i = 1; i < 4; ++i) {
                    if (!isdigit(employeeID[i])) {
                        isValid = false;
                        break;
                    }
                }

                if (isdigit(employeeID[4])) {
                    break; // Exit the loop when input is valid
                }
            }
            cout << endl;
            cout << "Invalid format for Employee ID. Please use 'E0001' format. Please try again: ";
        }

        // Validate Password
        char inputPassword[21];
        char ch;
        int index = 0;
        cout << endl;
        cout << "Password (e.g.abc123, maximum 20 characters ): ";

        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && index > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                index--;
            }
            else if (index < 20) {
                inputPassword[index++] = ch;
                cout << '*'; // Display asterisk for each character
            }
        }

        inputPassword[index] = '\0'; // Null-terminate the password

        // Check if the provided employee ID and password match an entry in the database
        string checkQuery = "SELECT COUNT(*) FROM employee WHERE EmployeeID = '" + employeeID + "' AND Password = '" + inputPassword + "'";
        qstate = mysql_query(conn, checkQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            int employeeCount = atoi(row[0]);
            mysql_free_result(res);

            if (employeeCount == 1) {
                cout << "-------------------------------" << endl;
                cout << "\nEmployee Login Successful!" << endl;
                cout << "-------------------------------" << endl;
                loginSuccessful = true;
                // You can add code here to perform employee tasks
                EmployeeMenu();
                break;
            }
            else {
                invalidAttempts++;
                cout << endl;
                cout << "\nInvalid employee ID or password. Login failed." << endl;
                if (invalidAttempts >= maxAttempts) {
                    cout << "\nMaximum invalid attempts reached. Exiting..." << endl;
                    exit(0);
                }
                else {
                    cout << endl;
                    cout << "Attempts left: " << maxAttempts - invalidAttempts << endl;
                    cout << endl;
                    cout << "Do you want to try again? (y/n): ";
                    cin >> retryChoice;
                }
            }
        }
        else {
            cout << "\nError checking login: " << mysql_error(conn) << endl;
            cout << "Do you want to try again? (y/n): ";
            cin >> retryChoice;
        }
    } while (retryChoice == 'y' || retryChoice == 'Y');

    cout << endl;
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    EmployeeMainMenu(); // Return to the Employee Record menu
}


void AdminMenu() {
    string choice;
    

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "        Admin Menu" << endl;
        cout << "===============================" << endl;

        cout << "1. Admin Record" << endl;
        cout << endl;
        cout << "2. Employee Record" << endl;
        cout << endl;
        cout << "3. Suppler Record" << endl; 
        cout << endl;
        cout << "4. Order Record" << endl; 
        cout << endl;
        cout << "5. Stock Information" << endl;
        cout << endl;
        cout << "6. Report" << endl;
        cout << endl;
        cout << "7. Back to Admin Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "1") {
            AdminRecord();
        }
        else if (choice == "2") {
            EmployeeRecord();
        }
        else if (choice == "3") {
            SupplierRecord();
        }
        else if (choice == "4") {
            OrderRecord();
        }
        else if (choice == "5") {
            StockInformation();
        }
        else if (choice == "6") {
             Report();
        }
        else if (choice == "7") {
            AdminMainMenu(); // Go back to the Admin Main Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 7." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7");
}
void AdminRecord() {
    string choice;
    
    do {
        system("cls");
        cout << "==============================" << endl;
        cout << "\tAdmin Record" << endl;
        cout << "==============================" << endl;
        cout << "1. Display Admin" << endl;
        cout << endl;
        cout << "2. Search Admin" << endl;
        cout << endl;
        cout << "3. Delete Admin" << endl;
        cout << endl;
        cout << "4. Update Admin" << endl;
        cout << endl;
        cout << "5. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            DisplayAdmin();
        }
        else if (choice == "2") {
           SearchAdmin();
        }
        else if (choice == "3") {
            DeleteAdmin();
        }
        else if (choice == "4") {
            UpdateAdmin();
        }
        else if (choice == "5") {
            AdminMenu();
        }

        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5");
}
void DisplayAdmin() {
    system("cls");

    // Fetch and display the list of admins
    string displayQuery = "SELECT * FROM admin";
    qstate = mysql_query(conn, displayQuery.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        cout << left << setw(15) << "Admin IC"
            << setw(16) << "Admin ID"
            << setw(23) << "Admin Name"
            << setw(20) << "Phone Number"
            << setw(30) << "Email Address" << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(16) << row[0]
                << setw(15) << row[1]
                << setw(23) << row[2]
                << setw(15) << row[3]
                << setw(30) << row[4] << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch admin list: " << mysql_error(conn) << endl;
    }

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    AdminRecord(); // Return to the Admin Record menu
}
void DeleteAdmin() {

    string adminID;
    char continueOption;

    do {
        system("cls");
        cout << "Admin List:" << endl;
        // Display the list of admins

        string displayQuery = "SELECT * FROM admin";
        qstate = mysql_query(conn, displayQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(15) << "Admin IC"
                << setw(16) << "Admin ID"
                << setw(23) << "Admin Name"
                << setw(20) << "Phone Number"
                << setw(30) << "Email Address" << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(16) << row[0]
                    << setw(15) << row[1]
                    << setw(23) << row[2]
                    << setw(15) << row[3]
                    << setw(30) << row[4] << endl;
                cout << "-----------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch admin list: " << mysql_error(conn) << endl;
        }
        cout << "Enter Admin ID to delete or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, adminID);
        cout << endl;
        if (adminID.empty()) {
            // If the input is empty, go back to the Employee Record menu
            break;
        }

        // Check if the admin exists
        if (CheckAdminExistence(adminID)) {
            // SQL query to delete the admin from the database
            string deleteQuery = "DELETE FROM admin WHERE AdminID = '" + adminID + "'";
            DeleteAdminQuery(deleteQuery);
        }
        else {
            cout << "Admin not found." << endl;
        }
        cout << endl;
        cout << "Do you want to delete another admin? (Y/N): ";
        cin >> continueOption;
    } while (continueOption == 'Y' || continueOption == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    AdminRecord(); // Return to the Admin Record menu
}
void UpdateAdmin() {
    string adminID, password;
    char updateMore;

    do {
        system("cls");

        // Validate Admin ID
        cout << "Enter Admin ID to update or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, adminID);

        if (adminID.empty()) {
            // If the input is empty, go back to the Admin Record menu
            break;
        }

        // Validate Password
        char inputPassword[21];
        char ch;
        int index = 0;
        cout << endl;
        cout << "Password: ";

        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && index > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                index--;
            }
            else if (index < 20) {
                inputPassword[index++] = ch;
                cout << '*'; // Display asterisk for each character
            }
        }

        inputPassword[index] = '\0'; // Null-terminate the password

        // Check if the provided admin ID and password match an entry in the database
        string checkQuery = "SELECT COUNT(*) FROM admin WHERE AdminID = '" + adminID + "' AND Password = '" + inputPassword + "'";
        qstate = mysql_query(conn, checkQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            int adminCount = atoi(row[0]);
            mysql_free_result(res);

            if (adminCount == 1) {
                // Valid admin ID and password
                system("cls");

                // Display the information of the logged-in admin
                cout << endl;
                cout << "Admin Information:" << endl;
                string displayQuery = "SELECT * FROM admin WHERE AdminID = '" + adminID + "'";
                qstate = mysql_query(conn, displayQuery.c_str());

                if (!qstate) {
                    res = mysql_store_result(conn);

                    cout << left << setw(15) << "Admin IC"
                        << setw(16) << "Admin ID"
                        << setw(23) << "Admin Name"
                        << setw(20) << "Phone Number"
                        << setw(30) << "Email Address" << endl;
                    cout << "-----------------------------------------------------------------------------------------------" << endl;

                    if ((row = mysql_fetch_row(res))) {
                        cout << left << setw(16) << row[0]
                            << setw(15) << row[1]
                            << setw(23) << row[2]
                            << setw(15) << row[3]
                            << setw(30) << row[4] << endl;
                        cout << "-----------------------------------------------------------------------------------------------" << endl;
                    }

                    mysql_free_result(res);
                }
                else {
                    cout << "Failed to fetch admin information: " << mysql_error(conn) << endl;
                }

                // Proceed with update only if the logged-in admin is the same as the one to be updated
                if (adminID == row[1]) {
                    cout << endl;
                    cout << "What do you want to update for admin " << adminID << "?" << endl;
                    cout << endl;
                    cout << "1. Update Admin Name" << endl;
                    cout << endl;
                    cout << "2. Update Phone Number" << endl;
                    cout << endl;
                    cout << "3. Update Email Address" << endl;
                    cout << endl;
                    cout << "4. Update Password" << endl;
                    string choiceStr;
                    int updateChoice;

                    while (true) {
                        cout << endl;
                        cout << "Enter your choice: ";
                        getline(cin, choiceStr);
                        cout << endl;
                        // Check if the input is a valid positive integer
                        try {
                            updateChoice = stoi(choiceStr);

                            if (updateChoice >= 1 && updateChoice <= 4) {
                                break;  // Break the loop if a valid choice is entered
                            }
                            else {
                                cout << "Invalid input. Please enter a numeric choice between 1 and 4." << endl;
                            }
                        }
                        catch (const std::invalid_argument& e) {
                            cout << "Invalid input. Please enter a numeric choice between 1 and 4." << endl;
                        }
                    }

                    // Update admin information based on the user's choice
                    if (updateChoice == 1) {
                        string newAdminName;
                        cout << "Enter new Admin Name: ";
                        cin.ignore(); // Clear the newline character from previous input
                        getline(cin, newAdminName);

                        string updateQuery = "UPDATE admin SET AdminName = '" + newAdminName + "' WHERE AdminID = '" + adminID + "'";
                        UpdateAdminQuery(updateQuery);
                    }
                    else if (updateChoice == 2) {
                        string newPhoneNumber;
                        cout << "Enter new Phone Number: ";

                        while (true) {
                            getline(cin, newPhoneNumber);

                            bool isValid = true;

                            for (char ch : newPhoneNumber) {
                                if (!isdigit(ch)) {
                                    isValid = false;
                                    break;
                                }
                            }

                            if (isValid && newPhoneNumber.length() >= 10 && newPhoneNumber.length() <= 11) {
                                break; // Exit the loop when input is valid
                            }

                            cout << "Please enter valid phone number format. Please try again: ";
                        }

                        string updateQuery = "UPDATE admin SET PhoneNumber = '" + newPhoneNumber + "' WHERE AdminID = '" + adminID + "'";
                        UpdateAdminQuery(updateQuery);
                    }
                    else if (updateChoice == 3) {
                        string newEmailAddress;
                        cout << "Enter new Email Address: ";

                        while (true) {
                            getline(cin, newEmailAddress);

                            if (Email_check(newEmailAddress)) {
                                break; // Exit the loop when input is valid
                            }

                            cout << "Invalid email address. Please try again: ";
                        }

                        string updateQuery = "UPDATE admin SET EmailAddress = '" + newEmailAddress + "' WHERE AdminID = '" + adminID + "'";
                        UpdateAdminQuery(updateQuery);
                    }
                    else if (updateChoice == 4) {
                        string newPassword;
                        bool hasLetter = false;
                        bool hasDigit = false;

                        do {
                            cout << "Enter new Password (alphanumeric mix, maximum 20 characters): ";

                            newPassword = ""; // Initialize newPassword

                            char ch;
                            while ((ch = _getch()) != '\r' && ch != '\n') {
                                if (ch == '\b') {
                                    if (!newPassword.empty()) {
                                        cout << "\b \b"; // Move cursor back, clear the character, move cursor back again
                                        newPassword.pop_back(); // Remove the last character from newPassword
                                    }
                                }
                                else {
                                    cout << '*'; // Display asterisk instead of the actual character
                                    newPassword.push_back(ch); // Add the character to newPassword
                                }
                            }

                            // Check password criteria
                            hasLetter = any_of(newPassword.begin(), newPassword.end(), ::isalpha);
                            hasDigit = any_of(newPassword.begin(), newPassword.end(), ::isdigit);

                            if (newPassword.length() > 20 || !(hasLetter && hasDigit)) {
                                cout << "\nPassword must be at most 20 characters and contain a mix of letters and numbers. Please try again." << endl;
                            }
                            else {
                                // Password criteria met, break the loop
                                break;
                            }
                        } while (true);

                        string updateQuery = "UPDATE admin SET Password = '" + newPassword + "' WHERE AdminID = '" + adminID + "'";
                        UpdateAdminQuery(updateQuery);
                    }
                    else {
                        cout << "Invalid choice. Please choose 1 to 4." << endl;
                    }
                }
                else {
                    cout << "Invalid admin ID or password. Update failed." << endl;
                }
            }
            else {
                cout << "\nInvalid admin ID or password. Try again." << endl;
            }
        }
        else {
            cout << "\nError checking login: " << mysql_error(conn) << endl;
        }

        cout << endl;
        cout << "Do you want to update another Admin? (Y/N): ";
        cin >> updateMore;
    } while (updateMore == 'Y' || updateMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    AdminRecord(); // Return to the Admin Record menu
}
void SearchAdmin() {
    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "\tSearch Admin Menu:" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Search by Admin ID" << endl;
        cout << endl;
        cout << "2. Search by Admin Name" << endl;
        cout << endl;
        cout << "3. Back to Admin Record Menu" << endl;
        cout << endl;

        int searchOption;
        cout << "Enter your choice: ";
        cin >> searchOption;
        cout << endl;
        string searchInput;
        string searchQuery;

        switch (searchOption) {
        case 1: {
            cout << "Enter Admin ID to search: ";
            cin >> searchInput;
            cout << endl;

            // Check the existence of the admin before executing the search query
            if (!CheckAdminExistence(searchInput)) {
                cout << "Admin with ID " << searchInput << " does not exist." << endl;
                cout << endl;
                cout << "Press any key to continue...";
                _getch();
                break; // Exit the switch case
            }

            searchQuery = "SELECT * FROM admin WHERE AdminID = '" + searchInput + "'";
            break;
        }
        case 2: {
            string adminName;
            cout << "Enter Admin Name to search: ";
            cin.ignore();
            getline(cin, adminName);
            cout << endl;
            searchQuery = "SELECT * FROM admin WHERE AdminName LIKE '%" + adminName + "%'";
            break;
                
        }
        case 3: {
            cout << "Press any key to continue...";
            _getch();
            AdminRecord(); // Return to the Admin Record Menu
            return;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }

        qstate = mysql_query(conn, searchQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Check if there are any rows returned
            if (mysql_num_rows(res) == 0) {
                cout << "No results found." << endl;
            }
            else {
                // Display column headers with horizontal lines
                cout << left << setw(16) << "Admin IC"
                    << setw(15) << "Admin ID"
                    << setw(23) << "Admin Name"
                    << setw(20) << "Phone Number"
                    << setw(30) << "Email Address" << endl;
                cout << "-----------------------------------------------------------------------------------------------" << endl;

                // Display admin data with horizontal lines
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(16) << row[0]
                        << setw(15) << row[1]
                        << setw(23) << row[2]
                        << setw(15) << row[3]
                        << setw(30) << row[4] << endl;
                    cout << "-----------------------------------------------------------------------------------------------" << endl;
                }
            }

            mysql_free_result(res);
        }

        char continueOption;
        cout << endl;
        cout << "\nDo you want to perform another search? (Y/N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            cout << endl;
            cout << "Press any key to continue...";
            _getch();
            AdminRecord(); // Return to the Admin Record Menu
            break; // Exit the loop
        }
    }
}





void EmployeeRecord() {
    string choice;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tEmployee Record" << endl;
        cout << "===============================" << endl;
        cout << "1. Display Employee" << endl;
        cout << endl;
        cout << "2. Search Employee" << endl;  // Added option for searching employee
        cout << endl;
        cout << "3. Delete Employee" << endl;
        cout << endl;
        cout << "4. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            DisplayEmployee();
        }
        else if (choice == "2") {
            SearchEmployee();  // Call the SearchEmployee function
        }
        else if (choice == "3") {
            DeleteEmployee();
        }
        else if (choice == "4") {
            AdminMenu();
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 4." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
}
void DisplayEmployee() {
    system("cls");

    // Fetch and display the list of admins
    string displayQuery = "SELECT * FROM employee";
    qstate = mysql_query(conn, displayQuery.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        cout << left << setw(20) << "Employee IC" 
            << setw(20) << "Employee ID" 
            << setw(26) << "Employee Name" 
            << setw(22) << "Phone Number" 
            << setw(28) << "Email Address" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(22) << row[0] 
                << setw(21) << row[1] 
                << setw(22) << row[2] 
                << setw(18) << row[3] 
                << setw(30) << row[4] << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch employee list: " << mysql_error(conn) << endl;
    }

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    EmployeeRecord(); // Return to the Admin Record menu
}
void DeleteEmployee() {
    string employeeID;
    char continueOption;

    do {
        system("cls");
        cout << "Employee List:" << endl;
        // Display the list of admins

        string displayQuery = "SELECT * FROM employee";
        qstate = mysql_query(conn, displayQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(20) << "Employee IC"
                << setw(20) << "Employee ID"
                << setw(26) << "Employee Name"
                << setw(22) << "Phone Number"
                << setw(28) << "Email Address" << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(22) << row[0]
                    << setw(21) << row[1]
                    << setw(22) << row[2]
                    << setw(18) << row[3]
                    << setw(30) << row[4] << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch employee list: " << mysql_error(conn) << endl;
        }

        cout << "Enter Employee ID to delete or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, employeeID);
        cout << endl;
        if (employeeID.empty()) {
            // If the input is empty, go back to the Employee Record menu
            break;
        }

        // Check if the employee exists
        if (CheckEmployeeExistence(employeeID)) {
            // SQL query to delete the employee from the database
            string deleteQuery = "DELETE FROM employee WHERE EmployeeID = '" + employeeID + "'";
            DeleteEmployeeQuery(deleteQuery);
        }
        else {
            cout << "EmployeeID not found." << endl;
        }
        cout << endl;
        cout << "Do you want to delete another employee? (Y/N): ";
        cin >> continueOption;
    } while (continueOption == 'Y' || continueOption == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    EmployeeRecord(); // Return to the Admin Record menu
}



void UpdateEmployee() {
    string employeeID, password;
    char updateMore;

    do {
        system("cls");

        // Validate Employee ID
        cout << "Enter Employee ID to update or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, employeeID);

        if (employeeID.empty()) {
            // If the input is empty, go back to the Employee Record menu
            break;
        }

        // Validate Password
        char inputPassword[21];
        char ch;
        int index = 0;
        cout << endl;
        cout << "Password: ";

        while (true) {
            ch = _getch(); // Capture the input without displaying it

            if (ch == 13) { // 13 is the ASCII code for Enter key
                break;
            }
            else if (ch == 8 && index > 0) { // 8 is the ASCII code for Backspace
                // Handle backspace: move cursor back, overwrite with a space, move back again
                cout << "\b \b";
                index--;
            }
            else if (index < 20) {
                inputPassword[index++] = ch;
                cout << '*'; // Display asterisk for each character
            }
        }

        inputPassword[index] = '\0'; // Null-terminate the password

        // Check if the provided employee ID and password match an entry in the database
        string checkQuery = "SELECT COUNT(*) FROM employee WHERE EmployeeID = '" + employeeID + "' AND Password = '" + inputPassword + "'";
        qstate = mysql_query(conn, checkQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            int employeeCount = atoi(row[0]);
            mysql_free_result(res);

            if (employeeCount == 1) {
                // Valid employee ID and password
                system("cls");

                // Display the information of the logged-in employee
                cout << endl;
                cout << "Employee Information:" << endl;
                string displayQuery = "SELECT * FROM employee WHERE EmployeeID = '" + employeeID + "'";
                qstate = mysql_query(conn, displayQuery.c_str());

                if (!qstate) {
                    res = mysql_store_result(conn);

                    cout << left << setw(20) << "Employee IC"
                        << setw(20) << "Employee ID"
                        << setw(26) << "Employee Name"
                        << setw(22) << "Phone Number"
                        << setw(28) << "Email Address" << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

                    if ((row = mysql_fetch_row(res))) {
                        cout << left << setw(22) << row[0]
                            << setw(21) << row[1]
                            << setw(22) << row[2]
                            << setw(18) << row[3]
                            << setw(30) << row[4] << endl;
                        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
                    }

                    mysql_free_result(res);
                }
                else {
                    cout << "Failed to fetch employee information: " << mysql_error(conn) << endl;
                }

                // Proceed with update only if the logged-in employee is the same as the one to be updated
                if (employeeID == row[1]) {
                    cout << endl;
                    cout << "What do you want to update for employee " << employeeID << "?" << endl;
                    cout << endl;
                    cout << "1. Update Employee Name" << endl;
                    cout << endl;
                    cout << "2. Update Phone Number" << endl;
                    cout << endl;
                    cout << "3. Update Email Address" << endl;
                    cout << endl;
                    cout << "4. Update Password" << endl;
                    string choiceStr;
                    int updateChoice;

                    while (true) {
                        cout << endl;
                        cout << "Enter your choice: ";
                        getline(cin, choiceStr);
                        cout << endl;
                        // Check if the input is a valid positive integer
                        try {
                            updateChoice = stoi(choiceStr);

                            if (updateChoice >= 1 && updateChoice <= 4) {
                                break;  // Break the loop if a valid choice is entered
                            }
                            else {
                                cout << "Invalid input. Please enter a numeric choice between 1 and 4." << endl;
                            }
                        }
                        catch (const std::invalid_argument& e) {
                            cout << "Invalid input. Please enter a numeric choice between 1 and 4." << endl;
                        }
                    }

                    if (updateChoice == 1) {
                        string newEmployeeName;
                        
                        cout << "Enter new Employee Name: ";
                         // Clear the newline character from previous input
                        cin>>newEmployeeName;
                        cout << endl;
                        string updateQuery = "UPDATE employee SET EmployeeName = '" + newEmployeeName + "' WHERE EmployeeID = '" + employeeID + "'";
                        UpdateEmployeeQuery(updateQuery);
                    }
                    else if (updateChoice == 2) {
                        string newPhoneNumber;
                        
                        cout << "Enter new Phone Number: ";

                        while (true) {
                            getline(cin, newPhoneNumber);

                            bool isValid = true;

                            for (char ch : newPhoneNumber) {
                                if (!isdigit(ch)) {
                                    isValid = false;
                                    break;
                                }
                            }

                            if (isValid && newPhoneNumber.length() >= 10) {
                                break; // Exit the loop when input is valid
                            }

                            cout << "Please enter valid phone number format. Please try again: ";
                        }

                        string updateQuery = "UPDATE employee SET PhoneNumber = '" + newPhoneNumber + "' WHERE EmployeeID = '" + employeeID + "'";
                        UpdateEmployeeQuery(updateQuery);
                    }
                    else if (updateChoice == 3) {
                        string newEmailAddress;
                         
                        cout << "Enter new Email Address: ";

                        while (true) {
                            getline(cin, newEmailAddress);

                            if (Email_check(newEmailAddress)) {
                                break; // Exit the loop when input is valid
                            }

                            cout << "Invalid email address. Please try again: ";
                        }

                        string updateQuery = "UPDATE employee SET EmailAddress = '" + newEmailAddress + "' WHERE EmployeeID = '" + employeeID + "'";
                        UpdateEmployeeQuery(updateQuery);
                    }
                    else if (updateChoice == 4) {
                        string newPassword;
                        bool hasLetter = false;
                        bool hasDigit = false;

                        do {
                            cout << endl;
                            cout << "Enter new Password (alphanumeric mix, maximum 20 characters): ";

                            newPassword = ""; // Initialize newPassword

                            char ch;
                            while ((ch = _getch()) != '\r' && ch != '\n') {
                                if (ch == '\b') {
                                    if (!newPassword.empty()) {
                                        cout << "\b \b"; // Move cursor back, clear the character, move cursor back again
                                        newPassword.pop_back(); // Remove the last character from newPassword
                                    }
                                }
                                else {
                                    cout << '*'; // Display asterisk instead of the actual character
                                    newPassword.push_back(ch); // Add the character to newPassword
                                }
                            }

                            // Check password criteria
                            hasLetter = any_of(newPassword.begin(), newPassword.end(), ::isalpha);
                            hasDigit = any_of(newPassword.begin(), newPassword.end(), ::isdigit);

                            if (newPassword.length() > 20 || !(hasLetter && hasDigit)) {
                                cout << "\nPassword must be at most 20 characters and contain a mix of letters and numbers. Please try again." << endl;
                            }
                            else {
                                // Password criteria met, break the loop
                                break;
                            }
                        } while (true);

                        string updateQuery = "UPDATE employee SET Password = '" + newPassword + "' WHERE EmployeeID = '" + employeeID + "'";
                        UpdateEmployeeQuery(updateQuery);
                    }
                    else {
                        cout << "Invalid choice. Please choose 1 to 4." << endl;
                    }

                    
                }
                else {
                    cout << "Invalid employee ID or password. Update failed." << endl;
                }
            }
            else {
                cout << "\nInvalid employee ID or password. Try again." << endl;
            }
        }
        else {
            cout << "\nError checking login: " << mysql_error(conn) << endl;
        }

        cout << endl;
        cout << "Do you want to update another Employee? (Y/N): ";
        cin >> updateMore;
    } while (updateMore == 'Y' || updateMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    EmployeeMenu(); // Return to the Admin Record menu
}

void SearchEmployee() {
    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "\tSearch Employee Menu:" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Search by Employee ID" << endl;
        cout << endl;
        cout << "2. Search by Employee Name" << endl;
        cout << endl;
        cout << "3. Back to Admin Menu" << endl;
        cout << endl;

        int searchOption;
        cout << "Enter your choice: ";
        cin >> searchOption;
        cout << endl;
        string searchInput;
        string searchQuery;

        switch (searchOption) {
        case 1: {
            cout << "Enter Employee ID to search: ";
            cin >> searchInput;
            cout << endl;

            // Check the existence of the employee before executing the search query
            if (!CheckEmployeeExistence(searchInput)) {
                cout << "Employee with ID " << searchInput << " does not exist." << endl;
                cout << endl;
                cout << "Press any key to continue...";
                _getch();
                break; // Exit the switch case
            }

            searchQuery = "SELECT * FROM employee WHERE EmployeeID = '" + searchInput + "'";
            break;
        }
        case 2: {
            string employeeName;
            cout << "Enter Employee Name to search: ";
            cin.ignore();
            getline(cin, employeeName);
            cout << endl;
            searchQuery = "SELECT * FROM employee WHERE EmployeeName LIKE '%" + employeeName + "%'";
            break;
        }
        case 3: {
            cout << "Press any key to continue...";
            _getch();
            AdminMenu(); // Return to the Admin Menu
            return;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }

        qstate = mysql_query(conn, searchQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Check if there are any rows returned
            if (mysql_num_rows(res) == 0) {
                cout << "No results found." << endl;
            }
            else {
                // Display column headers with horizontal lines
                cout << left << setw(20) << "Employee IC"
                    << setw(20) << "Employee ID"
                    << setw(26) << "Employee Name"
                    << setw(22) << "Phone Number"
                    << setw(28) << "Email Address" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

                // Display employee data with horizontal lines
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(22) << row[0]
                        << setw(21) << row[1]
                        << setw(22) << row[2]
                        << setw(18) << row[3]
                        << setw(30) << row[4] << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
                }
            }

            mysql_free_result(res);
        }
        cout << endl;
        char continueOption;
        cout << "\nDo you want to perform another search? (Y/N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            cout << endl;
            cout << "Press any key to continue...";
            _getch();
            EmployeeRecord(); // Return to the Admin Menu
            break; // Exit the loop
        }
    }
}


void DisplayCustomer() {
    system("cls");

    // Display the customer list
    string query = "SELECT * FROM customer";
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        cout << left << setw(15) << "Customer ID" << setw(30) << "Customer Name" << setw(15) << "Phone Number" << endl;
        cout << "-----------------------------------------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(30) << row[1] << setw(15) << row[2] << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch customer list: " << mysql_error(conn) << endl;
    }
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    AdminMenu(); // Return to the Admin Menu
}

void SupplierRecord() {
    string choice;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "       Supplier Record" << endl;
        cout << "===============================" << endl;

        cout << "1. Search Supplier" << endl;
        cout << endl;
        cout << "2. Display Supplier" << endl;
        cout << endl;
        cout << "3. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == "1") {
            SearchSupplier();
        }
        else if (choice == "2") {
            DisplaySupplier();
        }
        else if (choice == "3") {
            AdminMenu(); // Go back to the Admin Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }

    } while (choice != "1" && choice != "2" && choice != "3");
}
void DisplaySupplier() {
    system("cls");

    // Display the supplier list
    string query = "SELECT * FROM supplier";
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        // Display column headers with horizontal lines
        cout << left << setw(15) << "Supplier ID" <<
            setw(30) << "Company Name" <<
            setw(20) << "Phone Number" <<
            setw(62) << "Supplier Address" <<
            setw(30) << "Contact Person" <<
            setw(30) << "Email Address" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        // Display supplier data with horizontal lines
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] <<
                setw(30) << row[1] <<
                setw(20) << row[2] <<
                setw(62) << row[3] <<
                setw(30) << row[4] <<
                setw(30) << row[5] << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch supplier list: " << mysql_error(conn) << endl;
    }
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    SupplierRecord(); // Return to the Admin Menu

}
void SearchSupplier() {
    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "\tSearch Supplier Menu:" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Search by Supplier ID" << endl;
        cout << endl;
        cout << "2. Search by Company Name" << endl;
        cout << endl;
        cout << "3. Back to Admin Menu" << endl;
        cout << endl;

        int searchOption;
        cout << "Enter your choice: ";
        cin >> searchOption;
        cout << endl;
        string searchInput;
        string searchQuery;

        switch (searchOption) {
        case 1: {
            cout << "Enter Supplier ID to search: ";
            cin >> searchInput;
            cout << endl;

            // Check the existence of the supplier before executing the search query
            if (!CheckSupplierExistence(searchInput)) {
                cout << "Supplier with ID " << searchInput << " does not exist." << endl;
                cout << endl;
                cout << "Press any key to continue...";
                _getch();
                break; // Exit the switch case
            }

            searchQuery = "SELECT * FROM supplier WHERE SupplierID = '" + searchInput + "'";
            break;
        }
        case 2: {
            string companyName;
            cout << "Enter Company Name to search: ";
            cin.ignore();
            getline(cin, companyName);
            cout << endl;
            searchQuery = "SELECT * FROM supplier WHERE CompanyName LIKE '%" + companyName + "%'";
            break;
        }
        case 3: {
            cout << "Press any key to continue...";
            _getch();
            AdminMenu(); // Return to the Admin Menu
            return;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }

        qstate = mysql_query(conn, searchQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Check if there are any rows returned
            if (mysql_num_rows(res) == 0) {
                cout << "No results found." << endl;
            }
            else {
                // Display column headers with horizontal lines
                cout << left << setw(15) << "Supplier ID" <<
                    setw(30) << "Company Name" <<
                    setw(20) << "Phone Number" <<
                    setw(62) << "Supplier Address" <<
                    setw(30) << "Contact Person" <<
                    setw(30) << "Email Address" << endl;
                cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                // Display supplier data with horizontal lines
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(15) << row[0] <<
                        setw(30) << row[1] <<
                        setw(20) << row[2] <<
                        setw(62) << row[3] <<
                        setw(30) << row[4] <<
                        setw(30) << row[5] << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }

            mysql_free_result(res);
        }
        
        char continueOption;
        cout << "\nDo you want to perform another search? (Y/N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            cout << "Press any key to continue...";
            _getch();
            SupplierRecord(); // Return to the Admin Menu
            break; // Exit the loop
        }
    }
}

void OrderRecord() {
    string choice;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "       Order Record" << endl;
        cout << "===============================" << endl;

        cout << "1. Search Order" << endl;
        cout << endl;
        cout << "2. Display Order" << endl;
        cout << endl;
        cout << "3. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == "1") {
            SearchOrder();
        }
        else if (choice == "2") {
            DisplayOrder();
        }
        else if (choice == "3") {
            AdminMenu(); // Go back to the Admin Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }

    } while (choice != "1" && choice != "2" && choice != "3");
}
void DisplayOrder() {
    system("cls");

    // Display the order list
    string orderListQuery = "SELECT * FROM `order`";
    qstate = mysql_query(conn, orderListQuery.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        // Display column headers with horizontal lines
        cout << left << setw(15) << "Order ID"
            << setw(15) << "Order Date"
            << setw(20) << "Order Quantity"
            << setw(15) << "Product ID" << endl;
        cout << "-----------------------------------------------------------------" << endl;

        // Display order data with horizontal lines
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0]
                << setw(22) << row[1]
                << setw(15) << row[2]
                << setw(15) << row[3] << endl;
            cout << "-----------------------------------------------------------------" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch order list: " << mysql_error(conn) << endl;
    }
    cout << endl;
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    OrderRecord(); // Return to the Admin Menu
}
void SearchOrder() {
    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "\tSearch Order Menu:" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Basic Search (Order ID)" << endl;
        cout << endl;
        cout << "2. Search by Date Range" << endl;
        cout << endl;
        cout << "3. Search by Order Quantity Range" << endl;
        cout << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << endl;

        int searchOption;
        cout << "Enter your choice (1-4): ";
        cin >> searchOption;
        cout << endl;
        string searchInput;
        string searchQuery;

        switch (searchOption) {
        case 1: {
            cout << "Enter Order ID to search: ";
            cin >> searchInput;
            cout << endl;

            // Check the existence of the order before executing the search query
            if (!CheckOrderExistence(searchInput)) {
                cout << "Order with ID " << searchInput << " does not exist." << endl;
                cout << endl;
                cout << "Press any key to continue...";
                _getch();
                break; // Exit the switch case
            }

            searchQuery = "SELECT * FROM `order` WHERE OrderID = '" + searchInput + "'";
            break;
        }
        case 2: {
            string startDate;
            do {
                cout << "Enter Start Date (YYYY-MM-DD): ";
                cin >> startDate;
                cout << endl;
                if (!isValidDateFormat(startDate)) {
                    ClearLastLine();
                    cout << "Invalid date format. Please enter the date in the format YYYY-MM-DD: ";
                }
            } while (!isValidDateFormat(startDate));
            
            string endDate;
            do {
                cout << "Enter End Date (YYYY-MM-DD): ";
                cin >> endDate;
                cout << endl;
                if (!isValidDateFormat(endDate)) {
                    ClearLastLine();
                    cout << "Invalid date format. Please enter the date in the format YYYY-MM-DD: ";
                }
            } while (!isValidDateFormat(endDate));
            cout << endl;
            // Build the query with date range criteria
            searchQuery = "SELECT * FROM `order` WHERE OrderDate BETWEEN '" + startDate + "' AND '" + endDate + "'";
            break;
        }
        case 3: {
            int minQuantity;
            string input;

            do {
                cout << "Enter Minimum Order Quantity: ";
                cin.ignore(); // Clear the input buffer
                cin >> input; // Read the entire line
                stringstream quantityStream(input);

                bool validInput = true;

                for (char ch : input) {
                    if (!isdigit(ch)) {
                        validInput = false;
                        break;
                    }
                }

                if (validInput && quantityStream >> minQuantity && quantityStream.eof() && minQuantity >= 0) {
                    break; // Break out of the loop if a valid input is provided
                }
                else {
                    ClearLastLine();
                    cout << "Invalid input. Please enter a valid format for minimum order quantity: ";
                }
            } while (true);

            int maxQuantity;
            do {
                cout << endl;
                cout << "Enter Maximum Order Quantity: ";
                cin.ignore(); // Clear the input buffer
                cin >> input; // Read the entire line
                cout << endl;
                stringstream quantityStream(input);

                bool validInput = true;

                for (char ch : input) {
                    if (!isdigit(ch)) {
                        validInput = false;
                        break;
                    }
                }

                if (validInput && quantityStream >> maxQuantity && quantityStream.eof() && maxQuantity >= 0) {
                    break; // Break out of the loop if a valid input is provided
                }
                else {
                    ClearLastLine();
                    cout << "Invalid input. Please enter a valid format for maximum order quantity: ";
                }
            } while (true);

            // Build the query with order quantity range criteria
            searchQuery = "SELECT * FROM `order` WHERE OrderQuantity BETWEEN " + to_string(minQuantity) + " AND " + to_string(maxQuantity);
            break;
        }
        case 4: {
            cout << "Press any key to continue...";
            _getch();
            OrderRecord(); // Assuming OrderMenu is the main menu for order-related operations
            return;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }

        qstate = mysql_query(conn, searchQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Check if there are any rows returned
            if (mysql_num_rows(res) == 0) {
                cout << "No results found." << endl;
            }
            else {
                // Display column headers with horizontal lines
                cout << left << setw(15) << "Order ID"
                    << setw(15) << "Order Date"
                    << setw(20) << "Order Quantity"
                    << setw(15) << "Product ID" << endl;
                cout << "-----------------------------------------------------------------" << endl;

                // Display order data with horizontal lines
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(15) << row[0]
                        << setw(22) << row[1]
                        << setw(15) << row[2]
                        << setw(15) << row[3] << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
            }

            mysql_free_result(res);
        }

        char continueOption;
        cout << "\nDo you want to search for another order? (Y/N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            cout << endl;
            cout << "Press any key to continue...";
            _getch();
            OrderRecord(); // Assuming OrderMenu is the main menu for order-related operations
            break; // Exit the loop
        }
    }
}


void StockInformation() {
    string choice;
    

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "      Stock Information" << endl;
        cout << "===============================" << endl;
        cout << "1. View All Products" << endl;
        cout << endl;
        cout << "2. Search for Products" << endl; 
        cout << endl;
        cout << "3. Filter by Low Stock" << endl;
        cout << endl;
        cout << "4. Calculate Total Inventory Value" << endl;
        cout << endl;
        cout << "5. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == "1") {
            // View all products
            DisplayAllProducts();
        }
        else if (choice == "2") {
            // Search for products
            SearchProduct();
        }
        else if (choice == "3") {
            // Filter by low stock
            FilterLowStock();
        }
        else if (choice == "4") {
            CalculateTotalInventoryValue();
        }
        else if (choice == "5") {
            // Back to Admin Menu
            AdminMenu();
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5");
}
void DisplayAllProducts() {
    system("cls");
    // Display all products without any sorting or filtering
    string query = "SELECT * FROM product";
    ExecuteQueryAndDisplayResult(query);
}
void SearchProduct() {
    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "\tSearch Product Menu:" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Search by Product ID" << endl;
        cout << endl;
        cout << "2. Search by Product Name" << endl;
        cout << endl;
        cout << "3. Search by Price Range" << endl;
        cout << endl;
        cout << "4. Search by Quantity Range" << endl;
        cout << endl;
        cout << "5. Back to Product Menu" << endl;
        cout << endl;

        int searchOption;
        cout << "Enter your choice: ";
        cin >> searchOption;
        cout << endl;

        switch (searchOption) {
        case 1: {
            string productId;
            cout << "Enter Product ID to search: ";
            cin >> productId;
            cout << endl;

            // Check the existence of the product before executing the search query
            if (!CheckProductExistence(productId)) {
                cout << "Product with ID " << productId << " does not exist." << endl;

                break; // Exit the switch case
            }

            string searchQuery = "SELECT * FROM product WHERE ProductID = '" + productId + "'";
            ExecuteSearchQuery(searchQuery);
            break;
        }
        case 2: {
            string productName;
            cout << "Enter Product Name to search: ";
            cin.ignore();
            getline(cin, productName);
            cout << endl;

            string searchQuery = "SELECT * FROM product WHERE ProductName LIKE '%" + productName + "%'";
            ExecuteSearchQuery(searchQuery);
            break;
        }
        case 3: {
            double minPrice, maxPrice;

            do {
                cout << "Enter Minimum Price: ";
                cin >> minPrice;
                cout << endl;
                cout << "Enter Maximum Price: ";
                cin >> maxPrice;
                cout << endl;

                if (minPrice >= 0 && maxPrice >= 0 && minPrice <= maxPrice) {
                    break; // Break out of the loop if valid input is provided
                }
                else {
                    ClearLastLine();
                    cout << endl;
                    cout << "Invalid input. Please enter valid minimum and maximum prices." << endl;
                    cout << endl;
                }
            } while (true);

            string searchQuery = "SELECT * FROM product WHERE ProductPrice BETWEEN " + to_string(minPrice) + " AND " + to_string(maxPrice);
            ExecuteSearchQuery(searchQuery);
            break;
        }
        case 4: {
            int minQuantity, maxQuantity;

            do {
                cout << "Enter Minimum Quantity: ";
                cin >> minQuantity;
                cout << endl;
                cout << "Enter Maximum Quantity: ";
                cin >> maxQuantity;
                cout << endl;

                if (minQuantity >= 0 && maxQuantity >= 0 && minQuantity <= maxQuantity) {
                    break; // Break out of the loop if valid input is provided
                }
                else {
                    ClearLastLine();
                    cout << endl;
                    cout << "Invalid input. Please enter valid minimum and maximum quantities." << endl;
                    cout << endl;
                    // Clear the error state and discard invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (true);

            string searchQuery = "SELECT * FROM product WHERE ProductQuantity BETWEEN " + to_string(minQuantity) + " AND " + to_string(maxQuantity);
            ExecuteSearchQuery(searchQuery);
            break;
        }
        case 5: {
            cout << "Press any key to continue...";
            _getch();
            StockInformation(); // Assuming ProductMenu is the main menu for product-related operations
            return;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }

        char continueOption;
        cout << "\nDo you want to perform another search? (Y/N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            cout << "Press any key to continue...";
            _getch();
            StockInformation(); // Assuming ProductMenu is the main menu for product-related operations
            break; // Exit the loop
        }
    }
}

void FilterLowStock() {
    char continueFiltering;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "      Filter Low Stock" << endl;
        cout << "===============================" << endl;
        cout << endl;

        // Prompt the admin to enter the low stock threshold
        int lowStockThreshold;
        cout << "Enter the low stock threshold: ";
        cin >> lowStockThreshold;
        cout << endl;
        // Construct the query with the custom low stock threshold
        string query = "SELECT * FROM product WHERE ProductQuantity < " + to_string(lowStockThreshold);
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(20) << "Product ID"
                << setw(30) << "Product Name"
                << setw(20) << "Price"
                << setw(15) << "Quantity"
                << setw(15) << "Supplier ID" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;

            // Display product data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(35) << row[1]
                    << setw(24) << row[2]
                    << setw(15) << row[3]
                    << setw(15) << row[4] << endl;
                cout << "--------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Do you want to continue filtering low stock? (Y/N): ";
        cin >> continueFiltering;

    } while (continueFiltering == 'Y' || continueFiltering == 'y');
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    StockInformation(); // Return to the Product Menu
}
void CalculateTotalInventoryValue() {
    system("cls");
    string productListQuery = "SELECT ProductID, ProductName, ProductPrice, ProductQuantity, SupplierID FROM product";
    qstate = mysql_query(conn, productListQuery.c_str());

    if (qstate == 0) {
        res = mysql_store_result(conn);

        // Display product list
        cout << left << setw(20) << "Product ID"
            << setw(30) << "Product Name"
            << setw(20) << "Price"
            << setw(15) << "Quantity"
            << setw(15) << "Supplier ID" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0]
                << setw(35) << row[1]
                << setw(24) << row[2]
                << setw(15) << row[3]
                << setw(15) << row[4] << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    else {
        cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
        return;
    }
    // Fetch total inventory value
    string totalValueQuery = "SELECT SUM(ProductPrice * ProductQuantity) AS GrandTotalValue FROM product";
    qstate = mysql_query(conn, totalValueQuery.c_str());

    if (qstate == 0) {
        res = mysql_store_result(conn);

        // Display total inventory value
        while ((row = mysql_fetch_row(res))) {
            cout << "Grand Total Inventory Value: RM" << row[0] << endl;
        }

        mysql_free_result(res);
    }
    else {
        cout << "Failed to calculate total inventory value: " << mysql_error(conn) << endl;
    }
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    StockInformation(); // Return to the View Stock Level menu
}

void Report() {
    string choice;
    do {
        system("cls");
        cout << "=================================" << endl;
        cout << "\tReport Menu" << endl;
        cout << "=================================" << endl;
        cout << endl;
        cout << "1. Sales Report" << endl;
        cout << endl;
        cout << "2. Product Sales Report" << endl;
        cout << endl;
        cout << "3. Back to Admin Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == "1") {
            
            SalesMenu();
        }
        else if (choice == "2") {
           
            ProductSales();
        }
        else if (choice == "3") {
           
            AdminMenu();
        }
        
        
        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" );
}
void SalesMenu() {
    string choice;
    
    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tSales Report" << endl;
        cout << "===============================" << endl;
        cout << "1. Monthly income" << endl;
        cout << endl;
        cout << "2. Yearly Income" << endl;
        cout << endl;
        cout << "3. Back to report Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            MonthlySales();
        }
        else if (choice == "2") {
            YearlySales();
        }
        else if (choice == "3") {
           Report();
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 3." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3");
}
void ProductSales() {
    string choice;
    do {
        system("cls");
        cout << "=================================" << endl;
        cout << "\tProduct Sales Menu" << endl;
        cout << "=================================" << endl;
        cout << endl;
        cout << "1. View Top Selling Product" << endl;
        cout << endl;
        cout << "2. View low Selling Products" << endl;
        cout << endl;
        cout << "3. Back to report Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == "1") {

            ViewTopSellingProducts();
        }
        else if (choice == "2") {

            ViewLowSellingProducts();
        }
        else if (choice == "3") {

            Report();
        }


        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3");
}
void MonthlySales() {
    do {
        system("cls");

        // Get the month and year from the user
        int year, month;

        // Get a valid 4-digit year
        do {

            cout << "Enter the year (YYYY): ";
            cin >> year;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || year < 1000 || year > 9999) {
                cout << "Invalid input. Please enter a valid 4-digit year." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Get a valid month (1-12)
        do {
            cout << "Enter the month (MM): ";
            cin >> month;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || month < 1 || month > 12) {
                cout << "Invalid input. Please enter a valid month (1-12)." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Display the monthly income calculation
        string monthlyIncomeQuery = "SELECT `order`.`OrderDate`, `order`.`OrderQuantity`, `product`.`ProductPrice` FROM `order` JOIN `product` ON `order`.`ProductID` = `product`.`ProductID` WHERE YEAR(`order`.`OrderDate`) = " + to_string(year) + " AND MONTH(`order`.`OrderDate`) = " + to_string(month);

        qstate = mysql_query(conn, monthlyIncomeQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            double totalIncome = 0.0;

            cout << left << setw(15) << "Order Date"
                << setw(20) << "Order Quantity"
                << setw(20) << "Product Price"
                << setw(15) << "Total Amount" << endl;
            cout << "--------------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                double orderQuantity = stod(row[1]);
                double productPrice = stod(row[2]);
                double orderAmount = orderQuantity * productPrice;

                totalIncome += orderAmount;

                cout << left << setw(20) << row[0]
                    << setw(20) << row[1]
                    << setw(20) << row[2]
                    << setw(15) << orderAmount << endl;
                cout << "--------------------------------------------------------------------" << endl;
            }

            cout << endl;
            cout << "Total Monthly Income: RM " << totalIncome << endl;

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch monthly income data: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Do you want to continue? (Y/N): ";
        char choice;
        cin >> choice;

        if (toupper(choice) != 'Y') {
            break;  // Exit the loop if the choice is not 'Y'
        }

    } while (true);

    SalesMenu(); // Return to the Admin Menu
}
void YearlySales() {
    do {
        system("cls");

        // Get a valid 4-digit year
        int year;
        do {
            cout << "Enter the year (YYYY): ";
            cin >> year;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || year < 1000 || year > 9999) {
                cout << "Invalid input. Please enter a valid 4-digit year." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Display the yearly income calculation
        string yearlyIncomeQuery = "SELECT `order`.`OrderDate`, `order`.`OrderQuantity`, `product`.`ProductPrice` FROM `order` JOIN `product` ON `order`.`ProductID` = `product`.`ProductID` WHERE YEAR(`order`.`OrderDate`) = " + to_string(year);

        qstate = mysql_query(conn, yearlyIncomeQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            double totalIncome = 0.0;

            cout << left << setw(15) << "Order Date"
                << setw(20) << "Order Quantity"
                << setw(20) << "Product Price"
                << setw(15) << "Total Amount" << endl;
            cout << "--------------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                double orderQuantity = stod(row[1]);
                double productPrice = stod(row[2]);
                double orderAmount = orderQuantity * productPrice;

                totalIncome += orderAmount;

                cout << left << setw(20) << row[0]
                    << setw(20) << row[1]
                    << setw(20) << row[2]
                    << setw(15) << orderAmount << endl;
                cout << "--------------------------------------------------------------------" << endl;
            }

            cout << endl;
            cout << "Total Yearly Income: RM " << totalIncome << endl;

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch yearly income data: " << mysql_error(conn) << endl;
        }

        cout << "Do you want to continue? (Y/N): ";
        char choice;
        cin >> choice;

        if (toupper(choice) != 'Y') {
            break; // Exit the loop if the choice is not 'Y'
        }

    } while (true);

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    SalesMenu(); // Return to the Admin Menu
}


void ViewTopSellingProducts() {
    char choice;

    do {
        system("cls");

        // Get the month and year from the user
        int year, month;

        // Get a valid 4-digit year
        do {
            cout << "Enter the year (YYYY): ";
            cin >> year;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || year < 1000 || year > 9999) {
                cout << "Invalid input. Please enter a valid 4-digit year." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Get a valid month (1-12)
        do {
            cout << "Enter the month (MM): ";
            cin >> month;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || month < 1 || month > 12) {
                cout << "Invalid input. Please enter a valid month (1-12)." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Display the top-selling products for the specified month and year
        string topSellingProductsQuery = "SELECT `product`.`ProductName`, SUM(`order`.`OrderQuantity`) AS TotalQuantity FROM `order` JOIN `product` ON `order`.`ProductID` = `product`.`ProductID` WHERE YEAR(`order`.`OrderDate`) = " + to_string(year) + " AND MONTH(`order`.`OrderDate`) = " + to_string(month) + " GROUP BY `product`.`ProductID` ORDER BY TotalQuantity DESC LIMIT 10";

        qstate = mysql_query(conn, topSellingProductsQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(25) << "Product Name"
                << setw(20) << "Total Quantity Sold" << endl;
            cout << "----------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(34) << row[0]
                    << setw(20) << row[1] << endl;
                cout << "----------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch top-selling products data: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Do you want to continue viewing top-selling products? (Y/N): ";
        cin >> choice;
        cout << endl;
    } while (choice == 'Y' || choice == 'y');

    cout << "\nPress any key to continue to Product Sales Menu...";
    _getch();
    ProductSales();
}

void ViewLowSellingProducts() {
    char choice;

    do {
        system("cls");

        // Get the month and year from the user
        int year, month;

        // Get a valid 4-digit year
        do {
            cout << "Enter the year (YYYY): ";
            cin >> year;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || year < 1000 || year > 9999) {
                cout << "Invalid input. Please enter a valid 4-digit year." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Get a valid month (1-12)
        do {
            cout << "Enter the month (MM): ";
            cin >> month;
            cout << endl;
            if (cin.fail() || cin.peek() != '\n' || month < 1 || month > 12) {
                cout << "Invalid input. Please enter a valid month (1-12)." << endl;
                clearInputBuffer(); // Clear the input buffer
                cout << endl;
            }
            else {
                break; // Exit the loop if the input is valid
            }
        } while (true);

        // Display the low-selling products for the specified month and year
        string lowSellingProductsQuery = "SELECT `product`.`ProductName`, SUM(`order`.`OrderQuantity`) AS TotalQuantity FROM `order` JOIN `product` ON `order`.`ProductID` = `product`.`ProductID` WHERE YEAR(`order`.`OrderDate`) = " + to_string(year) + " AND MONTH(`order`.`OrderDate`) = " + to_string(month) + " GROUP BY `product`.`ProductID` ORDER BY TotalQuantity ASC LIMIT 10";

        qstate = mysql_query(conn, lowSellingProductsQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(25) << "Product Name"
                << setw(20) << "Total Quantity Sold" << endl;
            cout << "----------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(34) << row[0]
                    << setw(20) << row[1] << endl;
                cout << "----------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch low-selling products data: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Do you want to continue viewing low-selling products? (Y/N): ";
        cin >> choice;
        cout << endl;
    } while (choice == 'Y' || choice == 'y');

    cout << "\nPress any key to continue to Product Sales Menu...";
    _getch();
    ProductSales();
}








void EmployeeMenu() {
    string choice;

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tEmployee Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Update Employee Information" << endl;
        cout << endl;
        cout << "2. Product Menu" << endl;
        cout << endl;
        cout << "3. Order Menu" << endl;
        cout << endl;
        cout << "4. Supplier Menu" << endl;
        cout << endl;
        cout << "5. Back to Employee Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "1") {
            UpdateEmployee();  // Call UpdateEmployee() function
        }
        else if (choice == "2") {
            ProductMenu();
        }
        else if (choice == "3") {
            OrderMenu();
        }
        else if (choice == "4") {
            SupplierMenu();
        }
        else if (choice == "5") {
            EmployeeMainMenu(); // Go back to the Employee Main Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5");
}

void ProductMenu() {
    string choice;
    

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tProduct Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Add product" << endl;
        cout << endl;
        cout << "2. Update product" << endl;
        cout << endl;
        cout << "3. Delete product" << endl;
        cout << endl;
        cout << "4. Back to Employee Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            AddProduct();
        }
        else if (choice == "2") {
            UpdateProduct();
        }
        else if (choice == "3") {
            DeleteProduct();
        }
        else if (choice == "4") {
            EmployeeMenu();
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 4." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" );
}
void AddProduct() {
    system("cls");
    string productId, productName, supplierID;
    int productQuantity;
    double productPrice;
    bool validSupplier = false;

    char addMore;
    string query;
    string input; // Variable to store user input

    do {
        system("cls");

        // Display the product list
        string displayQuery = "SELECT * FROM product";
        qstate = mysql_query(conn, displayQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(20) << "Product ID"
                << setw(30) << "Product Name"
                << setw(20) << "Price"
                << setw(15) << "Quantity"
                << setw(15) << "Supplier ID" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;

            // Display product data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(35) << row[1]
                    << setw(24) << row[2]
                    << setw(15) << row[3]
                    << setw(15) << row[4] << endl;
                cout << "--------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
        }

        // Auto-generate the ProductID in the format 'P0001', 'P0002', etc.
        string lastIDQuery = "SELECT ProductID FROM product ORDER BY ProductID DESC LIMIT 1";
        qstate = mysql_query(conn, lastIDQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);

            if (row) {
                // Extract the numeric part of the existing ProductID and increment
                int lastID = atoi(row[0] + 1);
                stringstream nextID;
                nextID << "P" << setfill('0') << setw(4) << (lastID + 1); // Increment lastID
                productId = nextID.str();
            }
            else {
                // If no existing records, start from P0001
                productId = "P0001";
            }

            mysql_free_result(res);
        }
        else {
            cout << "Error generating ProductID: " << mysql_error(conn) << endl;
            cout << "Press any key to continue...";
            _getch();
            ProductMenu();  // Return to the Product Menu
            return;
        }

        cout << "Enter Product Name to insert or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, productName);

        if (productName.empty()) {
            // If the input is empty, go back to the Employee Record menu
            break;
        }

        cout << endl;
        // Input validation for quantity
        do {
            cout << "Enter Product Quantity: ";
            getline(cin, input); // Read the entire line
            stringstream quantityStream(input);

            bool validInput = true;

            for (char ch : input) {
                if (!isdigit(ch)) {
                    validInput = false;
                    break;
                }
            }

            if (validInput && quantityStream >> productQuantity && quantityStream.eof() && productQuantity >= 0) {
                break; // Exit the loop when valid input is received
            }
            else {
                cout << "Invalid input. Please enter a valid format for quantity." << endl;
            }
        } while (true);

        cout << endl;
        // Input validation for price
        do {
            cout << "Enter Product Price: ";
            getline(cin, input); // Read the entire line
            stringstream priceStream(input);

            bool validInput = true;

            for (char ch : input) {
                if (!isdigit(ch) && ch != '.') {
                    validInput = false;
                    break;
                }
            }

            if (validInput && priceStream >> productPrice && priceStream.eof() && productPrice >= 0) {
                break; // Exit the loop when valid input is received
            }
            else {
                cout << "Invalid input. Please enter a valid format for price." << endl;
            }
        } while (true);

        cout << endl;
        // Input validation for supplier ID
        do {
            cout << "Enter Supplier ID: ";
            cin >> supplierID;
            cout << endl;

            // Check if the supplier exists
            if (!CheckSupplierExistence(supplierID)) {
                cout << "Supplier with ID '" << supplierID << "' does not exist. Please enter a valid supplier ID." << endl;
            }
            else {
                validSupplier = true;
            }

        } while (!validSupplier);

        query = "INSERT INTO product (ProductID, ProductName, ProductQuantity, ProductPrice, SupplierID) VALUES ('" + productId + "', '" + productName + "', " + to_string(productQuantity) + ", " + to_string(productPrice) + ", '" + supplierID + "')";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            cout << "Product added successfully!" << endl;
        }
        else {
            cout << "Failed to add product: " << mysql_error(conn) << endl;
        }

        cout << "Do you want to add another product? (Y/N): ";
        cin >> addMore;
        cout << endl;

    } while (addMore == 'Y' || addMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    ProductMenu(); // Return to the Product Menu
}

void UpdateProduct() {
    char continueOption;

    do {
        system("cls");
        // Display the product list
        string query = "SELECT * FROM product";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(20) << "Product ID"
                << setw(30) << "Product Name"
                << setw(20) << "Price"
                << setw(15) << "Quantity"
                << setw(15) << "Supplier ID" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;

            // Display product data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(35) << row[1]
                    << setw(24) << row[2]
                    << setw(15) << row[3]
                    << setw(15) << row[4] << endl;
                cout << "--------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
        }

        string productId;
        int updateChoice;

        cout << "Enter Product ID to update or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, productId);

        if (productId.empty()) {
            // If the input is empty, go back to the Product Menu
            break;
        }

        if (CheckProductExistence(productId)) {
            cout << "\nWhat do you want to update?" << endl;
            cout << endl;
            cout << "1. Product Quantity" << endl;
            cout << endl;
            cout << "2. Product Price" << endl;
            cout << endl;
            cout << "Enter your choice: ";
            cin >> updateChoice;
            cout << endl;

            if (updateChoice == 1) {
                // Update product quantity
                int newQuantity;
                string input;

                do {
                    cout << "Enter new quantity: ";
                    cin.ignore(); // Clear the input buffer
                    cin >> input; // Read the entire line
                    stringstream quantityStream(input);

                    bool validInput = true;

                    for (char ch : input) {
                        if (!isdigit(ch)) {
                            validInput = false;
                            break;
                        }
                    }

                    if (validInput && quantityStream >> newQuantity && quantityStream.eof() && newQuantity >= 0) {
                        string updateQuery = "UPDATE product SET ProductQuantity = " + to_string(newQuantity) + " WHERE ProductID = '" + productId + "'";
                        UpdateProductQuery(updateQuery);
                        break;
                    }
                    else {
                        cout << "Invalid input. Please enter a valid format for quantity." << endl;
                    }
                } while (true);
            }
            else if (updateChoice == 2) {
                // Update product price
                double newPrice;
                string input;

                do {
                    cout << "Enter new price: ";
                    cin.ignore(); // Clear the input buffer
                    cin >> input; // Read the entire line
                    stringstream priceStream(input);

                    bool validInput = true;

                    for (char ch : input) {
                        if (!isdigit(ch) && ch != '.') {
                            validInput = false;
                            break;
                        }
                    }

                    if (validInput && priceStream >> newPrice && priceStream.eof() && newPrice >= 0) {
                        string updateQuery = "UPDATE product SET ProductPrice = " + to_string(newPrice) + " WHERE ProductID = '" + productId + "'";
                        UpdateProductQuery(updateQuery);
                        break;
                    }
                    else {
                        cout << "Invalid input. Please enter a valid format for price." << endl;
                    }
                } while (true);
            }
            else {
                cout << "Invalid choice. Please choose 1 or 2." << endl;
            }
        }
        else {
            cout << "Product not found." << endl;
        }

        cout << "\nDo you want to update another product? (Y/N): ";
        cin >> continueOption;
        cout << endl;
    } while (continueOption == 'Y' || continueOption == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    ProductMenu(); // Return to the Product Menu
}


void DeleteProduct() {
    char continueOption;

    do {
        system("cls");
        // Display the product list
        string query = "SELECT * FROM product";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(20) << "Product ID"
                << setw(30) << "Product Name"
                << setw(20) << "Price"
                << setw(15) << "Quantity"
                << setw(15) << "Supplier ID" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------" << endl;

            // Display product data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(35) << row[1]
                    << setw(24) << row[2]
                    << setw(15) << row[3]
                    << setw(15) << row[4] << endl;
                cout << "--------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch product list: " << mysql_error(conn) << endl;
        }

        string productId;

        cout << "Enter Product ID to delete or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, productId);

        if (productId.empty()) {
            // If the input is empty, go back to the Product Menu
            break;
        }

        // Check if the product exists
        if (CheckProductExistence(productId)) {
            string deleteQuery = "DELETE FROM product WHERE ProductID = '" + productId + "'";
            DeleteProductQuery(deleteQuery);
        }
        else {
            cout << "Product not found." << endl;
        }

        cout << "Do you want to delete another product? (Y/N): ";
        cin >> continueOption;
        cout << endl;
    } while (continueOption == 'Y' || continueOption == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    ProductMenu(); // Return to the Product Menu
}




                                                                       
void CustomerMenu() {
    string choice;
    

    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tCustomer Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Add Customer" << endl;
        cout << endl;
        cout << "2. Update Customer" << endl;
        cout << endl;
        cout << "3. Delete Customer" << endl;
        cout << endl;
        cout << "4. Back to Employee Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            AddCustomer();
        }
        else if (choice == "2") {
            UpdateCustomer();
        }
        else if (choice == "3") {
            DeleteCustomer();
        }

        else if (choice == "4") {
            EmployeeMenu(); // Go back to the Employee Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 6." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
}
void AddCustomer() {
    char addMore;
    string customerId, customerName, phoneNumber;
    string query;
    do {
        system("cls");

        // Display the customer list
        string query = "SELECT * FROM customer";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(15) << "Customer ID" << setw(30) << "Customer Name" << setw(15) << "Phone Number" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] << setw(30) << row[1] << setw(15) << row[2] << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch customer list: " << mysql_error(conn) << endl;
        }


        // Auto-generate the CustomerID in the format 'C0001', 'C0002', etc.
        string lastIDQuery = "SELECT CustomerID FROM customer ORDER BY CustomerID DESC LIMIT 1";
        qstate = mysql_query(conn, lastIDQuery.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);

            if (row) {
                // Extract the numeric part of the existing CustomerID and increment
                int lastID = atoi(row[0] + 1);
                stringstream nextID;
                nextID << "C" << setfill('0') << setw(4) << (lastID + 1); // Increment lastID
                customerId = nextID.str();
            }
            else {
                // If no existing records, start from C0001
                customerId = "C0001";
            }

            mysql_free_result(res);
        }
        else {
            cout << "Error generating CustomerID: " << mysql_error(conn) << endl;
            cout << "Press any key to continue...";
            _getch();
            CustomerMenu();  // Return to the Customer Menu
            return;
        }

        cout << "Enter Customer Name: ";
        cin.ignore(); // Ignore the newline character from previous input
        getline(cin, customerName);
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;

        query = "INSERT INTO customer (CustomerID, CustomerName, PhoneNumber) VALUES ('" + customerId + "', '" + customerName + "', '" + phoneNumber + "')";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            cout << "Customer added successfully!" << endl;
        }
        else {
            cout << "Failed to add customer: " << mysql_error(conn) << endl;
        }

        cout << "\nDo you want to add another customer? (Y/N): ";
        cin >> addMore;
    } while (addMore == 'Y' || addMore == 'y');


    cout << "\nPress any key to continue...";
    _getch();
    CustomerMenu(); // Return to the Customer Menu

}
void DeleteCustomer() {
    char deleteMore;
    string customerId;

    do {
        system("cls");

        // Display the customer list
        string query = "SELECT * FROM customer";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(15) << "Customer ID" << setw(30) << "Customer Name" << setw(15) << "Phone Number" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] << setw(30) << row[1] << setw(15) << row[2] << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch customer list: " << mysql_error(conn) << endl;
        }

        cout << "Enter Customer ID to delete: ";
        cin >> customerId;

        // Check if the customer exists
        if (CheckCustomerExistence(customerId)) {
            string deleteQuery = "DELETE FROM customer WHERE CustomerID = '" + customerId + "'";
            DeleteCustomerQuery(deleteQuery);
        }
        else {
            cout << "Customer not found." << endl;
        }

        cout << "Do you want to delete another customer? (Y/N): ";
        cin >> deleteMore;
    } while (deleteMore == 'Y' || deleteMore == 'y');

    cout << "\nPress any key to continue...";
    _getch();
    CustomerMenu();
}
void UpdateCustomer() {
    char updateMore;
    string customerId;

    do {
        system("cls");

        // Display the customer list
        string query = "SELECT * FROM customer";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            cout << left << setw(15) << "Customer ID" << setw(30) << "Customer Name" << setw(15) << "Phone Number" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] << setw(30) << row[1] << setw(15) << row[2] << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch customer list: " << mysql_error(conn) << endl;
        }

        cout << "Enter Customer ID to update: ";
        cin >> customerId;

        if (CheckCustomerExistence(customerId)) {
            cout << "What do you want to update?" << endl;
            cout << "1. Update Customer Name" << endl;
            cout << "2. Update Phone Number" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                string customerName;
                cout << "Enter new Customer Name: ";
                cin.ignore(); // Ignore the newline character from previous input
                getline(cin, customerName);

                string updateQuery = "UPDATE customer SET CustomerName = '" + customerName + "' WHERE CustomerID = '" + customerId + "'";
                UpdateCustomerQuery(updateQuery);
            }
            else if (choice == 2) {
                string phoneNumber;
                cout << "Enter new Phone Number: ";
                cin >> phoneNumber;

                string updateQuery = "UPDATE customer SET PhoneNumber = '" + phoneNumber + "' WHERE CustomerID = '" + customerId + "'";
                UpdateCustomerQuery(updateQuery);
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        else {
            cout << "Customer not found." << endl;
        }

        cout << "Do you want to update another customer? (Y/N): ";
        cin >> updateMore;
    } while (updateMore == 'Y' || updateMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    CustomerMenu(); // Return to the Customer Menu
}




void OrderMenu() {
    string choice;
    
    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tOrder Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Add Order" << endl;
        cout << endl;
        cout << "2. Update Order" << endl;
        cout << endl;
        cout << "3. Delete Order" << endl;
        cout << endl;
        cout << "4. Back to Employee Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            AddOrder();
        }
        else if (choice == "2") {
            UpdateOrder();
        }
        else if (choice == "3") {
            DeleteOrder();
        }
        else if (choice == "4") {
            EmployeeMenu();
        }

        else {
            cout << "Invalid choice. Please choose 1 ~ 4." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
}
void AddOrder() {
    char addMore;
    string orderID, orderDate, orderQuantity, productID;
    bool validProduct = false;

    do {
        system("cls");

        // Display the existing order list
        string orderListQuery = "SELECT * FROM `order`";
        qstate = mysql_query(conn, orderListQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Order ID"
                << setw(15) << "Order Date" 
                << setw(20) << "Order Quantity" 
                << setw(15) << "Product ID" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            // Display order data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] 
                    << setw(22) << row[1] 
                    << setw(15) << row[2] 
                    << setw(15) << row[3] << endl;
                cout << "-----------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch order list: " << mysql_error(conn) << endl;
        }
        cout << endl;

        cout << "Enter Product ID for the order or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, productID);

        if (productID.empty()) {
            // If the input is empty, go back to the Order Menu
            break;
        }

        do {
            
            // Check if the product exists
            if (!CheckProductExistence(productID)) {
                cout << "Product with ID '" << productID << "' does not exist. Please enter a valid Product ID." << endl;
                cout << endl;
                cout << "Enter Product ID for the order or press 'Enter' to go back: ";
                getline(cin, productID);

                if (productID.empty()) {
                    // If the input is empty, go back to the Order Menu
                    break;
                }
            }
            else {
                validProduct = true;
            }

        } while (!validProduct);

        // If validProduct is false, it means the loop was terminated due to an empty input
        if (!validProduct) {
            break; // Exit the loop if the input is empty
        }

        // Auto-generate the OrderID in the format 'O0001', 'O0002', etc.
        string lastOrderIDQuery = "SELECT OrderID FROM `order` ORDER BY OrderID DESC LIMIT 1";
        qstate = mysql_query(conn, lastOrderIDQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            if (row) {
                // Extract the numeric part of the existing OrderID and increment
                int lastOrderID = atoi(row[0] + 1);
                stringstream nextOrderID;
                nextOrderID << "O" << setfill('0') << setw(4) << (lastOrderID + 1); // Increment lastOrderID
                orderID = nextOrderID.str();
            }
            else {
                // If no existing records, start from O0001
                orderID = "O0001";
            }

            mysql_free_result(res);
        }
        else {
            cout << "Error generating OrderID: " << mysql_error(conn) << endl;
            cout << "Press any key to continue...";
            _getch();
            OrderMenu(); // Return to the Order Menu
            return;
        }
        cout << endl;
        cout << "Enter Order Date (YYYY-MM-DD): ";

        do {
            cin >> orderDate;

            if (!isValidDateFormat(orderDate)) {
                ClearLastLine();
                cout << "Invalid date format. Please enter the date in the format YYYY-MM-DD: ";
            }
        } while (!isValidDateFormat(orderDate));

        cout << endl;
        cout << "Enter Order Quantity: ";
        cin >> orderQuantity;
        cout << endl;

        // Check if there is sufficient stock for the order
        if (!CheckStockAvailability(productID, stoi(orderQuantity))) {
            cout << "Do you want to add another order? (Y/N): ";
            cin >> addMore;

            if (addMore == 'Y' || addMore == 'y') {
                continue; // Skip the rest of the loop and start a new iteration
            }
            else {
                break; // Exit the loop if the user chooses not to add another order
            }
        }

        // SQL query to insert data into the orders table
        string query = "INSERT INTO `order` (OrderID, OrderDate, OrderQuantity, ProductID) VALUES ('" + orderID + "', '" + orderDate + "', '" + orderQuantity + "', '" + productID + "')";

        // Execute the query
        if (mysql_query(conn, query.c_str()) == 0) {
            cout << "Order added successfully!" << endl;

            // Update stock levels
            UpdateStockLevels(productID, stoi(orderQuantity));
        }
        else {
            cout << "Failed to add order: " << mysql_error(conn) << endl;
            return; // Exit the function if the query fails
        }
        cout << endl;
        cout << "Do you want to add another order? (Y/N): ";
        cin >> addMore;

    } while (addMore == 'Y' || addMore == 'y');
    cout << endl;
    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    OrderMenu(); // Return to the Order Menu
}
void DeleteOrder() {
    string orderID;
    char continueOption;

    do {
        system("cls");

        // Display the existing order list
        string orderListQuery = "SELECT * FROM `order`";
        qstate = mysql_query(conn, orderListQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Order ID"
                << setw(15) << "Order Date"
                << setw(20) << "Order Quantity"
                << setw(15) << "Product ID" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            // Display order data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(22) << row[1]
                    << setw(15) << row[2]
                    << setw(15) << row[3] << endl;
                cout << "-----------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch order list: " << mysql_error(conn) << endl;
        }
        cout << endl;


        cout << "Enter Order ID for delete or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, orderID);
        cout << endl;
        if (orderID.empty()) {
            // If the input is empty, go back to the Order Menu
            break;
        }

        if (CheckOrderExistence(orderID)) {
            // SQL query to delete the order from the database
            string deleteQuery = "DELETE FROM `order` WHERE OrderID = '" + orderID + "'";
            DeleteOrderQuery(deleteQuery);
        }
        else {
            cout << "Order not found." << endl;
        }
        cout << endl;
        cout << "Do you want to delete another order? (Y/N): ";
        cin >> continueOption;
    } while (continueOption == 'Y' || continueOption == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    OrderMenu(); // Return to the Order Menu
}
void UpdateOrder() {
    string orderID;
    char updateMore;

    do {
        // Display the order list
        system("cls");

        // Display the existing order list
        string orderListQuery = "SELECT * FROM `order`";
        qstate = mysql_query(conn, orderListQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Order ID"
                << setw(15) << "Order Date"
                << setw(20) << "Order Quantity"
                << setw(15) << "Product ID" << endl;
            cout << "-----------------------------------------------------------------" << endl;

            // Display order data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(22) << row[1]
                    << setw(15) << row[2]
                    << setw(15) << row[3] << endl;
                cout << "-----------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch order list: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Enter Order ID for update or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, orderID);
        cout << endl;
        if (orderID.empty()) {
            // If the input is empty, go back to the Order Menu
            break;
        }

        if (CheckOrderExistence(orderID)) {
            cout << "What do you want to update for order " << orderID << "?" << endl;
            cout << endl;
            cout << "1. Update Order Date" << endl;
            cout << endl;
            cout << "2. Update Order Quantity" << endl;
            cout << endl;
           
            cout << "Enter your choice: ";
            int updateChoice;
            cin >> updateChoice;
            cout << endl;
            if (updateChoice == 1) {
                string newOrderDate;
                do {
                    cout << "Enter new Order Date (YYYY-MM-DD): ";
                    cin >> newOrderDate;

                    if (!isValidDateFormat(newOrderDate)) {
                        ClearLastLine();
                        cout << "Invalid date format. Please enter the date in the format YYYY-MM-DD: ";
                    }
                } while (!isValidDateFormat(newOrderDate));

                string updateQuery = "UPDATE `order` SET OrderDate = '" + newOrderDate + "' WHERE OrderID = '" + orderID + "'";
                UpdateOrderQuery(updateQuery);
            }
            else if (updateChoice == 2) {
                int newOrderQuantity;
                string input;

                do {
                    cout << "Enter new Order Quantity: ";
                    cin.ignore(); // Clear the input buffer
                    cin >> input; // Read the entire line
                    stringstream quantityStream(input);

                    bool validInput = true;

                    for (char ch : input) {
                        if (!isdigit(ch)) {
                            validInput = false;
                            break;
                        }
                    }

                    if (validInput && quantityStream >> newOrderQuantity && quantityStream.eof() && newOrderQuantity >= 0) {
                        string updateQuery = "UPDATE `order` SET OrderQuantity = '" + to_string(newOrderQuantity) + "' WHERE OrderID = '" + orderID + "'";
                        UpdateOrderQuery(updateQuery);
                        break;
                    }
                    else {
                        cout << endl;
                        cout << "Invalid input. Please enterv valid format for order quantity." << endl;
                        cout << endl;
                    }
                } while (true);
            }
            
            else {
                cout << "Invalid choice. Please choose 1 or 2." << endl;
            }
        }
        else {
            
            cout << "Order not found." << endl;
        }
        cout << endl;
        cout << "Do you want to update another order? (Y/N): ";
        cin >> updateMore;
    } while (updateMore == 'Y' || updateMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    OrderMenu(); // Return to the Order Menu
}





void SupplierMenu() {
    string choice;
   
    do {
        system("cls");
        cout << "===============================" << endl;
        cout << "\tSupplier Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Add Supplier" << endl;
        cout << endl;
        cout << "2. Delete Supplier" << endl;
        cout << endl;
        cout << "3. Update Supplier" << endl;
        cout << endl;
        cout << "4. Back to Employee Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            AddSupplier();
        }
        else if (choice == "2") {
            DeleteSupplier();
        }
        else if (choice == "3") {
            UpdateSupplier();
        }
        else if (choice == "4") {
            EmployeeMenu(); // Go back to the Admin Main Menu
        }
        else {
            cout << "Invalid choice. Please choose 1 ~ 5." << endl;
            cout << endl;
            cout << "Press any key to continue...";
            _getch();  // Wait for a key press
        }
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
}
void AddSupplier() {
    char addMore;
    string supplierID, companyName, phoneNumber, supplierAddress, contactPerson, emailAddress;
    string query;

    do {
        system("cls");

        // Display the supplier list
        string query = "SELECT * FROM supplier";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Supplier ID"
                << setw(30) << "Company Name"
                << setw(20) << "Phone Number"
                << setw(62) << "Supplier Address"
                << setw(30) << "Contact Person"
                << setw(30) << "Email Address" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            // Display supplier data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]
                    << setw(30) << row[1]
                    << setw(20) << row[2]
                    << setw(62) << row[3]
                    << setw(30) << row[4]
                    << setw(30) << row[5] << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch supplier list: " << mysql_error(conn) << endl;
        }

        // Auto-generate the SupplierID in the format 'S0001', 'S0002', etc.
        string lastIDQuery = "SELECT SupplierID FROM supplier ORDER BY SupplierID DESC LIMIT 1";
        qstate = mysql_query(conn, lastIDQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            if (row) {
                // Extract the numeric part of the existing SupplierID and increment
                int lastID = atoi(row[0] + 1);
                stringstream nextID;
                nextID << "S" << setfill('0') << setw(4) << (lastID + 1); // Increment lastID
                supplierID = nextID.str();
            }
            else {
                // If no existing records, start from S0001
                supplierID = "S0001";
            }

            mysql_free_result(res);
        }
        else {
            cout << "Error generating SupplierID: " << mysql_error(conn) << endl;
            cout << "Press any key to continue...";
            _getch();
            SupplierMenu(); // Return to the Supplier Menu
            return;
        }
        cout << endl;

        cout << "Enter Company Name or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, companyName);
        cout << endl;
        if (companyName.empty()) {
            // If the input is empty, go back to the Product Menu
            break;
        }

        // Phone Number Validation
        cout << "Enter Phone Number: ";
        while (true) {
            getline(cin, phoneNumber);

            bool isValid = true;

            for (char ch : phoneNumber) {
                if (!isdigit(ch)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid && phoneNumber.length() >= 9 && phoneNumber.length() <= 11) {
                break; // Exit the loop when input is valid
            }

            cout << "Please enter valid format of phone number. Try again: ";
            
        }
        
        cout << endl;
        cout << "Enter Supplier Address: ";
        
        getline(cin, supplierAddress);
        cout << endl;

        cout << "Enter Contact Person: ";
        getline(cin, contactPerson);
        cout << endl;

        // Email Address Validation
        cout << "Enter Email Address: ";
        while (true) {
            getline(cin, emailAddress);
            if (Email_check(emailAddress)) {
                break; // Exit the loop when input is valid
            }

            cout << "Invalid email address. Please try again: ";
            
        }

        query = "INSERT INTO supplier (SupplierID, CompanyName, PhoneNumber, SupplierAddress, ContactPerson, EmailAddress) VALUES ('" + supplierID + "', '" + companyName + "', '" + phoneNumber + "', '" + supplierAddress + "', '" + contactPerson + "', '" + emailAddress + "')";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            cout << "Supplier added successfully!" << endl;
        }
        else {
            cout << "Failed to add supplier: " << mysql_error(conn) << endl;
        }

        cout << "\nDo you want to add another supplier? (Y/N): ";
        cin >> addMore;
        cout << endl;
    } while (addMore == 'Y' || addMore == 'y');

    cout << "\nPress any key to continue...";
    _getch();
    SupplierMenu(); // Return to the Supplier Menu
}

void DeleteSupplier() {
    char deleteMore;
    string supplierID;

    do {
        system("cls");

        // Display the supplier list
        string query = "SELECT * FROM supplier";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Supplier ID" <<
                setw(30) << "Company Name" <<
                setw(20) << "Phone Number" <<
                setw(62) << "Supplier Address" <<
                setw(30) << "Contact Person" <<
                setw(30) << "Email Address" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            // Display supplier data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] <<
                    setw(30) << row[1] <<
                    setw(20) << row[2] <<
                    setw(62) << row[3] <<
                    setw(30) << row[4] <<
                    setw(30) << row[5] << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch supplier list: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Enter Supplier ID to delete or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, supplierID);
        
        if (supplierID.empty()) {
            // If the input is empty, go back to the Product Menu
            break;
        }
        cout << endl;
        // Check if the supplier exists
        if (CheckSupplierExistence(supplierID)) {
            // SQL query to delete the supplier from the database
            string deleteQuery = "DELETE FROM supplier WHERE SupplierID = '" + supplierID + "'";
            DeleteSupplierQuery(deleteQuery);

          
        }
        else {
            cout << "Supplier not found." << endl;
        }

        cout << "Do you want to delete another supplier? (Y/N): ";
        cin >> deleteMore;
    } while (deleteMore == 'Y' || deleteMore == 'y');

    cout << "\nPress any key to continue...";
    _getch();
    SupplierMenu();
}
void UpdateSupplier() {
    char updateMore;
    string supplierID;

    do {
        system("cls");

        // Display the supplier list
        string query = "SELECT * FROM supplier";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            // Display column headers with horizontal lines
            cout << left << setw(15) << "Supplier ID" <<
                setw(30) << "Company Name" <<
                setw(20) << "Phone Number" <<
                setw(62) << "Supplier Address" <<
                setw(30) << "Contact Person" <<
                setw(30) << "Email Address" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            // Display supplier data with horizontal lines
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0] <<
                    setw(30) << row[1] <<
                    setw(20) << row[2] <<
                    setw(62) << row[3] <<
                    setw(30) << row[4] <<
                    setw(30) << row[5] << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }

            mysql_free_result(res);
        }
        else {
            cout << "Failed to fetch supplier list: " << mysql_error(conn) << endl;
        }
        cout << endl;
        cout << "Enter Supplier ID to update or press 'Enter' to go back: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, supplierID);
        cout << endl;
        if (supplierID.empty()) {
            // If the input is empty, go back to the Product Menu
            break;
        }
        

        if (CheckSupplierExistence(supplierID)) {
            cout << "What do you want to update for supplier " << supplierID << "?" << endl;
            cout << endl;
            cout << "1. Update Company Name" << endl;
            cout << endl;
            cout << "2. Update Phone Number" << endl;
            cout << endl;
            cout << "3. Update Supplier Address" << endl;
            cout << endl;
            cout << "4. Update Contact Person" << endl;
            cout << endl;
            cout << "5. Update Email Address" << endl;
            cout << endl;
            cout << "Enter your choice: ";

            int updateChoice;
            cin >> updateChoice;
            cout << endl;
            cin.ignore(); // Clear the newline character from the buffer

            string updateQuery;

            switch (updateChoice) {
            case 1: {
                string newCompanyName;
                cout << "Enter new Company Name: ";
                getline(cin, newCompanyName);
                updateQuery = "UPDATE supplier SET CompanyName = '" + newCompanyName + "' WHERE SupplierID = '" + supplierID + "'";
                break;
            }
            case 2: {
                
                string newPhoneNumber;
                cout << "Enter new Phone Number: ";
                while (true) {
                    getline(cin, newPhoneNumber);

                    bool isValid = true;

                    for (char ch : newPhoneNumber) {
                        if (!isdigit(ch)) {
                            isValid = false;
                            break;
                        }
                    }

                    if (isValid && newPhoneNumber.length() >= 9 && newPhoneNumber.length() <= 11) {
                        break; // Exit the loop when input is valid
                    }

                    cout << "Please enter valid format of phone number. Try again: ";
                    
                }
                updateQuery = "UPDATE supplier SET PhoneNumber = '" + newPhoneNumber + "' WHERE SupplierID = '" + supplierID + "'";
                break;
            }
            case 3: {
                cout << endl;
                string newSupplierAddress;
                cout << "Enter new Supplier Address: ";
                getline(cin, newSupplierAddress);
                updateQuery = "UPDATE supplier SET SupplierAddress = '" + newSupplierAddress + "' WHERE SupplierID = '" + supplierID + "'";
                break;
            }
            case 4: {
                cout << endl;
                string newContactPerson;
                cout << "Enter new Contact Person: ";
                getline(cin, newContactPerson);
                updateQuery = "UPDATE supplier SET ContactPerson = '" + newContactPerson + "' WHERE SupplierID = '" + supplierID + "'";
                break;
            }
            case 5: {
                cout << endl;
                string newEmailAddress;
                cout << "Enter new Email Address: ";
                while (true) {
                    getline(cin, newEmailAddress);
                    if (Email_check(newEmailAddress)) {
                        break; // Exit the loop when input is valid
                    }

                    cout << "Invalid email address. Please try again: ";
                    
                }
                updateQuery = "UPDATE supplier SET EmailAddress = '" + newEmailAddress + "' WHERE SupplierID = '" + supplierID + "'";
                break;
            }
            default:
                cout << "Invalid choice. Please choose a number between 1 and 5." << endl;
                continue;
            }

            UpdateSupplierQuery(updateQuery);

        }
        else {
            cout << "Supplier not found." << endl;
        }
        cout << endl;
        cout << "Do you want to update another supplier? (Y/N): ";
        cin >> updateMore;

    } while (updateMore == 'Y' || updateMore == 'y');

    cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    SupplierMenu(); // Return to the Supplier Menu
}








