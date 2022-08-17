// DSA-1 Project
// -----------------  Bank Management System ---------------------------------------
// 112003152 Prathamesh Wani
// 112003106 Shrirang Patil


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Account
{
    char account_name[40];
    char account_number[20];
    char DOB[15];
    char address[100];
    char contact_number[15];
    float account_balance;
} Account;

void password_check();
void generate_password();
void if_valid_password();
void Account_creator();
void show_all_account();
void update_account();
void delete_account();
void find_account();
void transaction();

int main()
{
    char passwordOption;

    while (passwordOption != '0')
    {
        system("cls");
        system("color 9");
        printf("\t\t\t\xB2\xB2\xB2\xB2\xB2 Bank Management System \xB2\xB2\xB2\xB2\xB2\n");
        printf("\n\t\t    You are the Bank Manager\n");
        printf("\n\t\t\t1. Enter Password");
        printf("\n\t\t\t2. Renew Password");
        printf("\n\t\t\t0. Exit");

        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &passwordOption);

        switch (passwordOption)
        {
        case '1':
            password_check();
            break;
        case '2':
            generate_password();
            break;
        case '0':
            printf("\n\t\t\t====== Thank You =========\n");
            break;
        default:
            printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
        }
    }

    return 0;
}

void password_check()
{
    char password[50], storePassword[50];

    FILE *passwordFile = fopen("password.bin", "rb");
    fscanf(passwordFile, "%s", storePassword);

    if (passwordFile == NULL)
    {
        printf("\n\t\t\tCreate a password then try again !\n");
        printf("\n\n\t\t\tEnter any keys to continue.......");
        getch();
        return;
    }

    printf("\n\t\t\tEnter Password : ");
    getchar();
    gets(password);

    if (strcmp(storePassword, password) == 0)
    {
        if_valid_password();
    }
    else
    {
        printf("\n\t\t\tWrong Password ! Please Try Again");
        printf("\n\n\t\t\tEnter any keys to continue.......");
        getch();
    }

    fclose(passwordFile);
}

void generate_password()
{
    char storePassword[50], oldPassword[50], newPassword[50];

    FILE *passwordFile = fopen("password.bin", "rb");
    FILE *tempFile = fopen("tempPassword.bin", "wb");

    if (passwordFile == NULL)
    {
        printf("\n\t\t\tPlease enter new password : ");
        getchar();
        gets(newPassword);
        fprintf(tempFile, "%s", newPassword);

        printf("\n\t\t\tNew Password has been created successfully.");
    }
    else
    {
        fscanf(passwordFile, "%s", storePassword);

        printf("\n\t\t\tPlease enter old password : ");
        getchar();
        gets(oldPassword);

        if (strcmp(storePassword, oldPassword) == 0)
        {
            printf("\n\t\t\tPlease enter new password : ");
            gets(newPassword);
            fprintf(tempFile, "%s", newPassword);

            printf("\n\t\t\tNew Password has been created successfully.");
        }
        else
        {
            fprintf(tempFile, "%s", storePassword);
            printf("\n\t\t\tWrong Password ! PLease Try Later.... ");
        }
    }

    fclose(passwordFile);
    fclose(tempFile);

    remove("password.bin");
    rename("tempPassword.bin", "password.bin");

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void if_valid_password()
{
    char option;

    while (option != '0')
    {
        system("cls");
        printf("\t\t\t====== Bank Management System ======\n");
        printf("\n\t\t\t1. Create Account");
        printf("\n\t\t\t2. Display All Accounts Information");
        printf("\n\t\t\t3. Update Account Information");
        printf("\n\t\t\t4. Delete Account Information");
        printf("\n\t\t\t5. Search Account Information");
        printf("\n\t\t\t6. Transaction");
        printf("\n\t\t\t0. Exit");

        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            Account_creator();
            break;
        case '2':
            show_all_account();
            break;
        case '3':
            update_account();
            break;
        case '4':
            delete_account();
            break;
        case '5':
            find_account();
            break;
        case '6':
            transaction();
            break;
        case '0':
            printf("\n\t\t\t====== Thank You ===========\n");
            exit(0);
        default:
            printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
        }
    }
}

void Account_creator()
{
    FILE *fileOne = fopen("accountInfo.bin", "ab+");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    Account accountInformation;

    system("cls");

    printf("\t\t\t====== Create Student Account ======\n");

    printf("\n\t\t\tEnter Account's Name : ");
    getchar();
    gets(accountInformation.account_name);
    printf("\t\t\tEnter Account's Number : ");
    gets(accountInformation.account_number);
    printf("\t\t\tEnter Account Holder's Date of birth : ");
    gets(accountInformation.DOB);
    printf("\t\t\tEnter Account Holder's Address : ");
    gets(accountInformation.address);
    printf("\t\t\tEnter Account Holder's Contact Number : ");
    gets(accountInformation.contact_number);
    printf("\t\t\tEnter Current Account Balance : $  ");
    scanf("%f", &accountInformation.account_balance);

    fwrite(&accountInformation, sizeof(accountInformation), 1, fileOne);

    printf("\n\n\t\t\tAccount has been opened sucessfully\n");
    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();

    fclose(fileOne);
}

void show_all_account()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    Account accountInformation;

    system("cls");

    printf("\t\t\t====== Display All Account's Information ======\n\n");

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        printf("\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.account_name, accountInformation.account_number, accountInformation.DOB, accountInformation.address, accountInformation.contact_number, accountInformation.account_balance);
        printf("\t\t\t---------------------------------------------------\n");
    }

    fclose(fileOne);
    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void update_account()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Update Account Information ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.account_number);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.account_number, tempInformation.account_number) == 0)
        {
            flag++;
            printf("\n\t\t\tChoose your option :\n\t\t\t1.Update Account Name\n\t\t\t2.Update Date of Birth.\n\t\t\t3.Update Address\n\t\t\t4.Update Contact No.");
            printf("\n\n\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\t\t\tEnter Account's Name to Update: ");
                getchar();
                gets(tempInformation.account_name);
                strcpy(accountInformation.account_name, tempInformation.account_name);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 2)
            {
                printf("\n\t\t\tEnter Date of Birth to Update: ");
                getchar();
                gets(tempInformation.DOB);
                strcpy(accountInformation.DOB, tempInformation.DOB);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 3)
            {
                printf("\n\t\t\tEnter Address to Update: ");
                getchar();
                gets(tempInformation.address);
                strcpy(accountInformation.address, tempInformation.address);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 4)
            {
                printf("\n\t\t\tEnter Contact No. to Update: ");
                getchar();
                gets(tempInformation.contact_number);
                strcpy(accountInformation.contact_number, tempInformation.contact_number);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else
            {
                printf("\n\t\t\tInvalid Option.");
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void delete_account()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Delete Account Information ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.account_number);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.account_number, tempInformation.account_number) == 0)
        {
            flag++;
            printf("\n\t\t\tAre you sure to delete ??\n\t\t\t\t1.Yes\n\t\t\t\t2.Back\n\t\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\n\t\t\tInformation has been deleted successfully!\n\n");
            }
            else if (choice == 2)
            {
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
            else
            {
                printf("\n\t\t\tInvalid Option");
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void find_account()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");

    Account accountInformation;

    int choice, flag = 0;
    char find_account_number[20], searchName[50];

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Search Account Information ======\n");

    printf("\n\t\t\tChoose your option :\n\t\t\t1.Search by Account Number\n\t\t\t2.Search by Account's Name");
    printf("\n\n\t\t\tEnter Your Option : ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        system("cls");
        printf("\t\t\t\t====== Search Account Information ======\n");
        printf("\n\n\t\t\tEnter Account Number : ");
        getchar();
        gets(find_account_number);
        while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
        {
            if (strcmp(accountInformation.account_number, find_account_number) == 0)
            {
                flag++;
                printf("\n\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.account_name, accountInformation.account_number, accountInformation.DOB, accountInformation.address, accountInformation.contact_number, accountInformation.account_balance);
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tAccount is not found");
        }
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\t\t\t\t====== Search Account Information ======\n");
        printf("\n\n\t\t\tEnter Account Name : ");
        getchar();
        gets(searchName);
        while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
        {
            if (stricmp(accountInformation.account_name, searchName) == 0)
            {
                flag++;
                printf("\n\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.account_name, accountInformation.account_number, accountInformation.DOB, accountInformation.address, accountInformation.contact_number, accountInformation.account_balance);
                printf("\t\t\t---------------------------------------------------\n");
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tAccount is not found");
        }
    }
    else
    {
        printf("\n\t\t\tInvalid Option");
    }

    fclose(fileOne);

    printf("\n\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void transaction()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int op, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Account Transaction ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.account_number);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.account_number, tempInformation.account_number) == 0)
        {
            flag++;
            printf("\n\n\t\t\tDo you want to\n\t\t\t1.Deposit\n\t\t\t2.Withdraw\n\n\t\t\tEnter your choice:");
            scanf("%d", &op);
            if (op == 1)
            {
                printf("\n\t\t\tCurrent Balance:$ %.2f", accountInformation.account_balance);
                printf("\n\t\t\tEnter the amount you want to deposit:$ ");
                scanf("%f", &tempInformation.account_balance);
                accountInformation.account_balance += tempInformation.account_balance;
                printf("\n\t\t\tCurrent Balance after Deposit:$ %.2f", accountInformation.account_balance);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tDeposited successfully!\n\n");
            }
            else
            {
                printf("\n\t\t\tCurrent Balance:$ %.2f", accountInformation.account_balance);
                printf("\n\t\t\tEnter the amount you want to withdraw:$ ");
                scanf("%f", &tempInformation.account_balance);
                if (accountInformation.account_balance < tempInformation.account_balance)
                {
                    printf("\n\n\t\t\tUnsufficient Balance!\n\n");
                    fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                }
                else
                {
                    accountInformation.account_balance -= tempInformation.account_balance;
                    printf("\n\t\t\tCurrent Balance after Withdraw:$ %.2f", accountInformation.account_balance);

                    fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                    printf("\n\n\t\t\tWithdraw successfully!\n\n");
                }
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}


