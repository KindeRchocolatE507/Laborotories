#include <stdio.h>
#include <stdlib.h>
#define list struct data
#define lenthRefresh lenth=listLenth(root, root)


enum color {
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE,
    BROWN,
    YELLOW
};

list{
    enum color thiscolor;
    list *next;
};



int menu(){
    static int a;
    printf("Выберите вариант действия:\n1. Печать списка\n2. Вставка нового элемента в список\n3. Удаление элемента из списка\n4. Подсчет длины списка\n5. Добавить элемент в конец списка\n6. Удалить весь список\n7. Выйти из программы\n");
    scanf("%d", &a);
    return a;
}

int listLenth(list *root, list *cur){
    if(cur->next==root){
        return 1;
    }
    else{
        return listLenth(root, cur->next)+1;
    }
}

void listPrint(list *root, list *cur){
    switch (cur->thiscolor)
    {
    case 0:
        printf("RED ");
        break;
    case 1:
        printf("BLUE ");
        break;
    case 2:
        printf("GREEN ");
        break;
    case 3:
        printf("BLACK ");
        break;
    case 4:
        printf("WHITE ");
        break;
    case 5:
        printf("BROWN ");
        break;
    case 6:
        printf("YELLOW ");
        break;
    }
    if (cur->next!=root)
    {
        listPrint(root, cur->next);
    }
}





void listAddElement(list *cur, int num){
    while(num!=2){
        cur=cur->next;
        num--;
    }
    list *newElement=malloc(sizeof(list));
    newElement->next=(list*)cur->next;
    cur->next=(list*)newElement;
    int choise=10;
    while (choise>7||choise<1)
    {
        printf("Выберите цвет:\n1.RED\n2.BLUE\n3.GREEN\n4.BLACK\n5.WHITE\n6.BROWN\n7.YELLOW\n"); 
        scanf("%d", &choise);
    }
    newElement->thiscolor=choise-1;
}


void listSpin (list **root, int num){
    int lenth=listLenth(*root, *root);
    while (num!=lenth){
        lenth--;
        (*root)=(*root)->next;
    }
    
}













void listDeleteElement(list *cur, int num, list **root){
    if(num==2){
        list *temp;
        temp=cur->next;
        cur->next=temp->next;
        free (temp);
        (*root)=cur->next;
    }
    else{
        listDeleteElement(cur->next, num-1, root);
    }
}

void listFree(list *root, list *cur){
    if(cur->next!=root){
        listFree(root, cur->next);
    }
    free(cur);
}

int main(){
    list *root=NULL;
    int a, lenth, choise, index;
    while(1)
    {
        a=menu();
        switch (a)
        {
            case 1://Печать
                if(root!=NULL){
                    printf("Список: ");
                    listPrint(root,root);
                    printf("\n");
                }
                else{
                    printf("Не задано ни одного элемента\n\n");
                }
                break;
            case 2://вставка нового
                if(root==NULL){
                    choise=10;
                    while (choise>7||choise<1)
                    {
                        printf("Выберите цвет:\n1.RED\n2.BLUE\n3.GREEN\n4.BLACK\n5.WHITE\n6.BROWN\n7.YELLOW\n"); 
                        scanf("%d", &choise);
                    }
                    root=malloc(sizeof(list));
                    root->thiscolor=choise-1;
                    root->next=root;
                }
                else{
                    lenthRefresh;
                    printf("Введите индекс вставки в текущем состоянии списка\n");
                    scanf("%d", &index);
                    if(index<1){
                        printf("Индекс должен быть натуральным числом\n\n");
                        break;
                    }
                    if(lenth<index){
                        index=index%lenth;
                    }
                    if(index==0){
                        index+=lenth;
                    }
                    if(index==1) {
                        index=lenth+1;
                    }
                    listAddElement(root, index);//спецфунк для первого эл-та
                }
                break;
            case 3://удаление эл-та из списка
                if(root==NULL){
                    printf("Cписок и так пуст");
                    break;
                }
                else{
                    lenthRefresh;
                    printf("Введите индекс удаляемого элемента в текущей расстановке: ");
                    scanf("%d", &index);
                    if(index<1){
                        printf("Индекс должен быть натуральным числом\n");
                        break;
                    }
                    if(lenth<index){
                        index%=lenth;
                    }
                    if(index==1) {
                        index=lenth+1;
                    }  
                    if(index==0) {
                        index=lenth;
                    }  
                    listDeleteElement(root, index, &root);
                    if(index!=1){
                        listSpin(&root, index-1);
                    }
                    printf("Элемент удалён\n");
                }
                break;
            case 4://Подсчет длины
                if(root){
                    lenth=listLenth(root, root);
                    printf("Длина списка: %d\n", lenth);
                }
                else{
                    printf("Не задано ни одного элемента\n");
                }
                break;
            case 5://добавить в конец
                if(root==NULL){
                    choise=10;
                    while (choise>7||choise<1)
                    {
                        printf("Выберите цвет:\n1.RED\n2.BLUE\n3.GREEN\n4.BLACK\n5.WHITE\n6.BROWN\n7.YELLOW\n"); 
                        scanf("%d", &choise);
                    }
                    root=malloc(sizeof(list));
                    root->thiscolor=choise-1;
                    root->next=root;
                }
                else{
                    lenthRefresh;
                    listAddElement(root, lenth+1);
                }
                break;
            case 6://удалить список
                listFree(root, root);
                root=NULL;
                break;
            case 7://выйти из программы
                printf("Программа завершена\n");
                return 0;
                break;
            default:
                printf("Повторите ввод\n");
                break;
        }
    }
}