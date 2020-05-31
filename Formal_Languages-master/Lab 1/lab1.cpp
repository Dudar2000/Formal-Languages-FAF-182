#include<iostream>
#include<chrono>
#include<string>

using namespace std;

int main(int argc, char const *argv[]){

    char cur_state, button, initial;

    string sentence;
    while(true){
        HERE:
    cur_state = 'S';
    cout << "\n\nInitial point: "<< cur_state << "\n\nEnter expression: ";
    cin >> sentence;

    cout<<"\nPath:\n";

    for(int i = 0; i < sentence.length(); i++){
        button = sentence[i];
        switch(cur_state){
            case 'S':
            switch(button){
                case 'a':
                cur_state = 'D';
                break;
                default: 
                cout<<"\nInvalid expression!";
                goto HERE;
                ;

            };
            break;
            case 'D':
            switch(button){
                case 'b':
                cur_state = 'E';
                break;
                default: cout<<"\nInvalid expression!";
                goto HERE;
                ;

            };
            break;

            case 'E':
            switch(button){
                case 'c':
                cur_state = 'F';
                break;
                case 'd':
                cur_state = 'L';
                break;
                default: 
                 cout<<"\nInvalid expression!";
                 goto HERE;
                ;

            };
            break;

            case 'F':
            switch(button){
                case 'd':
                cur_state = 'D';
                break;
                default: 
                 cout<<"\nInvalid expression!";
                 goto HERE;
                ;

            };
            break;

             case 'L':
            switch(button){
                case 'b':
                cur_state = 'L';
                break;
                case 'a':
                cur_state = 'L';
                break;
                case 'c':
                cout<<"terminal point reached"<< "\nValid expression";
                goto HERE;
                
                break;
                default: 
                 cout<<"\nInvalid expression!";
                 goto HERE;
                ;

            };
            break;

            

        }
            

        printf("%c\n", cur_state);

    }

             
    cout<<"\nFinal destination - "<<cur_state << "\nSentence is valid!";

    }
    return 0;
}
