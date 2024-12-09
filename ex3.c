/******************
Name:Noam Kaveblum
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 2
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
 
void get_daily_data(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[], int day);

void get_daily_for_all_brands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[], int day);

void print_str(char str[]);

void provide_daily_stats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);

int sum_array(int arr[], int size);

int find_max_index(int arr[], int size);

int sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_dat, int end_day);

int best_sales_brand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day);

int best_sales_type(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day);

int type_sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day, int type);

int best_sales_day(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);

void print_brand_data(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand);

void print_insights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day);


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}


int main() {


    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] = {-1};
    int day = 0;
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                get_daily_data(cube, days, day);
                break;
            case addAll:
                get_daily_for_all_brands(cube, days, day);
                if (day <= DAYS_IN_YEAR)
                    day++;
                break;
            case stats:
                provide_daily_stats(cube, day);
                break;
            case print:
                printf("*****************************************\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++)
                    print_brand_data(cube, day, i);
                printf("\n\n*****************************************\n");
                break;
             case insights:
                print_insights(cube, 0, DAYS_IN_YEAR - 1);
                break; 
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");

    return 0;
}


void get_daily_data(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[], int day)  //idk if i'm allowed to use pointers 
{                                                                                     //to pass the array
    int brand;
    int sum;

    scanf("%d",&brand);
    if (brand < 0 || brand >= NUM_OF_BRANDS || days[brand] > day)
    {
        printf("This brand is not valid\n");
        return;
    }

    if (days[brand] >= DAYS_IN_YEAR) // max is a year
        return;

    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        scanf(" %d",&sum);
        cube[day][brand][i] = sum;
    }
    days[brand]++;
    return;
}


void get_daily_for_all_brands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] ,int days[], int day) // case 2
{   
    if (day >= DAYS_IN_YEAR || day < 0)
        return;
        
    int flag = 1; //true
    while (flag) 
    {
        get_daily_data(cube, days, day);

        flag = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++)
            if (days[i] <= day)
                {
                    if (!flag)  // The first one
                    {
                        flag = !flag;
                        printf("No data for brands ");
                    }
                    else
                    {
                        printf(" ,");
                    }
                    printf("%s", brands[i]);
                }
        if (flag)
            printf(".\nPlease complete the data.\n");
    }
}

void print_str(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%c", str[i]);
        i++;
    }
}

void provide_daily_stats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)  //case 3
{
    int day_to_analyze;
    printf("What day would you like to analyze?\n");
    scanf(" %d", &day_to_analyze);
    //printf("--------------- %d\n", day_to_analyze);
    while(day_to_analyze >= day)
    {
        //printf("--------------- %d\n day: %d", day_to_analyze, day);
        printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
        scanf(" %d", &day_to_analyze);
    }

    int total_sales = sales_sum(cube, day_to_analyze, day_to_analyze);

    printf("In day number %d:\n", day_to_analyze);
    printf("The sales total was %d\n", total_sales);

    int best_brand = best_sales_brand(cube, day_to_analyze, day_to_analyze);
    int best_brand_sales = sum_array(cube[day_to_analyze][best_brand], NUM_OF_TYPES);

    printf("The best sold brand with %d sales was ", best_brand_sales);
    print_str(brands[best_brand]);
    printf("\n");

    int best_type = best_sales_type(cube, day_to_analyze, day_to_analyze);
    int best_type_sales = type_sales_sum(cube, day_to_analyze, day_to_analyze, best_type);
    printf("The best sold type with %d sales was ", best_type_sales);
    print_str(types[best_type]);
    printf("\n");
}

int sum_array(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++)
        sum += arr[i];
    return sum;
}

int find_max(int arr[], int size)
{
    if (size == 0)
        return 0;

    int index = 0;
    int max = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            index = i;
        }

    }
    return index;
}

int sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day)
{
    int sum = 0;
    for (int i = start_day; i < end_day + 1; i++) 
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            sum += sum_array(cube[i][j], NUM_OF_TYPES);
    return sum;
}

int best_sales_brand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day)
{
    int sum_brand_arr[NUM_OF_BRANDS];
    for (int i = start_day; i < end_day + 1; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            sum_brand_arr[j] = sum_array(cube[i][j], NUM_OF_TYPES); 
    return find_max(sum_brand_arr, NUM_OF_BRANDS);
}

int best_sales_type(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day)
{
    int sum_types_arr[NUM_OF_TYPES] = {0};
    for (int i = start_day; i < end_day + 1; i++) 
        for (int j = 0; j < NUM_OF_TYPES; j++)
            for (int k = 0; k < NUM_OF_BRANDS; k++)
                sum_types_arr[j] += cube[i][k][j];   // This will give the same types from a brand.      
    return find_max(sum_types_arr, NUM_OF_TYPES);
}

int type_sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day , int type) 
//the only reason to do this is beacause I'm not allowed to return two values from the find_max function. 
{                                                                              
    int types_sum = 0;
    for (int i = start_day; i < end_day + 1; i++)
        for (int j = 0; j < NUM_OF_TYPES; j++)
            types_sum += cube[i][j][type];
    return types_sum;
}       

void print_brand_data(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand)
{
    printf("sales for ");
    print_str(brands[brand]);
    printf(":\n");

    for (int i = 0; i < day; i++)
    {
        printf("Day %d- ", i + 1);
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            print_str(types[j]);
            printf(": %d ", cube[i][brand][j]);
        }
        printf("\n");
    }
}

int best_sales_day(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int days_sum[DAYS_IN_YEAR] = {0};
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        days_sum[i] = sales_sum(cube, i, i);

    return find_max(days_sum, DAYS_IN_YEAR);
}

void print_insights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int start_day, int end_day)
{
    int best_brand = best_sales_brand(cube, start_day, end_day);
    int price = 0;
    for (int i = start_day; i < end_day + 1; i++)
        price += sum_array(cube[i][best_brand], NUM_OF_TYPES);
    printf("The best-selling brand overall is ");
    print_str(brands[best_brand]);
    printf(": %d$\n", price);     

    int best_type = best_sales_type(cube, start_day, end_day);
    price = type_sales_sum(cube, start_day, end_day, best_type); 
    
    printf("The best-selling type of car is ");
    print_str(types[best_type]);
    printf(": %d$\n", price);  

    int best_day = best_sales_day(cube, DAYS_IN_YEAR);  // note that the best day doesn't work for a range e.g 124 - 342
    price = sales_sum(cube, best_day, best_day);
    printf("The most profitable day was day number %d: %d$\n", best_day + 1, price);
}




    
