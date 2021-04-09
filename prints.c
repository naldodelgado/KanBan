#include <stdio.h>

void menu(){
    printf("\n________________________________________________________\n");
    printf("                               MENU                        \n");
    printf(" 1 - Insert task into \"ToDo\"\n");
    printf(" 2 - Move Tasks from \"ToDo\" to \"Doing\"\n");
    printf(" 3 - Give/Alternate task responsability to someone\n");
    printf(" 4 - Finish a task\n");
    printf(" 5 - Reopen a task\n");
    printf(" 6 - View boards\n");
    printf(" 7 - View someone's tasks\n");
    printf(" 8 - Sort tasks by creation date\n");
    printf("========================================================\n");
    printf("                    0 - SAVE AND QUIT \n");
    printf("========================================================\n");
}

void print_board(List l1, List l2, List l3) {
    printf("\n____________________________________\n");
    printf("             TO DO                  \n");
    printf("____________________________________\n");
    List k1 = l1->next;
    while (k1) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k1->card->id);
        printf("| PRIORITY - %d\n", k1->card->priority);
        printf("| DATE - %d/%d/%d\n", k1->card->begin.day, k1->card->begin.month, k1->card->begin.year);
        printf("| DESCRIPTION - %s", k1->card->description);
        k1 = k1->next;
    }
    printf("\nNumber of cards - %d\n", l1->n);

    printf("\n____________________________________\n");
    printf("             DOING                  \n");
    printf("____________________________________\n");
    List k2 = l2->next;
    while (k2) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k2->card->id);
        printf("| PRIORITY - %d\n", k2->card->priority);
        printf("| DATE - %d/%d/%d\n", k2->card->begin.day, k2->card->begin.month, k2->card->begin.year);
        printf("| DESCRIPTION - %s", k2->card->description);
        printf("| PERSON - %s", k2->card->person);
        printf("| DEADLINE - %d/%d/%d\n", k2->card->deadline.day, k2->card->deadline.month, k2->card->deadline.year);
        k2 = k2->next;
    }
    printf("\nNumber of cards - %d\n", l2->n);

    printf("\n____________________________________\n");
    printf("             DONE                   \n");
    printf("____________________________________\n");
    List k3 = l3->next;
    while (k3) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k3->card->id);
        printf("| PRIORITY - %d\n", k3->card->priority);
        printf("| DATE - %d/%d/%d\n", k3->card->begin.day, k3->card->begin.month, k3->card->begin.year);
        printf("| DESCRIPTION - %s", k3->card->description);
        printf("| PERSON - %s", k3->card->person);
        printf("| DEADLINE - %d/%d/%d\n", k3->card->deadline.day, k3->card->deadline.month, k3->card->deadline.year);
        printf("| DATE OF CONCLUSION - %d/%d/%d\n", k3->card->end.day, k3->card->end.month, k3->card->end.year);
        k3 = k3->next;
    }
    printf("\nNumber of cards - %d\n", l3->n);
    printf("___________________________________\n");
    printf("Press any key to go back to menu\n");
    getchar();
    getchar();system("clear");menu();
}

void cronologic_print(List l){
    printf("\n____________________________________\n");
    printf("             CRONOLOGIC TASK PRINT               \n");
    printf("____________________________________\n");
    List k1 = l->next;
    while (k1) {
        printf("___________________\n");
        printf("| ID - %d\n", k1->card->id);
        printf("| PRIORITY - %d\n", k1->card->priority);
        printf("| DATE - %d/%d/%d\n", k1->card->begin.day, k1->card->begin.month, k1->card->begin.year);
        printf("| DESCRIPTION - %s", k1->card->description);
        if(k1->card->person!=NULL)
            printf("| PERSON - %s", k1->card->person);
        if(k1->card->deadline.day>0)
            printf("| DATE - %d/%d/%d\n", k1->card->deadline.day, k1->card->deadline.month, k1->card->deadline.year);
        if(k1->card->end.day>0)
            printf("| DATE - %d/%d/%d\n", k1->card->end.day, k1->card->end.month, k1->card->end.year);
        k1 = k1->next;
    }
    printf("\nNumber of cards - %d\n", l->n);
    printf("___________________________________\n");
    printf("Press any key to go back to menu\n");
    getchar();
    getchar();system("clear");menu();
}