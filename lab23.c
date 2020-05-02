#include <stdio.h>
#include <stdlib.h>
#define lt left
#define rt right
#define pt parent
typedef struct treeComp {
    int key;
    struct treeComp *lt;
    struct treeComp *rt;
} comp;
void createTree(comp **root){
    int key;
    printf("Введите ключ корня ");
    scanf("%d", &key);
    comp *temp = malloc(sizeof(temp));
    temp -> key = key;
    temp -> lt = NULL;
    temp -> rt = NULL;
    *root = temp;
}
void addTree(comp *root, int key){
    if(key < root -> key){
        if(root -> lt == NULL){
            comp *temp = malloc(sizeof(temp));
            temp -> key = key;
            temp -> lt = NULL;
            temp -> rt = NULL;
            root -> lt = temp;
        }else{
            addTree( root -> lt, key);
        }        
    }else{
        if(root -> rt == NULL){
            comp *temp = malloc(sizeof(temp));
            temp -> key = key;
            temp -> lt = NULL;
            temp -> rt = NULL;
            root -> rt = temp;
        }else{
            addTree(root -> rt, key);
        }
    }
}
int lin(comp *root){
    if(root -> lt != NULL && root -> rt != NULL) return 0;
    if(root -> lt != NULL) return lin(root->lt);
    if(root -> rt != NULL) return lin(root->rt);
    return 1;
}
void printTree(comp *root){
    if (root -> lt != NULL){
        printTree(root->lt);
    }
    printf( "%d", root -> key );    
    if (root -> rt != NULL){
        printTree(root->rt);
    }    
}
void deleteTree(comp *root){
    if(root -> lt != NULL){    
        deleteTree(root -> lt);
        root -> lt = NULL;
    }
    if(root -> rt != NULL){
        deleteTree(root -> rt);
        root -> rt = NULL;
    }
    free(root);
}
int main(){
    int choise=1, c, mono=1, i, depth;
    int *wide;
    comp *root;
    while (choise){
        printf("Пожалуйста, выберите действие:\n1. Создать дерево\n2. Добавить к дереву элемент\n3. Текстовый вывод дерева\n4. Проверить, не является ли списком\n9. Удалить дерево\n0. Завершить программу\n");
        scanf("%d", &choise);
        switch (choise){
        case 0:
            printf("Программа завершена\n");
            break;
        case 1:
            createTree(&root);
            depth=1;
            break;
        case 2:
            printf("Введите ключ элемента ");
            scanf("%d", &c);
            addTree(root, c);
            break;
        case 3:
            printTree(root);
            printf("\n");
            break;
        case 4:
            if(lin(root)){
                printf("Дерево является линейным списком вершин\n");
            }else{
                printf("Дерево не является линейным списком вершин\n");
            }
            break;
        case 5:
            deleteTree(root);
            break;
        default:
            printf("Введите корректное значение\n");
            break;
        }
    }
}