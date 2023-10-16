//Program for the simulation of file handling in C
#include<stdio.h>
#include<stdlib.h>
main()
{
    FILE *fpWrite;
    char word[10];
    fpWrite=fopen("demo.txt","w");
    if(fpWrite==NULL)
    {
        printf("\nUnable to open the file\n");
        exit(0);
    }
    printf("Enter the string to be written\n");
    scanf("%s",word);
    fprintf(fpWrite,word);
    fclose(fpWrite);
    FILE *fpRead;
    fpRead=fopen("demo.txt","r");
    fscanf(fpRead,%s,word);
    
}