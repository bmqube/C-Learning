
/* Akaimma Programs By Morshed */

#include<bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c=5;
    srand(time(0));
    a=rand()%101;
    while(c--) {
        cout<<"Enter your guess: "<<endl;
        cin>>b;
        if(b==a){
            cout<<"You Won The Game!!!!!"<<endl;
            return 0;
        }
        else if(!c) cout<<"You lost the game"<<endl<<"The answer is "<<a<<endl;
        else if(b<a) cout<<"Guess higher"<<endl;
        else cout<<"Guess lower"<<endl;
    }
    return 0;
}
