#include <stdio.h>
#include <stdlib.h> // for system
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
               "[5] Reserve Book for Student\n"
               "[0] Exit\n\n" BGRN "B1-GroupB@CSE124" RESET BWHT ":" RESET BYEL
               "(%s)" RESET BWHT "$ " RESET;
  printf(menu, path);
}
/*
######################
 Backend Functions
#####################
*/
