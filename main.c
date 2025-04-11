#include "utils.c"

int main() {
  load(&head, &tail);
  while (1) {
    int opt;
    fflush(stdin);
    clear();
    menu(currentDir(), 0, 0);
    int input = scanf("%d", &opt);
    if (input == EOF) {
      printf("\n\nThanks for using our Library Management System :)\n");
      exit(0);
    } else if (input != 1) {
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
      printf("\nInvalid Input\n");
      _pause();
      continue;
    } else if (opt > 6 && opt > 33 && opt < 31 && opt < 41 && opt > 44 &&
                   opt < 51 && opt > 53 ||
               opt < 0) {
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
        menu(currentDir(), opt, 0);
        int srch_opt;
        scanf("%d", &srch_opt);
        clear();
        menu(currentDir(), opt, srch_opt);
        searchBook(srch_opt);
      } else if (opt > 30 && opt < 34) {
        clear();
        menu(currentDir(), opt, 0);
        searchBook(opt);
      } else if (opt == 4) { // update Book
        clear();
        updateBook();
      } else if (opt == 5) {
        clear();
        menu(currentDir(), opt, 0);
        int del_opt;
        scanf("%d", &del_opt);
        clear();
        menu(currentDir(), opt, del_opt);
        deleteBook(del_opt); // delete book
      } else if (opt == 6) {
        reserveBook();
      } else if (opt == 0) {
        printf("\nThanks for using our Library Management System :)\n");
        exit(0);
      }
    }
  }
  return 0;
}
