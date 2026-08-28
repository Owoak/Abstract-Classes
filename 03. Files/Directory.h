#pragma once
#include "File.h"
#include <string>
#include <vector>
class Directory :public FileSystemObject, public FileSystemObjectsContainer {
protected:
	std::vector <  std::shared_ptr<FileSystemObject>> directoryContents;
public:
	virtual ~Directory() = default;
	Directory(const std::string& directoryName) :directoryContents(), FileSystemObject(directoryName), FileSystemObjectsContainer() {}

	virtual size_t getSize() const override {
		if (directoryContents.empty()) {
			return (size_t)0;
		}

		size_t sizeSum = 0;
		for (auto it = directoryContents.begin(); it != directoryContents.end(); it++) {
			sizeSum += (*it)->getSize();
		}
		return sizeSum;
	}
	virtual void add(const std::shared_ptr<FileSystemObject>& obj) override {
		directoryContents.push_back(obj);
	}
};