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
    char type[20];
    char service[20];
    float amount;
    char status[10];
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
    char type[20];
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

struct Transaction transactions[50];
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

// ✅ Fixed getDateTime function
void getDateTime(char* date, char* timeStr) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(date, 20, "%Y-%m-%d", tm_info);
    strftime(timeStr, 20, "%H:%M:%S", tm_info);
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

// Function to register new user
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    char name[50], mobile[15], email[50], password[20];
    getchar(); // clear input buffer
    printf("Enter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter Mobile Number: ");
    scanf("%14s", mobile);
    printf("Enter Email: ");
    scanf("%49s", email);
    printf("Enter Password: ");
    scanf("%19s", password);

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

    printf("Registration successful. User ID: %d\n", users[userCount - 1].userID);
}

// Function to simulate login
struct User* login() {
    char identifier[50], password[20];
    printf("Enter Mobile Number or Email: ");
    scanf("%49s", identifier);
    printf("Enter Password: ");
    scanf("%19s", password);

    struct User* user = findUser(identifier);
    if (user && strcmp(user->password, password) == 0) {
        printf("Login successful. Welcome %s!\n", user->name);
        return user;
    }
    printf("Invalid credentials.\n");
    return NULL;
}

// Function to add money
void addMoney(struct User* user) {
    float amount;
    printf("Enter amount to add: ");
    scanf("%f", &amount);
    user->walletBalance += amount;
    printf("Wallet updated. Balance: ₹%.2f\n", user->walletBalance);
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
        }
        printf("Insufficient balance.\n");
        return 0;
    } else {
        printf("Simulating %s card payment...\n", mode);
        char dummy[20];
        scanf("%19s", dummy);
        return 1;
    }
}

// Function to calculate cashback
float calculateCashback(char* type, float amount) {
    if (strcmp(type, "Recharge") == 0)
        return amount * 0.02;
    else if (strcmp(type, "Bill Payment") == 0)
        return amount * 0.01;
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
    }
    user->walletBalance += cashback;
}

// Function for prepaid recharge
void prepaidRecharge(struct User* user) {
    printf("Select Operator: 1. Airtel 2. Jio 3. Vi\n");
    int op;
    scanf("%d", &op);
    if (op < 1 || op > 3) return;
    char selectedOp[20];
    char operators[3][10] = {"Airtel", "Jio", "Vi"};
    strcpy(selectedOp, operators[op - 1]);

    printf("Plans:\n");
    int planIndices[5], planCount = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(prepaidPlans[i].operator, selectedOp) == 0) {
            planIndices[planCount] = i;
            printf("%d. ₹%.0f - %s (%s)\n", planCount + 1,
                   prepaidPlans[i].amount, prepaidPlans[i].benefits, prepaidPlans[i].validity);
            planCount++;
        }
    }
    printf("Select plan: ");
    int plan;
    scanf("%d", &plan);
    if (plan < 1 || plan > planCount) return;
    float amount = prepaidPlans[planIndices[plan - 1]].amount;

    printf("Select Payment Mode: 1. Wallet 2. Credit 3. Debit\n");
    int mode;
    scanf("%d", &mode);
    char modes[3][10] = {"wallet", "credit", "debit"};
    if (processPayment(user, amount, modes[mode - 1])) {
        float cashback = calculateCashback("Recharge", amount);
        addTransaction(user, "Recharge", "Prepaid", amount, "Success", cashback);
        printf("Recharge Successful! Cashback: ₹%.2f\n", cashback);
    } else {
        addTransaction(user, "Recharge", "Prepaid", amount, "Failed", 0.0);
    }
}

// Function to show transaction history
void showHistory() {
    printf("\nTransaction History:\n");
    for (int i = 0; i < transCount; i++) {
        printf("ID: %d | Date: %s | Time: %s | Type: %s | Service: %s | Amount: ₹%.2f | Status: %s | Cashback: ₹%.2f\n",
               transactions[i].transID, transactions[i].date, transactions[i].time,
               transactions[i].type, transactions[i].service, transactions[i].amount,
               transactions[i].status, transactions[i].cashback);
    }
}

// Main Function
int main() {
    struct User* user = NULL;
    int choice;
    while (1) {
        if (!user) {
            printf("\n--- Welcome to Payment Platform ---\n");
            printf("1. Register\n2. Login\n3. Exit\nEnter choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1: registerUser(); break;
                case 2: user = login(); break;
                case 3: return 0;
                default: printf("Invalid choice.\n");
            }
        } else {
            printf("\n--- Menu ---\n");
            printf("1. Add Money\n2. Check Balance\n3. Prepaid Recharge\n4. Transaction History\n5. Logout\nEnter: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1: addMoney(user); break;
                case 2: checkBalance(user); break;
                case 3: prepaidRecharge(user); break;
                case 4: showHistory(); break;
                case 5: user = NULL; printf("Logged out.\n"); break;
                default: printf("Invalid choice.\n");
            }
        }
    }
    return 0;
}
