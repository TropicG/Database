#include "Table.h"

void Table::resize()
{
    Row* newRows = new (std::nothrow) Row[this->cap * 2];
    if (newRows == nullptr) {
        std::cout << "Failed memory allocation";
        return;
    }

    for (int i = 0; i < this->size; ++i) {
        newRows[i] = this->rows[i];
    }

    this->del();
    this->rows = newRows;


    this->cap *= 2;
}

void Table::cpy(const Table& other)
{
    for (int i = 0; i < this->size; ++i) {
        this->rows[i] = other[i];
    }
}

void Table::aloc(const int& cap)
{
    this->rows = new (std::nothrow) Row[cap];
}

void Table::del()
{
    delete[] this->rows;
}

Table::Table() : name("none"), filename("none"), cap(CAP_START_TABLE), size(0)
{
    this->aloc(cap);
}

Table::Table(const std::string& filename) : filename(filename)
{
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        file >> *this;
    }
    else {
        std::cout << "Could not open file, sry";
    }
}

Table::Table(const Table& other) :
    name(other.name), filename(other.filename), cap(other.cap), size(other.size)
{
    this->aloc(cap);
    this->cpy(other);
}

Table& Table::operator=(const Table& other)
{
    if (this != &other) {

        this->del();

        this->name = other.name;
        this->filename = other.filename;
        this->cap = other.cap;
        this->size = other.size;

        this->aloc(this->cap);
        this->cpy(other);
    }

    return *this;
}

Table::~Table()
{
    this->del();
}

void Table::add(const Row& row)
{
    if (this->size == this->cap) this->resize();

    this->rows[this->size] = row;
    this->size++;
}

void Table::select(const int& index, std::string& value) const
{
    std::vector<Row> selectedRows;

    for (int i = 0; i < this->size; ++i) {
        if (this->rows[i].find(value, index)) selectedRows.push_back(this->rows[i]);
    }

    std::string command;
    int i = 0;

    while (true) {

        std::cin >> command;

        selectedRows[i].print();

        if (command == "Next") i++;
        else if (command == "Last") i--;
        else break;

        if (i >= this->size || i < 0) break;
    }

}

void Table::update(const int& indexFind, const std::string& valueFind, const int& indexChange, const std::string& valueChange)
{
    for (int i = 0; i < this->size; ++i) {
        if (this->rows[i].find(valueFind, indexFind))
            this->rows[i].update(valueChange, indexChange);
    }
}

void Table::deleteRow(const int& index, const std::string& value)
{

    Row* newRows = new (std::nothrow) Row[this->cap];
    if (!newRows) {
        std::cout << "Failed memory allocation";
        return;
    }

    int newSize = 0;

    for (int i = 0; i < this->size; ++i) {
        if (!this->rows[i].find(value, index)) {
            newRows[newSize++] = this->rows[i];
        }
    }

    this->del();

    this->rows = newRows;
    this->size = newSize;
}

void Table::addCollum()
{
    
    Cell cell("NULL", "NULL");

    for (int i = 0; i < this->size; ++i) {
        this->rows[i].add(cell);
    }

}

int Table::count(const int& index, const std::string& value) const
{
    int count = 0;

    for (int i = 0; i < this->size; ++i) {
        if (this->rows[i].find(value, index)) count++;
    }

    return count;

}

void Table::exprt(const std::string& filename) const
{
    std::ofstream file;
    file.open(filename);
    if (!file) {
        std::cout << "Cant open file, sry";
        return;
    }

    file << *this;
}

Row Table::operator[](const int& index) const
{
    return this->rows[index];
}

std::string Table::getName() const
{
    return this->name;
}

void Table::setName(const std::string& name)
{
    this->name = name;
}

void Table::printTypes() const
{
    for (int i = 0; i < this->size; ++i) {
        this->rows[i].printTypes();
    }

    std::cout << "\n";
}

void Table::print() const
{

    std::string command;
    int i = 0;

    while (true) {

        std::cin >> command;

        this->rows[i].print();

        if (command == "Next") i++;
        else if (command == "Last") i--;
        else break;

        if (i >= this->size || i < 0) break;
    }
}

std::ostream& operator<<(std::ostream& os, const Table& table)
{
    os << table.size << "\n";
    os << table.name << "\n";
    for (int i = 0; i < table.size; ++i) {
        os << table.rows[i];
    }

    return os;
}

std::istream& operator>>(std::istream& is, Table& table)
{
    int rows = 0;
    is >> rows;
    is.ignore();

    std::getline(is, table.name);

    table.size = 0;
    table.cap = rows;
    table.del();
    table.aloc(rows);

    Row tempRow;

    for (int i = 0; i < rows; ++i) {
        is >> tempRow;
        table.add(tempRow);
    }

    return is;
}
