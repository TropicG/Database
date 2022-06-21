#ifndef COMMAND_H
#define COMMAND_H
#include "Database.h"

class Command
{
private:
	std::string command;
	Database database;

public:
	Command();

	void execute();

	void executeOpen();
	void executeHelp() const;

	void executeImport();

	void executeShowtables() const;

	void executeDescribe() const;

	void executePrint() const;

	void executeExport() const;

	void executeSelect() const;

	void executeAddCollum();

	void executeUpdate();

	void executeDelete();

	void executeRename();

	void executeCount() const;

	std::string getCommand() const;
};
#endif

