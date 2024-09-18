#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct player
    {
        char name[50];
        char characterWeapon[50];
        int healthPoints;
        int Defense;
        int frozenFlag;
        int thornsFlag;
        void (*magicSpells[3])(void*);
        char userSpells[3][50]; //array for display and string comparison

    } player;

void printBold(const char *text) {
    printf("\033[1m%s\033[0m", text); 
}

void encounterEnemy() {
    printf("You encounter an enemy! Prepare for battle!\n");
}
void findTreasure() {
    printf("You found a hidden treasure! Your wealth increases.\n");
}

void FireCast(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by Fire Cast!  ", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
    
    printf("Remaining health: %d\n", (targetPlayer->healthPoints));
}
void Freeze(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("A Freeze spell was casted !  Karma caused %s to withdraw during this intonation.  \n", targetPlayer->name);
    targetPlayer->frozenFlag = 1;  // Set the player's frozen status

}
void LightningStrike(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by Lighting Strike!  ", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
    printf("Remaining health: %d\n", (targetPlayer->healthPoints));
}
void HealOrb(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
 
    printf("%s sprayed itself with Holy Water!  ", targetPlayer->name);
    targetPlayer->healthPoints += 10;  // Increase health points by 10

    printf("Total health: %d\n", (targetPlayer->healthPoints));

}
void Thorns(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*

    printf("%s casted Thorns!\n", targetPlayer->name);
    targetPlayer->thornsFlag = 2;
}

void CharacterCreation(player *userInput){//PASSES BY REFERENCE ORIGINAL USERINPUT STRUCT FROM MAIN!
    //sets LOCAL placeholders to 0
    int numberWeapon = 0;
    int numberSpell = 0;
    int spellCount = 0;

    printf("\n");
    printf("\n");
    printf("****************************************************************************************************************\n");
    printf(" ____ __  __  ___  _____  ___   ____ _____ _____ _____        ____ _____ _____  ___  _____ __  _____  __  __ \n");
    printf("((    ||==|| ||=|| ||_// ||=|| ((     ||   ||==  ||_//       ((    ||_// ||==  ||=||  ||   || ((   )) ||\\\\|| \n");
    printf("  \\__ ||  || || || || \\\\ || ||  \\__   ||   ||___ || \\\\        \\__  || \\\\ ||___ || ||  ||   ||   \\_//  || \\\\| \n");
    printf("****************************************************************************************************************");
    printf("\n");

    printf("\n");
    printf("1.- Type a name for your character:  ");
    scanf("%s", userInput->name); //did not use amperson because .name is a char pointer


    printf("\n");
    printf("2.- Select a weapon for your character \n");
        printf("\t 1) Crucifix   2) Rosary   3) Dagger \n");
    printf("\033[1;31mENTER A NUMBER:  \033[0m");
    scanf("%d", &numberWeapon);  //stored answer in numberRace
    switch(numberWeapon){
        case 1:
            strcpy(userInput->characterWeapon, "Crucifix"); break;
        case 2:
            strcpy(userInput->characterWeapon, "Rosary"); break;
        case 3:
            strcpy(userInput->characterWeapon, "Dagger"); break;
        default:
            printf("Invalid choice.\n");
            break; 
    }
    

    printf("\n");
    printf("3.- Select 3 magic spells for your character \n");
        printf("\t 1) FireCast   2) Freeze   3) LightingStrike   4) HealOrb   5) Thorns \n");
    while (spellCount < 3) {
        printf("\033[1;31mENTER A NUMBER FOR MAGIC SPELL #%d:  \033[0m", spellCount + 1);
        scanf("%d", &numberSpell);

        // Validate the choice
        if (numberSpell < 1 || numberSpell > 5) {
            printf("Invalid choice.\n");
            continue;
        }
        //Validate there are no repeats

        // Store the chosen spell
        switch(numberSpell) {
            case 1:
                strcpy(userInput->userSpells[spellCount], "FireCast");
                userInput->magicSpells[spellCount] = FireCast; break;
            case 2:
                strcpy(userInput->userSpells[spellCount], "Freeze");
                userInput->magicSpells[spellCount] = Freeze; break;
            case 3:
                strcpy(userInput->userSpells[spellCount], "LightningStrike"); 
                userInput->magicSpells[spellCount] = LightningStrike; break;
            case 4:
                strcpy(userInput->userSpells[spellCount], "HealOrb");
                userInput->magicSpells[spellCount] = HealOrb; break;
            case 5:
                strcpy(userInput->userSpells[spellCount], "Thorns");
                userInput->magicSpells[spellCount] = Thorns; break;
        }

        printf("%s was brought upon thee. Your soul is purified further. \n", userInput->userSpells[spellCount]);
        printf("\n");
        spellCount++;
    }


    userInput->healthPoints = 100;
    userInput->Defense = 10;

    printf("\n");
    printf("PLAYER 1 \n");
    printf("Name: %s\n", userInput->name);
    printf("Weapon: %s\n", userInput->characterWeapon);

        for(int i=0; i<3; i++ ){ //Iterates from 0 to 2, prints all spells in userSpells array
        printf("\t %d) %s   ", (i+1), userInput->userSpells[i]);
    }
    printf("\n");
    printf("\n");
}
void GenerateCPU(player *CPU){
    strcpy(CPU->name, "Priest of the Veiled Sacrament");
    strcpy(CPU->characterWeapon, "Steel Crucifix");
    CPU->healthPoints = 100;  // Default health
    CPU->Defense = 10;        // Default defense

     // Assigning spells to CPU
    void (*availableSpells[5])(void*) = {FireCast, Freeze, LightningStrike, HealOrb, Thorns}; //array of functions
    char *spellNames[5] = {"FireCast", "Freeze", "LightningStrike", "HealOrb", "Thorns"}; //array of chars

    for (int i = 0; i < 3; i++) {
        int randomIndex = rand() % 5;   // Choose a random spell

        CPU->magicSpells[i] = availableSpells[randomIndex]; //Add the random spell to CPU magicspells array 
        strcpy(CPU->userSpells[i], spellNames[randomIndex]); //add the random spell to CPU index userSpells array. 
    }

    printf("\n");
    printf("CPU \n");
    printf("Name: %s\n", CPU->name);
    printf("Weapon: %s\n", CPU->characterWeapon);
    for(int i=0; i<3; i++ ){ //Iterates from 0 to 2, prints all spells in userSpells array
        printf("\t %d) %s   ", (i+1), CPU->userSpells[i]);
    }
    printf("\n");
}
void Help(){
    printf("MATRYR INCARNATIONS ---alpha v1.3.0\n");
    printf("\n");


}

int Attack(player *players){
    srand(time(0));

    int randomDice = 0;
    randomDice = rand()% 20 + 1; // Get random number between 1 and 20

    printf("Dice Roll: %d\n", randomDice);
    printf("\n");

    if(randomDice >= players[1].Defense && randomDice < 20){
        printf("%s 's %d attack vs %s %d defense . \n", players[0].name, randomDice, players[1].name, players[1].Defense);
        printf("Your blow found its mark. ");
        printf("%s lost 10 health\n", players[1].name);
        printf("\n");
        
    } else if (randomDice == 20){
        printf("%s 's %d attack vs %s %d defense . \n", players[0].name, randomDice, players[1].name, players[1].Defense);
        printf("Thy strike was delivered with unfailing wrath. ");
        printf("%s lost 20 health", players[1].name);
        printf("\n");
    } else {
        printf("%s 's %d attack vs %s %d defense . \n", players[0].name, randomDice, players[1].name, players[1].Defense);
        printf("You have missed, and the burden of thy failure lingers. ");
        printf("Remaining health: %d\n", (players[0].healthPoints-(randomDice)));
        printf("\n");
    }

    return randomDice;
}
int Defend(player *players){
    players[0].Defense += 5;
    printf("\n");
    printf("Thy defenses are strengthened by fivefold during this intonation. ");
    printf("%s defense points: %d \n", players[0].name, players[0].Defense);
    printf("\n");
}
void UserMagic(player *players){
    
    int numberSpellChoice = 0;

    printf("Which spell do you wish to cast?\n");
    printf("\n");
    
    for(int i=0; i<3; i++ ){ //Iterates from 0 to 2, prints all spells in userSpells array
        printf("\t %d) %s  ", (i+1), players[0].userSpells[i]);
    }
    printf("\n");
    printf("\n");

    printf("\033[1;31mENTER A NUMBER:  \033[0m");
    scanf("%d", &numberSpellChoice);  //stored answer in numberSpellChoice


    switch(numberSpellChoice){
        case 1:
             if(strcmp(players[0].userSpells[0], "HealOrb") == 0 ){
                //printf("IN\n");
                players[0].magicSpells[0](&players[0]); break;
             } else {
                players[0].magicSpells[0](&players[1]); break;
             }
             break;

        case 2:
            if(strcmp(players[0].userSpells[1], "HealOrb") == 0 ){
                players[0].magicSpells[1](&players[0]); break;
            } else {
                players[0].magicSpells[1](&players[1]); break;
            }
            break;

        case 3:
            if(strcmp(players[0].userSpells[2], "HealOrb") == 0 ){
                players[0].magicSpells[2](&players[0]); break; 
            } else {
                players[0].magicSpells[2](&players[1]); break;
            }
            break;

        default:
            printf("Invalid choice.\n");
            break; 
    }

}

int UserAction(player *players){
    int actionAnswer = 0;

    printf("What do you want to do?\n");
    printf("\t 1) Attack   2) Defend   3) Use Magic \n");

    printf("\n");
    printf("\033[1;31mENTER A NUMBER:  \033[0m");
    scanf("%d", &actionAnswer);  //stored answer in actionAnswer
    switch(actionAnswer){
        case 1:
            Attack(players); break;
        case 2:
            Defend(players); break;
        case 3:
            UserMagic(players); break; 
        default:
            printf("Invalid choice.\n");
            break; 
    }
return actionAnswer; //for defend gameplay loop in main
}
int CPUAction(player *players){
        srand(time(NULL));
        int randomAction= rand() % 3 + 1;  // Choose a random action from 1 to 3 
        int randomDice = 0;

        int randomIndex = rand() % 3;  // Choose a random spell from index 0 to 2 

        switch(randomAction){
        case 1:
                printf("\n");
                printf("Your enemy launches at you !\n");
                randomDice = rand()% 20 + 1; // Get random number between 1 and 20

                printf("Dice Roll: %d\n", randomDice);
                printf("\n");

                if(randomDice >= players[0].Defense && randomDice < 20){
                    printf("%s 's %d attack vs %s %d defense . \n", players[1].name, randomDice, players[0].name, players[0].Defense);
                    printf("Your enemy has struck against thee. ");
                    printf("%s lost 10 health\n", players[0].name);
                    printf("\n");
                } else if (randomDice == 20){
                    printf("%s 's %d attack vs %s %d defense . \n", players[1].name, randomDice, players[0].name, players[0].Defense);
                    printf("Your enemy's blow was delivered with grievous precision. ");
                    printf("%s lost 20 health\n", players[0].name);
                    printf("\n");
                } else {
                    printf("%s 's %d attack vs %s %d defense . \n", players[1].name, randomDice, players[0].name, players[0].Defense);
                    printf("Your enemy's strike has been in vain. You remain untouched. \n");
                    printf("\n");
                } break;
        case 2:
                printf("\n");
                players[1].Defense += 5;
                printf("%s chose to defend. \n", players[1].name);
                printf("Thy enemy is strengthened by fivefold. \n");
                printf("\n"); 
                break;
        case 3:
                if( strcmp(players[1].userSpells[randomIndex], "HealOrb") == 0 ){
                    players[1].magicSpells[randomIndex](&players[1]); break; //if the spell chosen in HealOrb, then it will throw players[1] instead
                
                } else { //every other spell. Code will throw player[0] (User) as target instead
                    players[1].magicSpells[randomIndex](&players[0]); break;
                } break;
        default:
            printf("default in cpuaction"); break;
    return randomAction;
    }   
        
}
void RandomEvent(){
    srand(time(NULL));
    int randomIndex = rand () % 2; //initialize random index to choose random event between 0 and 1

    void (*eventFunctions[2])() = {encounterEnemy, findTreasure}; //array of function pointers
    eventFunctions[randomIndex](); //Calls list and assigns random index
}

int main(){
    srand(time(NULL));
    int menuAnswer = 0;
    player players[2]; // players[0] is for the user, players[1] is for the CPU
    int turn = 0;  // 0 for User, 1 for CPU
    int actionAnswer = 0;  //store user action
    int randomAction = 0; //store cpu action

    printf("\n");
    printf("_______  _______  _______ _________          _______           _________ _        _______  _______  _______  _        _______ __________________ _______  _       _________ _______ \n");
    printf("(       )(  ___  )(  ____ )\\__   __/|\\     /|(  ____ )          \\__   __/( (    /|(  ____ \\(  ___  )(  ____ )( (    /|(  ___  )\\__   __/\\__   __/(  ___  )( (    /|\\__   __/(  ____ \\ \n");
    printf("| () () || (   ) || (    )|   ) (   ( \\   / )| (    )|             ) (   |  \\  ( || (    \\/| (   ) || (    )||  \\  ( || (   ) |   ) (      ) (   | (   ) ||  \\  ( |   ) (   | (    \\/ \n");
    printf("| || || || (___) || (____)|   | |    \\ (_) / | (____)|             | |   |   \\ | || |      | (___) || (____)||   \\ | || (___) |   | |      | |   | |   | ||   \\ | |   | |   | (_____  \n");
    printf("| |(_)| ||  ___  ||     __)   | |     \\   /  |     __)             | |   | (\\ \\) || |      |  ___  ||     __)| (\\ \\) ||  ___  |   | |      | |   | |   | || (\\ \\) |   | |   (_____  ) \n");
    printf("| |   | || (   ) || (\  (      | |      ) (   | (\\ (                | |   | | \\   || |      | (   ) || (\\ (   | | \\   || (   ) |   | |      | |   | |   | || | \\   |   | |         ) | \n");
    printf("| )   ( || )   ( || ) \  \__   | |      | |   | ) \\ \\__          ___) (___| )  \\  || (____/\\| )   ( || ) \\ \\__| )  \\  || )   ( |   | |   ___) (___| (___) || )  \\  |___) (___/\\____) | \n");
    printf("|/     \\||/     \\||/   \\__/   )_(      \\_/   |/   \\__/          \\_______/|/    )_)(_______/|/     \\||/   \\__/|/    )_)|/     \\|   )_(   \\_______/(_______)|/    )_\\_______/\\_______) \n");
    
        
    printf("\n");
    printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \tcoded in C, 2024\n");

while(1){ //main menu loop
    printf("\n");
    printf("\n");
    printf("Main Menu\n");
    printf("Select one of the following options:\n");
    printf("\n");

    printf("1.- New Game\n");
    printf("2.- Exit\n");
    printf("3.- Help\n");
    printf("\n");
    printf("\033[1;31mENTER A NUMBER:  \033[0m");
    scanf("%d", &menuAnswer);

    switch(menuAnswer){
        case 1:
            CharacterCreation(&players[0]); break;
        case 2:
            printf("Exiting the program. . .\n");
            exit(0);  // Exit the program with a success status (0)
        case 3:
            Help(); continue;
        default:
            printf("Invalid choice.\n"); continue; 
    }
    break; 
}

    GenerateCPU(&players[1]);

    printf("Salutations, gratus %s!\n", players[0].name);
    printf("**************************************");
    printf("\n");

    printf("\n");
    printf("You awake inside a tower. It is Full Moon.\n");
    printf("You have an overpowering urge to get to the top of the tower. \n");
    printf("\n");

    printf("\n");
    printBold("Your quest is set.\n");
    printf("**************************************");
    printf("\n");

    printf("\n");
   
 //User turn is first
    RandomEvent();
    actionAnswer = UserAction(players);
    turn = !turn; //changes turn to CPU

    int playerDefendedLastTurn = 0;  // Flag to track if the player defended last turn
    int cpuDefendedLastTurn = 0;     // Flag to track if the CPU defended last turn

    while (players[0].healthPoints > 0 && players[1].healthPoints > 0) { //Core Gameplay Loop
    //printf("%s flag is: %d", players[turn].name, players[turn].frozenFlag);


        // Revert defense points at the start of the player's turn if they defended last turn
        if (turn == 0 && playerDefendedLastTurn) {
            if (players[0].Defense > 10) {
                players[0].Defense = 10;
                printf("%s defense points reverted back to: %d \n", players[0].name, players[0].Defense);
            }
            playerDefendedLastTurn = 0;  // Reset the flag after defense reverts
        }

        // Revert CPU's defense at the start of its turn if it defended last turn
        if (turn == 1 && cpuDefendedLastTurn) {
            if (players[1].Defense > 10) {
                players[1].Defense = 10;
                printf("%s defense points reverted back to: %d\n", players[1].name, players[1].Defense);
            }
            cpuDefendedLastTurn = 0;  // Reset the flag after defense reverts
        }

        //Check for frozen flag
        if (players[turn].frozenFlag == 1) {
            printf("\n%s is frozen . \n", players[turn].name);
            printf("\n");
            players[turn].frozenFlag = 0;  // Unfreeze the player after they skip a turn
            turn = !turn;  // Switch to the next player
        } else {
            if (turn == 0){ //User turn
                printf("\n");
                printf("\n");
                RandomEvent();
                actionAnswer = UserAction(players);

                // Check if the user defended this turn
                if (actionAnswer == 2) {
                    playerDefendedLastTurn = 1;  // Set flag indicating the player defended
                }
                printf("===\n");
                printf("\n");
                turn = 1;

            } else if (turn == 1){ //CPU turn
                printf("\n");
                printf("\n");

                randomAction = CPUAction(players);

                if (randomAction == 2) {
                cpuDefendedLastTurn = 1;  // Set flag indicating the CPU defended
                }

                printf("===\n");
                printf("\n");
                turn = 0;
            }
        }
        //Verify players defense points every turn
                if (players[turn].Defense > 10) {
                    players[turn].Defense = 10;
                    printf("%s defense points reverted back to: %d \n", players[turn].name, players[turn].Defense);
                    printf("\n");
                }

        //Verify health points
            if (players[0].healthPoints <= 0) {
                printf("%s has been vanquished! MORTEM.\n", players[0].name);
                break; exit(0);
            }
            if (players[1].healthPoints <= 0) {
                printf("%s has fallen! Your victory is consecrated!\n", players[1].name);
                break; exit(0);
            }
    }

    return 0;
}