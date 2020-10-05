#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

float tasso_mutazione = 0.01;
int pop_max = 800;
char target[]="cappella";

int main()
{
    srand(time(NULL)); //seme per generare numeri casuali
    /*dichiarazione variabili*/
    int lunghezza_target,i,j,generazioni=0,finito=0;
    lunghezza_target=strlen(target)+1; //+1 perchè strlen esclude il \0
    char popolazione[pop_max][lunghezza_target];  //vettore popolazione
    char partner_a[lunghezza_target];
    char partner_b[lunghezza_target];
    int dim; //dimensione mating pool
    int *mating_pool;

    /*setup*/
    for(i=0;i<pop_max;i++)
    {
        for(j=0;j<lunghezza_target;j++)
        {
            popolazione[i][j]=(char)(97+rand()%26);
            //popolazione[i][j]=(char)(32+rand()%90); //generazione della popolazione di frasi casuali
        }
        printf("%s\n",popolazione[i]);
    }

    while(finito!=1)
    {
    /*selezione*/

        /*calcolo fitness*/
        int N[pop_max]; //numero di volte in cui la frase viene aggiunta alla mating pool
        int punteggio;
        float fitness;
        for(i=0;i<pop_max;i++)
        {
            punteggio=0;
            for(j=0;j<lunghezza_target;j++)
            {
                if (popolazione[i][j]==target[j])
                    punteggio++;
            }
            fitness=(float)punteggio/(lunghezza_target-1);
            N[i]=fitness*100;
        }
        /*generazione mating pool*/
        dim=0;
        for(i=0;i<pop_max;i++)
        {
            dim+=N[i];
        }
        mating_pool=malloc(dim*sizeof(int));
        assert(mating_pool!=NULL);
        int m=0;
        for(i=0;i<pop_max;i++)
        {
            for(j=0;j<N[i];j++)
            {
                mating_pool[m]=i; //memorizzo l'indice di ogni frase nella mating pool tante volte quanto il valore della rispettiva fitness
                m++;
            }
        }

    /*riproduzione*/
        int a,b;
        char figlio[lunghezza_target];
        for(i=0;i<pop_max && finito==0;i++)
        {
            a=mating_pool[rand()%dim]; //indirizzo partner_a
            b=mating_pool[rand()%dim]; //indirizzo partner_b
            strcpy(partner_a,popolazione[a]);
            strcpy(partner_b,popolazione[b]);
            int midpoint=1+rand()%(lunghezza_target-2); //taglio la frase in un punto casuale
            for(j=0;j<lunghezza_target;j++)
            {
                if(j<midpoint)
                    figlio[j]=partner_a[j];
                else
                    figlio[j]=partner_b[j];
            }
            /*in base al tasso di mutazione, cambia un carattere random*/
            for(j=0;j<lunghezza_target;j++)
            {
                if(((float)(rand()%101)/100.0)<tasso_mutazione)
                    figlio[j]=(char)(97+rand()%26);
            }
            strcpy(popolazione[i],figlio);
            printf("%s\n",popolazione[i]);
            /*valutazione*/
            if(strcmp(popolazione[i],target)==0)
            {
                finito=1;
                printf("\ngenerazione %d\n",generazioni);
            }
        }
        generazioni++;
        free(mating_pool);

    /*valutazione*/
        /*for(i=0;i<pop_max && finito==0;i++)
        {
            if(strcmp(popolazione[i],target)==0)
            {
                finito=1;
                printf("%s",popolazione[i]);
                printf("\tGenerazione %d\n",generazioni);
            }
        }*/
    }


    return 0;
}

