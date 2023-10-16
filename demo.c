void displayinfo(int acc_num,int pass){
    fopen("passbook.txt","w");
    if(file!=NULL){
        struct Customer customer;
        int x=0;
    
    while(fscanf(file,"%s,%d,%d,%f", customer.name,&customer.acc_num,&customer.pass,&customer.acc_balance)){
        if(customer.acc_num==acc_num && customer.pass==pass){
            printf("Customer name is %s",customer.name);
            printf("Customer account number is %d",customer.acc_num);
            printf("Customer account balance is %f",customer.acc_balance);
            x=1;
            break;
        }
    }
        if(!x){
            printf("Account not found");
        }
        fclose(file);
    }
        else{
            printf("Unable to read customer data");
        }
    }

void deposite(struct Customer *customer,double amount){
    if(amount>0 && amount<=50000){
        acc_balance+=amount;
        printf("Amount deposite is successful :%d", amount);
        printf("New balance is :%d", acc_balance);
        
        File *file=fopen("passbook.txt","w")
        if(file!=NULL){
            fprintf(file,"%s,%d",customer->name,customer->acc_balance);
            fclose(file);
        }
        else{
            printf("Unable to update the customer data");
        }
    }
    else{
        printf("Insufficient amount to deposite");
    }
}

void withdrawl(double amount){
    
    if(amount>0 && amount<=50000){
        if(acc_balance>=amount){
        acc_balance-=amount;
        printf("Amount withdrawl is successful %d",amount);
        printf("New balance is :%d", acc_balance);
        
        File *file=fopen("passbook.txt","w");
        if(file!=NULL){
            fprintf(file, "%s,%d",customer->name,customer->acc_balance);
        }
        else{
            printf("Unable to update the customer data");
        }
        }
        else{
            printf("Insufficient amount");
        }
    }
    else{
        printf("Insufficient amount to withdrawl");
    }
}