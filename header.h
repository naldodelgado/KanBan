typedef struct date {
    int day, month, year;
} Date;



typedef struct card {
    int id, priority;
    Date begin, deadline, end;
    char *description, *person;
} Card;

Card create_card();



typedef struct lnode* List;
typedef struct lnode {
    Card card;
    int n;
    List next;
} List_node;

List create_list();
void look_list(List l, int p, List *ant, List *atual);
List search_list(List l, int n);
void delete_list(List l, int n);
void insert_1(List l);
void insert_2(List l1, List l2);
void insert_3(List l2, List l3);
void print_board(List l1, List l2, List l3);
void reopen(List l1,List l2);
void spy(List l2,List l3);