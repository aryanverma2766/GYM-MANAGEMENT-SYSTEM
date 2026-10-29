#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

class MembershipPlan {
public:
    static string name(int choice) {
        if (choice == 1) return "Monthly";
        if (choice == 2) return "Quarterly";
        return "Yearly";
    }
    static double price(int choice) {
        if (choice == 1) return 1000;
        if (choice == 2) return 2700;
        return 10000;
    }
    static void show() {
        cout << "\n--- Membership Plans ---\n";
        cout << "1. Monthly   - Rs. 1000\n";
        cout << "2. Quarterly - Rs. 2700\n";
        cout << "3. Yearly    - Rs. 10000\n";
    }
};

class Person {
protected:
    string name_;
    int age_;
public:
    Person(string name, int age) : name_(name), age_(age) {}
    virtual ~Person() = default;
    virtual void display() const {
        cout << "Name: " << name_ << " | Age: " << age_;
    }
};

class Member : public Person {
    int id_;
    int plan_;
public:
    Member(int id, string name, int age, int plan)
        : Person(name, age), id_(id), plan_(plan) {}
    int id() const { return id_; }
    double fee() const { return MembershipPlan::price(plan_); }
    void display() const override {
        cout << "ID: " << id_ << " | ";
        Person::display();
        cout << " | Plan: " << MembershipPlan::name(plan_)
             << " | Fee: Rs. " << fixed << setprecision(2) << fee() << '\n';
    }
    string serialize() const {
        return to_string(id_) + "|" + name_ + "|" + to_string(age_) + "|" + to_string(plan_);
    }
};

class GymManagementSystem {
    vector<Member> members_;
    const string filename_ = "gym_members.txt";

    static int readInt(const string& prompt, int minValue, int maxValue) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= minValue && value <= maxValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    bool exists(int id) const {
        return any_of(members_.begin(), members_.end(), [id](const Member& m) { return m.id() == id; });
    }
    void load() {
        ifstream file(filename_);
        string line;
        while (getline(file, line)) {
            istringstream input(line);
            string idText, name, ageText, planText;
            if (getline(input, idText, '|') && getline(input, name, '|') &&
                getline(input, ageText, '|') && getline(input, planText)) {
                try {
                    int id = stoi(idText), age = stoi(ageText), plan = stoi(planText);
                    if (id > 0 && age >= 1 && age <= 120 && plan >= 1 && plan <= 3 &&
                        !name.empty() && !exists(id)) {
                        members_.emplace_back(id, name, age, plan);
                    }
                } catch (const exception&) { /* Ignore invalid saved records. */ }
            }
        }
    }
    void save() const {
        ofstream file(filename_);
        if (!file) {
            cout << "Error: Unable to save member records.\n";
            return;
        }
        for (const Member& m : members_) file << m.serialize() << '\n';
    }
    void addMember() {
        cout << "\n--- Add Member ---\n";
        int id = readInt("Enter member ID: ", 1, 1000000000);
        if (exists(id)) {
            cout << "A member with this ID already exists.\n";
            return;
        }
        string name;
        do {
            cout << "Enter member name: ";
            getline(cin, name);
            if (name.empty() || name.find('|') != string::npos)
                cout << "Enter a valid name (without |).\n";
        } while (name.empty() || name.find('|') != string::npos);
        int age = readInt("Enter age (1-120): ", 1, 120);
        MembershipPlan::show();
        int plan = readInt("Choose plan (1-3): ", 1, 3);
        members_.emplace_back(id, name, age, plan);
        save();
        cout << "Member added successfully!\n";
    }
    void viewMembers() const {
        cout << "\n--- All Members ---\n";
        if (members_.empty()) { cout << "No members registered.\n"; return; }
        for (const Member& m : members_) m.display();
    }
    void searchMember() const {
        int id = readInt("Enter member ID to search: ", 1, 1000000000);
        for (const Member& m : members_) {
            if (m.id() == id) { m.display(); return; }
        }
        cout << "Member not found.\n";
    }
    void removeMember() {
        int id = readInt("Enter member ID to remove: ", 1, 1000000000);
        auto it = remove_if(members_.begin(), members_.end(),
                            [id](const Member& m) { return m.id() == id; });
        if (it == members_.end()) { cout << "Member not found.\n"; return; }
        members_.erase(it, members_.end());
        save();
        cout << "Member removed successfully!\n";
    }
    void totalFees() const {
        double total = 0;
        for (const Member& m : members_) total += m.fee();
        cout << "Total value of registered membership plans: Rs. "
             << fixed << setprecision(2) << total << '\n';
        cout << "(This is plan value, not confirmed payments received.)\n";
    }
public:
    GymManagementSystem() { load(); }
    void run() {
        while (true) {
            cout << "\n========== GYM MANAGEMENT SYSTEM ==========\n"
                 << "1. Add Member\n2. View All Members\n3. Search Member\n"
                 << "4. Remove Member\n5. View Membership Plans\n"
                 << "6. Calculate Total Plan Value\n7. Exit\n";
            int choice = readInt("Enter your choice (1-7): ", 1, 7);
            switch (choice) {
                case 1: addMember(); break;
                case 2: viewMembers(); break;
                case 3: searchMember(); break;
                case 4: removeMember(); break;
                case 5: MembershipPlan::show(); break;
                case 6: totalFees(); break;
                case 7: cout << "Thank you for using Gym Management System!\n"; return;
            }
        }
    }
};

int main() {
    GymManagementSystem gym;
    gym.run();
    return 0;
}
