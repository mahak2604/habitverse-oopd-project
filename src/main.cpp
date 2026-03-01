#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/* ========================= ENTITY ========================= */

class Entity {
protected:
    int points;
    int darknessLevel;
    int progressLevel;

public:
    Entity(int p = 0, int d = 0, int pr = 0)
        : points(p), darknessLevel(d), progressLevel(pr) {}

    void setPoints(int p) { points = p; }
    void setDarknessLevel(int d) { darknessLevel = d; }
    void setProgressLevel(int p) { progressLevel = p; }

    int getPoints() { return points; }
    int getDarknessLevel() { return darknessLevel; }
    int getProgressLevel() { return progressLevel; }

    void increasePoints(int amount) { points += amount; }

    void increaseDarknessLevel() {
        darknessLevel += 5;
        displayDarknessChangeMessage();
    }

    void decreaseDarknessLevel() {
        if (darknessLevel > 0)
            darknessLevel -= 5;
        displayDarknessChangeMessage();
    }

    void increaseProgressLevel() {
        progressLevel += 5;
        displayProgressChangeMessage();
    }

    void decreaseProgressLevel() {
        if (progressLevel > 0)
            progressLevel -= 5;
        displayProgressChangeMessage();
    }

    virtual void displayMessage() = 0;
    virtual void displayProgressChangeMessage() = 0;
    virtual void displayDarknessChangeMessage() = 0;
};

/* ========================= GUARDIAN ========================= */

class Guardian : public Entity {
public:
    Guardian(int p = 0, int d = 0, int pr = 0)
        : Entity(p, d, pr) {}

    void displayMessage() override {
        if (progressLevel > darknessLevel && progressLevel > 50) {
            cout << "Guardian: Well done! Your universe is flourishing under your positive habits!" << endl;
        }
        else if (progressLevel < darknessLevel) {
            cout << "Guardian: I sense the darkness growing. Please increase your progress level!" << endl;
        }
        else if (progressLevel == darknessLevel) {
            cout << "Guardian: The balance is precarious. Focus on positive habits to tip the scales." << endl;
        }

        if (darknessLevel > 75 && progressLevel > 75 && darknessLevel > progressLevel) {
            cout << "Guardian: DANGER! The VoidBorn is preparing to attack!" << endl;
        }
    }

    void displayProgressChangeMessage() override {
        if (progressLevel % 25 == 0) {
            cout << "Guardian: Progress level now " << progressLevel << endl;
        }
    }

    void displayDarknessChangeMessage() override {
        if (darknessLevel % 25 == 0) {
            cout << "Guardian: Darkness level now " << darknessLevel << endl;
        }
    }
};

/* ========================= VOIDBORN ========================= */

class VoidBorn : public Entity {
public:
    VoidBorn(int p = 0, int d = 0, int pr = 0)
        : Entity(p, d, pr) {}

    void displayMessage() override {
        if (darknessLevel > progressLevel && darknessLevel > 50) {
            cout << "VoidBorn: Your darkness feeds me..." << endl;
        }
        else if (darknessLevel < progressLevel) {
            cout << "VoidBorn: Your progress disappoints me." << endl;
        }
        else {
            cout << "VoidBorn: Balance wavers..." << endl;
        }
    }

    void displayProgressChangeMessage() override {}
    void displayDarknessChangeMessage() override {}

    void attemptAttack() {
        if (darknessLevel > 75 && progressLevel > 75 && darknessLevel > progressLevel) {
            cout << "*** VOID ATTACK INITIATED ***" << endl;
            points = 0;
        }
    }
};

/* ========================= HABIT ========================= */

class Habit {
private:
    string name;
    int isPositive;
    int completionStatus[31];
    int currentStreak;
    int maxStreak;

public:
    Habit(string n = "", int positive = 0)
        : name(n), isPositive(positive), currentStreak(0), maxStreak(0) {
        for (int i = 0; i < 31; i++)
            completionStatus[i] = 0;
    }

    string getName() { return name; }
    int getIsPositive() { return isPositive; }
    int getCurrentStreak() { return currentStreak; }
    int getMaxStreak() { return maxStreak; }

    void trackCompletion(int day, int completed) {
        completionStatus[day] = completed;

        if (completed) {
            currentStreak++;
            if (currentStreak > maxStreak)
                maxStreak = currentStreak;
        }
        else {
            currentStreak = 0;
        }
    }

    int wasCompletedOnDay(int day) {
        return completionStatus[day];
    }
};

/* ========================= ACHIEVEMENT ========================= */

class Achievement {
private:
    string name;
    string description;
    int pointValue;
    int earned;

public:
    Achievement(string n = "", string d = "", int p = 0)
        : name(n), description(d), pointValue(p), earned(0) {}

    string getName() { return name; }
    string getDescription() { return description; }
    int getPointValue() { return pointValue; }
    int isEarned() { return earned; }
    void setEarned(int e) { earned = e; }
};

/* ========================= UNIVERSE ========================= */

class Universe {
private:
    Guardian guardian;
    VoidBorn voidBorn;
    int universeState;

public:
    Universe(Guardian g, VoidBorn v)
        : guardian(g), voidBorn(v), universeState(0) {}

    void updateState() {
        int progress = guardian.getProgressLevel();
        int darkness = guardian.getDarknessLevel();

        if (progress > darkness + 20)
            universeState = 1;
        else if (darkness > progress + 20)
            universeState = -1;
        else
            universeState = 0;
    }

    void displayMessage() {
        updateState();
        cout << "\n==== UNIVERSE STATUS ====" << endl;
        cout << "Progress Level: " << guardian.getProgressLevel() << endl;
        cout << "Darkness Level: " << guardian.getDarknessLevel() << endl;
        cout << "Points: " << guardian.getPoints() << endl;

        if (universeState > 0)
            cout << "Universe: Light is strong." << endl;
        else if (universeState < 0)
            cout << "Universe: Darkness rises." << endl;
        else
            cout << "Universe: Balance exists." << endl;

        guardian.displayMessage();
        voidBorn.displayMessage();
        cout << "========================\n" << endl;
    }

    void checkForAttack() {
        voidBorn.attemptAttack();
    }

    Guardian& getGuardian() { return guardian; }
    VoidBorn& getVoidBorn() { return voidBorn; }
};

/* ========================= MAIN ========================= */

int main() {
    cout << "Welcome to Habitverse!" << endl;

    string userName;
    cout << "Enter your name: ";
    getline(cin, userName);

    Guardian g;
    VoidBorn v;
    Universe universe(g, v);

    cout << "Program initialized successfully." << endl;

    return 0;
}
