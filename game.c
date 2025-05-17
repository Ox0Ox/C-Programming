#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define BASE_MAX_HP 100
#define BASE_MAX_STAMINA 100
#define HIGH_SCORE_FILE "highscores.txt"

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
    int totalCoins;      // Lifetime coins (saved)
    int sessionCoins;    // Current run coins (not saved)
} Player;

typedef struct {
    char *name;
    int hp;
    int attackPower;
    int level;
} Enemy;

Player player;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

const char* getEnemyPrefix(int level) {
    if (level >= 50) return "Legendary ";
    if (level >= 30) return "Epic ";
    if (level >= 20) return "Elite ";
    if (level >= 10) return "Veteran ";
    return "";
}

void showHUD() {
    clearScreen();
    printf("=== Adventure Dungeon ===\n");
    printf("HP: %d/%d | Stamina: %d/%d | Score: %d (High: %d)\n", 
           player.hp, player.maxHp, player.stamina, player.maxStamina, 
           player.score, player.highScore);
    printf("Steps: %d | Attack: %d | Speed: %d | Coins: %d (This Run: %d)\n",
           player.steps, player.attackPower, player.speed, player.totalCoins, player.sessionCoins);
    printf("---------------------------\n");
}

void saveProgress() {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file) {
        fprintf(file, "%d %d %d %d %d %d\n", 
               player.highScore, 
               player.totalCoins,    // Now saving totalCoins instead of coins
               player.attackPower,
               player.speed,
               player.maxHp,
               player.maxStamina);
        fclose(file);
    } else {
        printf("Error saving game progress!\n");
    }
}

void loadProgress() {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file) {
        int items_read = fscanf(file, "%d %d %d %d %d %d", 
                              &player.highScore,
                              &player.totalCoins,    // Now loading totalCoins
                              &player.attackPower,
                              &player.speed,
                              &player.maxHp,
                              &player.maxStamina);
        fclose(file);
        
        if (items_read != 6 || player.maxHp < BASE_MAX_HP || player.maxStamina < BASE_MAX_STAMINA) {
            player.maxHp = BASE_MAX_HP;
            player.maxStamina = BASE_MAX_STAMINA;
        }
    } else {
        player.attackPower = 10;
        player.speed = 5;
        player.maxHp = BASE_MAX_HP;
        player.maxStamina = BASE_MAX_STAMINA;
        player.totalCoins = 0;
        player.highScore = 0;
    }
    player.sessionCoins = 0;  // Always start new session with 0
}

void initializeGame() {
    player.hp = player.maxHp;
    player.stamina = player.maxStamina;
    player.score = 0;
    player.steps = 0;
    player.sessionCoins = 0;  // Reset session coins
    srand((unsigned int)time(0));
    loadProgress();
    
    if (player.hp <= 0) {
        player.hp = player.maxHp;
    }
}

Enemy spawnEnemy() {
    int enemyType = rand() % 3;
    int level = ((player.score / 50) + (player.steps / 30)) / 2 + 1;
    
    Enemy enemy;
    enemy.level = level;

    // Exponential scaling for high levels
    int scaledLevel = level;
    if (level > 20) {
        scaledLevel = 20 + (level - 20) * 1.5;
    }

    if (enemyType == 0) {
        enemy.name = "Goblin";
        enemy.hp = 30 + (scaledLevel * 10);
        enemy.attackPower = 5 + (scaledLevel * 2);
    } else if (enemyType == 1) {
        enemy.name = "Skeleton Warrior";
        enemy.hp = 40 + (scaledLevel * 15);
        enemy.attackPower = 7 + (scaledLevel * 3);
    } else {
        enemy.name = "Dragon";
        enemy.hp = 60 + (scaledLevel * 20);
        enemy.attackPower = 10 + (scaledLevel * 5);
    }

    const char* prefix = getEnemyPrefix(level);
    printf("\n⚔️ A level %d %s%s appears! (%d HP)\n", 
           level, prefix, enemy.name, enemy.hp);
    return enemy;
}

void attackEnemy(Enemy *enemy) {
    int damage = player.attackPower;
    int attackChoice;
    
    do {
        printf("Choose your attack: (1) Fire (2) Sword (3) Magic: ");
        if (scanf("%d", &attackChoice) != 1) {
            while (getchar() != '\n'); 
            attackChoice = 0;
        }
    } while (attackChoice < 1 || attackChoice > 3);

    while (getchar() != '\n');

    switch (attackChoice) {
        case 1:
            damage += (strcmp(enemy->name, "Goblin") == 0) ? 15 : 0;
            break;
        case 2:
            damage += (strcmp(enemy->name, "Skeleton Warrior") == 0) ? 10 : 0;
            break;
        case 3:
            damage += (strcmp(enemy->name, "Dragon") == 0) ? 20 : 0;
            break;
    }

    enemy->hp -= damage;
    printf("You dealt %d damage to the %s%s!\n", 
           damage, getEnemyPrefix(enemy->level), enemy->name);
    
    if (enemy->hp <= 0) {
        int coinReward = 10 * enemy->level;
        printf("🔥 You defeated the level %d %s%s! (+%d coins)\n", 
               enemy->level, getEnemyPrefix(enemy->level), enemy->name, coinReward);
        player.score += 20 * enemy->level;
        player.sessionCoins += coinReward;
        player.totalCoins += coinReward;
        
        if (player.score > player.highScore) {
            player.highScore = player.score;
        }
    } else {
        if (enemy->level <= 0) enemy->level = 1;
        int minSpeedForLevel = (enemy->level - 1) * 10;
        int speedRange = 10;

        if (player.speed >= minSpeedForLevel + speedRange) {
            printf("You dodged the %s%s's attack!\n", 
                  getEnemyPrefix(enemy->level), enemy->name);
        } else if (player.speed > minSpeedForLevel) {
            int speedInRange = player.speed - minSpeedForLevel;
            int dodgeChance = (speedInRange * 100) / speedRange;
            
            if (rand() % 100 < dodgeChance) {
                printf("You dodged the %s%s's attack!\n", 
                      getEnemyPrefix(enemy->level), enemy->name);
            } else {
                player.hp -= enemy->attackPower;
                printf("The %s%s attacks! You lost %d HP!\n", 
                      getEnemyPrefix(enemy->level), enemy->name, enemy->attackPower);
            }
        } else {
            player.hp -= enemy->attackPower;
            printf("The %s%s attacks! You lost %d HP!\n", 
                  getEnemyPrefix(enemy->level), enemy->name, enemy->attackPower);
        }
    }
}

void garageMenu();
void mainMenu();

void movePlayer() {
    player.steps++;
    player.score += 1;
    
    // Stamina regeneration
    player.stamina += 2 + (player.speed / 5);
    if (player.stamina > player.maxStamina) player.stamina = player.maxStamina;

    // Random coin finding (25% chance per step)
    if (rand() % 4 == 0) {
        int coinsFound = 1 + (player.steps / 20);
        player.sessionCoins += coinsFound;
        player.totalCoins += coinsFound;
        printf("Found %d coins while exploring!\n", coinsFound);
    }

    if (player.steps % ((rand() % 3) + 3) == 0) {
        Enemy enemy = spawnEnemy();
        int choice;
        
        do {
            printf("1. Fight\n2. Run Away (%d stamina)\nChoose: ", 10 + (enemy.level * 5));
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                choice = 0;
            }
            while (getchar() != '\n');

            if (choice == 2) {
                int fleeCost = 10 + (enemy.level * 5);
                if (player.stamina >= fleeCost) {
                    printf("You ran away! (-%d stamina)\n", fleeCost);
                    player.stamina -= fleeCost;
                    break;
                } else {
                    printf("Need %d stamina to flee! You must fight!\n", fleeCost);
                    choice = 1;
                }
            }
            
            if (choice == 1) {
                while (enemy.hp > 0 && player.hp > 0) {
                    attackEnemy(&enemy);
                    if (player.hp <= 0) {
                        printf("You were defeated by the %s%s!\n", 
                              getEnemyPrefix(enemy.level), enemy.name);
                        saveProgress();
                        return;
                    }
                }
            }
        } while (enemy.hp > 0 && player.hp > 0);
    }
    
    saveProgress();
}

void garageMenu() {
    int choice;
    while (1) {
        int attackCost = 50 + (player.attackPower * 2);
        int speedCost = 30 + (player.speed * 3);
        int hpCost = 40 + (player.maxHp / 2);
        int staminaCost = 35 + (player.maxStamina / 3);
        
        showHUD();
        printf("=== Garage ===\n");
        printf("Available Coins (This Run): %d\n\n", player.sessionCoins);
        
        printf("Current Stats:\n");
        printf("• Attack Power: %d (Next +5: %d coins)\n", player.attackPower, attackCost);
        printf("• Speed: %d (Next +3: %d coins)\n", player.speed, speedCost);
        printf("• Max HP: %d (Next +20: %d coins)\n", player.maxHp, hpCost);
        printf("• Max Stamina: %d (Next +15: %d coins)\n\n", player.maxStamina, staminaCost);
        
        printf("Upgrade Options:\n");
        printf("1. Increase Attack Power (+5)       - %d coins\n", attackCost);
        printf("2. Increase Speed (+3)             - %d coins\n", speedCost);
        printf("3. Increase Max HP (+20)           - %d coins\n", hpCost);
        printf("4. Increase Max Stamina (+15)      - %d coins\n", staminaCost);
        printf("5. Return to Main Menu\n\n");
        
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                if (player.sessionCoins >= attackCost) {
                    player.attackPower += 5;
                    player.sessionCoins -= attackCost;
                    printf("\nAttack Power increased to %d!", player.attackPower);
                } else {
                    printf("\nNot enough coins! Need %d, you have %d.", attackCost, player.sessionCoins);
                }
                break;
            case 2:
                if (player.sessionCoins >= speedCost) {
                    player.speed += 3;
                    player.sessionCoins -= speedCost;
                    printf("\nSpeed increased to %d!", player.speed);
                } else {
                    printf("\nNot enough coins! Need %d, you have %d.", speedCost, player.sessionCoins);
                }
                break;
            case 3:
                if (player.sessionCoins >= hpCost) {
                    player.maxHp += 20;
                    player.hp = player.maxHp;
                    player.sessionCoins -= hpCost;
                    printf("\nMax HP increased to %d! You've been fully healed!", player.maxHp);
                } else {
                    printf("\nNot enough coins! Need %d, you have %d.", hpCost, player.sessionCoins);
                }
                break;
            case 4:
                if (player.sessionCoins >= staminaCost) {
                    player.maxStamina += 15;
                    player.stamina = player.maxStamina;
                    player.sessionCoins -= staminaCost;
                    printf("\nMax Stamina increased to %d! Stamina fully restored!", player.maxStamina);
                } else {
                    printf("\nNot enough coins! Need %d, you have %d.", staminaCost, player.sessionCoins);
                }
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice!");
        }
        
        printf("\n\nPress Enter to continue...");
        while (getchar() != '\n');
    }
}

void mainMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("=== Main Menu ===\n");
        printf("Current High Score: %d\n", player.highScore);
        printf("Lifetime Coins: %d\n", player.totalCoins);
        printf("1. Play Game\n2. Upgrades\n3. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                initializeGame();
                while (player.hp > 0) {
                    showHUD();
                    printf("Press any key to move (Q to quit)...\n");
                    int input = _getch();
                    if (input == 'Q' || input == 'q') break;
                    
                    movePlayer();
                }
                printf("Game Over! Final Score: %d\n", player.score);
                printf("Coins earned this run: %d\n", player.sessionCoins);
                printf("Press Enter to continue...");
                while (getchar() != '\n');
                break;
            }
            case 2:
                garageMenu();
                break;
            case 3:
                saveProgress();
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    initializeGame();
    mainMenu();
    return 0;
}