#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void login();
void moviesavailable();
void displaymovie();
void book_ticket();
void updatemovie();
void seats_available();
void searchmovie();
void cancel_ticket();
void make_apayment();
void addMovie(int id, char *title, char *showtime, int price, float rating);
void clean_movie();

struct moviedetails {
    int id;
    char title[50];
    char showtime[50];
    int price;
    float rating;
    int seat[50]; // Array to track booked seats
    struct moviedetails *next;
};

struct moviedetails *first = NULL;
struct moviedetails *last = NULL;
struct moviedetails *newnode;
int global_movie_id;
int global_total_price;
char global_movie_title[50];
char sign_password[100];
char sign_username[100];

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    long int number;
    char gmail[50];

    printf("<<<<<<<<<<<<<<<<<BOOK MY CINEMA>>>>>>>>>>>>>\n");
    printf("*****************SIGN UP DETAILS**************\n");
    printf("Enter your mobile number: ");
    scanf("%ld", &number);
    clearInputBuffer();

    printf("Enter the correct mail ID to get updates: ");
    scanf("%s", gmail);
    clearInputBuffer();

    printf("Enter the user name: ");
    scanf("%[^\n]s", sign_username);
    clearInputBuffer();

    printf("Enter the password: ");
    scanf("%[^\n]s", sign_password);
    clearInputBuffer();

    printf("<---------------You Have Signed Up Successfully--------------->\n");
    printf("=========================User  Login============================\n");
    login();

    // Adding some movies
    addMovie(12, "KGF", "3:30 pm", 200, 9.5);
    addMovie(13, "EMPURAN", "3:30 pm", 200, 9.5);
    addMovie(14, "KGF2", "3:30 pm", 200, 9.5);

    while (1) {
        printf("============================================================\n");
        printf("\t1. Movies Available\n\t2. Search Movie\n\t3. Display Movie\n\t4. Seats Available\n\t5. Book a Ticket\n\t6. Cancel a Ticket\n\t7. Update Movie Details\n\t8. Make Payment\n\t9. Exit\n");
        printf("=============================================================\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                moviesavailable();
                break;
            case 2:
                searchmovie();
                break;
            case 3:
                displaymovie();
                break;
            case 4:
                seats_available();
                break;
            case 5:
                book_ticket();
                break;
            case 6:
                cancel_ticket();
                break;
            case 7:
                updatemovie();
                break;
            case 8:
                make_apayment();
                break;
            case 9:
                printf("Cleaning up memory and exiting...\n");
                clean_movie();
                printf("Thank you for using Book My Cinema! Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void login() {
    char username[100];
    char password[100];
    int attempts = 3;

    while (attempts > 0) {
        printf("Enter username: ");
        scanf("%[^\n]s", username);
        clearInputBuffer();

        printf("Enter password: ");
        scanf("%[^\n]s", password);
        clearInputBuffer();

        if (strcmp(username, sign_username) == 0 && strcmp(password, sign_password) == 0) {
            printf("..............User  login successful..............\n");
            return;
        } else {
            attempts--;
            if (attempts > 0) {
                printf("Login failed. You have %d attempt(s) remaining. Try again.\n", attempts);
            } else {
                printf("Login failed. No attempts remaining. Exiting...\n");
                exit(0);
            }
        }
    }
}

void addMovie(int id, char *title, char *showtime, int price, float rating) {
    newnode = (struct moviedetails *)malloc(sizeof(struct moviedetails));

    if (newnode == NULL) {
        perror("Memory allocation failed");
        return;
    }
    newnode->id = id;
    strcpy(newnode->title, title);
    strcpy(newnode->showtime, showtime);
    newnode->price = price;
    newnode->rating = rating;
    memset(newnode->seat, 0, sizeof(newnode->seat)); // Initialize seats to 0 (available)
    newnode->next = NULL;

    if (first == NULL) {
        first = last = newnode;
    } else {
        last->next = newnode;
        last = newnode;
    }
}

void moviesavailable() {
    printf(".......Movies available for booking........\n");
    displaymovie();
}

void displaymovie() {
    struct moviedetails *temp = first;

    if (temp == NULL) {
        printf("No movies available\n");
        return;
    }

    int count = 1;
    printf("\n================== Movies Available ==================\n");

    while (temp != NULL) {
        printf("----------------------------------------------------\n");
        printf("| Movie #%d                                         |\n", count++);
        printf("----------------------------------------------------\n");
        printf("| ID        : %-4d                                  |\n", temp->id);
        printf("| Title     : %-20s                   |\n", temp->title);
        printf("| Showtime  : %-10s                        |\n", temp->showtime);
        printf("| Price     : %-6d                                |\n", temp->price);
        printf("| Rating    : %-6.1f                             |\n", temp->rating);
        printf("----------------------------------------------------\n\n");
        temp = temp->next;
    }

    printf("====================================================\n");
}

void searchmovie() {
    int id;
    printf("Enter the movie ID to search: ");
    scanf("%d", &id);

    struct moviedetails *temp = first;
    int found = 0;

    while (temp != NULL) {
        if (id == temp->id) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (found) {
        printf("Movie details:\n");
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Showtime: %s\n", temp->showtime);
        printf("Price: %d\n", temp->price);
    } else {
        printf("Movie ID does not exist.\n");
    }
}

void seats_available() {
    int id;
    printf("Enter the movie ID to check seats:\n");
    scanf("%d", &id);
    struct moviedetails *temp = first;

    int flag = 0;
    while (temp != NULL) {
        if (id == temp->id) {
            flag = 1;
            printf("Available seats are:\n");

            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 10; col++) {
                    int seats_index = row * 10 + col;
                    if (temp->seat[seats_index] == 0) {
                        printf("  A ");  // Available
                    } else {
                        printf("  X ");  // Booked
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;
        }
        temp = temp->next;
    }

    if (flag == 0) {
        printf("Movie ID does not exist.\n");
    }
}

void book_ticket() {
    int id, num_seats;
    printf("Enter the movie ID to book tickets:\n");
    scanf("%d", &id);
    struct moviedetails *temp = first;
    int flag = 0;
    while (temp != NULL) {
        if (id == temp->id) {
            flag = 1;
            printf("Enter the number of seats to book: ");
            scanf("%d", &num_seats);

            if (num_seats < 1 || num_seats > 50) {
                printf("Invalid number of seats. Please choose between 1 and 50.\n");
                return;
            }
            int seats[num_seats];
            printf("Enter the seat numbers to book (1-50):\n");
            for (int i = 0; i < num_seats; i++) {
                scanf("%d", &seats[i]);
                if (seats[i] < 1 || seats[i] > 50) {
                    printf("Invalid seat number. Please choose between 1 and 50.\n");
                    return;
                }
                if (temp->seat[seats[i] - 1] == 1) {
                    printf("Seat number %d is already booked.\n", seats[i]);
                    return;
                }
                temp->seat[seats[i] - 1] = 1; // Mark seat as booked
            }
            global_movie_id = temp->id;
            strcpy(global_movie_title, temp->title);
            global_total_price = num_seats * temp->price;
            make_apayment();
            printf("Tickets booked successfully!\n");
            break;
        }
        temp = temp->next;
    }

    if (flag == 0) {
        printf("Movie ID does not exist.\n");
    }
}

void make_apayment() {
    int payment_method;
    char card_number[16];
    int cvv;
    char wallet[20];
    printf("\nTotal amount to pay: %d\n", global_total_price);
    printf("Choose Payment Method:\n");
    printf("1. Credit Card\n");
    printf("2. Debit Card\n");
    printf("3. Wallet\n");
    printf("Enter your choice: ");
    scanf("%d", &payment_method);
    switch (payment_method) {
        case 1:
        case 2:
            printf("Enter Card Number: ");
            scanf("%s", card_number);
            printf("Enter CVV: ");
            scanf("%d", &cvv);
            printf("Payment of %d successful for movie '%s'.\n", global_total_price, global_movie_title);
            break;
        case 3:
            printf("Enter Wallet Name (e.g., Paytm, PhonePe): ");
            scanf("%s", wallet);
            printf("Payment of %d successful through %s for movie '%s'.\n", global_total_price, wallet, global_movie_title);
            break;
        default:
            printf("Invalid Payment Method.\n");
            return;
    }
    printf("Thank you for your payment! Enjoy the movie.\n");
}

void cancel_ticket() {
    int id;
    printf("Enter the movie ID to cancel tickets:\n");
    scanf("%d", &id);
    struct moviedetails *temp = first;
    int flag = 0;
    while (temp != NULL) {
        if (id == temp->id) {
            flag = 1;
            int num_seats;
            printf("Enter the number of seats to cancel:\n");
            scanf("%d", &num_seats);

            if (num_seats < 1 || num_seats > 50) {
                printf("Invalid number of seats. Please choose between 1 and 50.\n");
                return;
            }
            int seats[num_seats];
            printf("Enter the seat numbers to cancel (1-50):\n");
            for (int i = 0; i < num_seats; i++) {
                scanf("%d", &seats[i]);
                if (seats[i] < 1 || seats[i] > 50) {
                    printf("Invalid seat number. Please choose between 1 and 50.\n");
                    return;
                }
                if (temp->seat[seats[i] - 1] == 0) {
                    printf("Seat number %d is not booked.\n", seats[i]);
                    return;
                }
                temp->seat[seats[i] - 1] = 0; // Mark seat as available
            }
            printf("Tickets canceled successfully!\n");
            printf("Your money will be refunded within 24 hours to your bank account.\n");
            break;
        }
        temp = temp->next;
    }
    if (flag == 0) {
        printf("Movie ID does not exist.\n");
    }
}

void updatemovie() {
    char admin_username[50], admin_password[50];
    printf("**** Admin Details ****\n");
    printf("Enter the admin username: ");
    getchar();
    scanf("%[^\n]s", admin_username);
    getchar();
    printf("Enter the admin password: ");
    scanf("%[^\n]s", admin_password);

    if (strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "password") == 0) {
        printf("** Admin login successful **\n");
    } else {
        printf("Only admins can update movie details.\n");
        return;
    }

    int movieprice, id;
    char movietime[100];
    printf("Enter the movie ID to update: ");
    scanf("%d", &id);

    struct moviedetails *temp = first;
    int found = 0;

    while (temp != NULL) {
        if (id == temp->id) {
            found = 1;
            printf("Enter the new movie price: ");
            scanf("%d", &movieprice);

            printf("Enter the new showtime: ");
            getchar();
            scanf("%[^\n]s", movietime);

            temp->price = movieprice;
            strncpy(temp->showtime, movietime, sizeof(temp->showtime) - 1);
            temp->showtime[sizeof(temp->showtime) - 1] = '\0';

            printf("Movie data updated successfully.\n");
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Movie ID does not exist.\n");
    }
}

void clean_movie() {
    struct moviedetails *temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        free(temp);
    }
}