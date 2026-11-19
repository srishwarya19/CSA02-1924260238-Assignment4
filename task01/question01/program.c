#include <stdio.h>
#include <string.h>

struct date {
    int day, month, year;
};

struct blood_pressure {
    int systolic;
    int diastolic;
};

struct patient {
    char name[50];
    int age;
    char phone[11];
    struct blood_pressure bp;
    struct date visitDate;
};

void addPatient(struct patient *p, char n[], int a,
                char phone[], int sys, int dia,
                int d, int m, int y)
{
    strcpy(p->name, n);
    p->age = a;
    strcpy(p->phone, phone);
    p->bp.systolic = sys;
    p->bp.diastolic = dia;
    p->visitDate.day = d;
    p->visitDate.month = m;
    p->visitDate.year = y;
}

int main()
{
    struct patient p;

    addPatient(&p, "Arun", 25, "9876543210",
               120, 80, 19, 11, 2026);

    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Phone: %s\n", p.phone);
    printf("Blood Pressure: %d/%d\n",
           p.bp.systolic, p.bp.diastolic);
    printf("Visit Date: %02d/%02d/%d\n",
           p.visitDate.day,
           p.visitDate.month,
           p.visitDate.year);

    return 0;
}#include <stdio.h>

struct date {
    int day, month, year;
};

struct address {
    char city[20];
    int pincode;
};

struct parcel {
    int id;
    float weight;
    struct address to;
    struct date booked;
};

void print_parcel(const struct parcel *p)
{
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id,
           p->weight,
           p->to.city,
           p->to.pincode,
           p->booked.day,
           p->booked.month,
           p->booked.year);
}

void sort_by_weight(struct parcel p[], int n)
{
    int i, j, min;
    struct parcel temp;

    for (i = 0; i < n - 1; i++) {
        min = i;

        for (j = i + 1; j < n; j++) {
            if (p[j].weight < p[min].weight)
                min = j;
        }

        temp = p[i];
        p[i] = p[min];
        p[min] = temp;
    }
}

int main()
{
    struct parcel list[3] = {
        {501, 4.5f, {"Madurai", 625001}, {12, 10, 2026}},
        {502, 1.2f, {"Chennai", 600077}, {12, 10, 2026}},
        {503, 2.8f, {"Coimbatore", 641001}, {13, 10, 2026}}
    };

    int i;

    sort_by_weight(list, 3);

    for (i = 0; i < 3; i++)
        print_parcel(&list[i]);

    return 0;
}n
