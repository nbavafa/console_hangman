
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//To-Do List
//export biggest guessed numbers to txt file
//Prettier to look at

//Problems


char guessedLetters[26];
int correct = 0;
int guesses = 0;
char userInput;


int game ();
bool isValidWord(string word);
int IsCharDuplication(string s);
char getGuess();
bool letterCheck(char c, string word);
int printer (char display[], int wordLength);
int game ();
int highscore(string name);

int main() {
	game();
}

int highscore(string name, string word, string score) {

    string strReplace;
    string strNew = "";
    ifstream filein("highscores.txt");
    ofstream fileout("temp.txt");
    if(!filein || !fileout) {
        cout << "Error opening files!" << endl;
        return 1; }

    string strTemp;
    bool found = false;
    while(filein >> strTemp) {
        if(strTemp == strReplace){
            strTemp = strNew;
            found = true;
        }
        strTemp += "\n";
        fileout << strTemp;
        if(found) break;
    }
  return 0;
}

bool isValidWord(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (word[i] <='a' && word[i] >='z') return false;}
	return true;
}

int IsCharDuplication(string s) {
  int num = 0;
  for (int i = 0; i < s.length(); i++)
    for (int j = i+1; j < s.length(); j++)
      if (s[i] == s[j])
        num++;
 return num;
}

char getGuess() {
	char input;
	bool run = true;
	bool found = false;

	while (run == true) {
		found = false;
		input = '\0';
		cout <<"Guessed Letters: ";
		for (int i = 0; i < 26; i++) {
			if (guessedLetters[i] != '\0')
				cout <<guessedLetters[i]<<", ";
		}
		cout <<endl<<endl<<"Enter a guess: ";
		cin >>input;
		guesses++;

		for (int j = 0; j < 26; j++) {
			if (guessedLetters[j] == input) {
				cout <<endl<<"That letter has been guessed already!"<<endl;
				 found = true;}
			}
			if (found == false)
				run = false;
		}

	guessedLetters[correct] = input;
	size_t arraySize = sizeof(guessedLetters)/sizeof(*guessedLetters);
	std::sort(guessedLetters, guessedLetters+arraySize);
	return tolower(input);
}

bool letterCheck(char c, string word) {

	for (int i = 0; i < word.length(); i++) {
		if (word[i] == c)
			return true;}
	return false;
}

int printer (char display[], int wordLength) {
	for (int i = 0; i < wordLength; i++)
		cout << display[i] << " ";
	cout <<endl;
	return 0;

}

int game () {

	string dictFilename= "wordlist.txt";
	string word;

	char duplicates[26];

	int dictLength = 69903;
	int unique = 0;
	int dups = 0;

	for (int i = 0; i < 26; i++) {
		guessedLetters[i] = '\0'; }

	ifstream fin;
	fin.open(dictFilename.c_str());
	if (!fin.good()) throw "I/O error";

	srand (time(NULL));

	int wordNum;
	while (true) {
		wordNum = rand() % dictLength;

		for (int i = 0; i < wordNum; i++) {
			getline(fin, word); }
		if (isValidWord(word) == true) break;
	}


	int wordLength = word.length() - 1;
  dups = IsCharDuplication(word);

	unique = wordLength - dups;

	char display[wordLength];

	for (int i = 0; i < wordLength; i++) {
		display[i] = '_'; }

	printer(display, wordLength);
	cout <<endl<<"Word Length: "<<wordLength<<endl;

	char again = 'y';
	bool go = true;
	while (true) {
		userInput = getGuess();
		if (letterCheck(userInput, word) == true) {
			correct++;

			cout <<"That letter is in the word!"<<endl;
			for (int i = 0; i < wordLength+1; i++) {
				if (tolower(word[i]) == userInput) {
					display[i] = userInput;
				}
			}
			printer(display, wordLength);
			go = true;
			while (go == true) {
				if (correct == unique) {

					//highscore check


					cout <<"You win! It took "<<guesses<<" guesses. \nWould you like to play again[Y/N]: ";
					cin >>again;

					if (tolower(again) == 'y') {
						correct = 0;
						guesses = 0;
						game();}
					else if (tolower(again) == 'n') {
						cout <<endl<<"Thanks for playing!"<<endl;
						return 0;}
					else {continue;}
				}
				else {go = false;}
			}
		}
   	else if (letterCheck(userInput, word) == false) {
			cout <<"That letter is NOT in the word!"<<endl;
			printer(display, wordLength);
			continue;
		}
		else {continue;}

}
	fin.close();
}
