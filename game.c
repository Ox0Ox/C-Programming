#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include <conio.h> 

#define BASE_MAX_HP 100
#define BASE_MAX_STAMINA 100
#define HIGH_SCORE_FILE "best_score.bin" 

// Player structure
typedef struct {
    int hp;
    int maxHp;
    int stamina;
    int maxStamina;
    int score;
    int highScore; 
    int steps;
    int attackPower;
    int speed;
    int totalCoins;   
    int sessionCoins; 
} Player;

// Enemy structure
typedef struct {
    char *name; 
    const char *baseName; 
    int hp;
    int attackPower;
    int level;
} Enemy;

// Template for creating enemy types
typedef struct {
    const char *baseName;
    int baseHp;
    int baseAttack;
    int hpScale;
    int attackScale;
} EnemyTemplate;

// Structure for saving the single best game state/high score
typedef struct {
    int score;          
    int totalCoins;     
    int attackPower;    
    int speed;          
    int maxHp;          
    int maxStamina;     
} BestScoreEntry;

// Function pointer type for different attack implementations
typedef void (*AttackHandler)(Enemy *enemy, int *damage);

Player player; 
EnemyTemplate *enemyTemplates = NULL;
int numEnemyTypes = 0;

BestScoreEntry bestScoreEntry;       
int bestScoreEntryExists = 0;    

// Clears the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Seeds the standard C random number generator
void seedRandomizer(unsigned int seed) {
    if (seed == 0) {
        srand((unsigned int)time(NULL)); // Seed with current time if seed is 0
    } else {
        srand(seed); // Seed with the provided value
    }
}

// Generates a random integer between 0 and n-1 using standard rand()
int random_int(int n) {
    if (n <= 0) return 0;
    return rand() % n; // Uses standard library rand()
}

// Returns a prefix for the enemy's name based on its level
const char* getEnemyPrefix(int level) {
    if (level >= 50) return "Legendary ";
    if (level >= 30) return "Epic ";
    if (level >= 20) return "Elite ";
    if (level >= 10) return "Veteran ";
    return "";
}

// Displays the Heads-Up Display (HUD) during gameplay
void showHUD() {
    clearScreen();
    printf("=== Adventure Dungeon ===\n");
    printf("HP: %d/%d | Stamina: %d/%d | Score: %d (High: %d)\n",
           player.hp, player.maxHp, player.stamina, player.maxStamina,
           player.score, player.highScore);
    printf("Steps: %d | Attack: %d | Speed: %d | Coins: %d (Run Coins: %d)\n",
           player.steps, player.attackPower, player.speed, player.totalCoins, player.sessionCoins);
    printf("---------------------------\n");
}

// Saves the single best score entry to a binary file
void saveBestScore() {
    FILE *file = fopen(HIGH_SCORE_FILE, "wb");
    if (file) {
        fwrite(&bestScoreEntryExists, sizeof(int), 1, file);
        if (bestScoreEntryExists) {
            fwrite(&bestScoreEntry, sizeof(BestScoreEntry), 1, file);
        }
        fclose(file);
    } else {
        printf("Error saving best score to %s!\n", HIGH_SCORE_FILE);
    }
}

// Loads the single best score entry and populates player's persistent stats
void loadBestScore() {
    FILE *file = fopen(HIGH_SCORE_FILE, "rb");
    if (file) {
        if (fread(&bestScoreEntryExists, sizeof(int), 1, file) != 1) {
            bestScoreEntryExists = 0;
        }
        if (bestScoreEntryExists) {
            if (fread(&bestScoreEntry, sizeof(BestScoreEntry), 1, file) != 1) {
                printf("Warning: Could not read best score entry from %s.\n", HIGH_SCORE_FILE);
                bestScoreEntryExists = 0; 
            }
        }
        fclose(file);

        if (bestScoreEntryExists) {
            player.totalCoins = bestScoreEntry.totalCoins;
            player.attackPower = bestScoreEntry.attackPower;
            player.speed = bestScoreEntry.speed;
            player.maxHp = bestScoreEntry.maxHp;
            player.maxStamina = bestScoreEntry.maxStamina;
            player.highScore = bestScoreEntry.score;

            if (player.maxHp < BASE_MAX_HP) player.maxHp = BASE_MAX_HP;
            if (player.maxStamina < BASE_MAX_STAMINA) player.maxStamina = BASE_MAX_STAMINA;
            if (player.attackPower < 10) player.attackPower = 10;
            if (player.speed < 5) player.speed = 5;
        } else {
            player.attackPower = 10;
            player.speed = 5;
            player.maxHp = BASE_MAX_HP;
            player.maxStamina = BASE_MAX_STAMINA;
            player.totalCoins = 0;
            player.highScore = 0;
        }
    } else {
        player.attackPower = 10;
        player.speed = 5;
        player.maxHp = BASE_MAX_HP;
        player.maxStamina = BASE_MAX_STAMINA;
        player.totalCoins = 0;
        player.highScore = 0;
        bestScoreEntryExists = 0;
    }
    player.sessionCoins = 0; 
}

// Initializes the enemy templates
void initializeEnemyTemplates() {
    numEnemyTypes = 3;
    enemyTemplates = (EnemyTemplate *)calloc(numEnemyTypes, sizeof(EnemyTemplate));
    if (!enemyTemplates) {
        perror("Memory allocation failed for enemy templates");
        exit(EXIT_FAILURE);
    }
    enemyTemplates[0] = (EnemyTemplate){"Goblin", 30, 5, 10, 2};
    enemyTemplates[1] = (EnemyTemplate){"Skeleton Warrior", 40, 7, 15, 3};
    enemyTemplates[2] = (EnemyTemplate){"Dragon", 60, 10, 20, 5};
}

// Cleans up dynamically allocated memory
void cleanupGame() {
    if (enemyTemplates) {
        free(enemyTemplates);
        enemyTemplates = NULL;
    }
}

// Initializes or resets game state for a new run using loaded persistent stats
void initializeGame() {
    player.hp = player.maxHp;
    player.stamina = player.maxStamina;
    player.score = 0;
    player.steps = 0;
    player.sessionCoins = 0; 

    if (player.hp <= 0 || player.hp > player.maxHp) {
        player.hp = player.maxHp;
    }
    if (!enemyTemplates) {
        initializeEnemyTemplates();
    }
}

// Spawns an enemy
Enemy spawnEnemy() {
    int enemyTypeIdx = random_int(numEnemyTypes);
    const EnemyTemplate* chosenTemplate = &enemyTemplates[enemyTypeIdx];
    int level = ((player.score / 50) + (player.steps / 30)) / 2 + 1;
    if (level < 1) level = 1;
    int scaledLevel = level > 20 ? 20 + (int)((level - 20) * 1.5) : level;

    Enemy enemy;
    enemy.level = level;
    enemy.baseName = chosenTemplate->baseName; 
    
    const char* prefix = getEnemyPrefix(level);
    size_t prefixLen = strlen(prefix);
    size_t baseNameLen = strlen(chosenTemplate->baseName);

    enemy.name = (char *)calloc(prefixLen + baseNameLen + 1, sizeof(char));
    if (!enemy.name) {
        perror("Memory allocation failed for enemy name");
        exit(EXIT_FAILURE);
    }
    strcpy(enemy.name, prefix);
    strcat(enemy.name, chosenTemplate->baseName);

    enemy.hp = chosenTemplate->baseHp + (scaledLevel * chosenTemplate->hpScale);
    enemy.attackPower = chosenTemplate->baseAttack + (scaledLevel * chosenTemplate->attackScale);

    printf("\nA level %d %s appears! (%d HP)\n", level, enemy.name, enemy.hp);
    return enemy;
}

// --- Attack Handler Implementations ---
void fireAttack(Enemy *enemy, int *damage) {
    if (strcmp(enemy->baseName, "Goblin") == 0) { *damage += 15; printf("The Goblin sizzles!\n"); }
}
void swordAttack(Enemy *enemy, int *damage) {
    if (strcmp(enemy->baseName, "Skeleton Warrior") == 0) { *damage += 10; printf("The Skeleton Warrior rattles!\n"); }
}
void magicAttack(Enemy *enemy, int *damage) {
    if (strcmp(enemy->baseName, "Dragon") == 0) { *damage += 20; printf("The Dragon roars!\n"); }
}

// Handles player's attack on an enemy, including dynamic dodging
void attackEnemy(Enemy *enemy) {
    if (!enemy) return;
    AttackHandler attacks[] = {fireAttack, swordAttack, magicAttack};
    const char *attackNames[] = {"Fire", "Sword", "Magic"};
    int attackChoice;

    do {
        printf("Choose attack: (1) %s (2) %s (3) %s: ", attackNames[0], attackNames[1], attackNames[2]);
        if (scanf("%d", &attackChoice) != 1) {
            while (getchar() != '\n'); attackChoice = 0; printf("Invalid. (1-3)\n");
        } else { while (getchar() != '\n'); }
    } while (attackChoice < 1 || attackChoice > 3);

    int damage = player.attackPower;
    attacks[attackChoice - 1](enemy, &damage);
    enemy->hp -= damage;
    printf("You dealt %d damage to %s with %s!\n", damage, enemy->name, attackNames[attackChoice - 1]);

    if (enemy->hp <= 0) {
        int coinReward = 10 * enemy->level;
        printf("You defeated the Lvl %d %s! (+%d Run Coins)\n", enemy->level, enemy->name, coinReward);
        player.score += 20 * enemy->level;
        player.sessionCoins += coinReward;

        if (player.score > player.highScore) { 
            player.highScore = player.score; 
            printf("New High Score for this run: %d!\n", player.highScore);
        }
    } else { 
        if (enemy->level <= 0) enemy->level = 1;
        int minSpeedForLevel = (enemy->level - 1) * 10;
        
        int currentSpeedRange = 10; 
        if (strcmp(enemy->baseName, "Dragon") == 0) {
            currentSpeedRange = 18; 
        } else if (strcmp(enemy->baseName, "Skeleton Warrior") == 0) {
            currentSpeedRange = 13; 
        }

        if (player.speed >= minSpeedForLevel + currentSpeedRange) {
            printf("You swiftly DODGED the %s's attack!\n", enemy->name);
        } else if (player.speed > minSpeedForLevel) {
            int speedInRange = player.speed - minSpeedForLevel;
            int dodgeChance = (currentSpeedRange > 0) ? ((speedInRange * 100) / currentSpeedRange) : 0;
            if (dodgeChance < 0) dodgeChance = 0; 
            if (dodgeChance > 95) dodgeChance = 95;

            if (random_int(100) < dodgeChance) {
                printf("You nimbly DODGED the %s's attack!\n", enemy->name);
            } else {
                player.hp -= enemy->attackPower;
                printf("The %s attacks! You lost %d HP!\n", enemy->name, enemy->attackPower);
            }
        } else {
            player.hp -= enemy->attackPower;
            printf("The %s attacks! You lost %d HP!\n", enemy->name, enemy->attackPower);
        }
    }
}

// Updates the single best score entry if current run is better, and saves all persistent data.
void updateAndSaveBestScore() {
    player.totalCoins += player.sessionCoins; 
    player.sessionCoins = 0; 

    if (!bestScoreEntryExists || player.score > bestScoreEntry.score) {
        bestScoreEntry.score = player.score; 
        player.highScore = player.score;     
        printf("Your new all-time best score is %d!\n", player.highScore);
        bestScoreEntry.totalCoins = player.totalCoins;
        bestScoreEntry.attackPower = player.attackPower;
        bestScoreEntry.speed = player.speed;
        bestScoreEntry.maxHp = player.maxHp;
        bestScoreEntry.maxStamina = player.maxStamina;
        bestScoreEntryExists = 1; 
    } else if (player.score == bestScoreEntry.score && player.totalCoins > bestScoreEntry.totalCoins) {
        bestScoreEntry.totalCoins = player.totalCoins;
        bestScoreEntry.attackPower = player.attackPower; 
        bestScoreEntry.speed = player.speed;
        bestScoreEntry.maxHp = player.maxHp;
        bestScoreEntry.maxStamina = player.maxStamina;
        printf("Stats for your high score of %d updated (more coins).\n", player.highScore);
    } else {
        bestScoreEntry.totalCoins = player.totalCoins;
        bestScoreEntry.attackPower = player.attackPower;
        bestScoreEntry.speed = player.speed;
        bestScoreEntry.maxHp = player.maxHp;
        bestScoreEntry.maxStamina = player.maxStamina;
    }
    
    if (!bestScoreEntryExists) {
        bestScoreEntry.score = player.score; 
        bestScoreEntry.totalCoins = player.totalCoins;
        bestScoreEntry.attackPower = player.attackPower;
        bestScoreEntry.speed = player.speed;
        bestScoreEntry.maxHp = player.maxHp;
        bestScoreEntry.maxStamina = player.maxStamina;
        bestScoreEntryExists = 1;
        if (player.score > player.highScore) player.highScore = player.score;
    }
    
    saveBestScore(); 
}


// Garage for upgrades
void garageMenu() {
    int choice;
    while (1) {
        int attackCost = 50 + (player.attackPower * 2);
        int speedCost = 30 + (player.speed * 3);
        int hpCost = 40 + (player.maxHp / 2);
        int staminaCost = 35 + (player.maxStamina / 3);

        clearScreen();
        printf("=== Garage (Upgrades) ===\n");
        printf("Available Coins: %d\n\n", player.totalCoins);

        printf("Current Persistent Stats:\n");
        printf("  Max HP: %d, Max Stamina: %d\n", player.maxHp, player.maxStamina);
        printf("  Attack: %d, Speed: %d\n\n", player.attackPower, player.speed);
        
        printf("Upgrade Options (Permanent):\n");
        printf("1. Attack Power (+5)      - %d Coins\n", attackCost);
        printf("2. Speed (+3)             - %d Coins\n", speedCost);
        printf("3. Max HP (+20)           - %d Coins\n", hpCost);
        printf("4. Max Stamina (+15)      - %d Coins\n", staminaCost);
        printf("5. Return to Main Menu\n\nChoice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); printf("Invalid input. Please enter a number.\nPress Enter to continue..."); while (getchar() != '\n'); continue;
        }
        while (getchar() != '\n');

        int purchaseMade = 0;
        switch (choice) {
            case 1:
                if (player.totalCoins >= attackCost) { player.attackPower += 5; player.totalCoins -= attackCost; printf("Attack Power permanently increased!\n"); purchaseMade = 1; }
                else { printf("Not enough Coins!\n"); } break;
            case 2:
                if (player.totalCoins >= speedCost) { player.speed += 3; player.totalCoins -= speedCost; printf("Speed permanently increased!\n"); purchaseMade = 1; }
                else { printf("Not enough Coins!\n"); } break;
            case 3:
                if (player.totalCoins >= hpCost) { player.maxHp += 20; player.hp = player.maxHp; player.totalCoins -= hpCost; printf("Max HP permanently increased! You've been healed.\n"); purchaseMade = 1; }
                else { printf("Not enough Coins!\n"); } break;
            case 4:
                if (player.totalCoins >= staminaCost) { player.maxStamina += 15; player.stamina = player.maxStamina; player.totalCoins -= staminaCost; printf("Max Stamina permanently increased! Stamina restored.\n"); purchaseMade = 1; }
                else { printf("Not enough Coins!\n"); } break;
            case 5: 
                if (purchaseMade) {
                    if (!bestScoreEntryExists) { 
                        bestScoreEntry.score = player.highScore; 
                        bestScoreEntryExists = 1;
                    }
                    bestScoreEntry.totalCoins = player.totalCoins;
                    bestScoreEntry.attackPower = player.attackPower;
                    bestScoreEntry.speed = player.speed;
                    bestScoreEntry.maxHp = player.maxHp;
                    bestScoreEntry.maxStamina = player.maxStamina;
                    saveBestScore(); 
                }
                return;
            default: printf("Invalid choice.\n");
        }
        printf("Press Enter to continue..."); while (getchar() != '\n');
    }
}

// Player movement and encounters
void movePlayer() {
    player.steps++;
    player.score++;
    player.stamina += 2 + (player.speed / 5);
    if (player.stamina > player.maxStamina) player.stamina = player.maxStamina;

    if (random_int(4) == 0) {
        int coinsFound = 1 + (player.steps / 20);
        player.sessionCoins += coinsFound;
        printf("Found %d Run Coins! (Current Run: %d)\n", coinsFound, player.sessionCoins);
    }

    if (player.steps % (random_int(3) + 3) == 0) {
        Enemy enemy = spawnEnemy();
        int choice, fleeCost = 10 + (enemy.level * 5);
        do {
            printf("1. Fight\n2. Run Away (%d stamina)\nChoose: ", fleeCost);
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n'); choice = 0; printf("Invalid. 1 or 2.\n");
            } else { while (getchar() != '\n'); }

            if (choice == 2) {
                if (player.stamina >= fleeCost) {
                    printf("Ran away! (-%d stamina)\n", fleeCost); player.stamina -= fleeCost; free(enemy.name); enemy.name = NULL; return;
                } else { printf("Need %d stamina. Must fight!\n", fleeCost); choice = 1; }
            }
            if (choice == 1) {
                while (enemy.hp > 0 && player.hp > 0) {
                    attackEnemy(&enemy);
                    if (player.hp <= 0) { printf("You were defeated by %s!\n", enemy.name); free(enemy.name); enemy.name = NULL; return; }
                    if (enemy.hp <= 0) { free(enemy.name); enemy.name = NULL; break; } 
                }
            } else if (choice != 2) printf("Invalid choice.\n");
        } while (enemy.hp > 0 && player.hp > 0 && choice != 2);
        
        if (enemy.name != NULL) { 
             free(enemy.name);
             enemy.name = NULL;
        }
    }
}

// Game states
typedef enum {
    STATE_MAIN_MENU, STATE_PLAYING, STATE_GARAGE,
    STATE_GAME_OVER, STATE_EXITING
} GameState;

// Main game loop
void runGame() {
    GameState currentState = STATE_MAIN_MENU;
    seedRandomizer(0); // Seed standard randomizer
    loadBestScore();   

    while (currentState != STATE_EXITING) {
        switch (currentState) {
            case STATE_MAIN_MENU:
                clearScreen();
                printf("=== Main Menu ===\n");
                printf("High Score: %d\n", player.highScore);
                printf("Coins: %d\n", player.totalCoins);
                printf("---------------------------\n");
                printf("Player Stats (Persistent):\n");
                printf("  Max HP: %d, Max Stamina: %d\n", player.maxHp, player.maxStamina);
                printf("  Attack: %d, Speed: %d\n", player.attackPower, player.speed);
                printf("---------------------------\n");
                printf("1. Play Game\n2. Upgrades (Garage)\n3. Exit\nChoose: ");
                int menuChoice;
                if (scanf("%d", &menuChoice) != 1) {
                    while (getchar() != '\n'); printf("Invalid input.\nPress Enter to continue..."); while (getchar() != '\n'); continue;
                }
                while (getchar() != '\n');
                if (menuChoice == 1) { initializeGame(); currentState = STATE_PLAYING; }
                else if (menuChoice == 2) { currentState = STATE_GARAGE; }
                else if (menuChoice == 3) { currentState = STATE_EXITING; }
                else { printf("Invalid choice.\nPress Enter to continue..."); while (getchar() != '\n'); }
                break;

            case STATE_PLAYING:
                showHUD();
                printf("Any key to move (Q to quit)...\n");
                int input = _getch();
                if (input == 'Q' || input == 'q') { printf("\nQuitting current run...\n"); currentState = STATE_GAME_OVER; }
                else { movePlayer(); if (player.hp <= 0) currentState = STATE_GAME_OVER; }
                break;

            case STATE_GARAGE:
                garageMenu(); 
                currentState = STATE_MAIN_MENU; 
                break;

            case STATE_GAME_OVER:
                clearScreen();
                printf(player.hp <= 0 ? "*** GAME OVER! ***\n" : "--- Run Ended ---\n");
                printf("Final Score this run: %d\n", player.score);
                printf("Run Coins earned: %d\n", player.sessionCoins);
                
                updateAndSaveBestScore(); 
                
                printf("Total Coins: %d\n", player.totalCoins); 
                printf("\nYour All-Time High Score: %d\n", player.highScore); 

                printf("\nPress Enter to return to Main Menu...");
                while (getchar() != '\n');
                
                currentState = STATE_MAIN_MENU;
                break;

            case STATE_EXITING: 
                break; 
        }
    }
    printf("Exiting Adventure Dungeon. Thanks for playing!\n");
    cleanupGame();
}

int main() {
    runGame();
    return 0;
}
