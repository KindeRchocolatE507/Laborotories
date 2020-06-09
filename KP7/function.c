/*
 *  Умножение строки на матрицу и подсчет ненулевых элементов
 */
#include <stdio.h>
#include "data.h"

float fabs(float a){
    return (a<0)?(-a):a;
}

void function(cell *list)
{
    int height = 0;
    int width = 0;
    float max=0;
    cell *tmp = list, *sectemp = list;
    while (list) //определение высоты и ширины матрицы
    {
        if (list->index / 10 > height)
        {
            height = list->index / 10;
        }
        if (list->index % 10 > width)
        {
            width = list->index % 10;
        }
        if (list->next)
        {
            list = list->next;
        }
        else
        {
            break;
        }
    }
    while(tmp) //Поиск максимального по модулю элемента
    {
        if(fabs(tmp->value)>max){
            max=tmp->value;
        }
        if(tmp->next){
            tmp=tmp->next;
        }
        else{
            break;
        }
    }
    tmp = sectemp;
    int str;
    while(sectemp) //поиск необходимых строк 
    {
        if(fabs(sectemp->value)==max){
            str=(sectemp->index)/10;
            while(tmp) 
            {
                if((tmp->index)/10==str){
                    tmp->value/=max;
                }
                if(tmp->next){
                    tmp=tmp->next;
                }
                else{
                    break;
                }
            }
        }
        if(sectemp->next){
            sectemp=sectemp->next;
        }
        else{
            break;
        }
    }
    
}
