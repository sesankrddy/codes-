#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MENU 100
#define MAX_ORDERS 100
#define MAX_ITEMS_PER_ORDER 10  // Updated to 10 as per your request
#define NUM_TABLES 50

typedef struct {
    int code;
    char name[50];
    char category[20];
    float price;
    int availability; // 1 for available, 0 for not
} MenuItem;

typedef struct {
    int table_no; // 0 for takeaway
    int item_codes[MAX_ITEMS_PER_ORDER];
    int quantities[MAX_ITEMS_PER_ORDER];
    int num_items;
    char timestamp[20];
} Order;

// Arrays of structures as per requirements
MenuItem menu[MAX_MENU];  // Array for menu items
Order orders[MAX_ORDERS]; // Array for active orders
int menu_count = 0;
int order_count = 0;
int tables[NUM_TABLES] = {0}; // 0 free, 1 occupied

// Function to add menu item
void add_menu_item(int code, char* name, char* cat, float price, int avail) {
    if (menu_count < MAX_MENU) {
        menu[menu_count].code = code;
        strcpy(menu[menu_count].name, name);
        strcpy(menu[menu_count].category, cat);
        menu[menu_count].price = price;
        menu[menu_count].availability = avail;
        menu_count++;
    }
}

// Function to display menu
void display_menu() {
    printf("\n--- Digital Menu Card ---\n");
    printf("Starters:\n");
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].category, "Starters") == 0 && menu[i].availability) {
            printf("%d. %s - Rs. %.2f\n", menu[i].code, menu[i].name, menu[i].price);
        }
    }
    printf("\nMain Course:\n");
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].category, "Main Course") == 0 && menu[i].availability) {
            printf("%d. %s - Rs. %.2f\n", menu[i].code, menu[i].name, menu[i].price);
        }
    }
    printf("\nBeverages:\n");
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].category, "Beverages") == 0 && menu[i].availability) {
            printf("%d. %s - Rs. %.2f\n", menu[i].code, menu[i].name, menu[i].price);
        }
    }
    printf("\nDesserts:\n");
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].category, "Desserts") == 0 && menu[i].availability) {
            printf("%d. %s - Rs. %.2f\n", menu[i].code, menu[i].name, menu[i].price);
        }
    }
}

// Function to take order
void take_order() {
    if (order_count >= MAX_ORDERS) {
        printf("Order limit reached.\n");
        return;
    }
    Order new_order;
    new_order.num_items = 0;
    printf("Enter table number (1-50 for dine-in, 0 for takeaway): ");
    scanf("%d", &new_order.table_no);
    if (new_order.table_no < 0 || new_order.table_no > NUM_TABLES) {
        printf("Invalid table number.\n");
        return;
    }
    if (new_order.table_no > 0 && tables[new_order.table_no - 1] == 1) {
        printf("Table %d is occupied.\n", new_order.table_no);
        return;
    }
    if (new_order.table_no > 0) {
        tables[new_order.table_no - 1] = 1;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(new_order.timestamp, "%02d-%02d-%04d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

    int choice;
    do {
        printf("Enter item code to add (0 to finish): ");
        scanf("%d", &choice);
        if (choice == 0) break;
        int found = 0;
        for (int i = 0; i < menu_count; i++) {
            if (menu[i].code == choice && menu[i].availability) {
                printf("Enter quantity: ");
                int qty;
                scanf("%d", &qty);
                new_order.item_codes[new_order.num_items] = choice;
                new_order.quantities[new_order.num_items] = qty;
                new_order.num_items++;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Invalid item code.\n");
        }
    } while (new_order.num_items < MAX_ITEMS_PER_ORDER);

    orders[order_count] = new_order;
    order_count++;
    printf("Order placed successfully. Order ID: %d\n", order_count);
}

// Function to modify order
void modify_order(int order_id) {
    if (order_id < 1 || order_id > order_count) {
        printf("Invalid order ID.\n");
        return;
    }
    Order* ord = &orders[order_id - 1];
    printf("Current order:\n");
    for (int i = 0; i < ord->num_items; i++) {
        for (int j = 0; j < menu_count; j++) {
            if (menu[j].code == ord->item_codes[i]) {
                printf("%d. %s x%d\n", ord->item_codes[i], menu[j].name, ord->quantities[i]);
                break;
            }
        }
    }
    printf("1. Add item\n2. Remove item\n3. Update quantity\nChoose: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter item code: ");
        int code;
        scanf("%d", &code);
        int found = 0;
        for (int i = 0; i < menu_count; i++) {
            if (menu[i].code == code && menu[i].availability) {
                printf("Enter quantity: ");
                int qty;
                scanf("%d", &qty);
                ord->item_codes[ord->num_items] = code;
                ord->quantities[ord->num_items] = qty;
                ord->num_items++;
                found = 1;
                break;
            }
        }
        if (!found) printf("Invalid item.\n");
    } else if (choice == 2) {
        printf("Enter item code to remove: ");
        int code;
        scanf("%d", &code);
        for (int i = 0; i < ord->num_items; i++) {
            if (ord->item_codes[i] == code) {
                for (int j = i; j < ord->num_items - 1; j++) {
                    ord->item_codes[j] = ord->item_codes[j + 1];
                    ord->quantities[j] = ord->quantities[j + 1];
                }
                ord->num_items--;
                break;
            }
        }
    } else if (choice == 3) {
        printf("Enter item code: ");
        int code;
        scanf("%d", &code);
        for (int i = 0; i < ord->num_items; i++) {
            if (ord->item_codes[i] == code) {
                printf("Enter new quantity: ");
                scanf("%d", &ord->quantities[i]);
                break;
            }
        }
    }
}

// Function to calculate bill
void calculate_bill(int order_id) {
    if (order_id < 1 || order_id > order_count) {
        printf("Invalid order ID.\n");
        return;
    }
    Order ord = orders[order_id - 1];
    float subtotal = 0;
    for (int i = 0; i < ord.num_items; i++) {
        for (int j = 0; j < menu_count; j++) {
            if (menu[j].code == ord.item_codes[i]) {
                subtotal += menu[j].price * ord.quantities[i];
                break;
            }
        }
    }
    float gst = 0.05 * subtotal; // Assuming all items are food
    float service_charge = (ord.table_no > 0) ? 0.1 * (subtotal + gst) : 0;
    float total_before_discount = subtotal + gst + service_charge;
    float discount = 0;
    if (total_before_discount > 2000) {
        discount = 0.15 * total_before_discount;
    } else if (total_before_discount > 1000) {
        discount = 0.10 * total_before_discount;
    }
    float total = total_before_discount - discount;
    printf("\n--- Bill Calculation ---\n");
    printf("Subtotal: Rs. %.2f\n", subtotal);
    printf("GST (5%%): Rs. %.2f\n", gst);
    printf("Service Charge: Rs. %.2f\n", service_charge);
    printf("Discount: Rs. %.2f\n", discount);
    printf("Total: Rs. %.2f\n", total);
}

// Function to generate KOT
void generate_kot(int order_id) {
    if (order_id < 1 || order_id > order_count) {
        printf("Invalid order ID.\n");
        return;
    }
    Order ord = orders[order_id - 1];
    printf("\n--- Kitchen Order Token (KOT) ---\n");
    printf("Order ID: %d\n", order_id);
    printf("Table: %d\n", ord.table_no);
    printf("Timestamp: %s\n", ord.timestamp);
    printf("Items:\n");
    for (int i = 0; i < ord.num_items; i++) {
        for (int j = 0; j < menu_count; j++) {
            if (menu[j].code == ord.item_codes[i]) {
                printf("%s x%d\n", menu[j].name, ord.quantities[i]);
                break;
            }
        }
    }
}

// Function to generate receipt
void generate_receipt(int order_id) {
    if (order_id < 1 || order_id > order_count) {
        printf("Invalid order ID.\n");
        return;
    }
    Order ord = orders[order_id - 1];
    printf("\n--- Detailed Receipt ---\n");
    printf("Order ID: %d\n", order_id);
    printf("Table: %d\n", ord.table_no);
    printf("Timestamp: %s\n", ord.timestamp);
    printf("Items:\n");
    float subtotal = 0;
    for (int i = 0; i < ord.num_items; i++) {
        for (int j = 0; j < menu_count; j++) {
            if (menu[j].code == ord.item_codes[i]) {
                printf("%s x%d - Rs. %.2f\n", menu[j].name, ord.quantities[i], menu[j].price * ord.quantities[i]);
                subtotal += menu[j].price * ord.quantities[i];
                break;
            }
        }
    }
    float gst = 0.05 * subtotal;
    float service_charge = (ord.table_no > 0) ? 0.1 * (subtotal + gst) : 0;
    float total_before_discount = subtotal + gst + service_charge;
    float discount = 0;
    if (total_before_discount > 2000) {
        discount = 0.15 * total_before_discount;
    } else if (total_before_discount > 1000) {
        discount = 0.10 * total_before_discount;
    }
    float total = total_before_discount - discount;
    printf("Subtotal: Rs. %.2f\n", subtotal);
    printf("GST (5%%): Rs. %.2f\n", gst);
    printf("Service Charge: Rs. %.2f\n", service_charge);
    printf("Discount: Rs. %.2f\n", discount);
    printf("Total: Rs. %.2f\n", total);
    // Free table if dine-in
    if (ord.table_no > 0) {
        tables[ord.table_no - 1] = 0;
    }
}

// Function to display table status
void display_table_status() {
    printf("\n--- Table Status ---\n");
    for (int i = 0; i < NUM_TABLES; i++) {
        printf("Table %d: %s\n", i + 1, tables[i] == 0 ? "Free" : "Occupied");
    }
}

int main() {
    // Populate menu with 25 items
    add_menu_item(101, "Spring Rolls", "Starters", 150.0, 1);
    add_menu_item(102, "Chicken Wings", "Starters", 200.0, 1);
    add_menu_item(103, "Paneer Tikka", "Starters", 180.0, 1);
    add_menu_item(104, "Fish Fingers", "Starters", 220.0, 1);
    add_menu_item(105, "Samosa", "Starters", 50.0, 1);
    add_menu_item(201, "Butter Chicken", "Main Course", 350.0, 1);
    add_menu_item(202, "Paneer Butter Masala", "Main Course", 300.0, 1);
    add_menu_item(203, "Biryani", "Main Course", 250.0, 1);
    add_menu_item(204, "Dal Makhani", "Main Course", 200.0, 1);
    add_menu_item(205, "Chole Bhature", "Main Course", 180.0, 1);
    add_menu_item(206, "Pizza Margherita", "Main Course", 400.0, 1);
    add_menu_item(207, "Burger", "Main Course", 150.0, 1);
    add_menu_item(208, "Pasta", "Main Course", 250.0, 1);
    add_menu_item(301, "Coke", "Beverages", 50.0, 1);
    add_menu_item(302, "Juice", "Beverages", 80.0, 1);
    add_menu_item(303, "Coffee", "Beverages", 100.0, 1);
    add_menu_item(304, "Tea", "Beverages", 40.0, 1);
    add_menu_item(305, "Water", "Beverages", 20.0, 1);
    add_menu_item(401, "Ice Cream", "Desserts", 120.0, 1);
    add_menu_item(402, "Cake", "Desserts", 150.0, 1);
    add_menu_item(403, "Gulab Jamun", "Desserts", 100.0, 1);
    add_menu_item(404, "Ras Malai", "Desserts", 80.0, 1);
    add_menu_item(405, "Jalebi", "Desserts", 90.0, 1);
    add_menu_item(406, "Kulfi", "Desserts", 70.0, 1);

    int choice;
    while (1) {
        printf("\n--- Restaurant Management System ---\n");
        printf("1. Display Menu\n");
        printf("2. Take Order\n");
        printf("3. Modify Order\n");
        printf("4. Calculate Bill\n");
        printf("5. Generate KOT\n");
        printf("6. Generate Receipt\n");
        printf("7. Display Table Status\n");
        printf("8. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        if (choice == 1) {
            display_menu();
        } else if (choice == 2) {
            take_order();
        } else if (choice == 3) {
            printf("Enter order ID: ");
            int id;
            scanf("%d", &id);
            modify_order(id);
        } else if (choice == 4) {
            printf("Enter order ID: ");
            int id;
            scanf("%d", &id);
            calculate_bill(id);
        } else if (choice == 5) {
            printf("Enter order ID: ");
            int id;
            scanf("%d", &id);
            generate_kot(id);
        } else if (choice == 6) {
            printf("Enter order ID: ");
            int id;
            scanf("%d", &id);
            generate_receipt(id);
        } else if (choice == 7) {
            display_table_status();
        } else if (choice == 8) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
