#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

#define AMOUNT_PAID_CHIEF 1400
#define BIRIYANI_PRICE 110
#define RICE_PRICE 50

enum basic{SUCCESS = 0, FAILURE = 1};

void file_write(char[], int,int,int,int);
void user_input();
int expense_func();
void response(int);
void help();
void command_line();
void total();
void list();

char month[10];
int day;
int income;
int expense;
int biriyani;
int pro_or_los;
int normal_rice;
int given_data_income;
int exp_to_buy_product_for_cooking;


int main(){
    user_input();
    return 0;
}

void file_write(char month[], int day, int income,int expense,int pro_or_los){
    FILE *fpointer = fopen("day_details.csv", "a");
    if (fpointer == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fpointer, "%s,%d,%d,%d,%d\n",month,day,income,expense,pro_or_los);
    fclose(fpointer);

}
void user_input(){
    char first_option[10];
    printf("Sir, Want would you like to do\n");
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
        printf("Enter amount of  biriyani selled: ");
        scanf("%d", &biriyani);
        printf("Enter amount of normal rice selled: ");
        scanf("%d", &normal_rice);
        given_data_income =  (biriyani*BIRIYANI_PRICE) + (normal_rice*RICE_PRICE);
        printf("Total income get from biriyania and rice: %d \n", given_data_income);
        printf("Is \"%d\" is the actually total income (y/n): ", given_data_income);
        scanf("%s", temp);
        if(strcmp(temp, "y")==0){
            income = given_data_income;
            expense = expense_func();
            pro_or_los = income - expense;
            file_write(month,day,income,expense,pro_or_los);
            printf("Your profit of the day : %d \n", pro_or_los);
            sleep(2);
            response(pro_or_los);
            sleep(3);
            printf("Call your data are stored ina csv file");
            sleep(5);


        }else if(strcmp(temp,"n")==0){
            printf("Enter the total amount of income: ");
            scanf("%d", &income);
            expense = expense_func();
            pro_or_los = income - expense;
            file_write(month,day,income,expense,pro_or_los);
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

int expense_func(){
    printf("Enter the amount to product bought for cooking: ");
    scanf("%d", &exp_to_buy_product_for_cooking);
    return AMOUNT_PAID_CHIEF + exp_to_buy_product_for_cooking;
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
    printf("search    - You can serach with the data to look for specific day details\n");
    printf("previous  - It will show the details of the previous day\n");
    printf("total     - It will show the total profit or loss to get\n");
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorIndex = 16 + (36 * 7) + (6 * 0) + 0;
    printf("\tMonth\tDay\tIncome\tExpense\tProfit/Loss\n");
    while (fscanf(fpointer, "%9[^,],%d,%d,%d,%d\n", month, &day, &income, &expense, &pro_or_los) == 5) {
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

    while (fscanf(fpointer, "%*[^,],%*d,%*d,%*d,%d\n", &individual_profit) == 1) {
        total_profit += individual_profit;
    }

    fclose(fpointer);
    printf("Total profit/Loss of this entire time: %d\n", total_profit);
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
        }else{
            printf("Invalid Command!\n");
        }
    }
}


