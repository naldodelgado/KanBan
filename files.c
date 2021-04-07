#include "header.h"
#include <stdio.h>

void storeList(List l){
    FILE *fp;
    List k;
    sleep(1.5);
    if(!strcmp(l->name,"ToDo") && l->n>0){
        fp = fopen("ToDo.txt","w");
        k = l->next;
        while (k) {
            k->card->description[strcspn(k->card->description,"\n")] = '\0';
            fprintf(fp,"%d ", k->card->id);
            fprintf(fp,"%d ", k->card->priority);
            fprintf(fp,"%d/%d/%d ", k->card->begin.day, k->card->begin.month, k->card->begin.year);
            fprintf(fp,"\"%s\"", k->card->description);
            fprintf(fp,"\n");
            k = k->next;
        }
        fprintf(fp,"\n%d\n", l->n);
        fclose(fp);
    }
    else{
            if(!strcmp(l->name,"Doing") && l->n>0){
                fp = fopen("Doing.txt","w");
                k = l->next;
                k->card->description[strcspn(k->card->description,"\n")] = '\0';
                k->card->person[strcspn(k->card->person,"\n")] = '\0';
                while (k) {
                    fprintf(fp,"%d ", k->card->id);
                    fprintf(fp,"%d ", k->card->priority);
                    fprintf(fp,"%d/%d/%d ", k->card->begin.day, k->card->begin.month, k->card->begin.year);
                    fprintf(fp,"\"%s\"", k->card->description);
                    fprintf(fp,"\"%s\"", k->card->person);
                    fprintf(fp,"%d/%d/%d ", k->card->deadline.day, k->card->deadline.month, k->card->deadline.year);
                    fprintf(fp,"\n");
                    k = k->next;
                }
                fprintf(fp,"\n%d\n", l->n);
                fclose(fp);
            }
            else{
                if(!strcmp(l->name,"Done") && l->n>0){
                    fp = fopen("Done.txt","w");
                    k = l->next;
                    k->card->description[strcspn(k->card->description,"\n")] = '\0';
                    k->card->person[strcspn(k->card->person,"\n")] = '\0';
                    while (k) {
                        fprintf(fp,"%d ", k->card->id);
                        fprintf(fp,"%d ", k->card->priority);
                        fprintf(fp,"%d/%d/%d ", k->card->begin.day, k->card->begin.month, k->card->begin.year);
                        fprintf(fp,"\"%s\"", k->card->description);
                        fprintf(fp,"\"%s\"", k->card->person);
                        fprintf(fp,"%d/%d/%d ", k->card->deadline.day, k->card->deadline.month, k->card->deadline.year);
                        fprintf(fp,"%d/%d/%d ", k->card->end.day, k->card->end.month, k->card->end.year);
                        fprintf(fp,"\n");
                        k = k->next;
                    }
                    fprintf(fp,"\n%d\n", l->n);
                    fclose(fp);
                }
            }
        }
        printf("Done\n");
    }

void loadList(List l,List Crono){
    FILE *fp;
    char *line = malloc(256*sizeof(char));
    char* filename = l->name;
    strcat(filename,".txt");
    fp =fopen(filename,"r");
    if(fp==NULL){printf("ERROR READING FILE %s.txt",l->name);exit(1);}
    fseek(fp,0,SEEK_END);
    int length =ftell(fp);
    fseek(fp,0,SEEK_SET);
    char *buffer = malloc(length);
    fread(buffer,1,length,fp);

    line = strtok(buffer,"\n");
    while(line !=NULL){
        List no;
        List ant, inutil;
        if (no!=NULL) {
            no->card = load_card(line);
            look_list1(l,no->card->priority,&ant,&inutil);
            no->next = ant->next;
            ant->next = no;
        }
        l->n++;
        insertCrono(Crono,no->card);
        line = strtok(NULL,"\n");
    }
    fclose(fp);
}