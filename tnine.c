#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
const int MAX_LENGTH = 102;

int isDigit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}
int validArgv(char check[]){
    for(int i = 0; check[i] != '\0'; i++){
        if (isDigit(check[i]) == 0) {
            return 0;
        }  
    }
    return 1;
}
int charValue(char c){
    c = tolower(c);
    if(c == '1') return 1;
    if((c >= 'a' && c <= 'c' )|| c == '2'){
        return 2;
    }
    if((c >= 'd' && c <= 'f' )|| c == '3'){
        return 3;
    }
    if((c >= 'g' && c <= 'i' )|| c == '4'){
        return 4;
    }
    if((c >= 'j' && c <= 'l' )|| c == '5'){
        return 5;
    }
    if((c >= 'm' && c <= 'o' )|| c == '6'){
        return 6;
    }
    if((c >= 'p' && c <= 's' )|| c == '7'){
        return 7;
    }
    if((c >= 't' && c <= 'v' )|| c == '8'){
        return 8;
    }
    if((c >= 'w' && c <= 'z' )|| c == '9'){
        return 9;
    }
    if(c == '0' || c == '+'){
        return 0;
    }
    return -1;
}

int search(char prompt[], char contact[]){
    for(int i = 0; contact[i] != ('\0'); i++) {
        for(int j = 0;;j++){
            if(prompt[j] == '\0') return 1;
            if(charValue(prompt[j]) != charValue(contact[i+j])){
                break;
            }
        
        }
    }
    return 0;
}

int main(int argc, char *argv[]){

    int contacts_found = 0;

    char jmeno[MAX_LENGTH];
    char telcislo[MAX_LENGTH];
    char pattern[MAX_LENGTH];

    

    if(argc > 1){
        if (validArgv(argv[1]) == 0){
            fprintf(stderr, "Invalid argument\n");
            return 1;
        }
        strncpy(pattern, argv[1], MAX_LENGTH - 1);
        pattern[strlen(pattern)] = '\0';
    }
    else pattern[0] = '\0';


    while (fgets(jmeno, MAX_LENGTH, stdin) != NULL)
    {
        if(fgets(telcislo, MAX_LENGTH, stdin) == NULL){
            fprintf(stderr, "Telephone number not found");
            return 1;
        }

        jmeno[strcspn(jmeno, "\n")] = '\0';
        telcislo[strcspn(telcislo, "\n")] = '\0';

        

        if(search(pattern, jmeno) || search(pattern, telcislo)== 1) {
            fprintf(stdout, "%s, %s\n", jmeno, telcislo);
            contacts_found++;
        }


    }
    if (contacts_found == 0)
    {
        fprintf(stdout, "Not found\n");
    }
    
    return 0;

}