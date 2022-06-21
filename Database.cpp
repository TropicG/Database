#include "Database.h"

bool Database::inside(const std::string& name) const
{
    for (int i = 0; i < this->size; ++i) {
        if (this->tables[i].getName() == name) return true;
    }

    return false;
}

int Database::getLocOfTable(const std::string& name) const
{
    for (int i = 0; i < this->size; ++i) {
        if (this->tables[i].getName() == name) return i;
    }

    return -1;
}

void Database::resize()
{
    Table* newTables = new (std::nothrow) Table[this->cap * 2];

    this->cap *= 2;

    for (int i = 0; i < this->size; ++i) {
        newTables[i] = this->tables[i];
    }

    this->del();
    this->tables = newTables;
}

void Database::cpy(const Database& other)
{
    for (int i = 0; i < this->size; ++i) {
        this->tables[i] = other.tables[i];
    }
}

void Database::aloc(const int& cap)
{
    this->tables = new (std::nothrow) Table[cap];
}

void Database::del()
{
    delete[] this->tables;
}

Database::Database() : cap(CAP_START_TABLE)
{
    this->aloc(cap);
}

Database::Database(const std::string& filename)
{
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        file >> *this;
    }
    else {
        std::cout << "Cant open file, sry";
    }
}

Database::Database(const Database& other)
{
    this->size = other.size;
    this->cap = other.cap;

    this->del();
    this->aloc(this->cap);
    this->cpy(other);
}

Database& Database::operator=(const Database& other)
{
    if (this != &other) {

        this->size = other.size;
        this->cap = other.cap;

        this->del();
        this->aloc(this->cap);
        this->cpy(other);
    }

    return *this;
}

Database::~Database()
{
    this->del();
}

void Database::addCollum(const std::string name)
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].addCollum();
}

void Database::update(const std::string name, const int& searchIndex, const std::string& searchValue, const int& changeIndex, const std::string& changeValue)
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].update(searchIndex, searchValue, changeIndex, changeValue);
}

void Database::select(const int& index, std::string& value, std::string& name) const
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].select(index, value);
}

void Database::dlt(const std::string name, const int& index, const std::string& value)
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].deleteRow(index, value);
}

void Database::rename(const std::string& oldName,const std::string& newName)
{
    if (this->getLocOfTable(newName) == -1) {
    
        int loc = this->getLocOfTable(oldName);
        this->tables->setName(newName);
        return;
    }

    std::cout << "Cant change to: " << newName << "\n";
    return;
}

int Database::count(const std::string& name, const int& index, const std::string& value) const
{
    int loc = this->getLocOfTable(name);

    return this->tables[loc].count(index,value);
}

void Database::import(const Table& table)
{

    if (this->size == this->cap) this->resize();

    if (this->inside(table.getName())) {
        std::cout << "This table is already added";
        return;
    }

    this->tables[this->size] = table;
    this->size++;
}

void Database::exprt(const std::string& name, const std::string& filename) const
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].exprt(filename);
}

void Database::showtables() const
{
    for (int i = 0; i < this->size; ++i) {
        std::cout << this->tables[i].getName() << " ";
    }
}

void Database::print(const std::string& name) const
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].print();
}

void Database::describe(const std::string& name) const
{
    int loc = this->getLocOfTable(name);

    this->tables[loc].printTypes();
}

std::ostream& operator<<(std::ostream& os, const Database& database)
{
    os << database.size << "\n";
    for (int i = 0; i < database.size; ++i) {
        os << database.tables[i];
    }

    return os;
}

std::istream& operator>>(std::istream& is, Database& database)
{
    int tables = 0;
    is >> tables;
    is.ignore();

    database.size = 0;
    database.cap = tables;
    database.del();
    database.aloc(tables);

    Table temp;

    for (int i = 0; i < tables; ++i) {
        is >> temp;
        database.import(temp);
    }

    return is;
}
