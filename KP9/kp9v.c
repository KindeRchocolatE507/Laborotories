#include <stdio.h>
#include <stdlib.h>
#define row struct data
#define dataLenth 100
#define THE_WAY_TO_FILE "input.txt"
#define printThis printTable(thisTable, thisHeight)
#define sortThis sortTable(thisTable, thisHeight)

enum boolean{
    TABLE_IS_EMPTY,
    TABLE_IS_NOT_EMPTY
};

enum sorted{
    REVERS=-1,
    UNSORTED,
    SORTED
};

row{//  =struct data
    int key;
    char data[dataLenth];
};

int menu(){
    int menu;
    printf("Выберите необходимое действие:\n0.Выйти из программы\n1.Считать таблицу из файла \"input.txt\"\n2.Отобразить таблицу в терминале(консоле)\n3.Удалить данные таблицы из памяти\n4.Выполнить сортировку\n");
    scanf("%d",&menu);
    return menu;
}

void readTable(row**table, int *height){
    FILE *stream=fopen(THE_WAY_TO_FILE, "r");
    int i;
    for(i=0;;i++){
        table[i]=malloc(sizeof(row));
        if(fscanf(stream,"%d", &(table[i]->key))==EOF){
            if(feof(stream)==1){
                printf("\nЧтение файла окончено.");
                break;
            }
            else{
                printf("\nОшибка чтения из файла\n\n");
                break;
            }
        }
        fscanf(stream, "%[^\n]s", table[i]->data);                          //Поэтому таблица должна заканчиваться на перенос строки
    }    
    *height=i;
    fclose(stream);
}

void swapTableElements(row**table, int index_1, int index_2){
    row*bufer;
    bufer=(row*)table[index_1];
    table[index_1]=table[index_2];
    table[index_2]=bufer;
}

void sortTable(row**table, int height){
    int nonSortedMinKeyIndex;
    for(int i=0;i<height;i++){
        nonSortedMinKeyIndex=i;
        for(int j=i+1;j<height;j++){
            if(table[nonSortedMinKeyIndex]->key>table[j]->key){
                nonSortedMinKeyIndex=j;
            }
        }
        if(i!=nonSortedMinKeyIndex) swapTableElements(table, i, nonSortedMinKeyIndex);
    }
}

void printTable(row**table, int height){
    int j;
    for(int i=0;i<height;i++){
        j=0;
        printf("\t%d\t", table[i]->key);
        while (table[i]->data[j]!='\0'){
            printf("%c", table[i]->data[j]);
            j++;
        }
        printf("\n");
    }
}

enum sorted isItSorted(row**table, int height){
    if(height>1){
        if(table[0]->key<table[1]->key){
            enum sorted sort=SORTED;
            for(int i=1;i<height-1;i++){
                if(table[i]->key>table[i+1]->key){
                    return UNSORTED;
                }
            }
            return SORTED;
        }
        else{
            enum sorted sort=REVERS;
            for(int i=1;i<height-1;i++){
                if(table[i]->key<table[i+1]->key){
                    return UNSORTED;
                }
            }
            return REVERS;
        }
    }else{
        return SORTED;
    }
}



int main(){
    enum boolean tab=TABLE_IS_EMPTY;
    enum sorted isSorted=UNSORTED;
    row* thisTable[12];
    int thisHeight, i, j;
    while(1)
    {
        switch(menu()){
            case 0:                                                 //Выход из проги
                printf("\nПрограмма завершена\n\n");
                exit(0);
            break;
            case 1:                                                 //Считать таблицу из файла
                readTable(thisTable, &thisHeight);
                printf("\nТаблица считана\n\n");
                tab=TABLE_IS_NOT_EMPTY;
            break;
            case 2:                                                 //Вывести таблицу в терминал
                if(tab!=TABLE_IS_EMPTY){
                    printf("\nИсходная таблица:\n\n");
                    printThis;
                }
                else{
                    printf("\nТаблица не была введена в программу или была очищена\n\n");
                }
                
            break;
            case 3:                                                 //Удалить из памяти таблицу
                if(tab!=TABLE_IS_EMPTY){
                    for(i=0;i<thisHeight;i++){
                        free(thisTable[i]);
                    }
                    tab=TABLE_IS_EMPTY;
                    printf("\nТаблица выла удалена из памяти\n\n");
                }
                else{
                    printf("\nТаблица в памяти отсутствует\n\n");
                }
            break;
            case 4:                                                 //Сортировка
                isSorted=isItSorted(thisTable, thisHeight);
                if(tab!=TABLE_IS_EMPTY){
                    if(isSorted!=SORTED){
                        if(isSorted==REVERS){
                            printf("\nТаблица изначально была записана в обратном порядке\n");
                        }
                        else{
                            printf("\nТаблица не была отсортирована\n");
                        }
                        printf("\nИсходная таблица:\n");
                        printThis;
                        sortTable(thisTable, thisHeight);
                        printf("\nСортировка выполнена:\n");
                        printThis;
                    }
                    else{
                        printf("\nТаблица уже была отсортирована\n\n");
                        printThis;
                    }
                }
                else{
                    printf("\nТаблица не была введена в программу или была очищена\n\n");                    
                }
            break;
        }        
    }

}