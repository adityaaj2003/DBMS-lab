#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct bank
{
    char name[30];
    long long acNo;
    long cardNo;
    int passWord;
    float balance;
};
FILE* adminFile,*user,*read;
void createAccount()
{
    struct bank Bank;
    char line[1000];
    char line2[200];
    double bal1=0,bal2=0,bal3=0,bal4=0;
    long long upper=1000000000000-1,lower=100000000000;
    user =fopen("accounts.txt","a");
    adminFile = fopen("adminFile.txt","a");
    printf("Enter the name\n");
    scanf("%s",Bank.name);
    printf("Enter the amount to be added\n");
    scanf("%f",&Bank.balance);
    srand(time(NULL));
    Bank.acNo=(rand()%(upper-lower+1)+lower);
    Bank.cardNo=(rand()%(9900000000-1000000000+1)+1000000000);
    Bank.passWord=(rand()%(9900-1000+1)+1000);
    sprintf(line,"%-20s||%-14lld||%-10ld||%-6d||%-8f||active\n",Bank.name,Bank.acNo,Bank.cardNo,Bank.passWord,Bank.balance);
    sprintf(line2,"%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||%-8f||%-8f\n",Bank.cardNo,Bank.passWord,0.0,0.0,0.0,0.0,Bank.balance,Bank.balance);
    fwrite(line,1,strlen(line),adminFile);
    fwrite(line2,1,strlen(line2),user);
     fclose(adminFile);
     fclose(user);
    
}
void viewDetails()
{
  
    read = fopen("adminFile.txt","r");
    printf("Account details are\n");
    char line[100];
    while(fgets(line,100,read)!=NULL)
    {
      printf("%s\n",line);
    }
    fclose(read);
}
void main()
{
   int choice;
   while(1)
   {
    printf("Emter the choice\n1-Create account 2-View accounts 0-Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1:createAccount();
	   break;
     case 2:viewDetails();
	   break;
     case 0:
     fclose(adminFile);
     fclose(user);
     return;
     default:printf("Invalid choice\n");
	    break;
    }
  }
}