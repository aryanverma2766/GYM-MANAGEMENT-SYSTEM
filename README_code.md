# Gym Management System

A simple **Python console-based Gym Management System** developed as an Object-Oriented Programming (OOP) mini-project. It helps manage gym member records and membership plans through a menu-driven interface.

## Features

- Register new gym members with name, 10-digit phone number, and membership plan.
- View all registered members with their IDs and membership expiry dates.
- Search for a member by member ID.
- Remove a member from the system.
- Display available membership plans and fees.
- View the total number of registered members and the total value of their plans.
- Automatically save and reload member records using a JSON file.

## Technologies Used

- **Language:** Python 3
- **Interface:** Command-line / terminal
- **Storage:** JSON (`gym_data.json`)
- **Libraries:** `json`, `datetime`, and `pathlib` (all built into Python)

No external packages or database setup are required.

## Project Files

```text
Gym-Management-System/
├── gym_management.py   # Main Python application
├── gym_data.json       # Created automatically to store member records
└── README.md           # Instructions for running the code
```

## How to Run

1. Install Python 3.
2. Save `gym_management.py` in a folder.
3. Open a terminal or command prompt in that folder.
4. Run:

   ```bash
   python gym_management.py
   ```

   On some systems, use `python3 gym_management.py` instead.
5. Enter a number from the menu and follow the prompts.

## Main Menu

```text
===== GYM MANAGEMENT SYSTEM =====
1. Add member
2. View members
3. Search member
4. Remove member
5. Membership plans
6. Revenue summary
7. Exit
Enter choice:
```

## Membership Plans

| Plan | Fee | Duration used by code |
|---|---:|---:|
| Monthly | Rs. 1,000 | 30 days |
| Quarterly | Rs. 2,700 | 90 days |
| Yearly | Rs. 10,000 | 365 days |

The expiry date is calculated from the member's joining date.

## OOP Concepts Used

- **Classes and objects:** `Person`, `Member`, and `Gym` represent the system's main entities.
- **Inheritance:** `Member` inherits name and phone details from `Person`.
- **Constructors:** `__init__()` initializes member and gym objects.
- **Methods:** Functions such as `add_member()`, `search_member()`, `remove_member()`, and `expiry_date()` organize the application's behavior.
- **Encapsulation through class organization:** Member data and operations are grouped into classes; attributes are not strictly private.

## Example Output

```text
===== GYM MANAGEMENT SYSTEM =====
1. Add member
2. View members
3. Search member
4. Remove member
5. Membership plans
6. Revenue summary
7. Exit
Enter choice: 1
Name: Rahul Sharma
10-digit phone: 9876543210
Plans: Monthly, Quarterly, Yearly
Plan: Monthly
Member added successfully! ID: 101
```

*This is illustrative output; the actual member ID depends on existing saved records.*

## Data Storage and Validation

The program creates or updates `gym_data.json` in the same folder as the Python file whenever a member is added or removed. It validates that names are not empty, phone numbers contain exactly 10 digits, and plans match an available option. Member IDs are assigned automatically.

**Note:** The revenue summary calculates the sum of plan fees for currently registered members; it is not a historical payment ledger. The program is intended for learning and small-scale demonstration, not production gym billing.

## Conclusion

This project demonstrates how Python OOP can be used to build a practical menu-driven application for registering, searching, displaying, and removing gym members while storing data locally.
