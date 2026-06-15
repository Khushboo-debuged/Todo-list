#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Task {
    int id;
    string title;
    string description;
    string status; // "Pending" or "Done"
};

const string FILE_NAME = "tasks.txt";

// ─── File I/O ────────────────────────────────────────────────────────────────

void saveTasks(const vector<Task>& tasks) {
    ofstream file(FILE_NAME);
    for (const auto& t : tasks) {
        file << t.id << "\n"
             << t.title << "\n"
             << t.description << "\n"
             << t.status << "\n"
             << "---\n";
    }
}

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file(FILE_NAME);
    if (!file.is_open()) return tasks;

    string line;
    while (getline(file, line)) {
        Task t;
        try {
            t.id = stoi(line);
        } catch (...) { break; }
        getline(file, t.title);
        getline(file, t.description);
        getline(file, t.status);
        getline(file, line); // separator "---"
        tasks.push_back(t);
    }
    return tasks;
}

int getNextId(const vector<Task>& tasks) {
    int maxId = 0;
    for (const auto& t : tasks)
        if (t.id > maxId) maxId = t.id;
    return maxId + 1;
}

// ─── Display ─────────────────────────────────────────────────────────────────

void printDivider() {
    cout << string(60, '-') << "\n";
}

void printHeader() {
    cout << "\n";
    printDivider();
    cout << "         ✅  C++ To-Do List Manager\n";
    printDivider();
}

void listTasks(const vector<Task>& tasks) {
    cout << "\n";
    printDivider();
    cout << left
         << setw(5)  << "ID"
         << setw(22) << "Title"
         << setw(22) << "Description"
         << setw(10) << "Status" << "\n";
    printDivider();

    if (tasks.empty()) {
        cout << "  No tasks found. Add one!\n";
    } else {
        for (const auto& t : tasks) {
            string shortTitle = t.title.length() > 20
                                ? t.title.substr(0, 17) + "..."
                                : t.title;
            string shortDesc  = t.description.length() > 20
                                ? t.description.substr(0, 17) + "..."
                                : t.description;
            cout << left
                 << setw(5)  << t.id
                 << setw(22) << shortTitle
                 << setw(22) << shortDesc
                 << setw(10) << t.status << "\n";
        }
    }
    printDivider();
}

// ─── CRUD Operations ─────────────────────────────────────────────────────────

void addTask(vector<Task>& tasks) {
    Task t;
    t.id = getNextId(tasks);
    t.status = "Pending";

    cin.ignore();
    cout << "  Enter title       : ";
    getline(cin, t.title);
    if (t.title.empty()) { cout << "  Title cannot be empty.\n"; return; }

    cout << "  Enter description : ";
    getline(cin, t.description);

    tasks.push_back(t);
    saveTasks(tasks);
    cout << "  ✔  Task #" << t.id << " added successfully!\n";
}

void readTask(const vector<Task>& tasks) {
    if (tasks.empty()) { cout << "  No tasks available.\n"; return; }

    int id;
    cout << "  Enter task ID to view: ";
    cin >> id;

    for (const auto& t : tasks) {
        if (t.id == id) {
            cout << "\n";
            printDivider();
            cout << "  ID          : " << t.id          << "\n"
                 << "  Title       : " << t.title       << "\n"
                 << "  Description : " << t.description << "\n"
                 << "  Status      : " << t.status      << "\n";
            printDivider();
            return;
        }
    }
    cout << "  ✘  Task #" << id << " not found.\n";
}

void updateTask(vector<Task>& tasks) {
    if (tasks.empty()) { cout << "  No tasks to update.\n"; return; }

    int id;
    cout << "  Enter task ID to update: ";
    cin >> id;
    cin.ignore();

    for (auto& t : tasks) {
        if (t.id == id) {
            cout << "  Current title       : " << t.title << "\n";
            cout << "  New title (Enter to keep): ";
            string input;
            getline(cin, input);
            if (!input.empty()) t.title = input;

            cout << "  Current description : " << t.description << "\n";
            cout << "  New description (Enter to keep): ";
            getline(cin, input);
            if (!input.empty()) t.description = input;

            cout << "  Current status      : " << t.status << "\n";
            cout << "  Toggle status? (y/n): ";
            char ch; cin >> ch;
            if (ch == 'y' || ch == 'Y')
                t.status = (t.status == "Pending") ? "Done" : "Pending";

            saveTasks(tasks);
            cout << "  ✔  Task #" << id << " updated successfully!\n";
            return;
        }
    }
    cout << "  ✘  Task #" << id << " not found.\n";
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) { cout << "  No tasks to delete.\n"; return; }

    int id;
    cout << "  Enter task ID to delete: ";
    cin >> id;

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            saveTasks(tasks);
            cout << "  ✔  Task #" << id << " deleted successfully!\n";
            return;
        }
    }
    cout << "  ✘  Task #" << id << " not found.\n";
}

// ─── Menu ────────────────────────────────────────────────────────────────────

void showMenu() {
    cout << "\n"
         << "  1. View All Tasks\n"
         << "  2. Add Task\n"
         << "  3. Read Task (by ID)\n"
         << "  4. Update Task\n"
         << "  5. Delete Task\n"
         << "  6. Exit\n"
         << "\n"
         << "  Choose an option: ";
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main() {
    vector<Task> tasks = loadTasks();
    printHeader();

    while (true) {
        showMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1: listTasks(tasks);   break;
            case 2: addTask(tasks);     break;
            case 3: readTask(tasks);    break;
            case 4: updateTask(tasks);  break;
            case 5: deleteTask(tasks);  break;
            case 6:
                cout << "  Goodbye! 👋\n\n";
                return 0;
            default:
                cout << "  Invalid option. Please choose 1-6.\n";
        }
    }
}
