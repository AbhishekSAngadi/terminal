#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Player structure
struct Player {
    int id;
    string name;
    string position;
    int age;
    int goals;
};

// Function prototypes
void addPlayer();
void displayPlayers();
void searchPlayer();
void updatePlayer();

const string filename = "players.txt";

int main() {
    int choice;

    do {
        cout << "\n===== Football Management System =====\n";
        cout << "1. Add Player\n";
        cout << "2. Display All Players\n";
        cout << "3. Search Player\n";
        cout << "4. Update Player Info\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPlayer(); break;
            case 2: displayPlayers(); break;
            case 3: searchPlayer(); break;
            case 4: updatePlayer(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Add a new player
void addPlayer() {
    Player p;
    cout << "\nEnter Player ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter Player Name: ";
    getline(cin, p.name);
    cout << "Enter Player Position: ";
    getline(cin, p.position);
    cout << "Enter Player Age: ";
    cin >> p.age;
    cout << "Enter Goals Scored: ";
    cin >> p.goals;

    ofstream file(filename, ios::app);
    file << p.id << "," << p.name << "," << p.position << "," << p.age << "," << p.goals << "\n";
    file.close();

    cout << "Player added successfully!\n";
}

// Display all players
void displayPlayers() {
    ifstream file(filename);
    if (!file) {
        cout << "No player data found.\n";
        return;
    }

    cout << "\nID\tName\tPosition\tAge\tGoals\n";
    cout << "----------------------------------------------\n";

    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find(",")) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        cout << tokens[0] << "\t" << tokens[1] << "\t" << tokens[2] << "\t" << tokens[3] << "\t" << tokens[4] << "\n";
    }

    file.close();
}

// Search a player by ID
void searchPlayer() {
    int searchId;
    cout << "\nEnter Player ID to search: ";
    cin >> searchId;

    ifstream file(filename);
    if (!file) {
        cout << "No player data found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find(",")) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        if (stoi(tokens[0]) == searchId) {
            cout << "\nPlayer Found:\n";
            cout << "ID: " << tokens[0] << "\n";
            cout << "Name: " << tokens[1] << "\n";
            cout << "Position: " << tokens[2] << "\n";
            cout << "Age: " << tokens[3] << "\n";
            cout << "Goals: " << tokens[4] << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Player not found.\n";

    file.close();
}

// Update player info
void updatePlayer() {
    int updateId;
    cout << "\nEnter Player ID to update: ";
    cin >> updateId;

    ifstream file(filename);
    if (!file) {
        cout << "No player data found.\n";
        return;
    }

    vector<Player> players;
    Player p;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find(",")) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        p.id = stoi(tokens[0]);
        p.name = tokens[1];
        p.position = tokens[2];
        p.age = stoi(tokens[3]);
        p.goals = stoi(tokens[4]);

        if (p.id == updateId) {
            found = true;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, p.name);
            cout << "Enter new Position: ";
            getline(cin, p.position);
            cout << "Enter new Age: ";
            cin >> p.age;
            cout << "Enter new Goals: ";
            cin >> p.goals;
        }

        players.push_back(p);
    }
    file.close();

    if (!found) {
        cout << "Player ID not found.\n";
        return;
    }

    ofstream outfile(filename);
    for (auto &pl : players) {
        outfile << pl.id << "," << pl.name << "," << pl.position << "," << pl.age << "," << pl.goals << "\n";
    }
    outfile.close();

    cout << "Player info updated successfully!\n";
}
