#include<stdio.h>
#include<string.h>

char line[100];
struct Bank
{
  long cardNo;
  int pass;
  float bal1,bal2,bal3,bal4,bal5,totBal;
};
struct Bank bank;
int authenticate()
{
  FILE *file;
    long cardNo;
    int flag=0;
    file=fopen("accounts.txt","r+");
    if(file==NULL)
    { 
        printf("Error");
        return;
    }
    printf("Enter the card number\n");
    scanf("%ld",&cardNo);
    char *cardStr = (char)cardNo;
    while(fgets(line,100,file)!=NULL)
    {
      char *token=strtok(line,"||");
      if(token!=NULL){
        long card;
        char pass[6];
      if (sscanf(token, "%ld", &card) == 1)
      {
        if(card==cardNo)
        {
          bank.cardNo=card;
            flag=1;
        printf("Enter the Password\n");
        scanf("%s",pass);
        char ch;
        int count =0;
        char* passW=strtok(NULL,"||");
        int epass,opass;
        sscanf(pass, "%d", &epass);
        sscanf(passW, "%d", &opass);
        if(epass==opass)
        {
          bank.pass=epass;
          printf("Authenticated\n");
          fclose(file);
          return 1;
        }
        else
        {
           printf("Invalid password......\n");
           fclose(file);
          return 0;
          
        }
        break;
        }
      }
    }
}
if(flag!=1){
 printf("Account doesnot exist!\n");
return 0;}
else{ 
 
  return 1;}
}
void depositMoney()
{
     float bal1,bal2,bal3,bal4,bal5,totBal,depo;
     FILE *read,*write;
     write=fopen("temp.txt","w");
     read=fopen("accounts.txt","r");
     int lineUpdated=0;
     if(authenticate())
     {
      char newline[100],line2[100];
      while (fgets(line, 100, read) != NULL)
      { 
        strcpy(line2,line);
        long card;
        char *token = strtok(line, "||");
        char *pass=strtok(NULL,"||");
        if((sscanf(token, "%ld", &card) == 1)&&card==bank.cardNo)
        {
          char* cBal1=strtok(NULL,"||");
          char* cBal2=strtok(NULL,"||");
          char* cBal3=strtok(NULL,"||");
          char* cBal4=strtok(NULL,"||");
          char* cBal5=strtok(NULL,"||");
          char* cTotBal=strtok(NULL,"||");
          sscanf(cBal1, "%f",&bank.bal1 );
          sscanf(cBal2, "%f",&bank.bal2 );
          sscanf(cBal3, "%f",&bank.bal3 );
           sscanf(cBal4, "%f",&bank.bal4 );
          sscanf(cBal5, "%f",&bank.bal5 );
          sscanf(cTotBal, "%f",&bank.totBal );
          printf("Enter the amount to be deposited\n");
          scanf("%f",&depo);
          bank.totBal+=depo;
          bank.bal1=bank.bal2;
          bank.bal2=bank.bal3;
          bank.bal3=bank.bal4;
          bank.bal4=bank.bal5;
          bank.bal5=depo;
          printf("Balance is:%f",bank.totBal);
          sprintf(newline,"%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||%-8f||%-8f\n",bank.cardNo,bank.pass,bank.bal1,bank.bal2,bank.bal3,bank.bal4,bank.bal5,bank.totBal);
          fprintf(write,"%s",newline);
          lineUpdated=1;
          
        }
        else{
          fprintf(write,"%s",line2);
        }
      }
      fclose(read);
      fclose(write);
     }
     if(lineUpdated)
     {
       remove("accounts.txt");
       rename("temp.txt","accounts.txt");
     }
     else{
      printf("Account not found\n");
     }
}
void withDrawal()
{
  float money;
   FILE *read,*write;
   int lineUpdated;
  if(authenticate())
  {
    char newline[100],line2[100];
      while (fgets(line, 100, read) != NULL)
      { 
        strcpy(line2,line);
        long card;
        char *token = strtok(line, "||");
        char *pass=strtok(NULL,"||");
        if((sscanf(token, "%ld", &card) == 1)&&card==bank.cardNo)
        {
          char* cBal1=strtok(NULL,"||");
          char* cBal2=strtok(NULL,"||");
          char* cBal3=strtok(NULL,"||");
          char* cBal4=strtok(NULL,"||");
          char* cBal5=strtok(NULL,"||");
          char* cTotBal=strtok(NULL,"||");
          sscanf(cBal1, "%f",&bank.bal1 );
          sscanf(cBal2, "%f",&bank.bal2 );
          sscanf(cBal3, "%f",&bank.bal3 );
           sscanf(cBal4, "%f",&bank.bal4 );
          sscanf(cBal5, "%f",&bank.bal5 );
          sscanf(cTotBal, "%f",&bank.totBal );
          
          printf("Enter the amount to be withdrawn\n");
          scanf("%f",&money);
          if(money<bank.totBal-500)
          {
            printf("Insufficient balance\n");
            return;
          }
          bank.totBal-=money;
          bank.bal1=bank.bal2;
          bank.bal2=bank.bal3;
          bank.bal3=bank.bal4;
          bank.bal4=bank.bal5;
          bank.bal5=money;
          printf("Balance is:%f",bank.totBal);
          sprintf(newline,"%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||%-8f||%-8f\n",bank.cardNo,bank.pass,bank.bal1,bank.bal2,bank.bal3,bank.bal4,bank.bal5,bank.totBal);
          fprintf(write,"%s",newline);
          lineUpdated=1;
        }
         else{
          fprintf(write,"%s",line2);
        }
      }
      fclose(read);
      fclose(write);
     }
     if(lineUpdated)
     {
       remove("accounts.txt");
       rename("temp.txt","accounts.txt");
     }
     else{
      printf("Account not found\n");
     }
}
      
 
int main()
{ 
  int choice;
  printf("<Welcome to SDM Bank of India>\n");
  while(1)
  {
    printf("Enter the choice\n1-Deposit money 2-Withdraw money 0-Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:depositMoney();
          printf("\n\n\nThank you for Banking with us..\n");
          break;
    case 2:withDrawal();
           printf("\n\n\nThank you for Banking with us..\n");
           break;
    case 0:return 0;
    }
  }
   return 0;
}