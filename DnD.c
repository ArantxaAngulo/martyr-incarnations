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
        void (*magicSpells[3])(void*);
        char userSpells[3][50];

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
    printf("%s is hit by a Fire Cast!\n", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
    
    //printf("Remaining health: %d\n", (targetPlayer->healthPoints));
}
void Freeze(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by a Freeze!\n", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15

}
void LightningStrike(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by a Lighting Strike!\n", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
}
void HealOrb(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by a Freeze!\n", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
}
void ShieldWall(void* target) {
    player* targetPlayer = (player*)target;  // Cast the generic void* to a player*
    printf("%s is hit by a Shield Wall!\n", targetPlayer->name);
    targetPlayer->healthPoints -= 15;  // Reduce health points by 15
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
    printf("enter number:  ");
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


    char *ptruserSpells = userInput->userSpells;

    printf("\n");
    printf("3.- Select 3 magic spells for your character \n");
        printf("\t 1) FireCast   2) Freeze   3) LightingStrike   4) HealOrb   5) ShieldWall \n");
    while (spellCount < 3) {
        printf("Enter a number for magic spell #%d: ", spellCount + 1);
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
                *ptruserSpells = "FireCast"; 
                userInput->magicSpells[spellCount] = FireCast; break;
            case 2:
                *ptruserSpells = "Freeze"; 
                userInput->magicSpells[spellCount] = Freeze; break;
            case 3:
                *ptruserSpells = "LightningStrike"; 
                userInput->magicSpells[spellCount] = LightningStrike; break;
            case 4:
                *ptruserSpells = "HealOrb"; 
                userInput->magicSpells[spellCount] = HealOrb; break;
            case 5:
                *ptruserSpells = "ShieldWall"; 
                userInput->magicSpells[spellCount] = ShieldWall; break;
        }

        printf(" %s ", *ptruserSpells);
        ptruserSpells++;
        spellCount++;
    }


    userInput->healthPoints = 100;
    userInput->Defense = 10;

    printf("\n");
    printf("Player 1: \n");
    printf("Name: %s\n", userInput->name);
    printf("Weapon: %s\n", userInput->characterWeapon);
    printf("\n");
    printf("\n");
}
void GenerateCPU(player *CPU){
    strcpy(CPU->name, "Priest of the Veiled Sacrament");
    strcpy(CPU->characterWeapon, "Steel Crucifix");
    CPU->healthPoints = 100;  // Default health
    CPU->Defense = 10;        // Default defense

     // Assigning spells to CPU
    void (*availableSpells[5])(void*) = {FireCast, Freeze, LightningStrike, HealOrb, ShieldWall};
    for (int i = 0; i < 3; i++) {
        int randomIndex = rand() % 5;  // Choose a random spell
        CPU->magicSpells[i] = availableSpells[randomIndex];
    }
}
void Help(){
    printf("MATRYR INCARNATIONS ---alpha v1.0.0\n");
    printf("\n");


}

int Attack(player *players){
    srand(time(0));

    int randomDice = 0;
    randomDice = rand()% 20 + 1; // Get random number between 1 and 20

    printf("Dice Roll: %d\n", randomDice);
    printf("\n");

    if(randomDice >= players[1].Defense && randomDice < 20){
        printf("Your blow found its mark. ");
        printf("%s lost 10 health\n", players[1].name);
        printf("\n");
        
    } else if (randomDice == 20){
        printf("Thy strike was delivered with unfailing wrath. ");
        printf("%s lost 20 health", players[1].name);
        printf("\n");
    } else {
        printf("You have missed, and the burden of thy failure lingers. ");
        printf("Remaining health: %d\n", (players[0].healthPoints-(randomDice)));
        printf("\n");
    }

    return randomDice;
}
int Defend(player *players){
    players[0].Defense += 5;
    printf("\n");
    printf("Thy defenses are strengthened by fivefold. ");
    printf("\n");
}
void UserMagic(player *players){
    
    int numberSpellChoice = 0;

    printf("Which spell do you wish to cast?\n");
    printf("\n");
    for(int i=0; i<3; i++ ){ //Goes
        printf("\t 1) %s   2) %s   3) %s \n", players[0].magicSpells[i]);
    }

    printf("enter number:  ");
    scanf("%d", &numberSpellChoice);  //stored answer in numberSpellChoice
    
    switch(numberSpellChoice){
        case 1:
            players[0].magicSpells[numberSpellChoice](&players[1]); break;
        case 2:
            players[0].magicSpells[numberSpellChoice](&players[1]); break;
        case 3:
            players[0].magicSpells[numberSpellChoice](&players[1]); break;
        default:
            printf("Invalid choice.\n");
            break; 
    }

}

void UserAction(player *players){
    int actionAnswer = 0;

    printf("What do you want to do?\n");
    printf("\t 1) Attack   2) Defend   3) Use Magic \n");

    printf("\n");
    printf("enter number:  ");
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
}
void CPUAction(player *players){
        
        int randomAction= rand() % (3 + 1);  // Choose a random action from 1 to 3 
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
                    printf("Your enemy has struck against thee. ");
                    printf("%s lost 10 health\n", players[0].name);
                    printf("\n");
                } else if (randomDice == 20){
                    printf("Your enemy's blow was delivered with grievous precision. ");
                    printf("%s lost 20 health\n", players[0].name);
                    printf("\n");
                } else {
                    printf("Your enemy's strike has been in vain. You remain untouched. \n");
                    printf("\n");
                } break;
        case 2:
                printf("\n");
                printf("Your enemy sprays itself with Holy Water\n");
                players[1].Defense += 5;
                printf("Thy enemy is strengthened by fivefold. \n"); break;
                printf("\n");
        case 3:
            players[1].magicSpells[randomIndex](&players[0]);
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
    int turn = 0;  // 0 for Player 1 (User), 1 for Player 2 (CPU)

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

    printf("1.- Create Character\n");
    printf("2.- Exit\n");
    printf("3.- Help\n");
    printf("\n");
    printf("enter a number: ");
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
    turn = 0; //redundant, but ensures user always goes first
    while (players[0].healthPoints > 0 && players[1].healthPoints > 0) {
        
        //User turn is first
        RandomEvent();
        UserAction(players);
        turn = !turn; //changes turn

            if(turn == 0){ //User turn
                RandomEvent();
                UserAction(players);
                printf("==\n");
                printf("\n");
                turn = 1;
            } else { //CPU turn
                CPUAction(players);
                turn = 0;
                printf("==\n");
                printf("\n");
            }

            //Verify health points
            if (players[0].healthPoints <= 0) {
                printf("%s has been vanquished!! MORTEM.\n", players[0].name);
                break; exit(0);
            }
            if (players[1].healthPoints <= 0) {
                printf("%s has fallen! Your victory is consecrated!\n", players[1].name);
                break; exit(0);
            }


            printf("%s defense points: %d \n", players[0].name, players[0].Defense);
            //Verify defense points every turn
            if (players[0].Defense > 10) {
                players[0].Defense = 10;
                printf("%s defense points: %d \n", players[0].name, players[0].Defense);
            }
            if (players[1].Defense > 10) {
                players[1].Defense = 10;
                printf("%d defense points: \n", players[1].name, players[0].Defense);
            }
    }


    return 0;
}