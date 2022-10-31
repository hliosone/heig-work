/* ---------------------------
Laboratoire : 02
Auteur(s) : Diana Laurenti, Stan Stelcher, Cédric Kreis
Date : 24.10.2022
But : Recherche dichotomique sous la forme d’un jeu avec l’utilisateur comprenant deux modes et deux façons de jouer.
Remarque(s) : Verifier que l'utilisateur saisit des caracteres acceptables
--------------------------- */
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    //input mode and check if it is acceptable
    const char MODE_TEST = 't';
    const char MODE_GAME = 'j';
    char mode;

    do {//until the user doesn't input the character 'j' or 't'
        cout << "Mode jeu ou mode test ? Veuillez repondre par '" << MODE_GAME << "' ou '" << MODE_TEST << "' : ";
        cin >> mode;
        if (mode != MODE_GAME && mode != MODE_TEST) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (mode != MODE_GAME && mode != MODE_TEST);

    //input dichotomy method and check if it is acceptable
    const char METHOD_DEFAULT = 'd';
    const char METHOD_RAND = 'r';
    char dichotomyMethod;

    do {//until the user doesn't input the character 'd' or 'r'
        cout << "Methode default ou random ? Veuillez repondre par '" << METHOD_DEFAULT << "' ou '" << METHOD_RAND
             << "' : ";
        cin >> dichotomyMethod;
        if (dichotomyMethod != METHOD_DEFAULT && dichotomyMethod != METHOD_RAND) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (dichotomyMethod != METHOD_DEFAULT && dichotomyMethod != METHOD_RAND);


    //input interval limits and check if they are acceptable
    int lowerLimit = 0;
    int higherLimit = 0;

    do {//until the user doesn't input two limits that respect the requirements
        cout << "Entrez la borne inferieure de l'intervalle : ";
        cin >> lowerLimit;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << "Entrez la borne superieure de l'intervalle : ";
        cin >> higherLimit;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Veuillez entrer une intervalle correcte ! " << endl;
        }
    } while (lowerLimit >= higherLimit);

    int num = 0;
    const char YES = 'o';
    const char NO = 'n';

    //check if mode t or j
    if(mode == MODE_GAME){
        //ask to pick up a number (without input) and to answer n or o
        cout << "Veuillez choisir un nombre dans cet intervalle, "
                "puis repondre aux questions par '" << YES << "' ou '" << NO << "'. " << endl;
    }else{ //if mode t //

        do{ //until the user doesn't input a number included in the interval
            //ask to enter the chosen number and check if it's included in the interval
            cout << "Entrez le nombre que vous avez choisi (dans l'intervalle) : ";
            cin >> num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(num > higherLimit || num < lowerLimit);
    }

    //dichotomic research
    int iterator = 1;
    int X = 0;
    srand(time(NULL));

    while(higherLimit-lowerLimit != 0 ){ //until the redefined lower limit matches the redefined higher limit
        if(dichotomyMethod == METHOD_RAND){
            X = rand() % (higherLimit - lowerLimit) + lowerLimit; //define the splitter: a random number included in the interval
        }else{ //if dichotomy method is default
            X = (higherLimit - lowerLimit)/2 + lowerLimit; //define the splitter of the interval
        }

        cout << iterator++ << ". Le nombre est-il plus petit ou egal a " << X << " ? ";
        char answer;

        if(mode == MODE_TEST){
            answer = (num <= X) ? YES : NO;
            cout << answer << endl;
        }else { //if j mode
            do {
                cin >> answer;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Veuillez choisir seulement entre 'o' et 'n' !" << endl;
            } while (answer != NO && answer != YES); //until the user doesn't input the character 'n' or 'o'
        }

        if(answer == YES){
            higherLimit = X;
        }else{ //if answer == 'n'
            lowerLimit = X + 1; //redefine the lower limit as the splitter + 1 (because we ask if the number is inferior or equal to)
            if(higherLimit - X == 1){
                ++X;
            }
        }
    }

    cout << "Le nombre choisi est " << X;

    return 0;
}