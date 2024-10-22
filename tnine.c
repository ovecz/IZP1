/*
xvavrao00 - IZP projekt #1 - 22.10.2024
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
const int MAX_LENGTH = 102;

//Checking if character is a digit
int isDigit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}
//Checking if input are only digits
int validArgv(char check[]){
    for(int i = 0; check[i] != '\0'; i++){
        if (isDigit(check[i]) == 0) {
            return 0;
        }  
    }
    return 1;
}
int bonusCheck(char arg[]){
    if(arg[0] == '-' && arg[1] == 's'){
        return 1;
    }
    return 0;
}
//Giving each character a "value" accordingly
int charValue(char c){
    c = tolower(c);
    if(isDigit(c) == 1) {
        return (c - '0');
    }
    if(c >= 'a' && c <= 'c'){
        return 2;
    }
    if(c >= 'd' && c <= 'f'){
        return 3;
    }
    if(c >= 'g' && c <= 'i'){
        return 4;
    }
    if(c >= 'j' && c <= 'l'){
        return 5;
    }
    if(c >= 'm' && c <= 'o'){
        return 6;
    }
    if(c >= 'p' && c <= 's'){
        return 7;
    }
    if(c >= 't' && c <= 'v'){
        return 8;
    }
    if(c >= 'w' && c <= 'z'){
        return 9;
    }
    if(c == '+'){
        return 0;
    }
    return -1;
}
//Checking if the prompt matches contacts
int search(char prompt[], char contact[], bool bonus){
    int j = 0;
    for(int i = 0; contact[i] != ('\0'); i++) {
        if(bonus == false){
            j = 0;
        }
        while(contact[i] != '\0'){
            if(prompt[j] == '\0') return 1;
            if(charValue(prompt[j]) != charValue(contact[i+j])){
                break;
            }      
            j++;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    //Declares basic variables
    int contacts_found = 0;
    bool bonus = false;
    char name[MAX_LENGTH];
    char telnumber[MAX_LENGTH];
    char pattern[MAX_LENGTH];
    //Prints error message if user inputted too many arguments
    if(argc > 2){
        if(argc < 4 && bonusCheck(argv[1]) == true){
            bonus = true;
        }
        else {
        fprintf(stderr, "Too many arguments\n");
        return 1;
        }
    }

    //Checks if user input is valid, and writes it into "pattern" variable
    if(argc > 1){
        if (validArgv(argv[1 + bonus]) == 0){
            fprintf(stderr, "Invalid argument\n");
            return 1;
        }
        strncpy(pattern, argv[1 + bonus], MAX_LENGTH - 1);
        pattern[strlen(pattern)] = '\0';
    }
    else pattern[0] = '\0';

    //Goes through every contact 
    while (fgets(name, MAX_LENGTH, stdin) != NULL)
    {
        //Checks if every contact has a number
        if(fgets(telnumber, MAX_LENGTH, stdin) == NULL){
            fprintf(stderr, "Telephone number not found");
            return 1;
        }

        name[strcspn(name, "\n")] = '\0';
        telnumber[strcspn(telnumber, "\n")] = '\0';

        

        if(search(pattern, name, bonus) || search(pattern, telnumber, bonus) == 1) {
            fprintf(stdout, "%s, %s\n", name, telnumber);
            contacts_found++;
        }


    } 
    //Prints "Not found" if no matches were found
    if (contacts_found == 0)
    {
        fprintf(stdout, "Not found\n");
    }
    
    return 0;

}