#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User 
{
public:
    string username;
    string password;

    User() {}

    User(string uname, string pwd) : username(uname), password(pwd) {}
};

class UserManager
{
private:
    const string userFile = "users.txt";

public:
    bool registerUser(const User& user)
    {
        ifstream existingUsers(userFile);
        string storedUsername;
        while (existingUsers >> storedUsername)
        {
            if (user.username == storedUsername)
            {
                cerr << "Error: Username '" << user.username << "' already exists." << endl;
                existingUsers.close();
                return false;
            }
        }
        existingUsers.close();

        ofstream file(userFile, ios::app);
        if (!file.is_open()) 
        {
            cerr << "Error: Unable to open the user file." << endl;
            return false;
        }

        file << user.username << " " << user.password << endl;
        file.close();
        return true;
    }

    bool loginUser(const string& username, const string& password)
    {
        ifstream file(userFile);
        if (!file.is_open()) 
        {
            cerr << "Error: Unable to open the user file." << endl;
            return false;
        }

        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword) 
        {
            if (username == storedUsername && password == storedPassword) 
            {
                return true;
            }
        }

        file.close();
        return false;
    }
};

int main() 
{
    int choice;
    cout << "Welcome to the Login and Register System" << endl;

    UserManager userManager;

    while (true)
    {
        cout << "Choose an option:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Choice : " ;
        cin >> choice;

        if (choice == 1) 
        {
            User newUser;
            cout << "Enter a username: ";
            cin >> newUser.username;
            cout << "Enter a password: ";
            cin >> newUser.password;

            if (userManager.registerUser(newUser)) 
            {
                cout << "Registration successful!" << endl;
            } 
            else
            {
                cout << "Registration failed." << endl;
            }
        } 
        else if (choice == 2)
        {
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (userManager.loginUser(username, password))
            {
                cout << "Login successful!" << endl;
            } 
            else
            {
                cout << "Login failed. Please check your credentials." << endl;
            }
        } 
        else if (choice == 3)
        {
            cout << "Exiting... !" << endl ;
            exit(0) ;
            break;
        } 
        else 
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}