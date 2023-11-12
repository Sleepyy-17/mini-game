#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <ctime>
using namespace std;

class Weapon {
private:
    string name_;
    int damage_;
    float critChance_;

public:
    Weapon(const string &name, int damage, float critChance): name_(name), damage_(damage), critChance_(critChance) { }

    [[nodiscard]] const string& getName() const {
        return name_;
    }

    [[nodiscard]] int getDamage() const {
        if (static_cast<float >(rand()) / RAND_MAX < critChance_) {
            cout << "Critical hit!\n";

            return damage_ * 2;
        }
        return damage_;
    }

    void display() const {
        cout << "Weapon: " << name_ << ", damage: " << damage_ << endl;
    }
};

class Character {
private:
    string name_;
    int life_;
    Weapon weapon_;

public:
    Character(const string &name, int life, Weapon weapon): name_(name), life_(life), weapon_(weapon) { }

    [[nodiscard]] const string& getName() const {
        return name_;
    }

    [[nodiscard]] const Weapon& getWeapon() const {
        return weapon_;
    }

    void receiveDamage(int damage) {
        life_ -= damage;

        if (life_ < 0) {
            life_ = 0;
        }
    }

    [[nodiscard]] bool isAlive() const {
        return life_ > 0;
    }

    void attack(Character &target) {
        int damage = weapon_.getDamage();
        target.receiveDamage(damage);

        cout << name_ << " attacks " << target.name_ << " and deals " << damage << " damage." << endl;
    }

    void display() const {
        cout << "Name: " << name_ << ", health: " << life_ << endl;
        weapon_.display();
    }
};


int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(std::time(0)));

    Weapon sword("Sword", 20, 0.1);
    Weapon axe("Axe", 30, 0.2);

    Character player("Player", 100, sword);
    Character enemy("Enemy", 80, axe);

    int turn = 1;
    int playerCrits = 0;
    int enemyCrits = 0;

    cout << "----- Battle Starts -----\n";

    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n--- Turn " << turn << " ---\n";
        player.attack(enemy);

        if (!enemy.isAlive()) {
            cout << "Enemy defeated! " << player.getName() << " wins!\n";
            break;
        }

        enemy.attack(player);

        if (!player.isAlive()) {
            cout << player.getName() << " is defeated! Enemy wins!\n";
            break;
        }

        if (player.getWeapon().getDamage() == sword.getDamage() * 2) {
            playerCrits++;
        }
        if (enemy.getWeapon().getDamage() == axe.getDamage() * 2) {
            enemyCrits++;
        }

        turn++;
    }

    cout << "\n----- Battle Stats -----\n";
    cout << "Total Turns: " << turn << "\n";
    cout << "Player Critical Hits: " << playerCrits << "\n";
    cout << "Enemy Critical Hits: " << enemyCrits << "\n";

    return 0;
}
