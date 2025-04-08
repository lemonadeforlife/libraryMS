#include <stdio.h>
#include <stdlib.h> // for system
#include <string.h>
#include <unistd.h> // for getcwd functions

#ifdef _WIN32
#include <conio.h>
#endif
// COLORS
// TODO: Remove unused colors
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\e[0m"

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"
/*
######################
 UI Related Functions
#####################
 */
char *currentDir() {
  static char dir[1024];
  getcwd(dir, sizeof(dir));
  return dir;
}
// clear Terminal buffer or screen
void clear() { system("@cls||clear"); }

// Pauses screen & wait for user input for continue any process
void _pause() {
#ifdef __linux__
  system("sh -c \"read -n 1 -s -r -p 'Press any key to continue... '\"");
#else
  printf("Press any key to continue...");
  getch();
#endif
}
// TODO: Test this menu on windows @lemoande
void menu(char *path) {
  char *menu = "       .--.                   .---.\n"
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
               "[2] Display Book\n"
               "[3] Search Book\n"
               "\t[1] Title\n\t[2] Author\n"
               "[4] Update Book Details\n"
               "\t[1] Title\n\t[2] Author \n\t[3] Release Year\n"
               "[5] Delete Book\n"
               "[0] Exit\n\n" BGRN "B1-GroupB@CSE124" RESET BWHT ":" RESET BYEL
               "(%s)" RESET BWHT "$ " RESET;
  printf(menu, path);
}

/*
######################
 Backend Functions
#####################
*/

// Book structure for linked list
typedef struct Node {
  char title[100];
  char author[100];
  int releaseYear;
  struct Node *next;
} Node;

// Global Head and Tail
Node *head = NULL;
Node *tail = NULL;

// Backend Functions (Add, Delete, Display, Search, Update)
void addBook() {
  Node *newNode = (Node *)malloc(sizeof(Node));

  if (newNode == NULL) {
    printf(RED "Memory allocation failed!\n" RESET);
    return;
  }

  printf("\nEnter book title: ");
  getchar();
  fgets(newNode->title, 100, stdin);
  newNode->title[strcspn(newNode->title, "\n")] = '\0';

  printf("Enter author name: ");
  fgets(newNode->author, 100, stdin);
  newNode->author[strcspn(newNode->author, "\n")] = '\0';

  printf("Enter release year: ");
  scanf("%d", &newNode->releaseYear);

  newNode->next = NULL;

  if (head == NULL) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }

  printf(GRN "\nBook added successfully!\n" RESET);
  _pause();
}

void displayBooks() {
  if (head == NULL) {
    printf(RED "\nNo books available.\n" RESET);
    _pause();
    return;
  }

  Node *temp = head;
  printf("\nList of Books:\n");
  while (temp != NULL) {
    printf(YEL "\nTitle: %s\n" RESET, temp->title);
    printf("\tAuthor: %s\n", temp->author);
    printf("\tRelease Year: %d\n\n", temp->releaseYear);
    temp = temp->next;
  }
  _pause();
}

void searchBook() {
  if (head == NULL) {
    printf(RED "\nNo books to search.\n" RESET);
    _pause();
    return;
  }

  char title[100];
  printf("\nEnter the title of the book to search: ");
  getchar();
  fgets(title, 100, stdin);
  title[strcspn(title, "\n")] = '\0';

  Node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->title, title) == 0) {
      printf("\nBook found:\n");
      printf("Title: %s\n", temp->title);
      printf("Author: %s\n", temp->author);
      printf("Release Year: %d\n", temp->releaseYear);
      _pause();
      return;
    }
    temp = temp->next;
  }

  printf(RED "\nBook not found!\n" RESET);
  _pause();
}

void deleteBook() {
  if (head == NULL) {
    printf(RED "\nNo books to delete.\n" RESET);
    _pause();
    return;
  }

  char title[100];
  printf("\nEnter the title of the book to delete: ");
  getchar();
  fgets(title, 100, stdin);
  title[strcspn(title, "\n")] = '\0';

  Node *temp = head, *prev = NULL;

  // Head node deletion
  if (temp != NULL && strcmp(temp->title, title) == 0) {
    head = temp->next;
    if (tail == temp)
      tail = NULL;
    free(temp);
    printf(GRN "\nBook deleted successfully!\n" RESET);
    _pause();
    return;
  }

  while (temp != NULL && strcmp(temp->title, title) != 0) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    printf(RED "\nBook not found!\n" RESET);
    _pause();
    return;
  }

  prev->next = temp->next;
  if (tail == temp) {
    tail = prev;
  }
  free(temp);
  printf(GRN "\nBook deleted successfully!\n" RESET);
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

  Node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->title, title) == 0) {
      int choice;
      printf("\nWhat do you want to update?\n");
      printf("[1] Title\n");
      printf("[2] Author\n");
      printf("[3] Release Year\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      getchar(); // clear buffer

      switch (choice) {
      case 1:
        printf("Enter new title: ");
        fgets(temp->title, 100, stdin);
        temp->title[strcspn(temp->title, "\n")] = '\0';
        printf(GRN "\nTitle updated successfully!\n" RESET);
        break;
      case 2:
        printf("Enter new author: ");
        fgets(temp->author, 100, stdin);
        temp->author[strcspn(temp->author, "\n")] = '\0';
        printf(GRN "\nAuthor updated successfully!\n" RESET);
        break;
      case 3:
        printf("Enter new release year: ");
        scanf("%d", &temp->releaseYear);
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
