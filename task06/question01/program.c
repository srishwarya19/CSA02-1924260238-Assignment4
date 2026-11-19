#include <stdio.h>
#include <string.h>

#define MAX 20

struct date {
    int day, month, year;
};

struct packaged {
    struct date expiry;
};

struct cooked {
    int hour, minute;
};

struct combo {
    int item1, item2, item3;
    int qty1, qty2, qty3;
};

struct item {
    int id;
    char name[30];
    int type;
    float price;
    int stock;

    union {
        struct packaged pack;
        struct cooked cook;
        struct combo meal;
    } details;
};

struct sale {
    char name[30];
    float revenue;
};

int date_number(struct date d)
{
    int days[] = {
        31,28,31,30,31,30,
        31,31,30,31,30,31
    };

    int i, total = d.day;

    for (i = 1; i < d.month; i++)
        total += days[i - 1];

    total += (d.year - 1) * 365;
    total += (d.year - 1) / 4;
    total -= (d.year - 1) / 100;
    total += (d.year - 1) / 400;

    if (d.month > 2 &&
        ((d.year % 400 == 0) ||
         (d.year % 4 == 0 && d.year % 100 != 0)))
        total++;

    return total;
}

void display_items(struct item items[], int n)
{
    int i;

    printf("\nCANTEEN INVENTORY\n");

    for (i = 0; i < n; i++) {
        printf("%d %s Price: %.2f Stock: %d\n",
               items[i].id,
               items[i].name,
               items[i].price,
               items[i].stock);
    }
}

void check_expiry(struct item items[], int n,
                  struct date today)
{
    int i, difference;

    printf("\nEXPIRY WARNING\n");

    for (i = 0; i < n; i++) {
        if (items[i].type == 1) {
            difference =
                date_number(items[i].details.pack.expiry)
                - date_number(today);

            if (difference >= 0 && difference <= 2) {
                printf("%s is expiring within two days\n",
                       items[i].name);
            }
        }
    }
}

void record_sale(struct item items[], int n,
                 struct sale sales[], int *sale_count)
{
    int id, quantity, i;
    float total;

    printf("\nEnter item ID: ");
    scanf("%d", &id);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (i = 0; i < n; i++) {
        if (items[i].id == id) {
            if (quantity <= 0) {
                printf("Invalid quantity\n");
                return;
            }

            if (items[i].type == 3) {
                printf("Combo sales are not supported in this basic version\n");
                return;
            }

            if (items[i].stock < quantity) {
                printf("Insufficient stock\n");
                return;
            }

            items[i].stock -= quantity;
            total = items[i].price * quantity;

            strcpy(sales[*sale_count].name,
                   items[i].name);

            sales[*sale_count].revenue = total;
            (*sale_count)++;

            printf("Sale successful\n");
            printf("Total Bill: %.2f\n", total);

            return;
        }
    }

    printf("Item not found\n");
}

void sort_sales(struct sale sales[], int n)
{
    int i, j;
    struct sale temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (sales[j].revenue <
                sales[j + 1].revenue) {

                temp = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = temp;
            }
        }
    }
}

void display_summary(struct sale sales[], int n)
{
    int i;

    sort_sales(sales, n);

    printf("\nSALES SUMMARY\n");

    for (i = 0; i < n; i++) {
        printf("%s : Rs. %.2f\n",
               sales[i].name,
               sales[i].revenue);
    }
}

int main()
{
    struct item items[3] = {
        {101, "Biscuit", 1, 20, 10,
         {.pack = {{21, 11, 2026}}}},

        {102, "Sandwich", 2, 50, 5,
         {.cook = {10, 30}}},

        {103, "Juice", 1, 30, 8,
         {.pack = {{20, 11, 2026}}}}
    };

    struct sale sales[MAX];
    struct date today = {19, 11, 2026};

    int sale_count = 0;
    int choice;

    do {
        printf("\n1. Display Inventory\n");
        printf("2. Record Sale\n");
        printf("3. Check Expiry\n");
        printf("4. Sales Summary\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_items(items, 3);
                break;

            case 2:
                if (sale_count < MAX)
                    record_sale(items, 3, sales,
                                &sale_count);
                else
                    printf("Sales limit reached\n");
                break;

            case 3:
                check_expiry(items, 3, today);
                break;

            case 4:
                display_summary(sales, sale_count);
                break;

            case 5:
                printf("Thank you\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 5);

    return 0;
}
