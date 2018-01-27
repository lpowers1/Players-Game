/*
By Logan Powers
R11446104
End of the Semester Project, Numbers Game
3/31/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define bool int
#define TRUE 1
#define FALSE 0


//makes structure needed for the information in the file
struct names{
    char name[53];
    int money;
    int gain;
    };

//changes a players balance
void topUpBalance(struct names allNames[35], int size){

    char userName[53];

    startForTopUp:;
    printf("Enter the name of the person you'd like to add to: \n");
    scanf("%s", &userName);
    int i = 0;
    int addMoney;
    int checkIfFound = 0;
    //searches array for the player the user gave
    while(i<size){
        if(strcmp(userName, allNames[i].name)==0){
            printf("If you would like to add money to your existing name enter it here otherwise put 0: \n");
            scanf("%d", &addMoney);
            allNames[i].money += addMoney;
            checkIfFound = 1;
            return;
        }
        i++;
    }
    // if it goes through the whole array and doesnt find the person
    if(checkIfFound == 0){
        printf("Could not find name. \n");
        return;
    }
}

//runs the actual game part of the file and allows to make a new character
int playGame(struct names allNames[35], int size){

    char enter_checker;
    char enter_checker2;
    srand(time(NULL));
    int total;
    int current;
    char userName[53];
    int choice;
    int userBalanceToStart;
    //starting point if they enter the wrong information
    startForPlayGame:;
    printf("Enter 0 if you'd like to add a new player and 1 if you'd like to play off someone already listed.\n");
    scanf("%d", &choice);
    if(choice == 0){

        printf("Please enter your name: ");
        scanf("%s", &userName);

        printf("Ok, %s what balance would you like to start with? ");
        scanf("%d", &userBalanceToStart);
        //enter checker just grabs the enter after so it does not mess with the rest
        enter_checker2 = getchar();

        //adds the information the player just entered to the structure
        allNames[size].money = userBalanceToStart;
        allNames[size].gain = 0;
        strcpy(allNames[size].name, userName);

        //returns 1 to show the game that we should play next, not go to the menu
        printf("\n");
        //sets current to size to show where the players stats should be changed
        current = size;
    }
    //if they want to play off someone already in the file
    else if (choice == 1){
        printf("Please enter your name: ");
        scanf("%s", &userName);
        //enter checker just grabs the enter after so it does not mess with the rest
        enter_checker2 = getchar();
        int i = 0;
        int checkIfFound = 0;
        //goes through array
        while(i<size){
                //if theyre the same
            if(strcmp(userName, allNames[i].name)==0){
                //makes sure we found the same
                checkIfFound = 1;
                current = i;
            }
            i++;
        }
        if(checkIfFound == 0){
            printf("Could not find name. \n");
            goto startForPlayGame;
        }
    }
    else{ // if they enter jiberish
        printf("You did not enter a correct answer. \n");
        goto startForPlayGame;
    }

    //heres where the game happens
    start_playGame:;
    printf("Press ENTER to Roll the Dice. (or 0 to go back to menu) ");
    enter_checker = getchar();
    printf("\n");

    //if player wants to play
    if (enter_checker == '\n'){


        //sets dice 1 and 2
        int r1 = rand() % 6 + 1;
        int r2 = rand() % 6 + 1;
        int r3;
        int r4;
        int total2;
        total = (r1+r2);

        printf("Your numbers are %d and %d whose sum is %d\n", r1, r2, total);

        //only for first turn
        if(total == 7 || total == 11){
            printf("You win");
            allNames[current].gain +=10;
            allNames[current].money +=10;
            printf(", Your current balance is %d\n\n", allNames[current].money);
            goto start_playGame;
        }
        //only for first turn
        else if(total == 2 || total == 3 || total == 12){
            printf("You lose");
            allNames[current].gain -=1;
            allNames[current].money -=1;
            printf(", Your current balance is %d\n\n", allNames[current].money);
            if(allNames[current].money <=0){
                    printf("Im sorry youre out of money pls go add more");
                return 0;
            }
            goto start_playGame;
        }
        else{
            //for all subsequent turns
            printf("Now you need to roll a %d before rolling a 7... your next rolls are...\n", total);
            do { // does loop until they either win or lose
                //sets dice 3 and 4
                r3=rand() % 6+1;
                r4=rand() % 6+1;
                total2=r3+r4;
                printf("Your numbers are %d and %d whose sum is %d\n", r3, r4, total2);
                if(total2==total){
                    //if they won
                    printf("You win");
                    allNames[current].gain +=10;
                    allNames[current].money +=10;
                    printf(", Your current balance is %d\n\n", allNames[current].money);
                    goto start_playGame;
                }
            }while(total2 != 7);
            printf("You Lose");
            allNames[current].gain -=1;
            allNames[current].money -=1;
            printf(", Your current balance is %d\n\n", allNames[current].money);
            if(allNames[current].money <=0){
                    printf("Im sorry youre out of money pls go add more");
                return 0;
            }
            goto start_playGame;
        }

    }
    //back to main menu
    else if(enter_checker == '0'){
        if (choice == 0){
            //returning 400 here to show that the user made a new person so we can increment the array and 400 is just a random number it means nothing
            return 400;
        }
        else {
            return 0;
        }

    }
    //entered a bad option
    else{
        printf("You didnt press a valid option, try again\n\n");
        goto start_playGame;
    }

}

//gets the top 5 players by balance
void playersByBalance(struct names allNames[35], int size){
    int counter = 0;
    int recentMax = 0;
    int recentIndex = 0;
    int maxNumberForWhile;
    if(size >= 5){
        // if size is bigger than 5 we cant display more than 5 so we need a variable set to 5 to go to
        maxNumberForWhile = 5;
    }
    else{
        maxNumberForWhile = size;
    }
    //only goes to how many players are in the game
    while(counter<maxNumberForWhile){
        int y;
        int maxMoney = 0;
        int maxIndex=0;
        if(counter == 0){
                //finds first top player and rest have to be between 0 and this top player
            for(y=0;y<size;y++){
                //goes through the array
                if(allNames[y].money > maxMoney){
                    //keeps setting maxIndex to the higher of the 2 values
                    maxIndex = y;
                    //sets index of where the max money is
                    maxMoney = allNames[y].money;
                    //sets maxMoney amount to go up to
                }
            }
            printf("The top 5 players by total money are...\n");
            //prints the first max person by balance
            printf("%s with $%d\n", allNames[maxIndex].name, allNames[maxIndex].money);
            recentMax = allNames[maxIndex].money;
            recentIndex = maxIndex;
            //sets the last max index and amounts to compare
        }
        //all else top players must be smaller than first
        else{
            int y2;
            int maxMoney2 = 0;
            int maxIndex2=0;
            //goes through array
            for(y2=0;y2<size;y2++){
                if(allNames[y2].money > maxMoney2 && allNames[y2].money < recentMax){
                    //keeps setting maxIndex2 to the higher of the 2 values
                    maxIndex2 = y2;
                    //sets index of where the max money is
                    maxMoney2 = allNames[y2].money;
                    //sets maxMoney amount to go up to
                }
            }
            if(recentIndex == maxIndex2){
                return;
            }
            recentIndex = maxIndex2;
            printf("%s with $%d\n", allNames[maxIndex2].name, allNames[maxIndex2].money);
            recentMax = allNames[maxIndex2].money;
        }
        counter++;
    }
}

//gets the top 5 players by gain
void playersByGain(struct names allNames[35], int size){
    int counter = 0;
    int recentMax = 0;
    int recentIndex = 0;
    int maxNumberForWhile;
    if(size >= 5){
            // if size is bigger than 5 we cant display more than 5 so we need a variable set to 5 to go to
        maxNumberForWhile = 5;
    }
    else{
        maxNumberForWhile = size;
    }
    //goes to top 5 players or how many players there are
    while(counter<maxNumberForWhile){
        int y;
        int maxGain = 0;
        int maxIndex=0;
        if(counter == 0){
            //finds first top player and rest have to be between 0 and this top player
            for(y=0;y<size;y++){
                //goes through the array
                if(allNames[y].gain > maxGain){
                    //keeps setting maxIndex to the higher of the 2 values
                    maxIndex = y;
                    //sets index of where the max money is
                    maxGain = allNames[y].gain;
                     //sets maxMoney amount to go up to
                }
            }
            //finds first top player
            printf("The top 5 players by gain are...\n");
             //prints the first max person by balance
            printf("%s with $%d\n", allNames[maxIndex].name, allNames[maxIndex].gain);
            recentMax = allNames[maxIndex].gain;
			recentIndex = maxIndex;
			//sets the last max index and amounts to compare
        }
        else{
                //all else top players have to be less than that
            int y2;
            int maxGain2 = 0;
            int maxIndex2=0;
            //goes through array
            for(y2=0;y2<size;y2++){
                if(allNames[y2].gain > maxGain2 && allNames[y2].gain < recentMax){
                    //keeps setting maxIndex2 to the higher of the 2 values
                    maxIndex2 = y2;
                    //sets index of where the max money is
                    maxGain2 = allNames[y2].gain;
                    //sets maxMoney amount to go up to
                }
            }
            if(recentIndex == maxIndex2){
                return;
            }
            recentIndex = maxIndex2;
            printf("%s with $%d\n", allNames[maxIndex2].name, allNames[maxIndex2].gain);
            recentMax = allNames[maxIndex2].gain;
        }
        counter++;
    }
}


int main(){

    int numberOfLines = 0;
    int checkIfRan = 3;

    printf("Welcome to the Numbers Game, By Logan Powers\n");

    struct names allNames[35];

    //gets the info out of the text file and puts it into an array of structs
    FILE *fpointer2;
    fpointer2 = fopen("players.txt","r");
    if (fpointer2 == NULL) {
        printf("cant read file players.txt");
    }
    else{
        int i;
        for(i=0; ;i++){
            if(fscanf(fpointer2, "%s %d %d", allNames[i].name, &allNames[i].money,
                      &allNames[i].gain)!=3){
                        if(feof(fpointer2)){
                            fclose(fpointer2);
                            break;
                        }
                      }
        }

        numberOfLines = i;
    }
    start:;
    int user_menu_answer;

        char waste;
        //main menu
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Please choose from the menu below\n");
    printf("0) Top Up Your Balance\n");
    printf("1) Play Game\n");
    printf("2) Top 5 Players by Balance\n");
    printf("3) Top 5 Winners by What They Have Won\n");
    printf("4) Exit the Game\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    scanf("%d%c", &user_menu_answer, &waste);

    //main menu options
    if(user_menu_answer == 0){
        topUpBalance(allNames, numberOfLines);
        goto start;
    }
    else if (user_menu_answer == 1){
        checkIfRan = playGame(allNames, numberOfLines);
        // 400 is an arbitary number all it means is that we need to add one to the total "numberOfLines" since array wont go anywhere near 400
        if(checkIfRan == 400){
            numberOfLines++;
            goto start;
        }
        else{
            //this means that they choose a person from the list
            goto start;
        }
    }
    else if (user_menu_answer == 2){
        playersByBalance(allNames, numberOfLines);
        goto start;
    }
    else if (user_menu_answer == 3){
        playersByGain(allNames, numberOfLines);
        goto start;
    }
    //prints back to the file with the changes made to the array
    else if (user_menu_answer == 4)
    {
        FILE *fpointer;
        fpointer = fopen("players.txt","w");
        if (fpointer == NULL) {
            printf("cant read file players.txt");
        }
        else{
            int w;
            for(w=0;w<numberOfLines;w++){
                fprintf(fpointer, "%s %d %d\n", allNames[w].name, allNames[w].money, allNames[w].gain);
            }
        }
        fclose(fpointer);
        return 0;

    }
    else{
        printf("You didnt enter a valid option\n");
    }

}
