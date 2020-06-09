#include <stdio.h>
#include "../data.h"
#include <malloc.h>
#include "../re_builder/re_builder.h"



void scholarship_female_students(select_type *tmp)
{
    int count=0;
    do{
        if(tmp->sex_stud=='F' && tmp->mks.off.this_la==la_yes && tmp->mks.off.this_el==el_yes && tmp->mks.off.this_lab==lab_yes && tmp->mks.ez.ma>3 && tmp->mks.ez.hi>3 && tmp->mks.ez.dm>3 && tmp->mks.ez.cs>3){
            count++;
        }
        tmp=tmp->next;
    }while(tmp->next!=NULL);
    printf("There are %d female students who receive a scholarship\n", count);
}