#include <stdio.h>

void loadList(List l, List Crono){
    FILE *fp;
    
    //puts(strcat(l->name, ".txt"));
    fp = fopen(l->name,"r");
    if(fp==NULL){
        return ; // do nothing and leave it empty
    }
    int n;

    fscanf(fp,"%d",&n);

    if(strcmp(l->name,"ToDo") == 0){
        for(int j = 0; j<n; j++){
            List no;
            List ant, inutil;
            no = (List)malloc(sizeof(List_node));
            Card *c = malloc(sizeof(Card)); 
            fscanf(fp,"%d",&c->id);
            fscanf(fp,"%d",&c->priority);
            fscanf(fp,"%d %d %d",&c->begin.day,&c->begin.month,&c->begin.year);
            char * aux = malloc(1024*sizeof(char));
            fscanf(fp,"%s",aux);
            strcat(aux,"\n");
            c->description = aux;
            no->card = c;
            look_list1(l,no->card->priority,&ant,&inutil);
            no->next = ant->next;
            ant->next = no;
            l->n++;
            insertCrono(Crono,no->card);
        }
    }
    else if((strcmp(l->name,"Doing") == 0)){
        for(int j = 0; j<n; j++){
            List no;
            List ant, inutil;
            no = (List)malloc(sizeof(List_node));
            Card *c = malloc(sizeof(Card)); 
            fscanf(fp,"%d",&c->id);
            fscanf(fp,"%d",&c->priority);
            fscanf(fp,"%d %d %d",&c->begin.day,&c->begin.month,&c->begin.year);
            char * aux = malloc(1024*sizeof(char));
            fscanf(fp,"%s",aux);
            strcat(aux,"\n");
            c->description = aux;
            fscanf(fp,"%s",aux);
            strcat(aux,"\n");
            c->person = aux;
            fscanf(fp,"%d %d %d",&c->deadline.day,&c->deadline.month,&c->deadline.year);
            no->card = c;
            look_list2(l,no->card->person,&ant,&inutil);
            no->next = ant->next;
            ant->next = no;
            l->n++;
            insertCrono(Crono,no->card);
        }
    }
    else if((strcmp(l->name,"Done") == 0)){
            for(int j = 0; j<n; j++){
                List no;
                List ant, inutil;
                no = (List)malloc(sizeof(List_node));
                Card *c = malloc(sizeof(Card)); 
                fscanf(fp,"%d",&c->id);
                fscanf(fp,"%d",&c->priority);
                fscanf(fp,"%d %d %d",&c->begin.day,&c->begin.month,&c->begin.year);
                char * aux = malloc(1024*sizeof(char));
                fscanf(fp,"%s",aux);
                strcat(aux,"\n");
                c->description = aux;
                fscanf(fp,"%s",aux);
                strcat(aux,"\n");
                c->person = aux;
                fscanf(fp,"%d %d %d",&c->deadline.day,&c->deadline.month,&c->deadline.year);
                fscanf(fp,"%d %d %d",&c->end.day,&c->end.month,&c->end.year);
                no->card = c;
                look_list2(l,no->card->person,&ant,&inutil);
                no->next = ant->next;
                ant->next = no;
                l->n++;
                insertCrono(Crono,no->card);
        }
    }

    fclose(fp);
}

void storeList(List l){     // fazer storeList diferentes para cada lista (sugestão)
    FILE *fp;
    List k;
    sleep(1.5);
    if(!strcmp(l->name,"ToDo")){
        fp = fopen("ToDo","w");
        fprintf(fp,"%d\n",l->n);
        if (l->n>0) {
            k = l->next;
            while (k) {
                k->card->description[strcspn(k->card->description,"\n")] = '\0';
                fprintf(fp,"%d\n", k->card->id);
                fprintf(fp,"%d\n", k->card->priority);
                fprintf(fp,"%d %d %d\n", k->card->begin.day, k->card->begin.month, k->card->begin.year);
                fprintf(fp,"%s\n", k->card->description);
                //fprintf(fp,"\n");
                k = k->next;
            }
        }
        //fprintf(fp,"\n%d\n", l->n);
        fclose(fp);
    }
    else{
            if(!strcmp(l->name,"Doing")){
                fp = fopen("Doing","w");
                fprintf(fp,"%d\n",l->n);
                if (l->n>0) {
                    k = l->next;
                    k->card->description[strcspn(k->card->description,"\n")] = '\0';
                    k->card->person[strcspn(k->card->person,"\n")] = '\0';
                    while (k) {
                        fprintf(fp,"%d\n", k->card->id);
                        fprintf(fp,"%d\n", k->card->priority);
                        fprintf(fp,"%d %d %d\n", k->card->begin.day, k->card->begin.month, k->card->begin.year);
                        fprintf(fp,"%s\n", k->card->description);
                        fprintf(fp,"%s\n", k->card->person);
                        fprintf(fp,"%d %d %d\n", k->card->deadline.day, k->card->deadline.month, k->card->deadline.year);
                        //fprintf(fp,"\n");
                        k = k->next;
                    }
                }
                //fprintf(fp,"\n%d\n", l->n);
                fclose(fp);
            }
            else{
                if(!strcmp(l->name,"Done")){
                    fp = fopen("Done","w");
                    fprintf(fp,"%d\n",l->n);
                    if (l->n>0) {
                        k = l->next;
                        k->card->description[strcspn(k->card->description,"\n")] = '\0';
                        k->card->person[strcspn(k->card->person,"\n")] = '\0';
                        while (k) {
                            fprintf(fp,"%d\n", k->card->id);
                            fprintf(fp,"%d\n", k->card->priority);
                            fprintf(fp,"%d %d %d\n", k->card->begin.day, k->card->begin.month, k->card->begin.year);
                            fprintf(fp,"%s\n", k->card->description);
                            fprintf(fp,"%s\n", k->card->person);
                            fprintf(fp,"%d %d %d\n", k->card->deadline.day, k->card->deadline.month, k->card->deadline.year);
                            fprintf(fp,"%d %d %d\n", k->card->end.day, k->card->end.month, k->card->end.year);
                            //fprintf(fp,"\n");
                            k = k->next;
                        }
                    }
                    //fprintf(fp,"\n%d\n", l->n);
                    fclose(fp);
                }
            }
        }
        printf("Done\n");
    }

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