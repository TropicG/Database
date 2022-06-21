#include "Command.h"

void Command::execute()
{
	std::cin >> this->command;

	if (command == "open") { this->executeOpen(); return; }

	if (command == "help") { this->executeHelp(); return; }

	if (command == "import") { this->executeImport(); return; }

	if (command == "showtables") { this->executeShowtables(); return; }

	if (command == "describe") { this->executeDescribe(); return; }

	if (command == "print") { this->executePrint(); return; }

	if (command == "export") { this->executeExport(); return; }

	if (command == "select") { this->executeSelect(); return; }

	if (command == "addcollum") { this->executeAddCollum(); return; }

	if (command == "update") { this->executeUpdate(); return; }

	if (command == "delete") { this->executeDelete(); return; }

	if (command == "rename") { this->executeRename(); return; }

	if (command == "count") { this->executeCount(); return; }

	this->command = "end";
}

Command::Command() : database(), command("none")
{
}

void Command::executeOpen() {
	
	std::string fileName;
	std::cin.ignore();
	std::getline(std::cin, fileName);

	Database temp(fileName);

	this->database = temp;

	std::cout << "File succsesfully open!\n";
}

void Command::executeHelp() const {

	std::cout <<
		"The following commands are supported: \n" <<
		"open <file> opens <file> \n" <<
		"close closes currently opened file\n" <<
		"save saves the currently open file\n" <<
		"saveas <file> saves the currently open file in <file>\n" <<
		"help prints this information\n" <<
		"exit exists the program\n";
}

void Command::executeRename() {

	std::string oldName;
	std::getline(std::cin, oldName);

	std::string newName;
	std::getline(std::cin, newName);

	this->database.rename(oldName, newName);
}

void Command::executeCount() const
{
	std::string name;
	std::getline(std::cin, name);

	int searchIndex = 0;
	std::cin >> searchIndex;

	std::string searchValue;
	std::getline(std::cin, searchValue);

	this->database.count(name, searchIndex,searchValue);
}

std::string Command::getCommand() const
{
	return this->command;
}

void Command::executeImport() {

	std::string fileName;
	std::getline(std::cin, fileName);

	Table table(fileName);
	this->database.import(table);
}

void Command::executeShowtables() const {

	this->database.showtables();
}

void Command::executeDescribe() const {

	std::string name;
	std::getline(std::cin, name);

	this->database.describe(name);
}

void Command::executePrint() const {

	std::string name;
	std::getline(std::cin, name);

	this->database.print(name);
}

void Command::executeExport() const {

	std::string name;
	std::getline(std::cin, name);

	std::string fileName;
	std::getline(std::cin, fileName);

	this->database.exprt(name, fileName);
}

void Command::executeSelect() const
{

	int index = 0;
	std::cin >> index;

	std::string value;
	std::getline(std::cin, value);

	std::string name;
	std::getline(std::cin, name);

	this->database.select(index, value, name);
}

void Command::executeAddCollum()
{
	std::string name;
	std::getline(std::cin, name);

	this->database.addCollum(name);
}

void Command::executeUpdate()
{
	std::string name;
	std::getline(std::cin, name);

	int searchIndex = 0;
	std::cin >> searchIndex;

	std::string searchValue;
	std::getline(std::cin, searchValue);

	int changeIndex = 0;
	std::cin >> changeIndex;

	std::string changeValue;
	std::getline(std::cin, changeValue);

	this->database.update(name, searchIndex, searchValue, changeIndex, changeValue);
}

void Command::executeDelete()
{
	std::string name;
	std::getline(std::cin, name);

	int searchIndex = 0;
	std::cin >> searchIndex;

	std::string searchValue;
	std::getline(std::cin, searchValue);

	this->database.dlt(name, searchIndex, searchValue);
}