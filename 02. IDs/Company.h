#pragma once
#include <sstream>
#include <utility>
#include <vector>

class HasId {
public:
	virtual int getId() const = 0;
	virtual ~HasId() {}
};

class HasInfo {
public:
	virtual std::string getInfo() const = 0;
	virtual ~HasInfo() {}
};

class Company :public HasId, public HasInfo {
private:
	int id;
	std::string name;
	std::vector < std::pair<char, char>> employees;
public:
	Company();
	Company(int id, std::string name, std::vector<std::pair<char, char> > employees);
	virtual  int getId() const override;
	std::string getName() const;

	std::vector<std::pair<char, char>> getEmployees() const;
	virtual std::string getInfo() const override;

	friend std::ostream& operator<<(std::ostream& stream, const Company& c);
	friend std::istream& operator>>(std::istream& stream, Company& c);
};
