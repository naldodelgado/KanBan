#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define N 5

void menu(){
    printf("\n________________________________________________________\n");
    printf("                               MENU                        \n");
    printf(" 1 - Insert task into ToDo\n");
    printf(" 2 - Move Tasks from \"ToDo\" to \"Doing\"\n");
    printf(" 3 - Give/Alternate task responsability to someone\n");
    printf(" 4 - Finish a task\n");
    printf(" 5 - Interrupt a task\n");
    printf(" 6 - View boards\n");
    printf(" 7 - View someone's tasks\n");
    printf(" 8 - Sort tasks by creation date\n");
    printf("________________________________________________________\n");
}

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
    getchar();system("clear");printf("card %d inserted into ToDo\n",no->card.id);menu();
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
    getchar();system("clear");printf("card %d from ToDo moved to DOING\n",no->card.id);menu();
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
    getchar();system("clear");printf("card %d from DOING moved to DONE\n",no->card.id);menu();
}

void reopen(List l3, List l1){
    List no,ant,inutil;
    int n; printf("Type the card ID you want to move (Done -> ToDo) - "); scanf("%d", &n);
    List aux=search_list(l3,n);
     if (aux == NULL)
        printf("Error: Card not found\n");
    else {
        /* First copy everything we want to keep and then insert it into "ToDo" list*/
        no = (List)malloc(sizeof(List_node));
        no->card.id = aux->card.id; // copy id
        no->card.priority = aux->card.priority; // copy priority
        no->card.begin = aux->card.begin; // copy begin date
        no->card.description = aux->card.description; // copy description
        look_list(l1,no->card.id,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
        /* delete the card from "Done" list once we have stored a copy of itself on the "ToDo" list*/
        delete_list(l3,n);
        l3->n--;l1->n++;
    }
    getchar();system("clear");printf("task %d reopened\n",no->card.id);menu();
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
    getchar();system("clear");printf("%s is now in charge of the card %d\n",aux2,n);menu();
}

void spy(List l2,List l3){
    int foundflag = 0;
    char * name = malloc(256*sizeof(char));
    getchar();printf("Insert the name of the person whose tasks you would like to view\n"); fgets(name, 256, stdin);

    printf("\n____________________________________\n");
    printf("             DOING    //person:%s\n",name);
    printf("____________________________________\n");
    /*while funct searching for the person*/
    List k2 = l2->next;
    while(k2){
        if(!strcmp(k2->card.person,name)){ // comparing the two names
            foundflag = 1;
            printf(" ___________________\n");
            printf("| ID - %d\n", k2->card.id);
            printf("| PRIORITY - %d\n", k2->card.priority);
            printf("| DATE - %d/%d/%d\n", k2->card.begin.day, k2->card.begin.month, k2->card.begin.year);
            printf("| DESCRIPTION - %s", k2->card.description);
            printf("| DEADLINE - %d/%d/%d\n", k2->card.deadline.day, k2->card.deadline.month, k2->card.deadline.year);
        }
        k2 = k2->next;
    }
    if(!foundflag){
        printf("No tasks\n");
        foundflag = 0;
    }

    printf("\n____________________________________\n");
    printf("             DONE   //person:%s\n",name);
    printf("____________________________________\n");
    /*while funct searching for the person*/
    List k3 = l3->next;
    while(k3){
        if(!strcmp(k3->card.person,name)){ // comparing the two names
            foundflag =1;
            printf(" ___________________\n");
            printf("| ID - %d\n", k3->card.id);
            printf("| PRIORITY - %d\n", k3->card.priority);
            printf("| DATE - %d/%d/%d\n", k3->card.begin.day, k3->card.begin.month, k3->card.begin.year);
            printf("| DESCRIPTION - %s", k3->card.description);
            printf("| DEADLINE - %d/%d/%d\n", k3->card.deadline.day, k3->card.deadline.month, k3->card.deadline.year);
            printf("| DATE OF CONCLUSION - %d/%d/%d\n", k3->card.end.day, k3->card.end.month, k3->card.end.year);   
        }
        k3 = k3->next;
    }
    if(!foundflag){
        printf("No tasks\n");
        foundflag = 0;
    }
    getchar();system("clear");menu();
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
    printf("___________________________________\n");
    printf("Press any key to go back to menu\n");
    getchar();
    getchar();system("clear");menu();
}



int main() {
    List ToDo = create_list();
    List Doing = create_list();
    List Done = create_list();
    
    menu();
    int input;
    printf("$ "); scanf("%d", &input);

    while(input!=0) {
        
        if      (input==0) exit(0);
        else if (input==1) insert_1(ToDo);                             // 1. inserir uma nova tarefa na lista "To Do"
        else if (input==3) change_person(Doing);                // 3. Alterar a pessoa responsável por um cartão em "Doing"
        else if (input==2) insert_2(ToDo,Doing);                   // 2. Mover cartões "To Do" -> "Doing"
        else if (input==4) insert_3(Doing,Done);                  // 4. Fechar tarefa. "Doing" -> "Done"
        else if (input==6) print_board(ToDo,Doing,Done);    // 6. Visualizar o quadro
        else if (input==5) reopen(Done,ToDo);                     // 5. Reabrir tarefa. "Done" -> "To Do"
        else if (input==7) spy(Doing,Done);                         // 7. Visualizar as tarefas de uma pessoa
        
        else printf("Error: invalid input\n");
        
        printf("\n$ "); scanf("%d", &input);
    }
    printf("See you next time!\n");


    // 8. Visualizar as tarefas ordenas por data de criação
    return 0;
}