#include <stdio.h>
#include <stdlib.h> // for system
#include <string.h>
#include <unistd.h> // for getcwd functions

#ifdef _WIN32
#include <conio.h>
#endif
// COLORS
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define YEL "\e[0;33m"
#define RESET "\e[0m"
#define BGRN "\e[1;32m"
#define RED "\e[0;31m"
#define BYEL "\e[1;33m"
#define BWHT "\e[1;37m"

// UI Related Functions
char *currentDir() {
  static char dir[1024];
  getcwd(dir, sizeof(dir));
  return dir;
}
void clear() { system("@cls||clear"); }

void _pause() {
#ifdef __linux__
  system("sh -c \"read -n 1 -s -r -p 'Press any key to continue... '\"");
#else
  printf("Press any key to continue...");
  getch();
#endif
}

void menu(char *path, int opt, int alt_opt) {
  printf("       .--.                   .---.\n"
         "   .---|__|           .-.     |~~~|\n"
         ".--|===|--|_          |_|     |~~~|--.\n"
         "|  |===|  |'\\     .---!~|  .--|   |--|\n"
         "|%%%%|   |  |.'\\    |===| |--|%%%%|   |  |\n"
         "|%%%%|   |  |\\.'\\   |   | |__|  |   |  |\n"
         "|  |   |  | \\  \\  |===| |==|  |   |  |\n"
         "|  |   |__|  \\.'\\ |   |_|__|  |~~~|__|\n"
         "|  |===|--|   \\.'\\|===|~|--|%%%%|~~~|--|\n"
         "^--^---'--^    `-'`---^-^--^--^---'--'\n"
         "\n[1] Add Book\n"
         "[2] Display Book\n");

  if (opt == 3)
    printf(CYN "[3] Search Book (*)\n" RESET);
  else
    printf("[3] Search Book\n");
  if (alt_opt == 1 && opt == 3 || opt == 31) {
    printf(CYN "\t[1] Book ID" RESET);
    printf("\n\t[2] Title\n\t[3] Author\n");
  } else if (alt_opt == 2 && opt == 3 || opt == 32) {
    printf("\t[1] Book ID\n");
    printf(CYN "\t[2] Title\n" RESET);
    printf("\t[3] Author\n");
  } else if (alt_opt == 3 && opt == 3 || opt == 33) {
    printf("\t[1] Book ID\n");
    printf("\t[2] Title\n");
    printf(CYN "\t[3] Author\n" RESET);
  } else {
    printf("\t[1] Book ID\n");
    printf("\t[2] Title\n");
    printf("\t[3] Author\n");
  }
  printf("[4] Update Book Details\n");
  if (opt == 5)
    printf(CYN "[5] Delete Book (*)\n" RESET);
  else
    printf("[5] Delete Book\n");
  if (alt_opt == 1 && opt == 5 || opt == 51) {
    printf(CYN "\t[1] Book ID" RESET);
    printf("\n\t[2] Title\n\t[3] Author\n");
  } else if (alt_opt == 2 && opt == 5 || opt == 52) {
    printf("\t[1] Book ID\n");
    printf(CYN "\t[2] Title\n" RESET);
    printf("\t[3] Author\n");
  } else if (alt_opt == 3 && opt == 5 || opt == 53) {
    printf("\t[1] Book ID\n");
    printf("\t[2] Title\n");
    printf(CYN "\t[3] Author\n" RESET);
  } else {
    printf("\t[1] Book ID\n");
    printf("\t[2] Title\n");
    printf("\t[3] Author\n");
  }
  printf("[6] Reserve Book\n");
  printf("[0] Exit\n\n" BGRN "B1-GroupB@CSE124" RESET BWHT ":" RESET BYEL
         "(%s)" RESET BWHT "$ " RESET,
         path);
}

// Backend Functions

// Book structure for linked list
typedef struct Node {
  int id;
  char title[100];
  char author[100];
  int releaseYear;
  int is_reserved;
  char reserved_by[50];
  struct Node *next;
} node;
node *head = NULL, *tail = NULL;

// Database Function
void save(node *head, char operation[2]) {
  FILE *file = fopen("library.txt", operation);
  if (!file)
    return;
  node *curr = head;
  while (curr) {
    fprintf(file, "%d;%s;%s;%d;%d;%s\n", curr->id, curr->title, curr->author,
            curr->releaseYear, curr->is_reserved,
            strlen(curr->reserved_by) ? curr->reserved_by : " ");
    curr = curr->next;
  }
  fclose(file);
}

void load(node **head, node **tail) {
  FILE *file = fopen("library.txt", "r");
  if (!file)
    return;
  *head = *tail = NULL;
  while (!feof(file)) {
    node *new_node = malloc(sizeof(node));
    if (fscanf(file, "%d;%99[^;];%99[^;];%d;%d;%49[^\n]\n", &new_node->id,
               new_node->title, new_node->author, &new_node->releaseYear,
               &new_node->is_reserved, new_node->reserved_by) == 6) {
      new_node->next = NULL;
      if (*head == NULL)
        *head = *tail = new_node;
      else {
        (*tail)->next = new_node;
        *tail = new_node;
      }
    } else {
      free(new_node);
      break;
    }
  }
  fclose(file);
}

// Backend Functions (Add, Delete, Display, Search, Update)
void addBook() {
  node *newNode = (node *)malloc(sizeof(node));
  if (newNode == NULL) {
    printf(RED "Memory allocation failed!\n" RESET);
    return;
  }
  printf("\nEnter Book ID: ");
  scanf("%d", &newNode->id);
  printf("Enter book title: ");
  getchar();
  fgets(newNode->title, 100, stdin);
  newNode->title[strcspn(newNode->title, "\n")] = '\0';
  printf("Enter author name: ");
  fgets(newNode->author, 100, stdin);
  newNode->author[strcspn(newNode->author, "\n")] = '\0';
  printf("Enter release year: ");
  scanf("%d", &newNode->releaseYear);

  newNode->is_reserved = 0;
  strcpy(newNode->reserved_by, "");
  newNode->next = NULL;
  if (head == NULL) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  save(head, "a");
  printf(GRN "\nBook added successfully!\n" RESET);
  _pause();
}

void displayBooks() {
  if (head == NULL) {
    printf(RED "\nNo books available.\n" RESET);
    _pause();
    return;
  }
  node *temp = head;
  printf("\nList of Books:\n");
  while (temp != NULL) {
    printf(YEL "\nTitle: %s\n" RESET, temp->title);
    printf("\tAuthor: %s\n", temp->author);
    printf("\tRelease Year: %d\n", temp->releaseYear);
    printf("\tBook ID: %d\n", temp->id);
    if (temp->is_reserved)
      printf("\tReserved By: %s\n", temp->reserved_by);
    else
      printf("\tStatus: Available\n");
    temp = temp->next;
  }
  printf("\n");
  _pause();
}

void searchBook(int opt) {
  if (head == NULL) {
    printf(RED "\nNo books to search.\n" RESET);
    _pause();
    return;
  }
  node *temp = head;
  if (opt == 1 || opt == 31) {
    int id;
    printf("\nEnter the book ID to search: ");
    scanf("%d", &id);
    while (temp != NULL) {
      if (temp->id == id) {
        printf("\nBook found:\n");
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("Release Year: %d\n", temp->releaseYear);
        _pause();
        return;
      }
      temp = temp->next;
    }
  } else if (opt == 2 || opt == 32) {
    char title[100];
    printf("\nEnter the title of the book to search: ");
    getchar();
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = '\0';
    while (temp != NULL) {
      if (strcmp(temp->title, title) == 0) {
        printf("\nBook found:\n");
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("Release Year: %d\n", temp->releaseYear);
        _pause();
        return;
      }
      temp = temp->next;
    }
  } else if (opt == 3 || opt == 33) {
    char author[100];
    printf("\nEnter the author name to search: ");
    getchar();
    fgets(author, 100, stdin);
    author[strcspn(author, "\n")] = '\0';
    while (temp != NULL) {
      if (strcmp(temp->author, author) == 0) {
        printf("\nBook found:\n");
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("Release Year: %d\n", temp->releaseYear);
        _pause();
        return;
      }
      temp = temp->next;
    }
  }
  printf(RED "\nBook not found!\n" RESET);
  _pause();
}

void deleteBook(int opt) {
  if (head == NULL) {
    printf(RED "\nNo books to delete.\n" RESET);
    _pause();
    return;
  }
  char input[100];
  printf("\nEnter the ");
  if (opt == 1 || opt == 51)
    printf("ID");
  else if (opt == 2 || opt == 52)
    printf("title");
  else if (opt == 3 || opt == 53)
    printf("author");
  printf(" of the book to delete: ");
  getchar();
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0';
  node *temp = head, *prev = NULL;
  while (temp != NULL) {
    int match = 0;
    if ((opt == 1 || opt == 51) && atoi(input) == temp->id)
      match = 1;
    else if ((opt == 2 || opt == 52) && strcmp(input, temp->title) == 0)
      match = 1;
    else if ((opt == 3 || opt == 53) && strcmp(input, temp->author) == 0)
      match = 1;
    if (match) {
      if (temp == head)
        head = temp->next;
      else
        prev->next = temp->next;
      if (tail == temp)
        tail = prev;
      free(temp);
      save(head, "w");
      printf(GRN "\nBook deleted successfully!\n" RESET);
      _pause();
      return;
    }
    prev = temp;
    temp = temp->next;
  }
  printf(RED "\nBook not found!\n" RESET);
  _pause();
}

void updateBook() {
  if (head == NULL) {
    printf(RED "\nNo books available to update.\n" RESET);
    _pause();
    return;
  }
  char title[100];
  printf("\nEnter the title of the book to update: ");
  getchar();
  fgets(title, 100, stdin);
  title[strcspn(title, "\n")] = '\0';
  node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->title, title) == 0) {
      int choice;
      printf("\nWhat do you want to update?\n");
      printf("[1] Title\n");
      printf("[2] Author\n");
      printf("[3] Release Year\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      getchar();
      switch (choice) {
      case 1:
        printf("Enter new title: ");
        fgets(temp->title, 100, stdin);
        temp->title[strcspn(temp->title, "\n")] = '\0';
        save(head, "a");
        printf(GRN "\nTitle updated successfully!\n" RESET);
        break;
      case 2:
        printf("Enter new author: ");
        fgets(temp->author, 100, stdin);
        temp->author[strcspn(temp->author, "\n")] = '\0';
        save(head, "w");
        printf(GRN "\nAuthor updated successfully!\n" RESET);
        break;
      case 3:
        printf("Enter new release year: ");
        scanf("%d", &temp->releaseYear);
        save(head, "w");
        printf(GRN "\nRelease year updated successfully!\n" RESET);
        break;
      default:
        printf(RED "\nInvalid choice.\n" RESET);
        break;
      }
      _pause();
      return;
    }
    temp = temp->next;
  }

  printf(RED "\nBook not found!\n" RESET);
  _pause();
}

void reserveBook() {
  int bookId;
  char studentName[50];
  printf("Enter Book ID to reserve: ");
  scanf("%d", &bookId);
  node *current = head;
  while (current != NULL) {
    if (current->id == bookId) {
      if (current->is_reserved) {
        printf("Sorry, the book \"%s\" is already reserved by %s.\n",
               current->title, current->reserved_by);
        return;
      } else {
        printf("Enter Student Name: ");
        scanf(" %[^\n]", studentName);
        current->is_reserved = 1;
        strcpy(current->reserved_by, studentName);
        save(head, "w");
        printf("Book \"%s\" has been successfully reserved for %s.\n",
               current->title, studentName);
        return;
      }
    }
    current = current->next;
  }
  printf("Book with ID %d not found.\n", bookId);
}
