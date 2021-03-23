#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"



/***********************************************************Problems to solve***********************************************************************
*               - reserve cards ID so there will be no duplicated IDs                                                      ||||||||******* SOLVED ********||||||||
*                     ideas: reserve them on arrays and then store them on files
*                             autoincrement IDs (THIS IS ACTUALLY A REQUIREMENT)   
*                             run through every List and check of there is any card with that same ID 
*
*               - table apresentations on horizontal
*                     ideas: brute force
*                             find 'presentations hacks' w\o using <graph.h> on stack
*
*               -  data storing
*                     ideas: find an equivalent to JSON ex: "#include<json-c/json.h>"
*                               brute force creating functions to read and edit files
*                     questions:
*                           should we save state after every interaction or should we save state only before quitting the program?
*                           if we save state only before quitting is there a way to prevent Data loss/corruption after a forced interruption (^C or process kill)?
******************************************************************************************************************************************************/

/*****************************************************************************
 *  Data files should contain an array with all IDs so we dont repeat IDs
 *  Card List file for each List, probably should keep each List on different files
 **************************************************************************** */

#define N 5



int get_newid(){
    FILE *f = fopen("id.txt","r");
    if(f==NULL){ // if the file doenst exist then the program will create it and store the first ID
        f=fopen("id.txt","w");
        fprintf(f,"%d",1);
        fclose(f);
        return 1; // the first ID
    }else{
        int id;
        fscanf(f,"%d",&id);
        fclose(f);
        f = fopen("id.txt","w"); // clears the file
        fprintf(f,"%d",++id);
        fclose(f);
        return id;
    }

}

int IsDateValid(Date input){
    //check year
    if(input.year>=2000 && input.year<=9999)
    {
        //check month
        if(input.month>=1 && input.month<=12)
        {
            //check days
            if((input.day>=1 && input.day<=31) && (input.month==1 || input.month==3 || input.month==5 || input.month==7 || input.month==8 || input.month==10 || input.month==12))
                return 1;
            else if((input.day>=1 && input.day<=30) && (input.month==4 || input.month==6 || input.month==9 || input.month==11))
                return 1;
            else if((input.day>=1 && input.day<=28) && (input.month==2))
                return 1;
            else if(input.day==29 && input.month==2 && (input.year%400==0 ||(input.year%4==0 && input.year%100!=0)))
                return 1;
            else
                printf("Invalid Date, try again\n");
        }
        else
            printf("Invalid Date, try again\n");
    }
    else
        printf("Invalid Date, try again\n");
    return 0;
}

int datecmp(Date d1, Date d2){
    if(d1.year<d2.year)
        return 1;
    else if(d1.month<d2.month)
        return 1;
    else if(d1.day<d2.day)
        return 1;
    else if(d1.day == d2.day)
        return 0;
    else
        return -1;
}

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

Card* create_card() {
    Card *c = malloc(sizeof(*c));
    char *aux = malloc(256*sizeof(char));
    c->id = get_newid();
    printf("\nCREATE NEW CARD || id=%d\n",c->id);
    
    printf("Priority (1-10) = "); scanf("%d", &c->priority);
    Date input;
    do{
        printf("Creation date (day month year) = "); scanf("%d%d%d", &input.day, &input.month, &input.year); 
    }while(!IsDateValid(input));
    c->begin.day=input.day;
    c->begin.month=input.month;
    c->begin.year=input.year;
    getchar();
    printf("Description: "); fgets(aux, 256, stdin); c->description=aux;
    return c;
}

void look_list(List l, int p, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && (*atual)->card->id>p) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && (*atual)->card->id!=p)
        *atual = NULL;
}

void look_list1(List l, int p, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && (*atual)->card->priority>p) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && (*atual)->card->priority!=p)
        *atual = NULL;
}

void look_list2(List l, char *person, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && strcmp((*atual)->card->person,person) > 0) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && strcmp((*atual)->card->person,person) != 0)
        *atual = NULL;
}

void look_list3(List l, Date d, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && datecmp((*atual)->card->end,d) > 0) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && datecmp((*atual)->card->end,d) !=0)
        *atual = NULL;
}

void look_listCrono(List l, Date d, List *ant, List *atual) {
    *ant = l; *atual = l->next;
    while ((*atual)!=NULL && datecmp((*atual)->card->begin,d) > 0) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual)!=NULL && datecmp((*atual)->card->begin,d) !=0)
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

void insert_1(List l, List Crono) { // this one should insert them ordered by priority
    List no;
    List ant, inutil;
    no = (List)malloc(sizeof(List_node));
    if (no!=NULL) {
        no->card = create_card();
        look_list1(l,no->card->priority,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
    }
    l->n++;
    insertCrono(Crono,no->card);
    getchar();system("clear");printf("card %d inserted into ToDo\n",no->card->id);menu();
}

void insert_2(List l1, List l2) { // this one should insert them ordered by name
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
            getchar(); printf("Person responsable - "); fgets(aux2, 256, stdin); no->card->person = aux2;
            Date input;
            do{
                printf("Write a deadline (day month year) - "); scanf("%d%d%d", &input.day, &input.month, &input.year); 
            }while(!IsDateValid(input));
            no->card->deadline.day=input.day;
            no->card->deadline.month=input.month;
            no->card->deadline.year=input.year;
            look_list2(l2,no->card->person,&ant,&inutil);
            no->next = ant->next;
            ant->next = no;
            delete_list(l1,n);
            l1->n--; l2->n++;
        }
    }
    system("clear");
    printf("card %d from ToDo moved to DOING\n",no->card->id);menu();
}

void insert_3(List l2, List l3) { //this one should be ordered by end date
    List no, ant, inutil;
    int n; printf("Type the card ID you want to move (Doing -> Done) - "); scanf("%d", &n);
    List aux = search_list(l2,n);
    if (aux == NULL)
        printf("Error: Card not found\n");
    else {
        no = (List)malloc(sizeof(List_node));
        no->card = aux->card;
        Date input;
        do{
            printf("Write date of conclusion (day month year) - "); scanf("%d%d%d", &input.day, &input.month, &input.year); 
        }while(!IsDateValid(input));
        no->card->end.day=input.day;
        no->card->end.month=input.month;
        no->card->end.year=input.year;
        look_list3(l3,no->card->end,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
        delete_list(l2,n);
        l2->n--; l3->n++;
    }
    system("clear");printf("card %d from DOING moved to DONE\n",no->card->id);menu();
}

void insertCrono(List Crono, Card *c){
    List no;
    List ant,inutil;
    no = (List)malloc(sizeof(List_node));
    if(no!=NULL){
        no->card = c;
        look_listCrono(Crono,no->card->begin,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
    }
    Crono->n++;
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
        no->card->id = aux->card->id; // copy id
        no->card->priority = aux->card->priority; // copy priority
        no->card->begin = aux->card->begin; // copy begin date
        no->card->description = aux->card->description; // copy description
        look_list(l1,no->card->id,&ant,&inutil);
        no->next = ant->next;
        ant->next = no;
        /* delete the card from "Done" list once we have stored a copy of itself on the "ToDo" list*/
        delete_list(l3,n);
        l3->n--;l1->n++;
    }
    getchar();system("clear");printf("task %d reopened\n",no->card->id);menu();
}

void change_person(List l2) {
    List aux;
    int n; printf("Type the card ID you want to change the person (Doing) - "); scanf("%d", &n);
    char*aux2 = malloc(256*sizeof(char));
    aux = search_list(l2,n);
    if (aux == NULL)
        printf("Error: Card not found\n");
    else {
        getchar(); printf("New person responsable - "); fgets(aux2, 256, stdin); aux->card->person = aux2;
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
        if(!strcmp(k2->card->person,name)){ // comparing the two names
            foundflag = 1;
            printf(" ___________________\n");
            printf("| ID - %d\n", k2->card->id);
            printf("| PRIORITY - %d\n", k2->card->priority);
            printf("| DATE - %d/%d/%d\n", k2->card->begin.day, k2->card->begin.month, k2->card->begin.year);
            printf("| DESCRIPTION - %s", k2->card->description);
            printf("| DEADLINE - %d/%d/%d\n", k2->card->deadline.day, k2->card->deadline.month, k2->card->deadline.year);
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
        if(!strcmp(k3->card->person,name)){ // comparing the two names
            foundflag =1;
            printf(" ___________________\n");
            printf("| ID - %d\n", k3->card->id);
            printf("| PRIORITY - %d\n", k3->card->priority);
            printf("| DATE - %d/%d/%d\n", k3->card->begin.day, k3->card->begin.month, k3->card->begin.year);
            printf("| DESCRIPTION - %s", k3->card->description);
            printf("| DEADLINE - %d/%d/%d\n", k3->card->deadline.day, k3->card->deadline.month, k3->card->deadline.year);
            printf("| DATE OF CONCLUSION - %d/%d/%d\n", k3->card->end.day, k3->card->end.month, k3->card->end.year);   
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
        printf(" ___________________\n");
        printf("| ID - %d\n", k1->card->id);
        printf("| PRIORITY - %d\n", k1->card->priority);
        printf("| DATE - %d/%d/%d\n", k1->card->begin.day, k1->card->begin.month, k1->card->begin.year);
        printf("| DESCRIPTION - %s", k1->card->description);
        k1 = k1->next;
    }
    printf("\nNumber of cards - %d\n", l->n);
    printf("___________________________________\n");
    printf("Press any key to go back to menu\n");
    getchar();
    getchar();system("clear");menu();
}


int main() {
    List ToDo = create_list();
    List Doing = create_list();
    List Done = create_list();
    List Crono = create_list();
    
    
    menu();
    int input;
    printf("$ "); scanf("%d", &input);

    while(input!=0) {
        
        if         (input==0) exit(0);
        else if (input==1){insert_1(ToDo,Crono);}                   // 1. inserir uma nova tarefa na lista "To Do"
        else if (input==3) change_person(Doing);                   // 3. Alterar a pessoa responsável por um cartão em "Doing"
        else if (input==2) insert_2(ToDo,Doing);                      // 2. Mover cartões "To Do" -> "Doing"
        else if (input==4) insert_3(Doing,Done);                     // 4. Fechar tarefa. "Doing" -> "Done"
        else if (input==6) print_board(ToDo,Doing,Done);       // 6. Visualizar o quadro
        else if (input==5) reopen(Done,ToDo);                        // 5. Reabrir tarefa. "Done" -> "To Do"
        else if (input==7) spy(Doing,Done);                            // 7. Visualizar as tarefas de uma pessoa
        else if (input==8) cronologic_print(Crono);                 // 8.Print tasks by creation order
        
        else printf("Error: invalid input\n");
        
        printf("\n$ "); scanf("%d", &input);
    }
    printf("See you next time!\n");

    return 0;
}