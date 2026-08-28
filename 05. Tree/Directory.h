#pragma once
#include <vector>

class Directory final :public FileSystemObject, public FileSystemObjectsContainer {
private:
	std::vector < std::shared_ptr<FileSystemObject>> directoryContents;
public:
	Directory(const std::string& name) :directoryContents(), FileSystemObject(name), FileSystemObjectsContainer() {}

	virtual void add(const std::shared_ptr<FileSystemObject>& obj) override {
		directoryContents.push_back(obj);
	}
	virtual size_t getSize() const override {
		size_t sum = 0;
		for (const auto& content : directoryContents) {
			sum += content->getSize();
		}
		return sum;
	}

	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator begin() const override {
		return directoryContents.begin();
	}
	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator end() const override {
		return directoryContents.end();
	}
};