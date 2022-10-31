#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

//структура котора€ делает узелки и св€зывает их между собой

struct AnimalKnot
{
	string question = "";
	string animal_guess = "";
	AnimalKnot *yesnode = nullptr;
	AnimalKnot *nonode = nullptr;
};

AnimalKnot *newnode, *root, *start;


void ResponseCheck(string& UserResponse);

void LearningNewInformation(string& NewQuestion, string& NewAnimal, string& answer);

void NewNodes(AnimalKnot *CurrentNode, string& UserResponse);

void GameLaunch(AnimalKnot *CurrentNode);

bool ContinuationGame();

void filing(AnimalKnot*& root, fstream& file);

void FileReading(AnimalKnot*& root, fstream& file);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream file;
	struct stat buffer;
	int present = stat("Data.txt", &buffer);
	if (present == 0)
	{
		file.open("Data.txt", ios::in);
		FileReading(start, file);
		file.close();
		cout << "Ёто игра угадай животное. Ќа вопросы в ходе игры можно отвечать только в такой форме:" << endl;
		cout << "да" << endl;
		cout << "нет" << endl;
		do {
			GameLaunch(start);
		} while (ContinuationGame());
		file.open("Data.txt", ios::out);
		filing(start, file);
		file.close();
	}
	else
	{
		cout << "Ќе получилось открыть файл" << endl;
	}



	/*AnimalKnot *initial = new AnimalKnot;
	initial->animal_guess = "¬олк";

	cout << "Ёто игра угадай животное. Ќа вопросы в ходе игры можно отвечать только в такой форме:"<< endl;
	cout << "да" << endl;
	cout << "нет" << endl;

	do {
		GameLaunch(initial);
	} while (ContinuationGame());*/

}

//тут провер€етс€ правильность введенных ответов

void ResponseCheck(string& UserResponse) {
	cin >> UserResponse;

	while (!(UserResponse == "нет" || UserResponse == "да")) {
		cout << "¬ы ввели неправльный ответ. ќтвечать можно только нет и да, введите новый ответ:" << endl;
		cin >> UserResponse;
	}
}

//тут € получаю допольнительную информацию, если у мен€ еЄ недостаточно, когда дерево животное неугадало

void LearningNewInformation(string& NewQuestion, string& NewAnimal, string& answer) {
	cout << "„то за животное вы загадали?" << endl;
	cin >> NewAnimal;
	//ниже очищаю cin, иначе getline не работает, потому что думает, что в cin что-то есть
	cin.ignore(); 

	cout << "ѕридумайте вопрос, который будет отличать ваше животного, от предложенного ранее:" << endl;
	getline(cin, NewQuestion);

	cout << " акой будет ответ на этот вопрос, чтобы получить ваше животное?" << endl;

	cin >> answer;
}

//вот это вообще песн€. “ут дерево дополн€етс€ новыми узелками и расшир€етс€

void NewNodes(AnimalKnot *CurrentNode, string& UserResponse) {

	string NewQuestion;
	string NewAnimal;
	string answer;

	//тут вроде и так всЄ пон€тно, создаю новые узлы, заполн€ю их, мен€ю исходный узел
	cout << "Ёто " << CurrentNode->animal_guess << "?" << endl;
	ResponseCheck(UserResponse);

	if (UserResponse == "да") {
		cout << " омпьютер молодец! ќн угадал твоЄ животное!" << endl;
	}
	else {
		LearningNewInformation(NewQuestion, NewAnimal, answer);
		AnimalKnot *yesnode;
		AnimalKnot *nonode;

		if (answer == "да") {
			yesnode = new AnimalKnot;
			yesnode->animal_guess = NewAnimal;

			nonode = new AnimalKnot;
			nonode->animal_guess = CurrentNode->animal_guess;
		}
		else if (answer == "нет") {
			yesnode = new AnimalKnot;
			yesnode->animal_guess = CurrentNode->animal_guess;

			nonode = new AnimalKnot;
			nonode->animal_guess = NewAnimal;

		}
		CurrentNode->animal_guess = "";
		CurrentNode->question = NewQuestion;
		CurrentNode->yesnode = yesnode;
		CurrentNode->nonode = nonode;

	}
}

//вот тут перемещение по дереву 

void GameLaunch(AnimalKnot *CurrentNode) {

	string UserResponse;

	//если вопрос не пустой, то движемс€ дальше(использу€ рекурсию) и задаем пользователю вопросы, если пустой, то общаемс€ к другой функции

	if (CurrentNode->question != "") {
		cout << CurrentNode->question << endl;
		ResponseCheck(UserResponse);

		if (UserResponse == "да") {
			GameLaunch(CurrentNode->yesnode);
		}
		else {
			GameLaunch(CurrentNode->nonode);
		}
	}
	else {
		NewNodes(CurrentNode, UserResponse);
	}

}

//тут надо узнать хочет пользователь играть в это ещЄ раз или нет

bool ContinuationGame() {
	string proceed;

	cout << "’отите ещЄ сыграть?(ответьте да или нет)" << endl;
	ResponseCheck(proceed);

	if (proceed == "да") {
		return true;
	}
	else {
		return false;
	}
}

void filing(AnimalKnot*& root, fstream& file)
{
	if (root == nullptr)
		file << "#" << endl;
	else
	{	
		if (root->animal_guess != "") {
			file << root->animal_guess << endl;
		}
		else {
			file << root->question << endl;
			filing(root->yesnode, file);
			filing(root->nonode, file);
		}
	}
}

void FileReading(AnimalKnot*& root, fstream& file)
{
	string str;
	if (!file.eof())
	{
		getline(file, str);
		cin.clear();
	}
	else
		return;
	if (str != "#")
	{
		if (str.find("?") == -1) {
			root = new AnimalKnot;
			root->animal_guess = str;
		}
	
		else {
			root = new AnimalKnot;
			root->question = str;
			FileReading(root->yesnode, file);
			FileReading(root->nonode, file);
		}
	}
	else
	{
		root = nullptr;
	}
}