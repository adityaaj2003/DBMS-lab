#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char line[100];
struct Bank
{
  int status;
  long cardNo;
  int pass, attempts;
  float bal1, bal2, bal3, bal4, bal5, totBal, atmBal,dailyLimit;
};
struct Bank bank;
int authenticate()
{
  FILE *read, *write;
  write = fopen("temp.txt", "w");
  read = fopen("accounts.txt", "r");
  char newline[1024], line2[1024], line[1024];
  long cardNo;
  int flag = 0;
  printf("Enter the card number\n");
  scanf("%ld", &cardNo);
  while (fgets(line, 1024, read) != NULL)
  {
    strcpy(line2, line);
    char *status = strtok(line, "||");
    char *token = strtok(NULL, "||");
    char pass[6];
    long oCard;
    sscanf(token, "%ld", &oCard);
    int opass;
    if (oCard == cardNo)
    {
      bank.cardNo = oCard;
      char *passW = strtok(NULL, "||");
      if (strcmp(status, "active") == 0)
      {
        bank.attempts = 0;
      }
      else
      {
        printf("Account has been blocked\n");
        fclose(read);
        fclose(write);
        return 0;
      }
      int epass, opass;
      while (bank.attempts < 4)
      {
        printf("Enter the Password\n");
        scanf("%d", &epass);
        sscanf(passW, "%d", &opass);
        if (epass == opass)
        {
          bank.pass = epass;
          printf("Authenticated\n");
          bank.dailyLimit=20000;
          flag = 1;
          fprintf(write, "%s", line2);
          break;
        }
        else
        {
          bank.attempts++;
          printf("Invalid password......\n");
        }
      }
    }
    else
    {
      fprintf(write, "%s", line2);
      continue;
    }
    if (bank.attempts >= 3)
    {
      fprintf(write, "in");
      fprintf(write, "%s", line2);
      printf("Your card has been blocked\n");
    }
  }
  fclose(read);
  fclose(write);
  remove("accounts.txt");
  rename("temp.txt", "accounts.txt");
  if (flag == 1)
  {
    return 1;
  }
  else
  {
    printf("Account not found\n");
    return 0;
  }
}
void depositMoney()
{
  float bal1, bal2, bal3, bal4, bal5, totBal, depo;
  FILE *read, *write, *atmWrite, *atmRead;
  write = fopen("temp.txt", "w");
  read = fopen("accounts.txt", "r");

  atmRead = fopen("atmBalance.txt", "r");
  char Line[50];
  fgets(Line, 50, atmRead);
  sscanf(Line, "%f", &bank.atmBal);
  fclose(atmRead);
  int lineUpdated = 0;
  char newline[1024], line2[1024];
  while (fgets(line, 1024, read) != NULL)
  {
    strcpy(line2, line);
    long card;
    char *status1 = strtok(line, "||");
    char *token = strtok(NULL, "||");
    char *pass = strtok(NULL, "||");
    if ((sscanf(token, "%ld", &card) == 1) && card == bank.cardNo)
    {
      char *cBal1 = strtok(NULL, "||");
      char *cBal2 = strtok(NULL, "||");
      char *cBal3 = strtok(NULL, "||");
      char *cBal4 = strtok(NULL, "||");
      char *cBal5 = strtok(NULL, "||");
      char *cTotBal = strtok(NULL, "||");
      sscanf(cBal1, "%f", &bank.bal1);
      sscanf(cBal2, "%f", &bank.bal2);
      sscanf(cBal3, "%f", &bank.bal3);
      sscanf(cBal4, "%f", &bank.bal4);
      sscanf(cBal5, "%f", &bank.bal5);
      sscanf(cTotBal, "%f", &bank.totBal);
      printf("Enter the amount to be deposited\n");
      scanf("%f", &depo);
      if (depo > 50000)
      {
        printf("Limit exceeded");
        fclose(read);
        fclose(write);
        exit(0);
      }
      bank.totBal += depo;
      bank.bal1 = bank.bal2;
      bank.bal2 = bank.bal3;
      bank.bal3 = bank.bal4;
      bank.bal4 = bank.bal5;
      bank.bal5 = depo;
      lineUpdated = 1;
      printf("Balance is:%f", bank.totBal);
      sprintf(newline, "active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||+%-8f||%-8f\n", bank.cardNo, bank.pass, bank.bal1, bank.bal2, bank.bal3, bank.bal4, bank.bal5, bank.totBal);
      fprintf(write, "%s", newline);
      bank.atmBal += depo;
      sprintf(Line, "%f\n", bank.atmBal);
      atmWrite = fopen("atmBalance.txt", "w");
      fprintf(atmWrite, Line);
      fclose(atmWrite);
    }
    else
    {
      fprintf(write, "%s", line2);
    }
  }
  fclose(read);
  fclose(write);

  if (lineUpdated)
  {
    if (remove("accounts.txt") != 0)
      perror("Unable to remove the file\n");

    if (rename("temp.txt", "accounts.txt") != 0)
      perror("Unable to rename the file\n");
  }
  else
  {
    printf("Account not found\n");
  }
}
void withDrawal()
{
  float money;
  FILE *read, *write;
  write = fopen("temp.txt", "w");
  read = fopen("accounts.txt", "r");
  FILE *atmRead;
  atmRead = fopen("atmBalance.txt", "r");
  char Line[50];
  fgets(Line, 50, atmRead);
  sscanf(Line, "%f", &bank.atmBal);
  fclose(atmRead);
  FILE *atmWrite;
  
  int lineUpdated = 0;

  char newline[1024], line2[1024];
  while (fgets(line, 1024, read) != NULL)
  {
    strcpy(line2, line);
    long card;
    char *status1 = strtok(line, "||");
    char *token = strtok(NULL, "||");
    char *pass = strtok(NULL, "||");
    if ((sscanf(token, "%ld", &card) == 1) && card == bank.cardNo)
    {
      char *cBal1 = strtok(NULL, "||");
      char *cBal2 = strtok(NULL, "||");
      char *cBal3 = strtok(NULL, "||");
      char *cBal4 = strtok(NULL, "||");
      char *cBal5 = strtok(NULL, "||");
      char *cTotBal = strtok(NULL, "||");
      sscanf(cBal1, "%f", &bank.bal1);
      sscanf(cBal2, "%f", &bank.bal2);
      sscanf(cBal3, "%f", &bank.bal3);
      sscanf(cBal4, "%f", &bank.bal4);
      sscanf(cBal5, "%f", &bank.bal5);
      sscanf(cTotBal, "%f", &bank.totBal);

      printf("Enter the amount to be withdrawn\n");
      scanf("%f", &money);

      if (money > (bank.totBal + 500))
      {
        printf("Insufficient balance\n");
        
        fclose(read);
        fclose(write);
        return;
      }
      if (money > 10000)
      {
        printf("Exceeding the maximum limit\n");
        
        fclose(read);
        fclose(write);
        return;
      }
      if (money > bank.atmBal)
      {
        printf("ATM out of money\n");
        
         fclose(read);
        fclose(write);
       return;
      }
      
      bank.dailyLimit-=money;
      if(bank.dailyLimit<0){
         printf("You have crossed the daily limit\n");
        
         fclose(read);
        fclose(write);
        return;
      }
      bank.totBal -= money;
      bank.bal1 = bank.bal2;
      bank.bal2 = bank.bal3;
      bank.bal3 = bank.bal4;
      bank.bal4 = bank.bal5;
      bank.bal5 = money;

      printf("Balance is:%f", bank.totBal);
      sprintf(newline, "active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||-%-8f||%-8f\n", bank.cardNo, bank.pass, bank.bal1, bank.bal2, bank.bal3, bank.bal4, bank.bal5, bank.totBal);
      fprintf(write, "%s", newline);
      lineUpdated = 1;
      bank.atmBal -= money;
      atmWrite = fopen("atmBalance.txt", "w");
      sprintf(Line, "%f\n", bank.atmBal);

      fprintf(atmWrite,Line);
    }
    else
    {
      fprintf(write, "%s", line2);
    }
  }
  fclose(atmWrite);
  fclose(read);
  fclose(write);
  
  if (lineUpdated)
  {
    if (remove("accounts.txt") != 0)
      perror("Unable to remove the file\n");

    if (rename("temp.txt", "accounts.txt") != 0)
      perror("Unable to rename the file\n");
  }
  else
  {
    printf("Account not found\n");
  }
}
void miniStatement()
{
  float money;
  FILE *read;
  read = fopen("accounts.txt", "r");
  int lineUpdated = 0;
  char newline[1024], line2[1024];
  while (fgets(line, 1024, read) != NULL)
  {
    strcpy(line2, line);
    long card;
    char *status1 = strtok(line, "||");
    char *token = strtok(NULL, "||");
    char *pass = strtok(NULL, "||");
    if ((sscanf(token, "%ld", &card) == 1) && card == bank.cardNo)
    {
      char *cBal1 = strtok(NULL, "||");
      char *cBal2 = strtok(NULL, "||");
      char *cBal3 = strtok(NULL, "||");
      char *cBal4 = strtok(NULL, "||");
      char *cBal5 = strtok(NULL, "||");
      char *cTotBal = strtok(NULL, "||");
      sscanf(cBal1, "%f", &bank.bal1);
      sscanf(cBal2, "%f", &bank.bal2);
      sscanf(cBal3, "%f", &bank.bal3);
      sscanf(cBal4, "%f", &bank.bal4);
      sscanf(cBal5, "%f", &bank.bal5);
      sscanf(cTotBal, "%f", &bank.totBal);
      printf("Mini statement\nCredit/Debit||Amount\n");
      if (bank.bal1 >= 0)
        printf("Credit  ||  %f \n", bank.bal1);
      else
        printf("Debit  ||  %f \n", bank.bal1);
      if (bank.bal2 >= 0)
        printf("Credit  ||  %f \n", bank.bal2);
      else
        printf("Debit  ||  %f \n", bank.bal2);
      if (bank.bal3 >= 0)
        printf("Credit  ||  %f \n", bank.bal3);
      else
        printf("Debit  ||  %f \n", bank.bal3);
      if (bank.bal4 >= 0)
        printf("Credit  ||  %f \n", bank.bal4);
      else
        printf("Debit  ||  %f \n", bank.bal4);
      if (bank.bal5 >= 0)
        printf("Credit  ||  %f \n", bank.bal5);
      else
        printf("Debit  ||  %f  \n", bank.bal5);
      printf("The balance is:%f\n", bank.totBal);
    }
  }
  fclose(read);
}

void balanceEnquiry()
{
  float money;
  FILE *read;
  read = fopen("accounts.txt", "r");
  char newline[1024], line2[1024];
  while (fgets(line, 1024, read) != NULL)
  {
    strcpy(line2, line);
    long card;
    char *status1 = strtok(line, "||");
    char *token = strtok(NULL, "||");
    char *pass = strtok(NULL, "||");
    if ((sscanf(token, "%ld", &card) == 1) && card == bank.cardNo)
    {
      char *cBal1 = strtok(NULL, "||");
      char *cBal2 = strtok(NULL, "||");
      char *cBal3 = strtok(NULL, "||");
      char *cBal4 = strtok(NULL, "||");
      char *cBal5 = strtok(NULL, "||");
      char *cTotBal = strtok(NULL, "||");
      sscanf(cTotBal, "%f", &bank.totBal);
      printf("The balance is:%f\n", bank.totBal);
    }
  }
  fclose(read);
}

void transferMoney() {
    FILE *read, *write,*recipient;
    write = fopen("temp.txt", "w");
    read = fopen("accounts.txt", "r");
     recipient = fopen("accounts.txt", "r");
    int lineUpdated = 0;
    char newline[1024], line2[1024];

    long recipientCardNo;
    float transferAmount;

    printf("Enter the recipient's card number: ");
    scanf("%ld", &recipientCardNo);

    while (fgets(line, 1024, read) != NULL) {
        strcpy(line2, line);
        long card;
        char *status1 = strtok(line, "||");
        char *token = strtok(NULL, "||");
        char *pass = strtok(NULL, "||");

        if ((sscanf(token, "%ld", &card) == 1) && card == bank.cardNo) {
            char *cBal1 = strtok(NULL, "||");
            char *cBal2 = strtok(NULL, "||");
            char *cBal3 = strtok(NULL, "||");
            char *cBal4 = strtok(NULL, "||");
            char *cBal5 = strtok(NULL, "||");
            char *cTotBal = strtok(NULL, "||");

            sscanf(cBal1, "%f", &bank.bal1);
            sscanf(cBal2, "%f", &bank.bal2);
            sscanf(cBal3, "%f", &bank.bal3);
            sscanf(cBal4, "%f", &bank.bal4);
            sscanf(cBal5, "%f", &bank.bal5);
            sscanf(cTotBal, "%f", &bank.totBal);

            printf("Enter the amount to transfer: ");
            scanf("%f", &transferAmount);

            if (transferAmount > bank.totBal) {
                printf("Insufficient balance for the transfer.\n");
                return;
            }

            // Deduct the transfer amount from the sender's account
            bank.totBal -= transferAmount;

            // Update the balances history of the sender
            bank.bal1 = bank.bal2;
            bank.bal2 = bank.bal3;
            bank.bal3 = bank.bal4;
            bank.bal4 = bank.bal5;
            bank.bal5 = -transferAmount;

            while (fgets(line, 1024, recipient) != NULL) {
                long recipientCard;
                char *recipientStatus = strtok(line, "||");
                char *recipientToken = strtok(NULL, "||");
                sscanf(recipientToken, "%ld", &recipientCard);
                if (recipientCard == recipientCardNo) {
                  char *recipientpas = strtok(NULL, "||");
                    char *recipientBal1 = strtok(NULL, "||");
                    char *recipientBal2 = strtok(NULL, "||");
                    char *recipientBal3 = strtok(NULL, "||");
                    char *recipientBal4 = strtok(NULL, "||");
                    char *recipientBal5 = strtok(NULL, "||");
                    char *recipientTotBal = strtok(NULL, "||");

                    float recipientPassW,recipientBal1Val, recipientBal2Val, recipientBal3Val, recipientBal4Val, recipientBal5Val, recipientTotBalVal;
                    sscanf(recipientBal1, "%f", &recipientPassW);
                    sscanf(recipientBal1, "%f", &recipientBal1Val);
                    sscanf(recipientBal2, "%f", &recipientBal2Val);
                    sscanf(recipientBal3, "%f", &recipientBal3Val);
                    sscanf(recipientBal4, "%f", &recipientBal4Val);
                    sscanf(recipientBal5, "%f", &recipientBal5Val);
                    sscanf(recipientTotBal, "%f", &recipientTotBalVal);

                    // Update the recipient's balance
                    recipientTotBalVal += transferAmount;
                    recipientBal1Val = recipientBal2Val;
                    recipientBal2Val = recipientBal3Val;
                    recipientBal3Val = recipientBal4Val;
                    recipientBal4Val = recipientBal5Val;
                    recipientBal5Val = transferAmount;

                    // Construct updated lines for both sender and recipient
                    sprintf(newline, "active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||-%-8f||%-8f\n",
                            bank.cardNo, bank.pass, bank.bal1, bank.bal2, bank.bal3, bank.bal4, bank.bal5, bank.totBal);

                    char recipientNewline[1024];
                    sprintf(recipientNewline, "active||%-10ld||%-6d||%-8f||%-8f||%-8f||%-8f||+%-8f||%-8f\n",
                            recipientCard,recipientPassW , recipientBal1Val, recipientBal2Val, recipientBal3Val, recipientBal4Val, recipientBal5Val, recipientTotBalVal);

                    // Write the updated lines to the temp file
                    fprintf(write, "%s", newline);
                    fprintf(write, "%s", recipientNewline);
                    lineUpdated = 1;
                } else {
                    fprintf(write, "%s", line);
                    continue;
                }
            }
        } else {
            fprintf(write, "%s", line2);
        }
    }
    fclose(recipient);
    fclose(read);
    fclose(write);

    if (lineUpdated) {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        printf("Amount transferred successfully!\n");
    } else {
        printf("Account not found\n");
    }
}
int main()
{
  int choice;
  bank.attempts = 0;
  printf("\n<---Welcome to SDM Bank of India--->\n");
  if (authenticate())
  {
    while(1){
    printf("\n\n<---Enter the choice--->\n\n1-Deposit money 2-Withdraw money 3-Mini statement 4-Balance enquiry 0-Exit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      depositMoney();
      break;
    case 2:
      withDrawal();
      break;
    case 3:
      miniStatement();
      break;
    case 4:
      balanceEnquiry();
      break;
    case 5:
    //  transferMoney();
     break;
    case 0:
      printf("\n\n..Thank you for Banking with us..\n\n<--SDM Bank of INDIA-->\n");
      return 0;
    }
    }
  }
  else
  {
    printf("\n\n\nThank you for Banking with us..\n<--SDM Bank of INDIA-->\n");
    return 0;
  }

  return 0;
}
