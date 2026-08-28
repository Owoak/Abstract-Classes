#pragma once
#include "FileSystemObject.h"
#include "FileSystemObjectsContainer.h"

#include <memory>
#include <algorithm>
#include <vector>
#include <string>

class Directory final : public FileSystemObject, public FileSystemObjectsContainer, public std::enable_shared_from_this<Directory> {
private:
	std::vector < std::shared_ptr<FileSystemObject>> directoryContents;
public:
	Directory(const std::string& name) :FileSystemObject(name), FileSystemObjectsContainer(), enable_shared_from_this() {}

	virtual void add(const std::shared_ptr<FileSystemObject>& obj) override {
		directoryContents.push_back(obj);
		obj->setParent(shared_from_this());
	}

	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator begin() const override {
		return directoryContents.begin();
	}

	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator end() const override {
		return directoryContents.end();
	}

	virtual void remove(std::shared_ptr<FileSystemObject> obj) override {
		auto it = find(directoryContents.begin(), directoryContents.end(), obj);
		if (it != directoryContents.end()) {
			directoryContents.erase(it);
		}
	}

	virtual size_t getSize() const override {
		size_t sum = 0;
		for (const auto& obj : directoryContents) {
			sum += obj->getSize();
		}
		return sum;
	}
};