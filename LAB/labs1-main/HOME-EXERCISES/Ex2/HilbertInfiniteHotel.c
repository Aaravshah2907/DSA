#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    char address[100];
} Occupant;

typedef struct {
    char name[50];
    char address[100];
    int occupied_rooms;
    Occupant *rooms;   // dynamic array of occupants
} Hotel;

// Prototypes of Functions
void add_last(Hotel *h);
void add_at_zero(Hotel *h);
void remove_room(Hotel *h, int room_no);
void display_room(const Hotel *h, int room_no);

void add_last(Hotel *h)
{
    h->rooms = realloc(h->rooms, (h->occupied_rooms + 1) * sizeof(Occupant));

    Occupant *o = &h->rooms[h->occupied_rooms];

    printf("Enter name: ");
    scanf(" %[^\n]", o->name);
    printf("Enter age: ");
    scanf("%d", &o->age);
    printf("Enter address: ");
    scanf(" %[^\n]", o->address);

    h->occupied_rooms++;
}

void add_at_zero(Hotel *h)
{
    h->rooms = realloc(h->rooms, (h->occupied_rooms + 1) * sizeof(Occupant));

    for (int i = h->occupied_rooms; i > 0; i--)
        h->rooms[i] = h->rooms[i - 1];

    printf("Enter name: ");
    scanf(" %[^\n]", h->rooms[0].name);
    printf("Enter age: ");
    scanf("%d", &h->rooms[0].age);
    printf("Enter address: ");
    scanf(" %[^\n]", h->rooms[0].address);

    h->occupied_rooms++;
}

void remove_room(Hotel *h, int room_no)
{
    if (room_no < 0 || room_no >= h->occupied_rooms)
    {
        printf("Invalid room number.\n");
        return;
    }

    for (int i = room_no; i < h->occupied_rooms - 1; i++)
        h->rooms[i] = h->rooms[i + 1];

    h->occupied_rooms--;

    if (h->occupied_rooms == 0)
    {
        free(h->rooms);
        h->rooms = NULL;
    }
    else
    {
        h->rooms = realloc(h->rooms, h->occupied_rooms * sizeof(Occupant));
    }
}

void display_room(const Hotel *h, int room_no)
{
    if (room_no < 0 || room_no >= h->occupied_rooms)
    {
        printf("Invalid room number.\n");
        return;
    }

    Occupant o = h->rooms[room_no];

    printf("\nRoom %d Occupant Details:\n", room_no);
    printf("Name    : %s\n", o.name);
    printf("Age     : %d\n", o.age);
    printf("Address : %s\n", o.address);
}

int main(void)
{
    Hotel h;
    int choice, room_no;

    strcpy(h.name, "The Grand Hotel");
    strcpy(h.address, "Infinite Avenue");
    h.occupied_rooms = 0;
    h.rooms = NULL;

    printf("Welcome to %s\n", h.name);

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Assign first unoccupied room\n");
        printf("2. Assign Room #0\n");
        printf("3. Empty a room\n");
        printf("4. Display room information\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_last(&h);
                break;

            case 2:
                add_at_zero(&h);
                break;

            case 3:
                printf("Enter room number to empty: ");
                scanf("%d", &room_no);
                remove_room(&h, room_no);
                break;

            case 4:
                printf("Enter room number to display: ");
                scanf("%d", &room_no);
                display_room(&h, room_no);
                break;

            case 5:
                printf("Exiting hotel management system.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
    while (choice != 5);

    free(h.rooms);
    return 0;
}


