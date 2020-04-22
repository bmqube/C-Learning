#include <bits/stdc++.h>
using namespace std;

string decryptionKey {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
string encryptionKey {"9XZNLW6EBGJHQD4YVTKF5UOMP7CIA2SRcgh0ibokztpfjv8lsmqdu1exrwany3"};

void encrypt() {
    string meow;
    cout << "Enter the text to encrypt: ";
    getline(cin, meow);
    
    for(size_t i = 0; i<meow.size(); i++) 
        if(isalnum(meow.at(i)))
            meow.at(i) = encryptionKey.at(decryptionKey.find(meow.at(i)));
    
    cout << "Encrypted Text: " << meow << endl;
}

void decrypt() {
    string meow;
    cout << "Enter the text to decrypt: ";
    getline(cin, meow);
    
    for(size_t i = 0; i<meow.size(); i++) 
        if(isalnum(meow.at(i)))
            meow.at(i) = decryptionKey.at(encryptionKey.find(meow.at(i)));
    
    cout << "Decrypted Text: " << meow << endl;
}

void menu() {
    system("cls");
    cout << "\nWelcome to my Substitution Cipher" << endl;
    cout << "=================================" << endl;
    
    cout << "1. Encrypt your text" << endl;
    cout << "2. Decrypt your text" << endl;
    cout << "Q. Quit" << endl;
}

void quit() {
    cout << "Goodbye..." << endl;
    cout << "Have a nice day" << endl;
}

void invalid() {
    cout << "Invalid option" << endl;
    cout << "Please try again or type Q for quit" << endl;
}

int main() {
    char ch{};
    
    do {
        menu();
        cout << "\nEnter your choice: ";
        cin >> ch;
        cin.ignore();
        
        switch(ch) {
            case '1':
                encrypt();
                break;
                
            case '2':
                decrypt();
                break;
                
            case 'q':
            case 'Q':
                quit();
                break;
                
            default:
                invalid();
        }
        getchar();
    } while (ch != 'Q' && ch != 'q');
    
    cout << endl;
    return 0;
}