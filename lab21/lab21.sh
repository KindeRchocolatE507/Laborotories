#!/bin/bash
nextSymbol(){
    aaa=$1
if [ "`echo $aaa | sed 's/[[:digit:]]//'`" == "" ]
then
    let "aaa = ( aaa + 1 ) % 10"
    echo $aaa
    return 0
fi
if [ "`echo $aaa | sed 's/[a-z]//'`" == "" ]
then
    if [ "$aaa" == "z" ]
    then
    echo "a"
    else
        symbolArray=(a b c d e f g h i j k l m n o p q r s t u v w x y z)
        for ((i=0;i<26;i++))
        do
            if [ "$aaa" = "${symbolArray[i]}" ]
            then
                echo ${symbolArray[i+1]}
                break
            fi
        done
    fi
fi
if [ "`echo $aaa | sed 's/[A-Z]//'`" == "" ]
then
    if [ "$aaa" == "Z" ]
    then 
    echo "A"
    return 0
    else
        symbolArray=(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
        for ((i=0;i<26;i++))
        do
            if [ "$aaa" = "${symbolArray[i]}" ]
            then
                echo ${symbolArray[i+1]}
                break
            fi
        done
    fi
fi
}
numberOfCopies=$1
fileName=$2
startSymbol=$3
if [ "$1" == "0" ]
then
echo "Готово"
exit 1
fi
if [ "`echo $numberOfCopies | sed 's/[[:digit:]]//'`" != "" ]
then
echo "неверное кол-во"
exit 1
fi
if [ -z $2 ]
then
echo "Укажите входной файл"
exit 1
fi
if [ -z $3 ]
then
echo "укажите символ-счетчик для создания копий"
exit 1
fi
if [ "`echo $startSymbol | sed 's/[[:alnum:]]//'`" != "" ]
then
echo "Неверный сивол-счетчик"
exit 1
fi
cp -x -p $fileName $fileName$startSymbol
fileName=$fileName$startSymbol
startSymbol=$(nextSymbol "$startSymbol")
let "numberOfCopies = numberOfCopies - 1"
while [ $numberOfCopies -gt 0 ]
do
cp -x -p $fileName $fileName$startSymbol
fileName=$fileName$startSymbol
startSymbol=$(nextSymbol "$startSymbol")
let "numberOfCopies = numberOfCopies - 1"
done