#include "utils.c"

int main() {
  while (1) {
    int opt;
    fflush(stdin);
    clear();
    menu(currentDir());
    int input = scanf("%d", &opt);
    if (input == EOF) {
      printf("\n\nBye :)\n");
      exit(0);
    } else if (input != 1) {
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
      printf("\nInvalid Input\n");
      _pause();
      continue;
    } else if (opt > 5 || opt < 0) {
      printf("\nInvalid Input\n");
      fflush(stdin);
      _pause();
    } else {
      fflush(stdin);
      if (opt == 1) { // Add Book
        addBook();
      } else if (opt == 2) { // Display All Books
        clear();
        displayBooks();
      } else if (opt == 3) { // Search Book
        clear();
        searchBook();
      } else if (opt == 4) { // update Book
        clear();
        updateBook();
      } else if (opt == 5) {
        clear();
        deleteBook(); // delete book
      } else if (opt == 0) {
        printf("\nBye :)\n");
        exit(0);
      }
    }
  }
  return 0;
}
