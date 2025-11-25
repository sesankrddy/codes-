/*
 * Mobile Recharge and Bill Payment Platform
 * A comprehensive digital payment system for mobile recharges, bill payments, and DTH services
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 50
#define MAX_PLANS 10
#define MAX_SERVICES 5
#define MAX_NAME_LENGTH 50
#define MAX_MOBILE_LENGTH 15
#define MAX_EMAIL_LENGTH 100

// Structure Definitions
typedef struct {
    int planId;
    char operator[20];
    float amount;
    char validity[20];
    char benefits[100];
} RechargePlan;

typedef struct {
    int serviceId;
    char serviceName[30];
    char category[20]; // "recharge" or "bill"
} Service;

typedef struct {
    int transactionId;
    char date[20];
    char time[20];
    char type[20]; // "recharge", "bill", "wallet_add"
    char service[30];
    float amount;
    char status[20]; // "success", "failed"
    float cashback;
    char paymentMode[20]; // "wallet", "credit_card", "debit_card"
} Transaction;

typedef struct {
    int userId;
    char name[MAX_NAME_LENGTH];
    char mobile[MAX_MOBILE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    float walletBalance;
    int transactionCount;
    Transaction transactions[MAX_TRANSACTIONS];
} User;

// Global Variables
User users[MAX_USERS];
int userCount = 0;
int currentUserId = -1;
int transactionIdCounter = 1000;

// Predefined Recharge Plans
RechargePlan prepaidPlans[] = {
    {1, "Airtel", 99.0, "28 days", "1GB/day"},
    {2, "Airtel", 199.0, "28 days", "1.5GB/day"},
    {3, "Airtel", 299.0, "28 days", "2GB/day"},
    {4, "Airtel", 499.0, "56 days", "2GB/day"},
    {5, "Airtel", 666.0, "84 days", "1.5GB/day"},
    {6, "Jio", 99.0, "28 days", "1GB/day"},
    {7, "Jio", 199.0, "28 days", "1.5GB/day"},
    {8, "Jio", 299.0, "28 days", "2GB/day"},
    {9, "Jio", 499.0, "56 days", "2GB/day"},
    {10, "Jio", 666.0, "84 days", "1.5GB/day"},
    {11, "Vi", 99.0, "28 days", "1GB/day"},
    {12, "Vi", 199.0, "28 days", "1.5GB/day"},
    {13, "Vi", 299.0, "28 days", "2GB/day"},
    {14, "Vi", 499.0, "56 days", "2GB/day"},
    {15, "Vi", 666.0, "84 days", "1.5GB/day"}
};

RechargePlan dthPlans[] = {
    {101, "Tata Sky", 299.0, "1 month", "Basic Pack"},
    {102, "Tata Sky", 499.0, "1 month", "Standard Pack"},
    {103, "Tata Sky", 799.0, "1 month", "Premium Pack"},
    {104, "Dish TV", 299.0, "1 month", "Basic Pack"},
    {105, "Dish TV", 499.0, "1 month", "Standard Pack"},
    {106, "Dish TV", 799.0, "1 month", "Premium Pack"},
    {107, "Airtel Digital TV", 299.0, "1 month", "Basic Pack"},
    {108, "Airtel Digital TV", 499.0, "1 month", "Standard Pack"},
    {109, "Airtel Digital TV", 799.0, "1 month", "Premium Pack"}
};

Service services[] = {
    {1, "Prepaid Mobile Recharge", "recharge"},
    {2, "Postpaid Bill Payment", "bill"},
    {3, "DTH Recharge", "recharge"},
    {4, "Electricity Bill Payment", "bill"},
    {5, "Water Bill Payment", "bill"}
};

int prepaidPlanCount = 15;
int dthPlanCount = 9;
int serviceCount = 5;

// Function Prototypes
void displayMainMenu();
void userRegistration();
int userLogin();
void displayUserMenu();
void displayRechargePlans();
void displayDTHPlans();
void processPrepaidRecharge();
void processPostpaidBill();
void processDTHRecharge();
void processElectricityBill();
void processWaterBill();
void processPayment(float amount, char* service, char* type, char* paymentMode);
float calculateCashback(float amount, char* type);
void addTransaction(User* user, Transaction* trans);
void displayTransactionHistory();
void filterTransactionsByDate();
void filterTransactionsByService();
void generateMonthlyStatement();
void addMoneyToWallet();
void displayWalletBalance();
void displayMiniStatement();
void getCurrentDateTime(char* date, char* time);
int validateMobile(char* mobile);
int validateEmail(char* email);
float calculateCashbackOperator(float amount, char* type);

// Operator overloading simulation for cashback calculation
// In C, we use function pointers to simulate operator overloading
typedef float (*CashbackCalculator)(float, char*);

// Cashback Calculator Functions
float calculateCashback(float amount, char* type) {
    if (strcmp(type, "recharge") == 0) {
        return (float)(amount * 0.02); // 2% cashback
    } else if (strcmp(type, "bill") == 0) {
        return (float)(amount * 0.01); // 1% cashback
    }
    return 0.0;
}

// Main Function
int main() {
    int choice;
    int loggedIn = 0;
    
    printf("========================================\n");
    printf("  Mobile Recharge & Bill Payment Platform\n");
    printf("========================================\n\n");
    
    while (1) {
        if (!loggedIn) {
            displayMainMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    userRegistration();
                    break;
                case 2:
                    currentUserId = userLogin();
                    if (currentUserId != -1) {
                        loggedIn = 1;
                        printf("\nLogin successful! Welcome, %s!\n", users[currentUserId].name);
                    }
                    break;
                case 3:
                    printf("\nThank you for using our platform!\n");
                    exit(0);
                default:
                    printf("\nInvalid choice! Please try again.\n");
            }
        } else {
            displayUserMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    displayRechargePlans();
                    break;
                case 2:
                    processPrepaidRecharge();
                    break;
                case 3:
                    processPostpaidBill();
                    break;
                case 4:
                    processDTHRecharge();
                    break;
                case 5:
                    processElectricityBill();
                    break;
                case 6:
                    processWaterBill();
                    break;
                case 7:
                    displayTransactionHistory();
                    break;
                case 8:
                    filterTransactionsByDate();
                    break;
                case 9:
                    filterTransactionsByService();
                    break;
                case 10:
                    generateMonthlyStatement();
                    break;
                case 11:
                    addMoneyToWallet();
                    break;
                case 12:
                    displayWalletBalance();
                    break;
                case 13:
                    displayMiniStatement();
                    break;
                case 14:
                    loggedIn = 0;
                    currentUserId = -1;
                    printf("\nLogged out successfully!\n");
                    break;
                case 15:
                    printf("\nThank you for using our platform!\n");
                    exit(0);
                default:
                    printf("\nInvalid choice! Please try again.\n");
            }
        }
    }
    
    return 0;
}

// Display Main Menu
void displayMainMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Register New User\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("===============================\n");
}

// Display User Menu
void displayUserMenu() {
    printf("\n========== USER MENU ==========\n");
    printf("1. View Recharge Plans\n");
    printf("2. Prepaid Mobile Recharge\n");
    printf("3. Postpaid Bill Payment\n");
    printf("4. DTH Recharge\n");
    printf("5. Electricity Bill Payment\n");
    printf("6. Water Bill Payment\n");
    printf("7. View Transaction History\n");
    printf("8. Filter Transactions by Date\n");
    printf("9. Filter Transactions by Service\n");
    printf("10. Generate Monthly Statement\n");
    printf("11. Add Money to Wallet\n");
    printf("12. Check Wallet Balance\n");
    printf("13. Mini Statement\n");
    printf("14. Logout\n");
    printf("15. Exit\n");
    printf("===============================\n");
}

// User Registration
void userRegistration() {
    if (userCount >= MAX_USERS) {
        printf("\nError: Maximum user limit reached!\n");
        return;
    }
    
    User newUser;
    char tempMobile[MAX_MOBILE_LENGTH];
    char tempEmail[MAX_EMAIL_LENGTH];
    
    printf("\n========== USER REGISTRATION ==========\n");
    
    newUser.userId = userCount + 1;
    
    printf("Enter your name: ");
    getchar();
    fgets(newUser.name, MAX_NAME_LENGTH, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    
    printf("Enter mobile number: ");
    scanf("%s", tempMobile);
    if (!validateMobile(tempMobile)) {
        printf("Invalid mobile number format!\n");
        return;
    }
    strcpy(newUser.mobile, tempMobile);
    
    printf("Enter email: ");
    scanf("%s", tempEmail);
    if (!validateEmail(tempEmail)) {
        printf("Invalid email format!\n");
        return;
    }
    strcpy(newUser.email, tempEmail);
    
    newUser.walletBalance = 0.0;
    newUser.transactionCount = 0;
    
    users[userCount] = newUser;
    userCount++;
    
    printf("\nRegistration successful! Your User ID is: %d\n", newUser.userId);
    printf("Please login to continue.\n");
}

// User Login
int userLogin() {
    int userId;
    char mobile[MAX_MOBILE_LENGTH];
    
    printf("\n========== USER LOGIN ==========\n");
    printf("Enter User ID: ");
    scanf("%d", &userId);
    printf("Enter mobile number: ");
    scanf("%s", mobile);
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].userId == userId && strcmp(users[i].mobile, mobile) == 0) {
            return i;
        }
    }
    
    printf("\nInvalid credentials! Please try again.\n");
    return -1;
}

// Display Recharge Plans
void displayRechargePlans() {
    printf("\n========== PREPAID RECHARGE PLANS ==========\n");
    printf("%-5s %-15s %-10s %-15s %-20s\n", "ID", "Operator", "Amount", "Validity", "Benefits");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < prepaidPlanCount; i++) {
        printf("%-5d %-15s ₹%-9.2f %-15s %-20s\n", 
               prepaidPlans[i].planId, 
               prepaidPlans[i].operator,
               prepaidPlans[i].amount,
               prepaidPlans[i].validity,
               prepaidPlans[i].benefits);
    }
    
    printf("\n========== DTH RECHARGE PLANS ==========\n");
    printf("%-5s %-20s %-10s %-15s %-20s\n", "ID", "Operator", "Amount", "Validity", "Pack");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < dthPlanCount; i++) {
        printf("%-5d %-20s ₹%-9.2f %-15s %-20s\n", 
               dthPlans[i].planId, 
               dthPlans[i].operator,
               dthPlans[i].amount,
               dthPlans[i].validity,
               dthPlans[i].benefits);
    }
}

// Display DTH Plans
void displayDTHPlans() {
    printf("\n========== DTH RECHARGE PLANS ==========\n");
    printf("%-5s %-20s %-10s %-15s %-20s\n", "ID", "Operator", "Amount", "Validity", "Pack");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < dthPlanCount; i++) {
        printf("%-5d %-20s ₹%-9.2f %-15s %-20s\n", 
               dthPlans[i].planId, 
               dthPlans[i].operator,
               dthPlans[i].amount,
               dthPlans[i].validity,
               dthPlans[i].benefits);
    }
}

// Process Prepaid Recharge
void processPrepaidRecharge() {
    int planId, operatorChoice;
    char mobile[MAX_MOBILE_LENGTH];
    char paymentMode[20];
    RechargePlan* selectedPlan = NULL;
    
    printf("\n========== PREPAID MOBILE RECHARGE ==========\n");
    printf("Select Operator:\n");
    printf("1. Airtel\n");
    printf("2. Jio\n");
    printf("3. Vi\n");
    printf("Enter choice: ");
    scanf("%d", &operatorChoice);
    
    char operator[20];
    switch (operatorChoice) {
        case 1: strcpy(operator, "Airtel"); break;
        case 2: strcpy(operator, "Jio"); break;
        case 3: strcpy(operator, "Vi"); break;
        default:
            printf("Invalid operator choice!\n");
            return;
    }
    
    printf("Enter mobile number: ");
    scanf("%s", mobile);
    
    printf("\nAvailable Plans for %s:\n", operator);
    printf("%-5s %-10s %-15s %-20s\n", "ID", "Amount", "Validity", "Benefits");
    printf("--------------------------------------------------------\n");
    
    int count = 0;
    RechargePlan availablePlans[5];
    for (int i = 0; i < prepaidPlanCount; i++) {
        if (strcmp(prepaidPlans[i].operator, operator) == 0) {
            availablePlans[count] = prepaidPlans[i];
            printf("%-5d ₹%-9.2f %-15s %-20s\n", 
                   prepaidPlans[i].planId,
                   prepaidPlans[i].amount,
                   prepaidPlans[i].validity,
                   prepaidPlans[i].benefits);
            count++;
        }
    }
    
    printf("\nEnter Plan ID: ");
    scanf("%d", &planId);
    
    for (int i = 0; i < count; i++) {
        if (availablePlans[i].planId == planId) {
            selectedPlan = &availablePlans[i];
            break;
        }
    }
    
    if (selectedPlan == NULL) {
        printf("Invalid Plan ID!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Wallet\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "wallet"); break;
        case 2: strcpy(paymentMode, "credit_card"); break;
        case 3: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    char serviceName[50];
    sprintf(serviceName, "Prepaid %s - %s", operator, mobile);
    processPayment(selectedPlan->amount, serviceName, "recharge", paymentMode);
}

// Process Postpaid Bill
void processPostpaidBill() {
    char mobile[MAX_MOBILE_LENGTH];
    float billAmount;
    char paymentMode[20];
    
    printf("\n========== POSTPAID BILL PAYMENT ==========\n");
    printf("Enter mobile number: ");
    scanf("%s", mobile);
    printf("Enter bill amount: ₹");
    scanf("%f", &billAmount);
    
    if (billAmount <= 0) {
        printf("Invalid bill amount!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Wallet\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "wallet"); break;
        case 2: strcpy(paymentMode, "credit_card"); break;
        case 3: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    char serviceName[50];
    sprintf(serviceName, "Postpaid Bill - %s", mobile);
    processPayment(billAmount, serviceName, "bill", paymentMode);
}

// Process DTH Recharge
void processDTHRecharge() {
    int planId, operatorChoice;
    char subscriberId[30];
    char paymentMode[20];
    RechargePlan* selectedPlan = NULL;
    
    printf("\n========== DTH RECHARGE ==========\n");
    printf("Select Operator:\n");
    printf("1. Tata Sky\n");
    printf("2. Dish TV\n");
    printf("3. Airtel Digital TV\n");
    printf("Enter choice: ");
    scanf("%d", &operatorChoice);
    
    char operator[20];
    switch (operatorChoice) {
        case 1: strcpy(operator, "Tata Sky"); break;
        case 2: strcpy(operator, "Dish TV"); break;
        case 3: strcpy(operator, "Airtel Digital TV"); break;
        default:
            printf("Invalid operator choice!\n");
            return;
    }
    
    printf("Enter Subscriber ID: ");
    scanf("%s", subscriberId);
    
    printf("\nAvailable Plans for %s:\n", operator);
    printf("%-5s %-10s %-15s %-20s\n", "ID", "Amount", "Validity", "Pack");
    printf("--------------------------------------------------------\n");
    
    int count = 0;
    RechargePlan availablePlans[3];
    for (int i = 0; i < dthPlanCount; i++) {
        if (strcmp(dthPlans[i].operator, operator) == 0) {
            availablePlans[count] = dthPlans[i];
            printf("%-5d ₹%-9.2f %-15s %-20s\n", 
                   dthPlans[i].planId,
                   dthPlans[i].amount,
                   dthPlans[i].validity,
                   dthPlans[i].benefits);
            count++;
        }
    }
    
    printf("\nEnter Plan ID: ");
    scanf("%d", &planId);
    
    for (int i = 0; i < count; i++) {
        if (availablePlans[i].planId == planId) {
            selectedPlan = &availablePlans[i];
            break;
        }
    }
    
    if (selectedPlan == NULL) {
        printf("Invalid Plan ID!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Wallet\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "wallet"); break;
        case 2: strcpy(paymentMode, "credit_card"); break;
        case 3: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    char serviceName[50];
    sprintf(serviceName, "DTH %s - %s", operator, subscriberId);
    processPayment(selectedPlan->amount, serviceName, "recharge", paymentMode);
}

// Process Electricity Bill
void processElectricityBill() {
    char consumerId[30];
    float billAmount;
    char paymentMode[20];
    
    printf("\n========== ELECTRICITY BILL PAYMENT ==========\n");
    printf("Enter Consumer ID: ");
    scanf("%s", consumerId);
    printf("Enter bill amount: ₹");
    scanf("%f", &billAmount);
    
    if (billAmount <= 0) {
        printf("Invalid bill amount!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Wallet\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "wallet"); break;
        case 2: strcpy(paymentMode, "credit_card"); break;
        case 3: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    char serviceName[50];
    sprintf(serviceName, "Electricity Bill - %s", consumerId);
    processPayment(billAmount, serviceName, "bill", paymentMode);
}

// Process Water Bill
void processWaterBill() {
    char consumerId[30];
    float billAmount;
    char paymentMode[20];
    
    printf("\n========== WATER BILL PAYMENT ==========\n");
    printf("Enter Consumer ID: ");
    scanf("%s", consumerId);
    printf("Enter bill amount: ₹");
    scanf("%f", &billAmount);
    
    if (billAmount <= 0) {
        printf("Invalid bill amount!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Wallet\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "wallet"); break;
        case 2: strcpy(paymentMode, "credit_card"); break;
        case 3: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    char serviceName[50];
    sprintf(serviceName, "Water Bill - %s", consumerId);
    processPayment(billAmount, serviceName, "bill", paymentMode);
}

// Process Payment
void processPayment(float amount, char* service, char* type, char* paymentMode) {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    int paymentSuccess = 0;
    
    printf("\n========== PAYMENT PROCESSING ==========\n");
    printf("Service: %s\n", service);
    printf("Amount: ₹%.2f\n", amount);
    printf("Payment Mode: %s\n", paymentMode);
    
    // Validate payment
    if (strcmp(paymentMode, "wallet") == 0) {
        if (user->walletBalance < amount) {
            printf("\nInsufficient wallet balance!\n");
            printf("Current balance: ₹%.2f\n", user->walletBalance);
            printf("Required: ₹%.2f\n", amount);
            return;
        }
        user->walletBalance -= amount;
        paymentSuccess = 1;
    } else {
        // Credit/Debit card payment simulation
        char cardNumber[20];
        printf("Enter card number (16 digits): ");
        scanf("%s", cardNumber);
        
        if (strlen(cardNumber) == 16) {
            paymentSuccess = 1;
            printf("Card payment authorized.\n");
        } else {
            printf("Invalid card number!\n");
            return;
        }
    }
    
    if (paymentSuccess) {
        // Calculate cashback
        float cashback = calculateCashback(amount, type);
        
        // Add cashback to wallet
        user->walletBalance += cashback;
        
        // Create transaction
        Transaction newTrans;
        newTrans.transactionId = transactionIdCounter++;
        getCurrentDateTime(newTrans.date, newTrans.time);
        strcpy(newTrans.type, type);
        strcpy(newTrans.service, service);
        newTrans.amount = amount;
        strcpy(newTrans.status, "success");
        newTrans.cashback = cashback;
        strcpy(newTrans.paymentMode, paymentMode);
        
        // Add transaction to user's history
        addTransaction(user, &newTrans);
        
        printf("\n✅ Payment Successful!\n");
        printf("Transaction ID: %d\n", newTrans.transactionId);
        printf("Cashback earned: ₹%.2f\n", cashback);
        printf("Cashback credited to wallet!\n");
        if (strcmp(paymentMode, "wallet") == 0) {
            printf("Updated wallet balance: ₹%.2f\n", user->walletBalance);
        } else {
            printf("Current wallet balance: ₹%.2f\n", user->walletBalance);
        }
    } else {
        printf("\n❌ Payment Failed!\n");
    }
}

// Add Transaction to History
void addTransaction(User* user, Transaction* trans) {
    // Shift transactions if array is full (keep last 50)
    if (user->transactionCount >= MAX_TRANSACTIONS) {
        // Shift all transactions left
        for (int i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            user->transactions[i] = user->transactions[i + 1];
        }
        user->transactionCount = MAX_TRANSACTIONS - 1;
    }
    
    // Add new transaction
    user->transactions[user->transactionCount] = *trans;
    user->transactionCount++;
}

// Display Transaction History
void displayTransactionHistory() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    
    printf("\n========== TRANSACTION HISTORY ==========\n");
    if (user->transactionCount == 0) {
        printf("No transactions found.\n");
        return;
    }
    
    printf("%-8s %-12s %-10s %-15s %-30s %-10s %-10s %-10s %-15s\n",
           "Trans ID", "Date", "Time", "Type", "Service", "Amount", "Status", "Cashback", "Payment Mode");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    
    // Display in reverse order (newest first)
    for (int i = user->transactionCount - 1; i >= 0; i--) {
        Transaction* trans = &user->transactions[i];
        printf("%-8d %-12s %-10s %-15s %-30s ₹%-9.2f %-10s ₹%-9.2f %-15s\n",
               trans->transactionId,
               trans->date,
               trans->time,
               trans->type,
               trans->service,
               trans->amount,
               trans->status,
               trans->cashback,
               trans->paymentMode);
    }
}

// Filter Transactions by Date
void filterTransactionsByDate() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    char filterDate[20];
    
    printf("\n========== FILTER TRANSACTIONS BY DATE ==========\n");
    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", filterDate);
    
    printf("\nTransactions on %s:\n", filterDate);
    printf("%-8s %-12s %-10s %-15s %-30s %-10s %-10s %-10s\n",
           "Trans ID", "Date", "Time", "Type", "Service", "Amount", "Status", "Cashback");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = user->transactionCount - 1; i >= 0; i--) {
        Transaction* trans = &user->transactions[i];
        if (strcmp(trans->date, filterDate) == 0) {
            printf("%-8d %-12s %-10s %-15s %-30s ₹%-9.2f %-10s ₹%-9.2f\n",
                   trans->transactionId,
                   trans->date,
                   trans->time,
                   trans->type,
                   trans->service,
                   trans->amount,
                   trans->status,
                   trans->cashback);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No transactions found for the specified date.\n");
    }
}

// Filter Transactions by Service
void filterTransactionsByService() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    int serviceChoice;
    
    printf("\n========== FILTER TRANSACTIONS BY SERVICE ==========\n");
    printf("1. Prepaid Mobile Recharge\n");
    printf("2. Postpaid Bill Payment\n");
    printf("3. DTH Recharge\n");
    printf("4. Electricity Bill Payment\n");
    printf("5. Water Bill Payment\n");
    printf("6. Wallet Add Money\n");
    printf("Enter service choice: ");
    scanf("%d", &serviceChoice);
    
    char filterType[20];
    switch (serviceChoice) {
        case 1: strcpy(filterType, "recharge"); break;
        case 2: 
        case 4: 
        case 5: strcpy(filterType, "bill"); break;
        case 3: strcpy(filterType, "recharge"); break;
        case 6: strcpy(filterType, "wallet_add"); break;
        default:
            printf("Invalid service choice!\n");
            return;
    }
    
    printf("\nFiltered Transactions:\n");
    printf("%-8s %-12s %-10s %-15s %-30s %-10s %-10s %-10s\n",
           "Trans ID", "Date", "Time", "Type", "Service", "Amount", "Status", "Cashback");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = user->transactionCount - 1; i >= 0; i--) {
        Transaction* trans = &user->transactions[i];
        if (strcmp(trans->type, filterType) == 0) {
            printf("%-8d %-12s %-10s %-15s %-30s ₹%-9.2f %-10s ₹%-9.2f\n",
                   trans->transactionId,
                   trans->date,
                   trans->time,
                   trans->type,
                   trans->service,
                   trans->amount,
                   trans->status,
                   trans->cashback);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No transactions found for the specified service.\n");
    }
}

// Generate Monthly Statement
void generateMonthlyStatement() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    int month, year;
    
    printf("\n========== MONTHLY STATEMENT ==========\n");
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter year (YYYY): ");
    scanf("%d", &year);
    
    if (month < 1 || month > 12) {
        printf("Invalid month!\n");
        return;
    }
    
    printf("\nMonthly Statement for %d/%d\n", month, year);
    printf("User: %s (ID: %d)\n", user->name, user->userId);
    printf("==========================================\n\n");
    
    float totalAmount = 0.0;
    float totalCashback = 0.0;
    int transactionCount = 0;
    
    printf("%-8s %-12s %-10s %-15s %-30s %-10s %-10s %-10s\n",
           "Trans ID", "Date", "Time", "Type", "Service", "Amount", "Status", "Cashback");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < user->transactionCount; i++) {
        Transaction* trans = &user->transactions[i];
        int transMonth, transYear;
        sscanf(trans->date, "%d-%d-%d", &transMonth, &transMonth, &transYear);
        
        // Extract month and year from date (assuming DD-MM-YYYY format)
        char dateCopy[20];
        strcpy(dateCopy, trans->date);
        char* token = strtok(dateCopy, "-");
        if (token) {
            token = strtok(NULL, "-");
            if (token) {
                int transMonth = atoi(token);
                token = strtok(NULL, "-");
                if (token) {
                    int transYear = atoi(token);
                    
                    if (transMonth == month && transYear == year) {
                        printf("%-8d %-12s %-10s %-15s %-30s ₹%-9.2f %-10s ₹%-9.2f\n",
                               trans->transactionId,
                               trans->date,
                               trans->time,
                               trans->type,
                               trans->service,
                               trans->amount,
                               trans->status,
                               trans->cashback);
                        totalAmount += trans->amount;
                        totalCashback += trans->cashback;
                        transactionCount++;
                    }
                }
            }
        }
    }
    
    if (transactionCount == 0) {
        printf("No transactions found for the specified month.\n");
    } else {
        printf("\n==========================================\n");
        printf("Summary:\n");
        printf("Total Transactions: %d\n", transactionCount);
        printf("Total Amount: ₹%.2f\n", totalAmount);
        printf("Total Cashback Earned: ₹%.2f\n", totalCashback);
        printf("Current Wallet Balance: ₹%.2f\n", user->walletBalance);
        printf("==========================================\n");
    }
}

// Add Money to Wallet
void addMoneyToWallet() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    float amount;
    char paymentMode[20];
    
    printf("\n========== ADD MONEY TO WALLET ==========\n");
    printf("Current wallet balance: ₹%.2f\n", user->walletBalance);
    printf("Enter amount to add: ₹");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    
    printf("\nSelect Payment Mode:\n");
    printf("1. Credit Card\n");
    printf("2. Debit Card\n");
    printf("Enter choice: ");
    int pmChoice;
    scanf("%d", &pmChoice);
    
    switch (pmChoice) {
        case 1: strcpy(paymentMode, "credit_card"); break;
        case 2: strcpy(paymentMode, "debit_card"); break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
    
    // Simulate card payment
    char cardNumber[20];
    printf("Enter card number (16 digits): ");
    scanf("%s", cardNumber);
    
    if (strlen(cardNumber) == 16) {
        user->walletBalance += amount;
        
        // Create transaction
        Transaction newTrans;
        newTrans.transactionId = transactionIdCounter++;
        getCurrentDateTime(newTrans.date, newTrans.time);
        strcpy(newTrans.type, "wallet_add");
        sprintf(newTrans.service, "Wallet Top-up");
        newTrans.amount = amount;
        strcpy(newTrans.status, "success");
        newTrans.cashback = 0.0;
        strcpy(newTrans.paymentMode, paymentMode);
        
        addTransaction(user, &newTrans);
        
        printf("\n✅ Money added successfully!\n");
        printf("Transaction ID: %d\n", newTrans.transactionId);
        printf("Amount added: ₹%.2f\n", amount);
        printf("Updated wallet balance: ₹%.2f\n", user->walletBalance);
    } else {
        printf("Invalid card number! Transaction failed.\n");
    }
}

// Display Wallet Balance
void displayWalletBalance() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    
    printf("\n========== WALLET BALANCE ==========\n");
    printf("User: %s\n", user->name);
    printf("User ID: %d\n", user->userId);
    printf("Current Wallet Balance: ₹%.2f\n", user->walletBalance);
    printf("====================================\n");
}

// Display Mini Statement
void displayMiniStatement() {
    if (currentUserId == -1) {
        printf("Error: No user logged in!\n");
        return;
    }
    
    User* user = &users[currentUserId];
    int count = (user->transactionCount < 10) ? user->transactionCount : 10;
    
    printf("\n========== MINI STATEMENT (Last %d transactions) ==========\n", count);
    if (user->transactionCount == 0) {
        printf("No transactions found.\n");
        return;
    }
    
    printf("%-8s %-12s %-10s %-30s %-10s %-10s\n",
           "Trans ID", "Date", "Time", "Service", "Amount", "Cashback");
    printf("----------------------------------------------------------------------------------------\n");
    
    // Display last 10 transactions
    int start = (user->transactionCount > 10) ? user->transactionCount - 10 : 0;
    for (int i = user->transactionCount - 1; i >= start; i--) {
        Transaction* trans = &user->transactions[i];
        printf("%-8d %-12s %-10s %-30s ₹%-9.2f ₹%-9.2f\n",
               trans->transactionId,
               trans->date,
               trans->time,
               trans->service,
               trans->amount,
               trans->cashback);
    }
    
    printf("\nCurrent Wallet Balance: ₹%.2f\n", user->walletBalance);
}

// Get Current Date and Time
void getCurrentDateTime(char* date, char* time) {
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    sprintf(date, "%02d-%02d-%04d", 
            timeinfo->tm_mday, 
            timeinfo->tm_mon + 1, 
            timeinfo->tm_year + 1900);
    
    sprintf(time, "%02d:%02d:%02d", 
            timeinfo->tm_hour, 
            timeinfo->tm_min, 
            timeinfo->tm_sec);
}

// Validate Mobile Number
int validateMobile(char* mobile) {
    if (strlen(mobile) != 10) {
        return 0;
    }
    
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobile[i])) {
            return 0;
        }
    }
    
    return 1;
}

// Validate Email
int validateEmail(char* email) {
    int atFound = 0;
    int dotFound = 0;
    
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atFound = 1;
        }
        if (atFound && email[i] == '.') {
            dotFound = 1;
        }
    }
    
    return (atFound && dotFound);
}

