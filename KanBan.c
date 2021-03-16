#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define N 5

List create_list() {
    List a = (List)malloc(sizeof(List_node));
    if (a!=NULL) {
        a->n = 0;
        a->next = NULL;
    }
    return a;
}

Card create_card() {
    Card c;
    char *aux = malloc(256*sizeof(char));
    printf("\nCREATE NEW CARD\n");
    printf("ID = "); scanf("%d", &c.id);
    printf("Priority (1-10) = "); scanf("%d", &c.priority);
    printf("Creation date (day month year) = "); scanf("%d%d%d", &c.begin.day, &c.begin.month, &c.begin.year); getchar();
    printf("Description: "); fgets(aux, 256, stdin); c.description=aux;
    return c;
}

void look_list(List l, int p, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && (*atual)->card.id<p) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && (*atual)->card.id!=p)
        *atual = NULL;
}

List search_list(List l, int n) {
    List ant, atual;
    look_list(l,n,&ant,&atual);
    return (atual);
}

void delete_list(List l, int n) {
    List ant1, atual1;
    look_list(l,n,&ant1,&atual1);
    if (atual1!=NULL) {
        ant1->next = atual1->next;
        free(atual1);
    }
}

void insert_1(List l) {
    List no;
    List ant, inutil;
    no = (List)malloc(sizeof(List_node));
    if (no!=NULL) {
        no->card = create_card();
        look_list(l,no->card.id,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
    }
    l->n++;
}

void insert_2(List l1, List l2) {
    List no, ant, inutil;
    char *aux2 = malloc(256*sizeof(char));
    if (l2->n == N)
        printf("Error: List is full\n");
    else {
        int n; printf("Type the card ID you want to move (ToDo -> Doing) - "); scanf("%d", &n);
        List aux = search_list(l1,n);
        if (aux == NULL)
            printf("Error: Card not found\n");
        else {
            no = (List)malloc(sizeof(List_node));
            no->card = aux->card;
            getchar(); printf("Person responsable - "); fgets(aux2, 256, stdin); no->card.person = aux2;
            printf("Write a deadline (day month year) - "); scanf("%d%d%d", &no->card.deadline.day, &no->card.deadline.month, &no->card.deadline.year);
            look_list(l2,no->card.id,&ant,&inutil);
            no->next = ant->next;
            ant->next = no;
            delete_list(l1,n);
            l1->n--; l2->n++;
        }
    }
}

void insert_3(List l2, List l3) {
    List no, ant, inutil;
    int n; printf("Type the card ID you want to move (Doing -> Done) - "); scanf("%d", &n);
    List aux = search_list(l2,n);
    if (aux == NULL)
        printf("Error: Card not found\n");
    else {
        no = (List)malloc(sizeof(List_node));
        no->card = aux->card;
        printf("Write date of conclusion (day month year) - "); scanf("%d%d%d", &no->card.end.day, &no->card.end.month, &no->card.end.year);
        look_list(l3,no->card.id,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
        delete_list(l2,n);
        l2->n--; l3->n++;
    }
}

void change_person(List l2) {
    List aux;
    int n; printf("Type the card ID you want to change the person (Doing) - "); scanf("%d", &n);
    char*aux2 = malloc(256*sizeof(char));
    aux = search_list(l2,n);
    if (aux == NULL)
        printf("Error: Card not found\n");
    else {
        getchar(); printf("New person responsable - "); fgets(aux2, 256, stdin); aux->card.person = aux2;
    }
}

void print_board(List l1, List l2, List l3) {
    printf("\n____________________________________\n");
    printf("             TO DO                  \n");
    printf("____________________________________\n");
    List k1 = l1->next;
    while (k1) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k1->card.id);
        printf("| PRIORITY - %d\n", k1->card.priority);
        printf("| DATE - %d/%d/%d\n", k1->card.begin.day, k1->card.begin.month, k1->card.begin.year);
        printf("| DESCRIPTION - %s", k1->card.description);
        k1 = k1->next;
    }
    printf("\nNumber of cards - %d\n", l1->n);

    printf("\n____________________________________\n");
    printf("             DOING                  \n");
    printf("____________________________________\n");
    List k2 = l2->next;
    while (k2) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k2->card.id);
        printf("| PRIORITY - %d\n", k2->card.priority);
        printf("| DATE - %d/%d/%d\n", k2->card.begin.day, k2->card.begin.month, k2->card.begin.year);
        printf("| DESCRIPTION - %s", k2->card.description);
        printf("| PERSON - %s", k2->card.person);
        printf("| DEADLINE - %d/%d/%d\n", k2->card.deadline.day, k2->card.deadline.month, k2->card.deadline.year);
        k2 = k2->next;
    }
    printf("\nNumber of cards - %d\n", l2->n);

    printf("\n____________________________________\n");
    printf("             DONE                   \n");
    printf("____________________________________\n");
    List k3 = l3->next;
    while (k3) {
        printf(" ___________________\n");
        printf("| ID - %d\n", k3->card.id);
        printf("| PRIORITY - %d\n", k3->card.priority);
        printf("| DATE - %d/%d/%d\n", k3->card.begin.day, k3->card.begin.month, k3->card.begin.year);
        printf("| DESCRIPTION - %s", k3->card.description);
        printf("| PERSON - %s", k3->card.person);
        printf("| DEADLINE - %d/%d/%d\n", k3->card.deadline.day, k3->card.deadline.month, k3->card.deadline.year);
        printf("| DATE OF CONCLUSION - %d/%d/%d\n", k3->card.end.day, k3->card.end.month, k3->card.end.year);
        k3 = k3->next;
    }
    printf("\nNumber of cards - %d\n", l3->n);
}



int main() {
    List ToDo = create_list();
    List Doing = create_list();
    List Done = create_list();
    int input;
    printf("$ "); scanf("%d", &input);

    while(input!=0) {
        if      (input==0) exit(0);
        else if (input==1) insert_1(ToDo);                  // 1. inserir uma nova tarefa na lista "To Do"
        else if (input==3) change_person(Doing);            // 3. Alterar a pessoa responsável por um cartão em "Doing"
        else if (input==2) insert_2(ToDo,Doing);            // 2. Mover cartões "To Do" -> "Doing"
        else if (input==4) insert_3(Doing,Done);            // 4. Fechar tarefa. "Doing" -> "Done"
        else if (input==6) print_board(ToDo,Doing,Done);    // 6. Visualizar o quadro
        
        else printf("Error: invalid input\n");
        
        printf("\n$ "); scanf("%d", &input);
    }
    printf("See you next time!\n");

    
    // 5. Reabrir tarefa. "Done" -> "To Do"
    // 7. Visualizar as tarefas de uma pessoa
    // 8. Visualizar as tarefas ordenas por data de criação
    return 0;
}