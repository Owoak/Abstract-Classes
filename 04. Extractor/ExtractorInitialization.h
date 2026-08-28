#pragma once
#include "Extractor.h"
#include "BufferedExtractor.h"
#include <sstream>
#include <memory>

class digitsExtractor : public Extractor {
private:
	digitsExtractor(std::istringstream& lineIn) : Extractor(lineIn) {}
	virtual bool process(char symbol, std::string& output) override {
		if (symbol >= '0' and symbol <= '9') {
			output += symbol;
			return true;
		}
		return false;
	}
public:
	friend std::shared_ptr<Extractor> getExtractor(const std::string& extractType, std::istringstream& lineIn);
};

class numbersExtractor :public BufferedExtractor {
private:
	numbersExtractor(std::istringstream& lineIn) :BufferedExtractor(lineIn) {}
	virtual bool shouldBuffer(char symbol) override {
		if (symbol >= '0' and symbol <= '9') {
			return  true;
		}
		else {
			return false;
		}
	}

	friend std::shared_ptr<Extractor> getExtractor(const std::string& extractType, std::istringstream& lineIn);
};

class quotesExtract : public BufferedExtractor {
private:
	bool quoteOpened;
	quotesExtract(std::istringstream& lineIn) :quoteOpened(false), BufferedExtractor(lineIn) {}
	virtual bool shouldBuffer(char symbol) override {
		if (symbol == '"' and quoteOpened) {
			quoteOpened = false;
			return false;
		}
		else if (symbol == '"') {
			quoteOpened = true;
			return false;
		}
		if (quoteOpened) {
			return true;
		}
		else {
			return false;
		}
	}

	friend std::shared_ptr<Extractor> getExtractor(const std::string& extractType, std::istringstream& lineIn);
};

std::shared_ptr<Extractor> getExtractor(const std::string& extractType, std::istringstream& lineIn) {
	if (extractType == "digits") {
		return std::shared_ptr<Extractor>(new digitsExtractor(lineIn));
	}
	else if (extractType == "numbers") {
		return std::shared_ptr<Extractor>(new numbersExtractor(lineIn));
	}
	else if (extractType == "quotes") {
		return std::shared_ptr<Extractor>(new quotesExtract(lineIn));
	}
}