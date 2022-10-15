#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

//структура которая делает узелки и связывает их между собой

struct AnimalKnot
{
	string question = "";
	string animal_guess = "";

	AnimalKnot *yesnode = nullptr;
	AnimalKnot *nonode = nullptr;
};

void ResponseCheck(string& UserResponse);

void LearningNewInformation(string& NewQuestion, string& NewAnimal, string& answer);

void NewNodes(AnimalKnot *CurrentNode, string& UserResponse);

void GameLaunch(AnimalKnot *CurrentNode);

bool ContinuationGame();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	AnimalKnot *initial = new AnimalKnot;
	initial->animal_guess = "Волк";

	cout << "Это игра угадай животное. На вопросы в ходе игры можно отвечать только в такой форме:"<< endl;
	cout << "да" << endl;
	cout << "нет" << endl;

	do {
		GameLaunch(initial);
	} while (ContinuationGame());

}

//тут проверяется правильность введенных ответов

void ResponseCheck(string& UserResponse) {
	cin >> UserResponse;

	while (!(UserResponse == "нет" || UserResponse == "да")) {
		cout << "Вы ввели неправльный ответ. Отвечать можно только нет и да, введите новый ответ:" << endl;
		cin >> UserResponse;
	}
}

//тут я получаю допольнительную информацию, если у меня её недостаточно, когда дерево животное неугадало

void LearningNewInformation(string& NewQuestion, string& NewAnimal, string& answer) {
	cout << "Что за животное вы загадали?" << endl;
	cin >> NewAnimal;
	//ниже очищаю cin, иначе getline не работает, потому что думает, что в cin что-то есть
	cin.ignore(); 

	cout << "Придумайте вопрос, который будет отличать ваше животного, от предложенного ранее:" << endl;
	getline(cin, NewQuestion);

	cout << "Какой будет ответ на этот вопрос, чтобы получить ваше животное?" << endl;

	cin >> answer;
}

//вот это вообще песня. Тут дерево дополняется новыми узелками и расширяется

void NewNodes(AnimalKnot *CurrentNode, string& UserResponse) {

	string NewQuestion;
	string NewAnimal;
	string answer;

	//тут вроде и так всё понятно, создаю новые узлы, заполняю их, меняю исходный узел
	cout << "Это " << CurrentNode->animal_guess << "?" << endl;
	ResponseCheck(UserResponse);

	if (UserResponse == "да") {
		cout << "Компьютер молодец! Он угадал твоё животное!" << endl;
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

	//если вопрос не пустой, то движемся дальше(используя рекурсию) и задаем пользователю вопросы, если пустой, то общаемся к другой функции

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

//тут надо узнать хочет пользователь играть в это ещё раз или нет

bool ContinuationGame() {
	string proceed;

	cout << "Хотите ещё сыграть?(ответьте да или нет)" << endl;
	ResponseCheck(proceed);

	if (proceed == "да") {
		return true;
	}
	else {
		return false;
	}
}
