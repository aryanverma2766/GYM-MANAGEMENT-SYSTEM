"""Gym Management System - OOP mini project (Python 3, standard library)."""
import json
from datetime import date, timedelta
from pathlib import Path

DATA_FILE = Path(__file__).with_name('gym_data.json')
PLANS = {'Monthly': 1000, 'Quarterly': 2700, 'Yearly': 10000}

class Person:
    def __init__(self, name, phone):
        self.name = name.strip()
        self.phone = phone.strip()

class Member(Person):
    def __init__(self, member_id, name, phone, plan, joined=None):
        super().__init__(name, phone)
        self.member_id = member_id
        self.plan = plan
        self.joined = joined or date.today().isoformat()

    def expiry_date(self):
        days = {'Monthly': 30, 'Quarterly': 90, 'Yearly': 365}
        return (date.fromisoformat(self.joined) + timedelta(days=days[self.plan])).isoformat()

    def to_dict(self):
        return vars(self).copy()

class Gym:
    def __init__(self, path=DATA_FILE):
        self.path = Path(path)
        self.members = {}
        self.load()

    def load(self):
        if self.path.exists():
            try:
                data = json.loads(self.path.read_text(encoding='utf-8'))
                self.members = {int(x['member_id']): Member(**x) for x in data}
            except (ValueError, TypeError, KeyError) as exc:
                print('Could not read saved data:', exc)
                self.members = {}

    def save(self):
        self.path.write_text(json.dumps([m.to_dict() for m in self.members.values()], indent=2), encoding='utf-8')

    def add_member(self, name, phone, plan):
        if not name.strip() or not phone.isdigit() or len(phone) != 10:
            raise ValueError('Enter a name and a valid 10-digit phone number.')
        if plan not in PLANS:
            raise ValueError('Invalid membership plan.')
        member_id = max(self.members, default=100) + 1
        member = Member(member_id, name, phone, plan)
        self.members[member_id] = member
        self.save()
        return member

    def search_member(self, member_id):
        return self.members.get(member_id)

    def remove_member(self, member_id):
        if member_id not in self.members:
            return False
        del self.members[member_id]
        self.save()
        return True

    def total_revenue(self):
        return sum(PLANS[m.plan] for m in self.members.values())

    def display_members(self):
        if not self.members:
            print('No members registered.')
            return
        print(f"{'ID':<6}{'NAME':<20}{'PLAN':<14}{'EXPIRY':<12}")
        print('-' * 52)
        for m in sorted(self.members.values(), key=lambda x: x.member_id):
            print(f'{m.member_id:<6}{m.name:<20}{m.plan:<14}{m.expiry_date():<12}')


def main():
    gym = Gym()
    while True:
        print('\n===== GYM MANAGEMENT SYSTEM =====')
        print('1. Add member\n2. View members\n3. Search member\n4. Remove member')
        print('5. Membership plans\n6. Revenue summary\n7. Exit')
        choice = input('Enter choice: ').strip()
        try:
            if choice == '1':
                name = input('Name: ')
                phone = input('10-digit phone: ')
                print('Plans:', ', '.join(PLANS))
                plan = input('Plan: ').strip().title()
                member = gym.add_member(name, phone, plan)
                print(f'Member added successfully! ID: {member.member_id}')
            elif choice == '2':
                gym.display_members()
            elif choice == '3':
                member = gym.search_member(int(input('Member ID: ')))
                if member:
                    print(f'Name: {member.name} | Phone: {member.phone} | Plan: {member.plan} | Expires: {member.expiry_date()}')
                else:
                    print('Member not found.')
            elif choice == '4':
                print('Member removed.' if gym.remove_member(int(input('Member ID: '))) else 'Member not found.')
            elif choice == '5':
                for plan, fee in PLANS.items():
                    print(f'{plan}: Rs. {fee}')
            elif choice == '6':
                print(f'Total registered members: {len(gym.members)}')
                print(f'Total value of registered plans: Rs. {gym.total_revenue()}')
            elif choice == '7':
                print('Thank you for using Gym Management System!')
                break
            else:
                print('Invalid choice. Try again.')
        except ValueError as exc:
            print('Input error:', exc)
        except OSError as exc:
            print('File error:', exc)

if __name__ == '__main__':
    main()
