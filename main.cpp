#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Person {
    int id, userID;
    string name, surname, phoneNumber, email, address;
};

struct User {
    int id;
    string name, password;
};

void updateFileEDIT (vector <Person> &contacts, int answerEditID, int i);

void updateFileREMOVE (vector <Person> &contacts, int removeID);

void updateUsers (vector <User> &users);

void checkIfZeroContacts (vector <Person> &contacts);

void addPerson(vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void findByName(vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void findBySurname(vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void findAll(vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void removeContact (vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void editContact (vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void addUser(vector <User> &users);

void getUsersFromFile(vector <User> &users);

int userLogin(vector <Person> &contacts, vector <User> &users);

void displayMenu (vector <Person> &contacts, vector <User> &users, int idLoggedUser);

void getUsersContacts(vector <Person> &contacts, int idLoggedUser);

void changePassword (vector <Person> &contacts, vector <User> &users, int idLoggedUser);

int getLastID();

Person getContactData(string dataOfSingleContact, int idLoggedUser);

User getUserData(string dataOfSingleUser);

string bigFirstLetterRestSmall (string textToChange);

int main() {
    vector <Person> contacts;
    vector <User> users;
    char choice = 0;
    int idLoggedUser = 0;
    getUsersFromFile(users);

    while(true) {
        system("cls");
        cout << "1. Log in" << endl;
        cout << "2. Sign up" << endl;
        cout << "9. Exit" << endl;
        cin >> choice;

        if (choice == '1') {
            idLoggedUser = userLogin(contacts, users);
            if (idLoggedUser != 0) {
            getUsersContacts(contacts, idLoggedUser);
            displayMenu(contacts, users, idLoggedUser);
            }
        } else if (choice == '2') {
            addUser(users);
        } else if (choice == '9') {
            system("cls");
            cout << "See you again!" << endl;
            exit(0);
        }
    }
    return 0;
}

void addPerson(vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    Person people;
    people.userID = idLoggedUser;
    int lastID = 0;
    lastID = getLastID();

    if (lastID == 0) {
        people.id = 1;
    } else {
        people.id = lastID + 1;
    }

    system("cls");

    cout << "Adding a contact" << endl;
    cout << "---------------------------" << endl;

    cout << "Type in a name: ";
    cin >> people.name;
    people.name = bigFirstLetterRestSmall(people.name);

    cout << "Type in a surname: ";
    cin >> people.surname;
    people.surname = bigFirstLetterRestSmall(people.surname);

    cin.sync();
    cout << "Type in a phone number: ";
    getline(cin, people.phoneNumber);

    cout << "Type in an email: ";
    cin >> people.email;

    cin.sync();
    cout << "Type in an address (street, zip code, city): ";
    getline(cin, people.address);

    contacts.push_back(people);

    fstream file;
    file.open("AddressBook.txt", ios::out | ios::app);

    file << people.id << '|';
    file << people.userID << '|';
    file << people.name << '|';
    file << people.surname << '|';
    file << people.phoneNumber << '|';
    file << people.email << '|';
    file << people.address << '|' << endl;

    file.close();

    cout << endl << "A new contact has been added to your address book." << endl;

    Sleep(1500);
    displayMenu(contacts, users, idLoggedUser);
}

void findByName(vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) {
        displayMenu(contacts, users, idLoggedUser);
        return;
    }
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
        cout << endl << "No contact of that name " << name << " was found." << endl;
    }

    if (countPeople == 1) {
        cout << endl << "In your address book there is " << countPeople << " contact with name " << name << "." << endl;
    } else if (countPeople > 1) {
        cout << endl << "In your address book there are " << countPeople << " contacts with name " << name << "." << endl;
    }

    system("pause");
    displayMenu(contacts, users, idLoggedUser);
}

void findBySurname(vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) {
        displayMenu(contacts, users, idLoggedUser);
        return;
    }
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
    }

    if (countPeople == 1) {
        cout << endl << "In your address book there is " << countPeople << " contact with surname " << surname << "." << endl;
    } else if (countPeople > 1){
        cout << endl << "In your address book there are " << countPeople << " contacts with surname " << surname << "." << endl;
    }
    system("pause");
    displayMenu(contacts, users, idLoggedUser);
}

void findAll(vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) {
        displayMenu(contacts, users, idLoggedUser);
        return;
    }

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
    displayMenu(contacts, users, idLoggedUser);
}

void removeContact (vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) {
        displayMenu(contacts, users, idLoggedUser);
        return;
    }
    int removeID;
    int i = 0;
    char answerRemoveID;
    int sizeOfVector = contacts.size();

    cout << "Removing a contact" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Type in the contact's ID you are remove: ";
    cin >> removeID;

    for (i; i < sizeOfVector; i++) {
        if (removeID == contacts[i].id) break;
        else if (i == sizeOfVector - 1 && removeID != contacts[i].id) {
            cout << "Selected ID there is not in your address book!" << endl;
            Sleep(2000);
            displayMenu(contacts, users, idLoggedUser);
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
            cout << "Emainl: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
            cout << endl << "Do you remove this contact? (y/n)" << endl;
            cin >> answerRemoveID;
            if (answerRemoveID == 'y') {
                contacts.erase(contacts.begin() + i);
                cout << "Selected contact has been removed from your address book." << endl;
                break;
            } else {
                displayMenu(contacts, users, idLoggedUser);
                return;
            }
        }
    }

    updateFileREMOVE(contacts, removeID);
    system("pause");
    displayMenu(contacts, users, idLoggedUser);
}

void editContact (vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    int sizeOfVector = contacts.size();
    checkIfZeroContacts(contacts);
    if (contacts.size() == 0) {
        displayMenu(contacts, users, idLoggedUser);
        return;
    }
    int editID;
    string newName, newSurname, newPhoneNumber, newEmail, newAddress;
    int i = 0;
    int answerEditID;
    char choice;

    cout << "Editing a contact" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Type in the contact's ID you want to edit: ";
    cin >> answerEditID;

    for (i; i < sizeOfVector; i++) {
        if (answerEditID == contacts[i].id) break;
        else if (i == sizeOfVector - 1 && answerEditID != contacts[i].id) {
            cout << "Selected ID there is not in your address book!" << endl;
            Sleep(2000);
            displayMenu(contacts, users, idLoggedUser);
            return;
        }
    }

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
                displayMenu(contacts, users, idLoggedUser);
                return;
            }
            break;
        }
    }
    cout << "Contact's data have been changed." << endl;
    updateFileEDIT(contacts, answerEditID, i);
    system("pause");
    displayMenu(contacts, users, idLoggedUser);
}

void updateFileEDIT (vector <Person> &contacts, int answerEditID, int i) {

    int searchedID = 0;
    string people;
    string line;
    string singleVariable;

    int positionOfSign = 0;
    fstream file, tmpFile;
    file.open("AddressBook.txt", ios::in);
    tmpFile.open("tmpAddressBook.txt", ios::out);
    while(getline(file, line)) {
        people = line;
        while(people[positionOfSign] != '|') {
            singleVariable += people[positionOfSign];
            positionOfSign++;
        }
        searchedID = atoi(singleVariable.c_str());
        singleVariable = "";
        positionOfSign = 0;
        if (searchedID != answerEditID) {
            tmpFile << people << endl;
        } else {
            tmpFile << contacts[i].id << '|';
            tmpFile << contacts[i].userID << '|';
            tmpFile << contacts[i].name << '|';
            tmpFile << contacts[i].surname << '|';
            tmpFile << contacts[i].phoneNumber << '|';
            tmpFile << contacts[i].email << '|';
            tmpFile << contacts[i].address << '|' << endl;
        }
    }
    file.close();
    tmpFile.close();
    remove ("AddressBook.txt");
    rename("tmpAddressBook.txt", "AddressBook.txt");
}

void updateFileREMOVE (vector <Person> &contacts, int removeID) {

    int searchedID = 0;
    string people;
    string line;
    string singleVariable;

    int positionOfSign = 0;
    fstream file, tmpFile;
    file.open("AddressBook.txt", ios::in);
    tmpFile.open("tmpAddressBook.txt", ios::out);
    while(getline(file, line)) {
        people = line;
        while(people[positionOfSign] != '|') {
            singleVariable += people[positionOfSign];
            positionOfSign++;
        }
        searchedID = atoi(singleVariable.c_str());
        singleVariable = "";
        positionOfSign = 0;
        if (searchedID != removeID) {
            tmpFile << people << endl;
        } else {
            continue;
        }
    }
    file.close();
    tmpFile.close();
    remove ("AddressBook.txt");
    rename("tmpAddressBook.txt", "AddressBook.txt");
}

void updateUsers (vector <User> &users) {
    int i = 0;
    int sizeOfVector = users.size();

    fstream file;
    file.open("Users.txt", ios::out);
    for (i; i < sizeOfVector; i++) {
        file << users[i].id << '|';
        file << users[i].name << '|';
        file << users[i].password << '|' << endl;
    }
    file.close();
}

void checkIfZeroContacts (vector <Person> &contacts) {
    system("cls");
    int sizeOfVector = contacts.size();
    if (sizeOfVector == 0) {
        cout << "Your address book is empty. Please add someone :)" << endl << endl;
        system("pause");
    }
}

void addUser(vector <User> &users) {
    User addingUser;
    int id = 0;

    if (users.size() == 0) {
        id = 1;
    } else {
        id = users.back().id + 1;
    }

    string name, password;

    system("cls");

    cout << "Adding an user" << endl;
    cout << "---------------------------" << endl;

    cout << "Type in a name: ";
    cin >> name;

    cout << "Type in a password: ";
    cin >> password;

    addingUser.id = id;
    addingUser.name = name;
    addingUser.password = password;

    users.push_back(addingUser);

    fstream file;
    file.open("Users.txt", ios::out | ios::app);

    file << id << '|';
    file << name << '|';
    file << password << '|' << endl;

    file.close();

    cout << endl << "A new user has been added." << endl;

    Sleep(1500);
}

int userLogin(vector <Person> &contacts, vector <User> &users) {
    system("cls");

    int sizeOfVector = users.size();
    if (sizeOfVector == 0) {
        cout << "You have to sign up! :)";
        return 0;
    }

    int i = 0;
    string typedName, typedPassword;

    cout << "Name: ";
    cin >> typedName;

    cout << "Password: ";
    cin >> typedPassword;

    for (i; i < sizeOfVector; i++) {
        if (typedName == users[i].name && typedPassword == users[i].password) break;
        else if (i == sizeOfVector - 1 && (typedName != users[i].name || typedPassword != users[i].password)) {
            cout << "Wrong login or password!" << endl;
            Sleep(3000);
            return 0;
        }
    }

    int idLoggedUser = users[i].id;

    cout << "Login and password are correct! :)" << endl;
    Sleep(1500);

    return idLoggedUser;
}

void displayMenu (vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");
    char choice;
    cout << "1. Add new contact" << endl;
    cout << "2. Find by name" << endl;
    cout << "3. Find by surname" << endl;
    cout << "4. Find all" << endl;
    cout << "5. Remove a contact" << endl;
    cout << "6. Edit a contact" << endl;
    cout << "7. Change a password" << endl;
    cout << "9. Log out" << endl;
    cin >> choice;

    if (choice == '1') {
        addPerson(contacts, users, idLoggedUser);
    } else if (choice == '2') {
        findByName(contacts, users, idLoggedUser);
    } else if (choice == '3') {
        findBySurname(contacts, users, idLoggedUser);
    } else if (choice == '4') {
        findAll(contacts, users, idLoggedUser);
    } else if (choice == '5') {
        removeContact (contacts, users, idLoggedUser);
    } else if (choice == '6') {
        editContact (contacts, users, idLoggedUser);
    } else if (choice == '7') {
        changePassword(contacts, users, idLoggedUser);
    } else if (choice == '9') {
        system("cls");
        contacts.clear();
        cout << "See you again!" << endl;
        return;
    }
}

void getUsersContacts(vector <Person> &contacts, int idLoggedUser) {
    system("cls");
    fstream file;
    file.open("AddressBook.txt", ios::in);

    if(file.good()==false) {
        cout << "Your address book is empty. Please add someone :)" << endl << endl;
        system("pause");
        return;
    }

    Person friends;
    string dataOfSingleContact = "";
    while (getline(file, dataOfSingleContact)) {
        friends = getContactData(dataOfSingleContact, idLoggedUser);
        if (friends.userID == idLoggedUser) {
            contacts.push_back(friends);
        }
    }
    file.close();
}

Person getContactData(string dataOfSingleContact, int idLoggedUser) {
    Person friends;
    string singleDataOfContact = "";
    int numberOfSingleDataOfContact = 1;

    for (int positionOfSign = 0; positionOfSign < dataOfSingleContact.length(); positionOfSign++) {
        if (dataOfSingleContact[positionOfSign] != '|') {
            singleDataOfContact += dataOfSingleContact[positionOfSign];
        } else {
            switch(numberOfSingleDataOfContact) {
                case 1:
                    friends.id = atoi(singleDataOfContact.c_str());
                    break;
                case 2:
                    friends.userID = atoi(singleDataOfContact.c_str());
                    break;
                case 3:
                    if (friends.userID == idLoggedUser) {
                        friends.name = singleDataOfContact;
                        break;
                    case 4:
                        friends.surname = singleDataOfContact;
                        break;
                    case 5:
                        friends.phoneNumber = singleDataOfContact;
                        break;
                    case 6:
                        friends.email = singleDataOfContact;
                        break;
                    case 7:
                        friends.address = singleDataOfContact;
                        break;
                    } else {
                        return friends;
                    }
                }
                singleDataOfContact = "";
                numberOfSingleDataOfContact++;
        }
    }
    return friends;
}

void getUsersFromFile(vector <User> &users) {
    fstream file;
    file.open("Users.txt", ios::in);

    if(file.good()==false) {
        cout << "You have to sign up! :)" << endl << endl;
        system("pause");
        return;
    }

    User registredUsers;
    string dataOfSingleUser = "";

    while (getline(file, dataOfSingleUser)) {
        registredUsers = getUserData(dataOfSingleUser);
        users.push_back(registredUsers);
    }

    file.close();
}

User getUserData(string dataOfSingleUser) {
    User registredUsers;
    string singleDataOfUser = "";
    int numberOfSingleDataOfUser = 1;

    for (int positionOfSign = 0; positionOfSign < dataOfSingleUser.length(); positionOfSign++) {
        if (dataOfSingleUser[positionOfSign] != '|') {
            singleDataOfUser += dataOfSingleUser[positionOfSign];
        } else {
            switch(numberOfSingleDataOfUser) {
                case 1:
                    registredUsers.id = atoi(singleDataOfUser.c_str());
                    break;
                case 2:
                    registredUsers.name = singleDataOfUser;
                    break;
                case 3:
                    registredUsers.password = singleDataOfUser;
                    break;
                }
                singleDataOfUser = "";
                numberOfSingleDataOfUser++;
        }
    }
    return registredUsers;
}

void changePassword (vector <Person> &contacts, vector <User> &users, int idLoggedUser) {
    system("cls");

    string newPassword;
    string currentPassword;
    char answer;

    cout << "Changing a password" << endl;
    cout << "-----------------------------------------" << endl;
    while (answer != 'y' && answer != 'n') {
        cout << "Do you want to change the password? (y/n)" << endl;
        cin >> answer;
        if (answer != 'y' && answer != 'n') {
            cout << "You have to type y or n!" << endl;
        }
    }
    if (answer == 'n') {
       displayMenu(contacts, users, idLoggedUser);
       return;
    }

    cout << "Type a current password: ";
    cin >> currentPassword;

    for (int i = 0; i < users.size(); i++) {
        if (idLoggedUser == users[i].id) {
            if (users[i].password != currentPassword) {
                cout << "Current password is incorrect!" << endl;
                Sleep(1500);
                displayMenu(contacts, users, idLoggedUser);
                return;
            }
        }
    }

    while (true) {
        cout << "Type a new password: ";
        cin >> newPassword;
        if (newPassword != currentPassword) break;
        else {
            cout << "New password is the same as current password. Please try type another password!" << endl;
            Sleep(1500);
            system("cls");
        }
    }

    for (int i = 0; i < users.size(); i++) {
        if (idLoggedUser == users[i].id) {
            users[i].password = newPassword;
        }
    }
    updateUsers(users);
    cout << "Password has been changed!" << endl;
    Sleep(1500);
    displayMenu(contacts, users, idLoggedUser);
}

int getLastID() {
    int lastID = 0;
    string people;
    string line;
    string singleVariable;

    int positionOfSign = 0;
    fstream file;
    file.open("AddressBook.txt", ios::in);
    while(getline(file, line)) {
        people = line;
        while(people[positionOfSign] != '|') {
            singleVariable += people[positionOfSign];
            positionOfSign++;
        }
        lastID = atoi(singleVariable.c_str());
        singleVariable = "";
        positionOfSign = 0;
    }
    file.close();
    return lastID;
}

string bigFirstLetterRestSmall (string textToChange) {
    if (!textToChange.empty()) {
        transform(textToChange.begin(), textToChange.end(), textToChange.begin(), ::tolower);
        textToChange[0] = toupper(textToChange[0]);
    }
    return textToChange;
}
