#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for User
struct User {
    int userID;
    char name[50];
    char mobile[15];
    char email[50];
    char password[20];
    float walletBalance;
};

// Structure for Transaction
struct Transaction {
    int transID;
    char date[20];
    char time[20];
    char type[20]; // Recharge, Bill Payment
    char service[20]; // Mobile, DTH, etc.
    float amount;
    char status[10]; // Success, Failed
    float cashback;
};

// Structure for RechargePlan
struct RechargePlan {
    char operator[20];
    float amount;
    char validity[20];
    char benefits[100];
};

// Structure for Service (for bills)
struct Service {
    char type[20]; // Postpaid, Electricity, Water
    float billAmount;
};

// Global arrays
#define MAX_USERS 10
struct User users[MAX_USERS] = {
    {1, "Alice", "9876543210", "alice@example.com", "pass123", 1000.0},
    {2, "Bob", "9876543211", "bob@example.com", "pass456", 1500.0},
    {3, "Charlie", "9876543212", "charlie@example.com", "pass789", 800.0}
};
int userCount = 3;

struct Transaction transactions[50]; // Last 50 transactions
int transCount = 0;

struct RechargePlan prepaidPlans[5] = {
    {"Airtel", 99.0, "28 days", "1GB/day"},
    {"Jio", 199.0, "28 days", "1.5GB/day"},
    {"Vi", 299.0, "28 days", "2GB/day"},
    {"Airtel", 499.0, "56 days", "2GB/day"},
    {"Jio", 666.0, "84 days", "1.5GB/day"}
};

struct RechargePlan dthPlans[3] = {
    {"Tata Sky", 299.0, "1 month", "Basic pack"},
    {"Dish TV", 499.0, "1 month", "Standard pack"},
    {"Airtel Digital TV", 799.0, "1 month", "Premium pack"}
};

// Function to get current date and time
void getDateTime(char* date, char* time) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(date, 20, "%Y-%m-%d", tm_info);
    strftime(time, 20, "%H:%M:%S", tm_info);
}

// Function to find user by phone or email
struct User* findUser(char* identifier) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].mobile, identifier) == 0 || strcmp(users[i].email, identifier) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

// Function to check if phone or email is already registered
int isRegistered(char* mobile, char* email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].mobile, mobile) == 0 || strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to register a new user
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }
    
    char name[50], mobile[15], email[50], password[20];
    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Mobile Number: ");
    scanf("%s", mobile);
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);
    
    if (isRegistered(mobile, email)) {
        printf("Mobile or Email already registered.\n");
        return;
    }
    
    users[userCount].userID = userCount + 1;
    strcpy(users[userCount].name, name);
    strcpy(users[userCount].mobile, mobile);
    strcpy(users[userCount].email, email);
    strcpy(users[userCount].password, password);
    users[userCount].walletBalance = 0.0;
    userCount++;
    
    printf("Registration successful. Your User ID is %d.\n", users[userCount-1].userID);
}

// Function to simulate login
struct User* login() {
    char identifier[50], password[20];
    printf("Enter Mobile Number or Email: ");
    scanf("%s", identifier);
    printf("Enter Password: ");
    scanf("%s", password);
    
    struct User* user = findUser(identifier);
    if (user && strcmp(user->password, password) == 0) {
        printf("Login successful. Welcome %s!\n", user->name);
        return user;
    } else {
        printf("Invalid credentials.\n");
        return NULL;
    }
}

// Function to add money to wallet
void addMoney(struct User* user) {
    float amount;
    printf("Enter amount to add: ");
    scanf("%f", &amount);
    user->walletBalance += amount;
    printf("Wallet updated. New balance: ₹%.2f\n", user->walletBalance);
}

// Function to check wallet balance
void checkBalance(struct User* user) {
    printf("Wallet Balance: ₹%.2f\n", user->walletBalance);
}

// Function to process payment
int processPayment(struct User* user, float amount, char* mode) {
    if (strcmp(mode, "wallet") == 0) {
        if (user->walletBalance >= amount) {
            user->walletBalance -= amount;
            return 1;
        } else {
            printf("Insufficient wallet balance.\n");
            return 0;
        }
    } else if (strcmp(mode, "credit") == 0 || strcmp(mode, "debit") == 0) {
        // Simulate card payment
        printf("Card payment simulated. Enter card details (dummy): ");
        char dummy[20];
        scanf("%s", dummy);
        return 1;
    }
    return 0;
}

// Function to calculate cashback
float calculateCashback(char* type, float amount) {
    if (strcmp(type, "Recharge") == 0) {
        return amount * 0.02; // 2%
    } else if (strcmp(type, "Bill Payment") == 0) {
        return amount * 0.01; // 1%
    }
    return 0.0;
}

// Function to add transaction
void addTransaction(struct User* user, char* type, char* service, float amount, char* status, float cashback) {
    if (transCount < 50) {
        transactions[transCount].transID = transCount + 1;
        getDateTime(transactions[transCount].date, transactions[transCount].time);
        strcpy(transactions[transCount].type, type);
        strcpy(transactions[transCount].service, service);
        transactions[transCount].amount = amount;
        strcpy(transactions[transCount].status, status);
        transactions[transCount].cashback = cashback;
        transCount++;
    } else {
        // Shift array for circular buffer
        for (int i = 0; i < 49; i++) {
            transactions[i] = transactions[i+1];
        }
        transactions[49].transID = transCount + 1;
        getDateTime(transactions[49].date, transactions[49].time);
        strcpy(transactions[49].type, type);
        strcpy(transactions[49].service, service);
        transactions[49].amount = amount;
        strcpy(transactions[49].status, status);
        transactions[49].cashback = cashback;
        transCount++;
    }
    // Credit cashback to wallet
    user->walletBalance += cashback;
}

// Function for prepaid recharge
void prepaidRecharge(struct User* user) {
    printf("Select Operator: 1. Airtel 2. Jio 3. Vi\n");
    int op;
    scanf("%d", &op);
    if (op < 1 || op > 3) {
        printf("Invalid operator selection.\n");
        return;
    }
    char operators[3][10] = {"Airtel", "Jio", "Vi"};
    char selectedOp[20];
    strcpy(selectedOp, operators[op-1]);
    
    // Collect and display plans for selected operator
    int planIndices[5];
    int planCount = 0;
    printf("Plans:\n");
    for (int i = 0; i < 5; i++) {
        if (strcmp(prepaidPlans[i].operator, selectedOp) == 0) {
            planIndices[planCount] = i;
            printf("%d. ₹%.0f - %s (%s)\n", planCount+1, prepaidPlans[i].amount, prepaidPlans[i].benefits, prepaidPlans[i].validity);
            planCount++;
        }
    }
    
    int plan;
    printf("Select plan: ");
    scanf("%d", &plan);
    if (plan < 1 || plan > planCount) {
        printf("Invalid plan selection.\n");
        return;
    }
    int selectedIndex = planIndices[plan-1];
    float amount = prepaidPlans[selectedIndex].amount;
    
    printf("Select Payment Mode: 1. Wallet 2. Credit Card 3. Debit Card\n");
    int mode;
    scanf("%d", &mode);
    if (mode < 1 || mode > 3) {
        printf("Invalid payment mode.\n");
        return;
    }
    char modes[3][10] = {"wallet", "credit", "debit"};
    if (processPayment(user, amount, modes[mode-1])) {
        float cashback = calculateCashback("Recharge", amount);
        addTransaction(user, "Recharge", "Prepaid Mobile", amount, "Success", cashback);
        printf("Recharge successful. Cashback: ₹%.2f\n", cashback);
    } else {
        addTransaction(user, "Recharge", "Prepaid Mobile", amount, "Failed", 0.0);
    }
}

// Function for DTH recharge
void dthRecharge(struct User* user) {
    printf("Select DTH: 1. Tata Sky 2. Dish TV 3. Airtel Digital TV\n");
    int op;
    scanf("%d", &op);
    if (op < 1 || op > 3) {
        printf("Invalid selection.\n");
        return;
    }
    float amount = dthPlans[op-1].amount;
    printf("Selected Plan: ₹%.0f - %s (%s)\n", amount, dthPlans[op-1].benefits, dthPlans[op-1].validity);
    
    printf("Select Payment Mode: 1. Wallet 2. Credit Card 3. Debit Card\n");
    int mode;
    scanf("%d", &mode);
    if (mode < 1 || mode > 3) {
        printf("Invalid payment mode.\n");
        return;
    }
    char modes[3][10] = {"wallet", "credit", "debit"};
    if (processPayment(user, amount, modes[mode-1])) {
        float cashback = calculateCashback("Recharge", amount);
        addTransaction(user, "Recharge", "DTH", amount, "Success", cashback);
        printf("Recharge successful. Cashback: ₹%.2f\n", cashback);
    } else {
        addTransaction(user, "Recharge", "DTH", amount, "Failed", 0.0);
    }
}

// Function for bill payment (postpaid, electricity, water)
void billPayment(struct User* user, char* service) {
    float amount;
    printf("Enter bill amount: ");
    scanf("%f", &amount);
    printf("Select Payment Mode: 1. Wallet 2. Credit Card 3. Debit Card\n");
    int mode;
    scanf("%d", &mode);
    if (mode < 1 || mode > 3) {
        printf("Invalid payment mode.\n");
        return;
    }
    char modes[3][10] = {"wallet", "credit", "debit"};
    if (processPayment(user, amount, modes[mode-1])) {
        float cashback = calculateCashback("Bill Payment", amount);
        addTransaction(user, "Bill Payment", service, amount, "Success", cashback);
        printf("Payment successful. Cashback: ₹%.2f\n", cashback);
    } else {
        addTransaction(user, "Bill Payment", service, amount, "Failed", 0.0);
    }
}

// Function to show transaction history
void showHistory() {
    printf("Transaction History:\n");
    for (int i = 0; i < transCount; i++) {
        printf("ID: %d, Date: %s, Time: %s, Type: %s, Service: %s, Amount: ₹%.2f, Status: %s, Cashback: ₹%.2f\n",
               transactions[i].transID, transactions[i].date, transactions[i].time, transactions[i].type,
               transactions[i].service, transactions[i].amount, transactions[i].status, transactions[i].cashback);
    }
}

// Function for mini statement (last 5)
void miniStatement() {
    printf("Mini Statement (Last 5 Transactions):\n");
    int start = (transCount > 5) ? transCount - 5 : 0;
    for (int i = start; i < transCount; i++) {
        printf("ID: %d, Date: %s, Amount: ₹%.2f, Status: %s\n",
               transactions[i].transID, transactions[i].date, transactions[i].amount, transactions[i].status);
    }
}

// Main function
int main() {
    struct User* user = NULL;
    
    while (1) {
        if (!user) {
            printf("\n--- Welcome to Payment Platform ---\n");
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter choice: ");
            int choice;
            scanf("%d", &choice);
            
            if (choice == 1) {
                registerUser();
            } else if (choice == 2) {
                user = login();
            } else if (choice == 3) {
                printf("Exiting...\n");
                return 0;
            } else {
                printf("Invalid choice.\n");
            }
        } else {
            printf("\n--- Payment Platform Menu ---\n");
            printf("1. Add Money to Wallet\n");
            printf("2. Check Wallet Balance\n");
            printf("3. Prepaid Mobile Recharge\n");
            printf("4. DTH Recharge\n");
            printf("5. Postpaid Bill Payment\n");
            printf("6. Electricity Bill Payment\n");
            printf("7. Water Bill Payment\n");
            printf("8. Transaction History\n");
            printf("9. Mini Statement\n");
            printf("10. Logout\n");
            printf("Enter choice: ");
            int choice;
            scanf("%d", &choice);
            
            switch (choice) {
                case 1: addMoney(user); break;
                case 2: checkBalance(user); break;
                case 3: prepaidRecharge(user); break;
                case 4: dthRecharge(user); break;
                case 5: billPayment(user, "Postpaid"); break;
                case 6: billPayment(user, "Electricity"); break;
                case 7: billPayment(user, "Water"); break;
                case 8: showHistory(); break;
                case 9: miniStatement(); break;
                case 10: printf("Logged out.\n"); user = NULL; break;
                default: printf("Invalid choice.\n");
            }
        }
    }
    
    return 0;
}
// Function to modify an existing order