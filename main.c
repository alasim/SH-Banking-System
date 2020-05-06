#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Account account;
struct Account
{
    int acNo;
    int pin;
    char name[30];
    int balance;
    char message[200];
    account* link;
};
account* head;
int Menu()
{
    system("cls");
    system("color f0");
    int option;
    printf("\n\t\t******************** Welcome to SH Banking ********************");
    printf("\n\n\n\t\t\t============= Welcome Manu ==================");
    printf("\n\n\t\t\t[1] : Create Account");
    printf("\n\t\t\t[2] : Login Account");
    printf("\n\t\t\t[3] : Admin Login");
    printf("\n\t\t\t[4] : Exit");
    printf("\n\n\t\t\t============================================");
    printf("\n\t\t\t>> Enter Your Choice(1-4): ");
    scanf("%d",&option);


    return option;
}

void init(int acNo,int pin,int balance,char name[],char mess[])
{

    account* newAccount = (account*)malloc(sizeof(account));
    newAccount->acNo = acNo;
    newAccount->pin = pin;
    newAccount->balance = balance;
    strcpy(newAccount->name,name);
    strcpy(newAccount->message,mess);
//    printf("\n\t\t\t-------- Account Details ----------");
//    printf("\n\t\t\tAccount number: %d",newAccount->acNo);
//    printf("\n\t\t\tAccount pin: %d",newAccount->pin);
//    printf("\n\t\t\tAccount name: %s",newAccount->name);
//    printf("\n\t\t\tFirst deposit: %d",newAccount->balance);
//    printf("\n\t\t\t-------------okay!-----------------");
//    printf("\n\n\t\t\ty/n: ");
//    fflush(stdin);
//    char y;
//    scanf("%c",&y);
//    if(y!='y')
//        CreateAccount();
    newAccount->link=head;
    head = newAccount;
}

void reinit(){// rewrite file whenever node have got any change.

    FILE *fp,*fp_root;
    fp_root = fopen("Accounts.txt","wb");
    if(fp_root==NULL)
    {
        printf("->>> Accounts.txt couldn't open.");
        exit(1);
    }
    account* tempt = head;
    while(tempt!=NULL)
    {
        account a;
        a.acNo = tempt->acNo;
        a.pin = tempt->pin;
        a.balance = tempt->balance;
        strcpy(a.name,tempt->name);
        strcpy(a.message,tempt->message);
        a.link = tempt->link;
        fwrite(&a, sizeof(a), 1, fp_root);
        tempt=tempt->link;
        //system("pause");
    }
    fclose(fp_root);
}
int exist(int acNo)
{
    account* tempt = head;
    while(tempt!=NULL)
    {
        if(tempt->acNo==acNo)
            return 1;
        tempt = tempt->link;
    }
    return 0;
}
void CreateAccount()
{
start:
    ;
    system("color f0");
    system("cls");
    printf("\n\t\t\t************* Create account *************");
    //startAgain:
    int success=0;
    account* newAccount = (account*)malloc(sizeof(account));
    printf("\n\n\t\t\t>> Set an account number: ");
    scanf("%d",&newAccount->acNo);
    if(exist(newAccount->acNo))
    {
        system("color cf");
        printf("\n\n\t\t->>> Sorry, This(%d) account number already exist",newAccount->acNo);
        printf("\n\t\t     in our system. Try another new.");
        printf("\n\n");
        system("pause");
        goto start;
    }
    printf("\t\t\t>> Set your pin: ");
    scanf("%d",&newAccount->pin);
    printf("\t\t\t>> Type your name: ");
    fflush(stdin);
    gets(newAccount->name);
    fflush(stdin);
    printf("\t\t\t>> Enter your first deposit amount, TK: ");
    scanf("%d",&newAccount->balance);
    //strcpy(newAccount->message,"Welcome to SH Banking system.");
    sprintf(newAccount->message,">> First deposited %d TK.",newAccount->balance);
    //newAccount->message="Hello";

    printf("\n\t\t\t-------- Account Details ----------");
    printf("\n\t\t\t%-25s %-15d","Account number:",newAccount->acNo);
    printf("\n\t\t\t%-25s %-15d","Account pin:",newAccount->pin);
    printf("\n\t\t\t%-25s %-15s","Account name:",newAccount->name);
    printf("\n\t\t\t%-25s %-15d","First deposit amount, TK:",newAccount->balance);
    printf("\n\n\t\t\t-------------------- Conferm? y/n: ");
    fflush(stdin);
    char y;
    scanf("%c",&y);
    if(y!='y')
        CreateAccount();
    newAccount->link=head;
    head = newAccount;

    //all account rewrite to Accounts.txt file with new node
    reinit();
//    FILE *fp,*fp_root;
//    fp_root = fopen("Accounts.txt","wb");
//    if(fp_root==NULL)
//    {
//        printf("->>> Accounts.txt couldn't open.");
//        exit(1);
//    }
//    account* tempt = head;
//    while(tempt!=NULL)
//    {
//        account a;
//        a.acNo = tempt->acNo;
//        a.pin = tempt->pin;
//        a.balance = tempt->balance;
//        strcpy(a.name,tempt->name);
//        strcpy(a.message,tempt->message);
//        a.link = tempt->link;
//        fwrite(&a, sizeof(a), 1, fp_root);
//        tempt=tempt->link;
//        //system("pause");
//    }
//    fclose(fp_root);
    FILE* fp;
    char filePath[20];// creating new file and save on it
    sprintf(filePath,"account_%d.txt",newAccount->acNo);
    fp = fopen(filePath,"a");
    if(fp==NULL)
    {
        printf("\n->>> Can't create new file.");
        exit(1);
    }
    fprintf(fp,"->>> First deposit %d TK added.\n",newAccount->balance);
    fclose(fp);// file closed

    system("cls");// menu after creating account successfully
    printf("\n\t\t\tAccount created successfully.\n");
    printf("\n\n\t\t\t=============== Next ==============\n");
    printf("\n\t\t\t[1] : Login your account.");
    printf("\n\t\t\t[2] : Main menu.");
    printf("\n\t\t\t====================================");
    printf("\n\t\t\t>> Enter your choice(1-2): ");
    int ans;
    fflush(stdin);
    scanf("%d",&ans);
    if(ans==1)
        LoginAcount();

}
void LoginAcount()
{
    system("cls");
    printf("\n\t\t\t************* Login details *************\n\n");
    int accountNumber,inputPin,pin;
    char* name=NULL;
    printf("\n\t\t\t>> Type your account number: ");
    scanf("%d",&accountNumber);
    account* tempt = head;
    account* userAccount;
    while(tempt!=NULL)
    {
        if(accountNumber==tempt->acNo)
        {
            name = tempt->name;
            pin = tempt->pin;
            userAccount = tempt;
        }
        tempt=tempt->link;
    }
    if(name!=NULL)
    {
        printf("\n\t\t\t\t> Welcome, %s!",name);
        printf("\n\n\t\t\t>> Type your pin to continue: ");

        scanf("%d",&inputPin);
        if(pin==inputPin)
        {
            printf("\n\t\t\tWelcome to your account, %s",name);
            intoAccount(userAccount);
        }
        else
        {
            system("color cf");
            printf("\n\t\t\t->>> Invalid pin. Try again");
            printf("\n\n");
            system("pause");
        }
    }
    else
    {
        system("color cf");
        printf("\n\t\t\t->>> %d account doesn't exist.",accountNumber);
        printf("\n\t\t\t->>> Create new account. Or try again.");
         printf("\n\n");
        system("pause");
        //Menu();
    }

}

void intoAccount(account* user)// after login successful.
{
startAgain:
    ;
    system("color 2f");
    system("cls");
    printf("\n\t\t\t************* Welcome to your account *************");
    printf("\n\n\t\t\tAccount number: %d",user->acNo);
    printf("\n\t\t\tAccount name: %s",user->name);
    printf("\n\t\t\tBalance: %d",user->balance);
    printf("\n\t\t\tLast action: %s",user->message);
    printf("\n\n\n\t\t\t=========== Options ==============\n");
    printf("\n\t\t\t[1] : Deposit");
    printf("\n\t\t\t[2] : Withdraw");
    printf("\n\t\t\t[3] : Balance transfer");
    printf("\n\t\t\t[4] : View transactions");
    printf("\n\t\t\t[5] : Logout");
    printf("\n\t\t\t==================================");
    printf("\n\t\t\t>> Enter your choice(1-4): ");
    int ans;
    int amount,acNum;
    fflush(stdin);
    scanf("%d",&ans);


    FILE *my_fp,*other_fp;// working with file!!
    char filePath[20];
    sprintf(filePath,"account_%d.txt",user->acNo);
    my_fp = fopen(filePath,"a");
    if(my_fp==NULL)
    {
        printf("\n->>> Can't create new file.");
        exit(1);
    }


    switch(ans)
    {
    case 1:
        printf("\n\t\t\t>> Enter deposit amount, TK: ");
        scanf("%d",&amount);
        printf("\n\t\t\t->>> Deposit successful.\n\t\t\t->>> Previous balance: %d TK.",user->balance);
        user->balance = user->balance + amount;
        sprintf(user->message,"Deposited %d TK.",amount);

        fprintf(my_fp,"->>> Deposited %d TK.\n",amount);// working with file
        fclose(my_fp);// file closed

        printf("\n\t\t\t->>> New balance: %d TK.",user->balance);
        reinit();
         printf("\n\n");
        system("pause");
        goto startAgain;
        break;
    case 2:
        printf("\n\t\t\t>> Enter withdraw amount, TK: ");
        scanf("%d",&amount);
        if(user->balance<amount)
        {
            printf("\n\t\t\t->>> Insufficient balance.\n");
            system("color cf");
        }
        else
        {
            user->balance= user->balance-amount;
            printf("\n\t\t\t->>> Withdrawn successful.");
            sprintf(user->message,"Withdrawn %d TK.",amount);
            fprintf(my_fp,"->>> Withdrawn %d TK.\n",amount);// working with file
            fclose(my_fp);// file closed
            printf("\n\t\t\t->>> Current Balance: %d TK.",user->balance);
            reinit();// update nodes on file
        }
        printf("\n\n");
        system("pause");
        goto startAgain;
        break;
    case 3:
        printf("\n\t\t\t>> Enter transfer account number: ");
        scanf("%d",&acNum);
        if(acNum==user->acNo)
        {
            system("color cf");
            printf("\n\t\t\t->>> You can't transfer your balance to your own account.");
            printf("\n\n");
            system("pause");
            goto startAgain;
        }

        account* tempt = head;
        char* name=NULL;
        while(tempt!=NULL)
        {
            if(acNum==tempt->acNo)
            {
                name = tempt->name;
                break;
            }
            tempt=tempt->link;
        }
        if(name)
        {
            printf("\t\t\t>> Enter the amount, TK: ");
            scanf("%d",&amount);

            if(user->balance<amount)
            {
                printf("\n\t\t\t->>> Insufficient balance.");
                system("color cf");
                printf("\n\n");
                system("pause");
                goto startAgain;
            }
            else
            {
                tempt->balance = tempt->balance + amount;
                user->balance = user->balance - amount;
                printf("\n\t\t\t->>> Transfer balance successfully to %s's account.\n\n\n",name);
                sprintf(user->message,">> Transfered balance %d TK to %s.\n",amount,tempt->name);
                fprintf(my_fp,"->>> Transfered balance %d TK to %s.\n",amount,tempt->name);// working with file
                fclose(my_fp);// file closed


                sprintf(tempt->message,">> Balance added %d TK by %s.",amount,user->name);

                sprintf(filePath,"account_%d.txt",tempt->acNo);// working with file others account
                other_fp = fopen(filePath,"a");
                if(other_fp==NULL)
                {
                    printf("\n->>> Can't create new file.");
                    exit(1);
                }
                fprintf(other_fp,"->>> Balance added %d TK by %s.",amount,user->name);// working with file
                fclose(other_fp);// file closed
                reinit();// update nodes on file
                printf("\n\n");
                system("pause");
                goto startAgain;
            }
        }
        else
        {
            printf("\t\t\t->>> Account doesn't found.");
            system("color cf");
            printf("\n\n");
            system("pause");
            goto startAgain;
        }
    case 4:
        displayTransactions(user->acNo);
        printf("\n\n");
        system("pause");
        goto startAgain;

    }
    printf("\n\n");
    system("pause");
}
void displayTransactions(int acNo)
{

    FILE* fp_tran;// working with file!!
    char filePath[20],ch;
    sprintf(filePath,"account_%d.txt",acNo);
    fp_tran = fopen(filePath,"r");
    if(fp_tran==NULL)
    {
        printf("\n->>> Can't open this account file.");
        exit(1);
    }
    printf("\n>>>> Your all transactions-:\n\n");
    while((ch=fgetc(fp_tran))!=EOF)
    {
        printf("%c",ch);
    }
    printf("\n\n");
    fclose(fp_tran);
}
void AddminLogin()
{
    system("color 0a");
    system("cls");
    printf("\n\t\t\t->> Hey, admin password is 123. ;) ;)");
    printf("\n\t\t\t>> Type admin password: ");
    int adPass;
    scanf("%d",&adPass);
    if(adPass!=123)
    {
        system("color cf");
        printf("\n\t\t\t->>> Wrong password. try with 123.");
        printf("\n\n");
        system("pause");
        return;
    }
    system("cls");
    account* tempt = head;
    int count = 0;
    printf("\n\t\t\t********************************************\n");
    printf("\n\t\t\t|    ---      Admin Panel       ---        |\n");
    printf("\n\t\t\t**** All Accounts in SH Banking System *****\n");
    while(tempt!=NULL)
    {
        printf("\n\t\t\t=========== Account %d =============",++count);
        printf("\n\t\t\tAccount number: %d",tempt->acNo);
        printf("\n\t\t\tAccount pin: *******");
        printf("\n\t\t\tAccount name: %s",tempt->name);
        printf("\n\t\t\tBalance: %d",tempt->balance);
        printf("\n\t\t\t---------------END------------------\n");
        tempt=tempt->link;
    }
    if(tempt==head)
        printf("\n\n\t\t\t________________Empty_______________\n");
    printf("\n\n");
    system("pause");
}
void test()
{
    //printf("\nTesting mood on.\n");
    account accountOll;
    FILE *tfp;
    tfp = fopen("Accounts.txt","rb");
    if(tfp==NULL)
    {
        printf("\n->>> File error.");
        exit(1);
    }
    while(fread(&accountOll,sizeof(accountOll),1,tfp))
    {
        init(accountOll.acNo,accountOll.pin,accountOll.balance,accountOll.name,accountOll.message);
    }
    //printf("\n->>> Linke list created successfully.\n");
    //system("pause");
}
int main()
{
    system("color f0");
    head = NULL;
    test();

menu:
    ;
    int op = Menu();
    switch(op)
    {
    case 1:
        CreateAccount();
        system("cls");
        goto menu;
        break;
    case 2:
        LoginAcount();
        system("cls");
        goto menu;
        break;
    case 3:
        AddminLogin();
        system("cls");
        goto menu;
        break;
    case 4:
        return 0;
    default:
        printf("\n->>> Invalid Option. Try again.");
        printf("\n\n");
        system("pause");
        system("cls");
        goto menu;
    }
    return 0;
}
