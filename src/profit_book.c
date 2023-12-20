// Copyright (c) 2023 Gokul B
// Distributed under the MIT/X11 software license, see the accompanying
// http://www.opensource.org/licenses/mit-license.php.

#include "display.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

#define BIRIYANI_PRICE 110
#define RICE_PRICE 50

enum basic{SUCCESS = 0, FAILURE = 1};

void file_write(char[],int,int,int,int,int,int,int,int);
void user_input();
void response(int);
void help();
void command_line();
void total();
void list();
void highest();
void lowest();
void elaborate();
void search();
void check_if_new();
void collect_user_info();
void user_info_write(char[],char[],char[]);

/*CSV FORMAT
  month, day,biriyani_soled, normal_nice_soled, income, paid_of_chief, am_for_cooking_ingredient, expense, pro_or_los*/
char month[10];
int day;
int income;
int expense;
int biriyani;
int pro_or_los;
int normal_rice;
int paid_for_chief;
int given_data_income;
int am_for_cooking_ingredient;
int exp_to_buy_product_for_cooking;
int invest_day;
int invest_year;
int invest_amount;
char invest_month[10];
char invester_name[10];
char user_name[20];
char bussniess_name[20];
char bussniess_explain[20];

int main(){
    check_if_new();
    start_design();
    user_input();
    return 0;
}

void file_write(char month[], int day, int briyani_soled, int normal_rice_soled, int income, int paid_for_chief, int am_for_cooking_ingredient,int expense,int pro_or_los){
    FILE *fpointer = fopen("day_details.csv", "a");
    if (fpointer == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fpointer, "%s,%d,%d,%d,%d,%d,%d,%d,%d\n",month,day,briyani_soled,normal_rice_soled,income,paid_for_chief,am_for_cooking_ingredient,expense,pro_or_los);
    fclose(fpointer);

}
void user_input(){
    char first_option[10];
    printf("Hello , %s\n",user_name);
    printf("Hows the %s doing today\n\n", bussniess_name);

    printf("%s, Want would you like to do\n",user_name);
    printf("Take info or add info (take/add): ");
    scanf("%s", first_option);

    if(strcmp(first_option, "take") == 0){
        command_line();
    }else if (strcmp(first_option,"add") == 0){
        char temp[1];
        printf("Type full name of the month don't use uppercase\n");
        printf("Enter the Month: ");
        scanf("%s", month);
        printf("Enter the day: ");
        scanf("%d", &day);
        printf("Enter the amount paid to the cheif: ");
        scanf("%d", &paid_for_chief);
        printf("Enter amount used to buy cooking ingredient: ");
        scanf("%d", &am_for_cooking_ingredient);
        printf("Enter amount of  biriyani selled: ");
        scanf("%d", &biriyani);
        printf("Enter amount of normal rice selled: ");
        scanf("%d", &normal_rice);
        given_data_income =  (biriyani*BIRIYANI_PRICE) + (normal_rice*RICE_PRICE);
        printf("Total income get from biriyani and rice: %d \n", given_data_income);
        printf("Is \"%d\" is the actually total income (y/n): ", given_data_income);
        scanf("%s", temp);
        if(strcmp(temp, "y")==0){
            income = given_data_income;
            expense = paid_for_chief + am_for_cooking_ingredient;
            pro_or_los = income - expense;
            file_write(month,day,biriyani,normal_rice,income,paid_for_chief,am_for_cooking_ingredient,expense,pro_or_los);
            printf("Your profit of the day : %d \n", pro_or_los);
            sleep(2);
            response(pro_or_los);
            sleep(3);
            printf("All your data are stored in a csv file");
            sleep(5);


        }else if(strcmp(temp,"n")==0){
            printf("Enter the total amount of income: ");
            scanf("%d", &income);
            expense = paid_for_chief + am_for_cooking_ingredient;
            pro_or_los = income - expense;
            file_write(month,day,biriyani,normal_rice,income,paid_for_chief,am_for_cooking_ingredient,expense,pro_or_los);
            printf("Your profit of the day : %d \n", pro_or_los);
            sleep(2);
            response(pro_or_los);
            sleep(3);
            printf("All your data are stored ina csv file");
            sleep(5);

        }else{
            printf("Invalid Input!");
            printf("else worked");
            exit(1);
        }



    }else{
        printf("Invaild Input");
        exit(1);
    }
    sleep(2);
}

void response(int profit){
    if(profit < 0){
        printf("It's been a bad day isn't?\n");
    }else if (profit<2000 && profit>1000){
        printf("Today is not acutally bad tho\n");
    }else if (profit<1000){
        printf("Yeah we need improvement\n");
    }else if(profit>2000){
        printf("It's been Great Day sir\n");
    }
}


/*all the function above are used to give the user the data from the csv etc*/

void help(){
    printf("Here is the possible command to check the data from csv\n");
    printf("list      - list all the details about every days\n");
    printf("lsinvest  - This list all the investment made to the bussniness\n");
    printf("elaborate - It will give the more details list of every day\n");
    printf("search    - You can serach with the data to look for specific day details\n");
    printf("total     - It will show the total profit or loss to get\n");
    printf("highest   - To view the highest profited day and amount\n");
    printf("lowest    - To view the lowest profited day and amount\n");
    printf("invest    - Options for enter a new investment or take details of all investments\n");
    printf("exit      - To exit this program\n");
    printf("cls/clear - To clear the screen\n");
    printf("help      - To view this\n");
}

void list(){
    FILE * fpointer = fopen("day_details.csv", "r");
    if(fpointer == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    rewind(fpointer);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorIndex = 16 + (36 * 7) + (6 * 0) + 0;
    printf("\tMonth\tDay\tIncome\tExpense\tProfit/Loss\n");
    while (fscanf(fpointer, "%9[^,],%d,%*d,%*d,%d,%*d,%*d,%d,%d\n", month, &day, &income, &expense, &pro_or_los) == 5) {


        printf("\t%s\t%d\t%d\t%d\t", month, day, income, expense);
        // Check if profit is negative
        if (pro_or_los < 0) {
            SetConsoleTextAttribute(hConsole, colorIndex);
        }

        // Print the Profit/Loss value
        printf("%d\n", pro_or_los);

        // Reset color if changed
        if (pro_or_los < 0) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }



    fclose(fpointer);
}

void total() {
    int individual_profit;
    int total_profit = 0;
    FILE *fpointer = fopen("day_details.csv", "r");

    if (fpointer == NULL) {
        perror("Error opening file: ");
        sleep(4);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fpointer, "%*[^,],%*d,%*d,%*d,%*d,%*d,%*d,%*d,%d\n", &individual_profit) == 1) {
        total_profit += individual_profit;
    }

    fclose(fpointer);
    printf("Total profit/Loss of this entire time: %d\n", total_profit);
}

void highest(){
    int max_profit = 0;
    char max_month[10] = "";
    int max_day = 0;
    int current_profit = 0;
    char current_month[10] = "";
    int current_day = 0;
    FILE * fpointer = fopen("day_details.csv", "r");
    if(fpointer == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while(fscanf(fpointer, "%9[^,],%d,%*d,%*d,%*d,%*d,%*d,%*d,%d\n",current_month,&current_day, &current_profit) == 3){
        if (max_profit < current_profit){
            max_profit = current_profit;
            max_day = current_day;
            strcpy(max_month, current_month);
        }

    }
    printf("The most profited day is %s %d amount = %d\n", max_month,max_day,max_profit);
    fclose(fpointer);
}

void lowest(){
    int min_profit = __INT_MAX__;
    char min_month[10] = "";
    int min_day = 0;
    int current_profit = 0;
    char current_month[10] = "";
    int current_day = 0;
 
    FILE * fpointer = fopen("day_details.csv", "r");
    if(fpointer == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while(fscanf(fpointer, "%10[^,],%d,%*d,%*d,%*d,%*d,%*d,%*d,%d\n",current_month,&current_day, &current_profit) == 3){
        if (min_profit > current_profit){
            min_profit = current_profit;
            min_day = current_day;
            strcpy(min_month, current_month);
        }

    }
    printf("The minimum profited day is %s %d amount = %d\n", min_month,min_day,min_profit);
    fclose(fpointer);
}
void elaborate() {
    FILE *fpointer = fopen("day_details.csv", "r");
    if (fpointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorIndex = 16 + (36 * 7) + (6 * 0) + 0;
    
    // Move the file pointer to the beginning
    fseek(fpointer, 0, SEEK_SET);

    printf("\tMonth\tDay\tBriyani Soled\tNormal Rice Soled\tIncome\tPaid for Chief\tAmount for Cooking\tExpense\tProfit/Loss\n");
    
    while (fscanf(fpointer, "%10[^,],%d,%d,%d,%d,%d,%d,%d,%d\n", month, &day, &biriyani, &normal_rice, &income, &paid_for_chief, &am_for_cooking_ingredient, &expense, &pro_or_los) == 9) {
        printf("\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t", month, day, biriyani, normal_rice, income, paid_for_chief, am_for_cooking_ingredient, expense);

        // Check if profit is negativen
        if (pro_or_los < 0) {
            SetConsoleTextAttribute(hConsole, colorIndex);
        }

        // Print the Profit/Loss value
        printf("%d\n", pro_or_los);

        // Reset color if changed
        if (pro_or_los < 0) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }

    fclose(fpointer);
}

void search(){
    int temp_input;
    char entered_month[10];
    int entered_date;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorIndex = 16 + (36 * 7) + (6 * 0) + 0;
    printf("How would you like to search with (month and date) or month or date (1/2/3) :");
    scanf("%d", &temp_input);
    if(temp_input == 1){
        printf("Enter the month: ");
        scanf("%s", entered_month);
        printf("Enter the date: ");
        scanf("%d", &entered_date);

        FILE * fpointer = fopen("day_details.csv", "r");
        if(fpointer == NULL){
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        while(fscanf(fpointer, "%10[^,],%d,%d,%d,%d,%d,%d,%d,%d\n",month,&day,&biriyani,&normal_rice,&income,&paid_for_chief,&am_for_cooking_ingredient,&expense,&pro_or_los) == 9){
            if(strcmp(entered_month, month)==SUCCESS && entered_date == day){
                printf("\tMonth\tDay\tBriyani Soled\tNormal Rice Soled\tIncome\tPaid for Chief\tAmount for Cooking\tExpense\tProfit/Loss\n");
                printf("\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t", month, day, biriyani, normal_rice, income, paid_for_chief, am_for_cooking_ingredient, expense);
                        // Check if profit is negativen
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, colorIndex);
                }
                printf("%d\n", pro_or_los);
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }
        }

    }else if(temp_input==2){
        printf("Enter the Month: ");
        scanf("%s", entered_month);
        FILE * fpointer = fopen("day_details.csv", "r");
        if(fpointer == NULL){
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        printf("\tMonth\tDay\tBriyani Soled\tNormal Rice Soled\tIncome\tPaid for Chief\tAmount for Cooking\tExpense\tProfit/Loss\n");
        while(fscanf(fpointer, "%10[^,],%d,%d,%d,%d,%d,%d,%d,%d\n",month,&day,&biriyani,&normal_rice,&income,&paid_for_chief,&am_for_cooking_ingredient,&expense,&pro_or_los) == 9){
            if(strcmp(entered_month, month)==SUCCESS){
                printf("\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t", month, day, biriyani, normal_rice, income, paid_for_chief, am_for_cooking_ingredient, expense);
                        // Check if profit is negativen
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, colorIndex);
                }
                printf("%d\n", pro_or_los);
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }
        }   
    }else if(temp_input == 3){
        printf("Enter the Day: ");
        scanf("%d", &entered_date);

        FILE * fpointer = fopen("day_details.csv", "r");
        if(fpointer == NULL){
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        printf("\tMonth\tDay\tBriyani Soled\tNormal Rice Soled\tIncome\tPaid for Chief\tAmount for Cooking\tExpense\tProfit/Loss\n");
        while(fscanf(fpointer, "%10[^,],%d,%d,%d,%d,%d,%d,%d,%d\n",month,&day,&biriyani,&normal_rice,&income,&paid_for_chief,&am_for_cooking_ingredient,&expense,&pro_or_los) == 9){
            if(entered_date==day){
                printf("\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t", month, day, biriyani, normal_rice, income, paid_for_chief, am_for_cooking_ingredient, expense);
                        // Check if profit is negativen
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, colorIndex);
                }
                printf("%d\n", pro_or_los);
                if (pro_or_los < 0) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }
        }
    }

}

/* The above function will take care of the investment made*/

void investment_writer(char name[], int amount,int year,char month[], int day){
    FILE * fpointer = fopen("investment.csv", "a");
    fprintf(fpointer, "%s,%d,%d,%s,%d\n",name,amount,year,month,day);
    fclose(fpointer);
}

void invest_list(){
    FILE * fpointer = fopen("investment.csv","r");
    printf("\tName\tAmount\tYear\tMonth\tDay\n");
    while(fscanf(fpointer,"%10[^,],%d,%d,%10[^,],%d", invester_name,&invest_amount,&invest_year,invest_month,&invest_day)==5){
        printf("\t%s\t%d\t%d\t%s\t%d\n",invester_name,invest_amount,invest_year,invest_month,invest_day);

    }
    fclose(fpointer);
}

void investment_input(){
    printf("Enter the name of the Invester: ");
    scanf("%s",invester_name);
    printf("Enter the total amount invested by %s : ",invester_name);
    scanf("%d", &invest_amount);
    printf("Enter the year %s Invested: ", invester_name);
    scanf("%d", &invest_year);
    printf("Enter the month %s Invested: ",invester_name);
    scanf("%s", invest_month);
    printf("Enter the day %s Invested: ", invester_name);
    scanf("%d", &invest_day);
    investment_writer(invester_name,invest_amount,invest_year,invest_month,invest_day);
    printf("Your Inputed Data are been stored");

}
void command_line(){
    char command[10];
    printf("Type \"help\" to see possible command\n");
    while(1==1){
        printf(">>> ");
        scanf("%s", command);
        if(strcmp(command, "exit")==SUCCESS){
            printf("Have a great day Sir");
            sleep(4);
            exit(EXIT_FAILURE);
        }else if (strcmp(command,"help")==SUCCESS){
            help();
        }else if (strcmp(command, "list")==SUCCESS){
            list();
        }else if (strcmp(command, "clear") == SUCCESS || strcmp(command, "cls") == SUCCESS){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }else if(strcmp(command, "total")==SUCCESS){
            total();
        }else if(strcmp(command, "highest")==SUCCESS){
            highest();
        }else if(strcmp(command, "lowest")==SUCCESS){
            lowest();
        }else if(strcmp(command, "elaborate")==SUCCESS){
            elaborate();
        }else if(strcmp(command, "search")==SUCCESS){
            search();
        }else if(strcmp(command, "invest")==SUCCESS){
            investment_input();
        }else if(strcmp(command, "lsinvest")==SUCCESS){
            invest_list();
        }
        else{
            printf("Invalid Command!\n");
        }
    }
}

/*All the function above are used for user information*/

void user_info_write(char name[],char bussniess_name[],char bussniess_explain[]){
    FILE * fpointer = fopen("user_info.csv","a");
    fprintf(fpointer, "%s,%s,%s\n", name,bussniess_name,bussniess_explain);
    fclose(fpointer);
}

void collect_user_info(){
    printf("\tWelcome to profit Book\n");
    printf("Enter Your name: ");
    scanf("%s",user_name);
    printf("Enter You Bussniess name: ");
    scanf("%s", bussniess_name);
    printf("What type of Bussniess, explain in one word: ");
    scanf("%s", bussniess_explain);
    user_info_write(user_name,bussniess_name,bussniess_explain);

}
void check_if_new(){
    int temp_int=0;
    FILE * fpointer = fopen("user_info.csv", "r");
    if (fpointer == NULL){
        FILE * fpointer_dup = fopen("user_info.csv", "a");
        fclose(fpointer_dup);
        collect_user_info();
        printf("\n");
    }else{
            while(fscanf(fpointer, "%20[^,],%20[^,],%20[^,]\n", user_name,bussniess_name,bussniess_explain)==3){
                temp_int++;
            }
            printf("%d",temp_int);
            if(temp_int==0){
                collect_user_info();
            }
            if(temp_int>1){
                printf("\nError occured in the user_info.csv");
                sleep(3);
                exit(EXIT_FAILURE);
            }
    }
    fclose(fpointer);
}
