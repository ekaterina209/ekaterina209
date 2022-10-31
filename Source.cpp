#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

//��������� ������� ������ ������ � ��������� �� ����� �����

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
		cout << "��� ���� ������ ��������. �� ������� � ���� ���� ����� �������� ������ � ����� �����:" << endl;
		cout << "��" << endl;
		cout << "���" << endl;
		do {
			GameLaunch(start);
		} while (ContinuationGame());
		file.open("Data.txt", ios::out);
		filing(start, file);
		file.close();
	}
	else
	{
		cout << "�� ���������� ������� ����" << endl;
	}



	/*AnimalKnot *initial = new AnimalKnot;
	initial->animal_guess = "����";

	cout << "��� ���� ������ ��������. �� ������� � ���� ���� ����� �������� ������ � ����� �����:"<< endl;
	cout << "��" << endl;
	cout << "���" << endl;

	do {
		GameLaunch(initial);
	} while (ContinuationGame());*/

}

//��� ����������� ������������ ��������� �������

void ResponseCheck(string& UserResponse) {
	cin >> UserResponse;

	while (!(UserResponse == "���" || UserResponse == "��")) {
		cout << "�� ����� ����������� �����. �������� ����� ������ ��� � ��, ������� ����� �����:" << endl;
		cin >> UserResponse;
	}
}

//��� � ������� ��������������� ����������, ���� � ���� � ������������, ����� ������ �������� ���������

void LearningNewInformation(string& NewQuestion, string& NewAnimal, string& answer) {
	cout << "��� �� �������� �� ��������?" << endl;
	cin >> NewAnimal;
	//���� ������ cin, ����� getline �� ��������, ������ ��� ������, ��� � cin ���-�� ����
	cin.ignore(); 

	cout << "���������� ������, ������� ����� �������� ���� ���������, �� ������������� �����:" << endl;
	getline(cin, NewQuestion);

	cout << "����� ����� ����� �� ���� ������, ����� �������� ���� ��������?" << endl;

	cin >> answer;
}

//��� ��� ������ �����. ��� ������ ����������� ������ �������� � �����������

void NewNodes(AnimalKnot *CurrentNode, string& UserResponse) {

	string NewQuestion;
	string NewAnimal;
	string answer;

	//��� ����� � ��� �� �������, ������ ����� ����, �������� ��, ����� �������� ����
	cout << "��� " << CurrentNode->animal_guess << "?" << endl;
	ResponseCheck(UserResponse);

	if (UserResponse == "��") {
		cout << "��������� �������! �� ������ ��� ��������!" << endl;
	}
	else {
		LearningNewInformation(NewQuestion, NewAnimal, answer);
		AnimalKnot *yesnode;
		AnimalKnot *nonode;

		if (answer == "��") {
			yesnode = new AnimalKnot;
			yesnode->animal_guess = NewAnimal;

			nonode = new AnimalKnot;
			nonode->animal_guess = CurrentNode->animal_guess;
		}
		else if (answer == "���") {
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

//��� ��� ����������� �� ������ 

void GameLaunch(AnimalKnot *CurrentNode) {

	string UserResponse;

	//���� ������ �� ������, �� �������� ������(��������� ��������) � ������ ������������ �������, ���� ������, �� �������� � ������ �������

	if (CurrentNode->question != "") {
		cout << CurrentNode->question << endl;
		ResponseCheck(UserResponse);

		if (UserResponse == "��") {
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

//��� ���� ������ ����� ������������ ������ � ��� ��� ��� ��� ���

bool ContinuationGame() {
	string proceed;

	cout << "������ ��� �������?(�������� �� ��� ���)" << endl;
	ResponseCheck(proceed);

	if (proceed == "��") {
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