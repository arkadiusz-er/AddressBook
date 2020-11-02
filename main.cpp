#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Person {
    int id;
    string name, surname, phoneNumber, email, address;
};

vector <Person> updateFile (vector <Person> &contacts);

void checkIfZeroContacts (vector <Person> &contacts);

void addPerson(vector <Person> &contacts);

void findByName(vector <Person> &contacts);

void findBySurname(vector <Person> &contacts);

void findAll(vector <Person> &contacts);

int getContactsFromFile(vector <Person> &contacts);

void removeContact (vector <Person> &contacts);

void editContact (vector <Person> &contacts);

int main() {
    vector <Person> contacts;
    char choice;
    getContactsFromFile(contacts);

    while(true) {
        system("cls");
        cout << "1. Add new contact" << endl;
        cout << "2. Find by name" << endl;
        cout << "3. Find by surname" << endl;
        cout << "4. Find all" << endl;
        cout << "5. Remove a contact" << endl;
        cout << "6. Edit a contact" << endl;
        cout << "9. Exit" << endl;
        cin >> choice;

        if (choice == '1') {
            addPerson(contacts);
        } else if (choice == '2') {
            findByName(contacts);
        } else if (choice == '3') {
            findBySurname(contacts);
        } else if (choice == '4') {
            findAll(contacts);
        } else if (choice == '5') {
            removeContact (contacts);
        } else if (choice == '6') {
            editContact (contacts);
        } else if (choice == '9') {
            system("cls");
            cout << "See you again!" << endl;
            exit(0);
        }
    }
    return 0;
}

void addPerson(vector <Person> &contacts) {
    Person people;
    int id = 0;
    int i = 0;
    vector <Person>::iterator startItr = contacts.begin();
    vector <Person>::iterator endItr = contacts.end();

    for (startItr; startItr < endItr; startItr++, i++);

    if (contacts.size() == 0) {
        id = 1;
    } else {
        id = contacts[i-1].id + 1;
    }

    string name, surname, phoneNumber, email, address;

    system("cls");

    cout << "Adding a contact" << endl;
    cout << "---------------------------" << endl;

    cout << "Type in a name: ";
    cin >> name;

    cout << "Type in a surname: ";
    cin >> surname;

    cin.sync();
    cout << "Type in a phone number: ";
    getline(cin, phoneNumber);

    cout << "Type in an email: ";
    cin >> email;

    cin.sync();
    cout << "Type in an address (street, zip code, city): ";
    getline(cin, address);

    people.id = id;
    people.name = name;
    people.surname = surname;
    people.phoneNumber = phoneNumber;
    people.email = email;
    people.address = address;

    contacts.push_back(people);

    fstream file;
    file.open("AddressBook.txt", ios::out | ios::app);

    file << id << '|';
    file << name << '|';
    file << surname << '|';
    file << phoneNumber << '|';
    file << email << '|';
    file << address << '|' << endl;

    file.close();

    i++;

    cout << endl << "A new contact has been added to your address book." << endl;

    if (i == 1) {
        cout << "In your address book there is " << i << " contact.";
    } else {
        cout << "In your address book there are " << i << " contacts.";
    }

    Sleep(1500);
}

void findByName(vector <Person> &contacts) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) return;
    string name;

    cout << "Finding by name" << endl;
    cout << "---------------------------" << endl;
    cout << "Type in the name you are looking for: ";
    cin >> name;

    int sizeOfVector = contacts.size();
    int countPeople = 0;

    for (int i = 0; i < sizeOfVector; i++) {
        if (contacts[i].name == name) {
            countPeople++;
            cout << endl << countPeople << "." << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Surname: " << contacts[i].surname << endl;
            cout << "Phone number: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
        }
    }
    if (countPeople == 0) {
        cout << endl << "No contact of that name " << name << " was found." << endl << endl;
        system("pause");
        return;
    }

    if (countPeople == 1) {
        cout << endl << "In your address book there is " << countPeople << " contact with name " << name << "." << endl;
    } else {
        cout << endl << "In your address book there are " << countPeople << " contacts with name " << name << "." << endl;
    }

    system("pause");
}

void findBySurname(vector <Person> &contacts) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) return;
    string surname;

    cout << "Finding by surname" << endl;
    cout << "---------------------------" << endl;
    cout << "Type in the surname you are looking for: ";
    cin >> surname;

    int sizeOfVector = contacts.size();
    int countPeople = 0;

    for (int i = 0; i < sizeOfVector; i++) {
        if (contacts[i].surname == surname) {
            countPeople++;
            cout << endl << countPeople << "." << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Surname: " << contacts[i].surname << endl;
            cout << "Phone number: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
        }
    }

    if (countPeople == 0) {
        cout << endl << "No contact of that surname " << surname << " was found." << endl << endl;
        system("pause");
        return;
    }

    if (countPeople == 1) {
        cout << endl << "In your address book there is " << countPeople << " contact with surname " << surname << "." << endl;
    } else {
        cout << endl << "In your address book there are " << countPeople << " contacts with surname " << surname << "." << endl;
    }
    system("pause");
}

void findAll(vector <Person> &contacts) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) return;

    cout << "Your contacts in address book" << endl;
    cout << "-----------------------------------------------" << endl;

    int sizeOfVector = contacts.size();
    int countPeople = 0;

    for (int i = 0; i < sizeOfVector; i++) {
        countPeople++;
        cout << countPeople << "." << endl;
        cout << "ID: " << contacts[i].id << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Surname: " << contacts[i].surname << endl;
        cout << "Phone number: " << contacts[i].phoneNumber << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << "Address: " << contacts[i].address << endl << endl;
    }

    if (countPeople == 1) {
        cout << "In your address book there is " << countPeople << " contact." << endl;
    } else {
        cout << "In your address book there are " << countPeople << " contacts." << endl;
    }
    system("pause");
}

int getContactsFromFile(vector <Person> &contacts) {
    fstream file;
    file.open("AddressBook.txt", ios::in);

    if(file.good()==false) {
        cout << "Your address book is empty. Please add someone :)" << endl << endl;
        system("pause");
        return 0;
    }

    Person friends;
    int id = 0;
    string name, surname, phoneNumber, email, address;
    int countPeople = 0;
    string people;
    string line;

    while(getline(file, line)) {
        people = line;
        int len = people.size();
        int countSigns = 0;
        int signBeginning = 0;
        for (int i = 0; i < len; i++) {
            while(people[i] == '|') {
                if (id == NULL) {
                    friends.id = atoi(people.substr(signBeginning, countSigns).c_str());
                    signBeginning = i + 1;
                    countSigns = -1;
                    id++;
                    break;
                }
                if (friends.name == "") {
                    friends.name = people.substr(signBeginning, countSigns);
                    signBeginning = i + 1;
                    countSigns = -1;
                    break;
                }
                if (friends.surname == "") {
                    friends.surname = people.substr(signBeginning, countSigns);
                    signBeginning = i + 1;
                    countSigns = -1;
                    break;
                }
                if (friends.phoneNumber == "") {
                    friends.phoneNumber = people.substr(signBeginning, countSigns);
                    signBeginning = i + 1;
                    countSigns = -1;
                    break;
                }
                if (friends.email == "") {
                    friends.email = people.substr(signBeginning, countSigns);
                    signBeginning = i + 1;
                    countSigns = -1;
                    break;
                }
                if (friends.address == "") {
                    friends.address = people.substr(signBeginning, countSigns);
                    signBeginning = i + 1;
                    countSigns = -1;
                    break;
                }
            }
            if (i == len - 1) {
                contacts.push_back(friends);
                id = 0;
                friends.name = "";
                friends.surname = "";
                friends.phoneNumber = "";
                friends.email = "";
                friends.address = "";
            }
            countSigns++;
        }
        countPeople++;
    }
    file.close();
    return countPeople;
}

void removeContact (vector <Person> &contacts) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) return;

    int removeID;
    int i = 0;
    char answerRemoveID;
    int sizeOfVector = contacts.size();

    cout << "Removing a contact" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Type in the contact's ID you are remove: ";
    cin >> removeID;

    vector <Person>::iterator startItr = contacts.begin();
    vector <Person>::iterator endItr = contacts.end();

    for (i; i < sizeOfVector; i++) {
        if (removeID == contacts[i].id) break;
        else if (i == sizeOfVector - 1 && removeID != contacts[i].id) {
            cout << "Selected ID there is not in your address book!" << endl;
            Sleep(3000);
            return;
        }
    }

    i = 0;
    sizeOfVector = contacts.size();

    for (i; i < sizeOfVector; i++) {
        if (removeID == contacts[i].id) {
            cout << endl << "Selected contact to remove:" << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Surname: " << contacts[i].surname << endl;
            cout << "Phone number: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
            cout << endl << "Do you remove this contact? (y/n)" << endl;
            cin >> answerRemoveID;
            if (answerRemoveID == 'y') {
                contacts.erase(contacts.begin() + i);
                cout << "Selected contact has been removed from your address book." << endl;
                break;
            } else {
                return;
            }
        }
    }

    updateFile(contacts);
    system("pause");
}

void editContact (vector <Person> &contacts) {
    system("cls");
    int sizeOfVector = contacts.size();
    checkIfZeroContacts(contacts);
    if (sizeOfVector == 0) return;
    int editID;
    string newName, newSurname, newPhoneNumber, newEmail, newAddress;
    int i = 0;
    int answerEditID;
    char choice;

    cout << "Editing a contact" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Type in the contact's ID you want to edit: ";
    cin >> answerEditID;


    cout << "------------------------------------------------------";
    for (i; i < sizeOfVector; i++) {
        if (answerEditID == contacts[i].id) {
            cout << endl << "Selected contact to edit:" << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Surname: " << contacts[i].surname << endl;
            cout << "Phone number: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
        }
    }
    cout << "------------------------------------------------------" << endl;

    cout << "Edit: " << endl;
    cout << "1. Name" << endl;
    cout << "2. Surname" << endl;
    cout << "3. Phone number" << endl;
    cout << "4. Email" << endl;
    cout << "5. Address" << endl;
    cout << "6. Return to MENU" << endl;
    cin >> choice;

    i = 0;

    for (i; i < sizeOfVector; i++) {
        if (answerEditID == contacts[i].id) {
            switch(choice) {
            case '1':
                cout << "Type new name: ";
                cin >> newName;
                contacts[i].name = newName;
                break;
            case '2':
                cout << "Type new surname: ";
                cin >> newSurname;
                contacts[i].surname = newSurname;
                break;
            case '3':
                cout << "Type new phone number: ";
                getline(cin, newPhoneNumber);
                contacts[i].phoneNumber = newPhoneNumber;
                break;
            case '4':
                cout << "Type new email: ";
                cin >> newEmail;
                contacts[i].email = newEmail;
                break;
            case '5':
                cout << "Type new address: ";
                getline(cin, newAddress);
                contacts[i].address = newAddress;
                break;
            case '6':
                return;
            }
        }
    }
    cout << "Contact's data have been changed." << endl;
    updateFile(contacts);
    system("pause");
}

vector <Person> updateFile (vector <Person> &contacts) {
    int i = 0;
    int sizeOfVector = contacts.size();

    fstream file;
    file.open("AddressBook.txt", ios::out);
    for (i; i < sizeOfVector; i++) {
        file << contacts[i].id << '|';
        file << contacts[i].name << '|';
        file << contacts[i].surname << '|';
        file << contacts[i].phoneNumber << '|';
        file << contacts[i].email << '|';
        file << contacts[i].address << '|' << endl;
    }
    file.close();

    return contacts;
}

void checkIfZeroContacts (vector <Person> &contacts) {
    int sizeOfVector = contacts.size();
    if (sizeOfVector == 0) {
        cout << "Your address book is empty. Please add someone :)" << endl << endl;
        system("pause");
    }
}
