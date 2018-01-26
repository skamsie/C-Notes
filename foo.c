#include <menu.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char **elements;
    int length;
} splitArray;

// save file contents to string pointer
char *readFile(char *filename) {
    FILE *f = fopen(filename, "rt");

    if (f == NULL) {
        puts("Cannot open file.");
        exit(-1);
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *) malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);

    return buffer;
}

splitArray split(char *str, char *delimiter) {
    char **array = NULL;
    char *p = strtok(str, delimiter);
    int n_spaces = 0;
    splitArray arr;

    while (p) {
      array = realloc (array, sizeof (char*) * ++n_spaces);

      if (array == NULL)
        exit (-1); /* memory allocation failed */

      size_t len = strlen(p);

      // strip newline if exists
      if (p[len - 1] == '\n') {
        p[--len] = '\0';
      }

      array[n_spaces - 1] = p;
      p = strtok(NULL, "::");
    }

    /* realloc one extra element for the last NULL */

    array = realloc (array, sizeof (char*) * (n_spaces + 1));
    array[n_spaces] = 0;

    arr.elements = array;
    arr.length = n_spaces;

    return arr;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void func(char *name);

int main()
{
    char *str = readFile("file.txt");
    splitArray arr = split(str, "::");
    char **choices = arr.elements;
    int n_choices = arr.length;

    ITEM **my_items;
    MENU *my_menu;

    int i;
    int c;
    int l = 0;

    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

    /* Initialize items */
    my_items = malloc(n_choices * sizeof(ITEM));

    for(i = 0; i < n_choices; i++) {
        if (i % 2 == 0) {
            my_items[l] = new_item(choices[i], choices[i + 1]);
            set_item_userptr(my_items[l], func); // set user pointer
            ++l;
        }
    }

    my_items[n_choices] = (ITEM *)NULL;

    /* Create menu */
    my_menu = new_menu((ITEM **)my_items);

    /* Post the menu */
    mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
    mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
    post_menu(my_menu);
    refresh();

    while((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: {
                ITEM *cur;
                void (*p)(char *);
                cur = current_item(my_menu);
                p = item_userptr(cur);
                p((char *)item_description(cur));
                pos_menu_cursor(my_menu);
            }
            break;
        }
    }

    unpost_menu(my_menu);
    for(i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    free_menu(my_menu);
    endwin();

    puts("/Users/adimian/Github");
    return 0;
}

void func(char *name)
{	move(25, 0);
    clrtoeol();
    mvprintw(25, 0, "Item selected is : %s", name);
}
