#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
const char filename[] = "TheLibrary.txt";

struct book{
    char name[50];
    int id;
    int quantity;
};

struct book books[MAX_BOOKS];
int num_books = 0;

void load_books_from_file() {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(fp, "%d %s %d", &books[num_books].id, books[num_books].name, &books[num_books].quantity) != EOF) {
        num_books++;
    }
    fclose(fp);
}

void save_books_to_file() {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_books; i++) {
        fprintf(fp, "%d   %s   %d\n", books[i].id, books[i].name, books[i].quantity);
    }
    fclose(fp);
}

void insert_book() {
    if (num_books == MAX_BOOKS) {
        printf("Error: Maximum number of books reached.\n");
        return;
    }
    printf("Enter book name: ");
    scanf("%s", books[num_books].name);
    printf("Enter book ID: ");
    scanf("%d", &books[num_books].id);
    printf("Enter book quantity: ");
    scanf("%d", &books[num_books].quantity);
    num_books++;
    save_books_to_file(); // Close and reopen the file after writing.
    load_books_from_file();
}

void delete_book() {
    int id, pos = -1;
    printf("Enter book ID to delete: ");
    fflush(stdin);fflush(stdout);
    scanf("%d", &id);
    for (int i = 0; i < num_books; i++) {
        if (books[i].id == id) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Book not found.\n");
        return;
    }
    for (int i = pos; i < num_books-1; i++) {
        books[i] = books[i+1];
    }
    num_books--;
    save_books_to_file();
}

int binary_search_books(char *name, int left, int right) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (strcmp(books[mid].name, name) == 0) {
            return mid;
        }
        if (strcmp(books[mid].name, name) > 0) {
            return binary_search_books(name, left, mid-1);
        }
        return binary_search_books(name, mid+1, right);
    }
    return -1;
}

void search_by_name() {
    char name[50];
    printf("Enter book name to search: ");
    //fflush(stdin);fflush(stdout);
    gets(name);
    int pos = binary_search_books(name, 0, num_books-1);
    if (pos == -1) {
        printf("Not found.\n");
    } else {
        printf("Book found: ID=%d, Quantity=%d\n", books[pos].id, books[pos].quantity);
    }
}

void search_by_id() {
    int id;
    printf("Enter book ID to search: ");
    fflush(stdin);fflush(stdout);
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (books[i].id == id) {
            printf("Book found: ID=%d, Name=%s, Quantity=%d\n", books[i].id, books[i].name, books[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

void display_all_books() {
    for (int i = 0; i < num_books; i++) {
        printf("ID=%d, Name=%s, Quantity=%d\n", books[i].id, books[i].name, books[i].quantity);
    }
}

void bubble_sort_books() {
    for (int i = 0; i < num_books-1; i++) {
        for (int j = 0; j < num_books-i-1; j++) {
            if (strcmp(books[j].name, books[j+1].name) > 0) {
                struct book temp = books[j];
                books[j] = books[j+1];
                books[j+1] = temp;
            }
        }
    }
}

void display_all_books_sorted() {
    bubble_sort_books();
    display_all_books();
}
int main() {
    load_books_from_file();
    int choice;
    do {
        printf("\n");
        printf("1. Insert a book\n");
        printf("2. Delete a book\n");
        printf("3. Search by name\n");
        printf("4. Search by ID\n");
        printf("5. Display all books\n");
        printf("6. Display all books sorted by name\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 0:
                return 0;
            case 1:
                insert_book();
                break;
            case 2:
                delete_book();
                break;
            case 3:
                search_by_name();
                break;
            case 4:
                search_by_id();
                break;
            case 5:
                display_all_books();
                break;
            case 6:
                display_all_books_sorted();
                break;
            default:
                printf("Invalid choice.\n");
        }
        printf("\nDo you want to perform another operation? (y/n): ");
        char answer;
        scanf(" %c", &answer);
        if (answer == 'n') {
            choice = 0;
        }
    } while (choice != 0);
    return 0;
}
