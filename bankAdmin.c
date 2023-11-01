#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>

struct Bank
{
  char name[30];
  long long acNo;
  long cardNo;
  int passWord;
  float bal1,bal2,bal3,bal4,bal5,totBal,atmBal;
};
struct Bank bank;
FILE* adminFile,*user;
void createAccount()
{
   
    char line[1000];
    char line2[200];
    double bal1=0,bal2=0,bal3=0,bal4=0;
    long long upper=1000000000000-1,lower=100000000000;
    user =fopen("accounts.txt","a");
    adminFile = fopen("adminFile.txt","a");
    printf("Enter the name\n");
    scanf("%s",bank.name);
    printf("Enter the amount to be added\n");
    scanf("%f",&bank.totBal);
    srand(time(NULL));
    bank.acNo=(rand()%(upper-lower+1)+lower);
    bank.cardNo=(rand()%(9900000000-1000000000+1)+1000000000);
    bank.passWord=(rand()%(9900-1000+1)+1000);
    sprintf(line,"%-20s||%-14lld||%-10ld||%-6d\n",bank.name,bank.acNo,bank.cardNo,bank.passWord);
    sprintf(line2,"active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||+%-8f||+%-8f\n",bank.cardNo,bank.passWord,0.0,0.0,0.0,0.0,bank.totBal,bank.totBal);
    fwrite(line,1,strlen(line),adminFile);
    fwrite(line2,1,strlen(line2),user);
     fclose(adminFile);
     fclose(user);
    
}
void viewDetails()
{
   FILE *read;
    read = fopen("adminFile.txt","r");
    printf("Account details are\n");
    char line[100];
    while(fgets(line,100,read)!=NULL)
    {
      printf("%s\n",line);
    }
  fclose(read);
}
void unBlock()
{
   float bal1,bal2,bal3,bal4,bal5,totBal;
     FILE *read,*write,*atm;
     write=fopen("temp.txt","w");
     read=fopen("accounts.txt","r");
     long card;
     printf("Enter the card number to be unblocked\n");
     scanf("%ld",&card);
      char newline[100],line2[100],line[100];
      while (fgets(line, 100, read) != NULL)
      { 
        strcpy(line2,line);
        char *status1=strtok(line,"||");
        char *token = strtok(NULL,"||");
        char *pass=strtok(NULL,"||");
        long oCard;
        int passW;
        sscanf(token, "%ld", &oCard);
        sscanf(pass, "%d", &passW);
        if(card==oCard)
        {
          printf("%ld",oCard);
          bank.cardNo=oCard;
          bank.passWord=passW;
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
          sprintf(newline,"active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||+%-8f||%-8f\n",bank.cardNo,bank.passWord,bank.bal1,bank.bal2,bank.bal3,bank.bal4,bank.bal5,bank.totBal);
          fprintf(write,"%s",newline);
         }
         else
         {
          fprintf(write,"%s",line2);
         }
       }
       printf("!!!Congragulations!!!\n");
        fclose(write);
        fclose(read);
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
}
void viewBalance()
{
  FILE *atm;
  atm=fopen("atmBalance.txt","r");
  char line[50];
  fgets(line,50,atm);
  sscanf(line, "%f",&bank.atmBal);
  printf("Balance in ATM is %f\n",bank.atmBal);
  fclose(atm);
}
void addMoney()
{
  FILE *atm;
  atm=fopen("atmBalance.txt","w");
  char newLine[100];
  float money;
  printf("Enter the money to be added\n");
  scanf("%f",&money);
  bank.atmBal+=money;
  sprintf(newLine,"%f\n",bank.atmBal);
  fprintf(atm,newLine);
  fclose(atm);
}
void main()
{
   int choice;
   while(1)
   {
    printf("Emter the choice\n1-Create account 2-View accounts 3-Unblock 4-View balance in ATM 5-Add money to ATM 0-Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1:createAccount();
	   break;
     case 2:viewDetails();
	   break;
     case 3:unBlock();
            break;
     case 4:viewBalance();
            break;
     case 5:addMoney();
            break;
     case 0:
     return;
     default:printf("Invalid choice\n");
	    break;
    }
  }
}