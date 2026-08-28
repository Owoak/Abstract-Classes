#pragma once
#include "Filter.h"

class FilterCapital :public Filter {
protected:
	virtual bool shouldFilterOut(char symbol)  const override {
		if (symbol >= 'A' and symbol <= 'Z') {
			return true;
		}
		else {
			return false;
		}
	}
};
class FilterNonCapital :public Filter {
protected:
	virtual bool shouldFilterOut(char symbol)  const override {
		if (symbol >= 'a' and symbol <= 'z') {
			return true;
		}
		else {
			return false;
		}
	}
};
class FilterDigits :public Filter {
protected:
	virtual bool shouldFilterOut(char symbol)  const override {
		if (symbol >= '0' and symbol <= '9') {
			return true;
		}
		else {
			return false;
		}
	}
};

class FilterFactory {
private:

public:
	Filter* buildFilter(const std::string& filterDefinition) const {
		if (filterDefinition == "A-Z") {
			return new FilterCapital();
		}
		else if (filterDefinition == "a-z") {
			return new FilterNonCapital();
		}
		else if (filterDefinition == "0-9") {
			return new FilterDigits();
		}
		return nullptr;
	}
};
