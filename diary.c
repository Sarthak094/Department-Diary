#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "department_diary.dat"

typedef struct {
    int id;
    char name[50];
    char date[15];
    char time[10];
    char duration[20];
    char address[100];
} Diary;

int next_id();
void add_entry();
void view_entries();
void edit_entry();
void delete_entry();
void follow_up();

int main() {
    int ch;
    do {
        printf("\n=== Department Diary ===\n"
               "1. Add Activity\n2. View All\n3. Edit\n4. Delete\n5. Follow-up\n6. Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }
        getchar(); // clear buffer

        switch (ch) {
            case 1: add_entry(); break;
            case 2: view_entries(); break;
            case 3: edit_entry(); break;
            case 4: delete_entry(); break;
            case 5: follow_up(); break;
            case 6: puts("Exiting..."); break;
            default: puts("Invalid choice!");
        }
    } while (ch != 6);
    return 0;
}

// Generate next ID
int next_id() {
    FILE *f = fopen(FILE_NAME, "rb");
    Diary d; 
    int id = 0;
    if (!f) return 1; // if file not found, start IDs from 1
    while (fread(&d, sizeof(d), 1, f))
        if (d.id > id) id = d.id;
    fclose(f);
    return id + 1;
}

// Add activity
void add_entry() {
    FILE *f = fopen(FILE_NAME, "ab");
    if (!f) {
        printf("File error!\n");
        return;
    }

    Diary d;
    d.id = next_id();

    printf("Activity Name: ");
    fgets(d.name, sizeof(d.name), stdin);
    printf("Date (DD-MM-YYYY): ");
    fgets(d.date, sizeof(d.date), stdin);
    printf("Time (HH:MM AM/PM): ");
    fgets(d.time, sizeof(d.time), stdin);
    printf("Duration: ");
    fgets(d.duration, sizeof(d.duration), stdin);
    printf("Address: ");
    fgets(d.address, sizeof(d.address), stdin);

    d.name[strcspn(d.name, "\n")] = 0;
    d.date[strcspn(d.date, "\n")] = 0;
    d.time[strcspn(d.time, "\n")] = 0;
    d.duration[strcspn(d.duration, "\n")] = 0;
    d.address[strcspn(d.address, "\n")] = 0;

    fwrite(&d, sizeof(d), 1, f);
    fclose(f);

    printf("✅ Activity (ID %d) added.\n", d.id);
}

// View all activities
void view_entries() {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) {
        printf("No records found!\n");
        return;
    }

    Diary d;
    printf("\nID | Name | Date | Time | Duration | Address\n"
           "-------------------------------------------------------------\n");

    while (fread(&d, sizeof(d), 1, f)) {
        printf("%-2d | %-15s | %-10s | %-8s | %-8s | %s\n",
               d.id, d.name, d.date, d.time, d.duration, d.address);
    }

    fclose(f);
}

// Edit activity by ID
void edit_entry() {
    int id, found = 0;
    Diary d;

    printf("Enter ID to edit: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); // clear buffer

    FILE *in = fopen(FILE_NAME, "rb");
    FILE *out = fopen("temp.dat", "wb");

    if (!in || !out) {
        printf("File error!\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    while (fread(&d, sizeof(d), 1, in)) {
        if (d.id == id) {
            found = 1;
            printf("Editing Activity ID %d\n", id);

            printf("New Name: ");
            fgets(d.name, sizeof(d.name), stdin);
            printf("New Date: ");
            fgets(d.date, sizeof(d.date), stdin);
            printf("New Time: ");
            fgets(d.time, sizeof(d.time), stdin);
            printf("New Duration: ");
            fgets(d.duration, sizeof(d.duration), stdin);
            printf("New Address: ");
            fgets(d.address, sizeof(d.address), stdin);

            d.name[strcspn(d.name, "\n")] = 0;
            d.date[strcspn(d.date, "\n")] = 0;
            d.time[strcspn(d.time, "\n")] = 0;
            d.duration[strcspn(d.duration, "\n")] = 0;
            d.address[strcspn(d.address, "\n")] = 0;

            printf("✅ Updated successfully!\n");
        }
        fwrite(&d, sizeof(d), 1, out);
    }

    fclose(in);
    fclose(out);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (!found) {
        printf("ID %d not found!\n", id);
    }
}

// Delete activity
void delete_entry() {
    int id, found = 0;
    Diary d;

    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    FILE *in = fopen(FILE_NAME, "rb");
    FILE *out = fopen("temp.dat", "wb");

    if (!in || !out) {
        printf("File error!\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    while (fread(&d, sizeof(d), 1, in)) {
        if (d.id == id) {
            found = 1;
        } else {
            fwrite(&d, sizeof(d), 1, out);
        }
    }

    fclose(in);
    fclose(out);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("🗑️ ID %d deleted.\n", id);
    else
        printf("ID %d not found!\n", id);
}

// Follow-up (view all)
void follow_up() {
    puts("\n--- Follow-up Activities ---");
    view_entries();
    puts("\nReview complete.");
}