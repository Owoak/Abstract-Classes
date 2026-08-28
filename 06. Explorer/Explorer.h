#pragma once
#include "File.h"
#include "Directory.h"
#include "Shortcuts.h"

#include <vector>
#include <memory>

class RootDirectory : public FileSystemObjectsContainer, public FileSystemObject, public std::enable_shared_from_this<RootDirectory> {
public:
	std::vector<std::shared_ptr<FileSystemObject>>& rootObjects;
	RootDirectory(std::vector<std::shared_ptr<FileSystemObject>>& rootObjects) :FileSystemObject("RootDirectory"), FileSystemObjectsContainer(), rootObjects(rootObjects) {}

	virtual void add(const std::shared_ptr<FileSystemObject>& obj)override {
		rootObjects.push_back(obj);
		obj->setParent(shared_from_this());
	}
	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator begin() const override {
		return rootObjects.begin();
	}
	virtual std::vector<std::shared_ptr<FileSystemObject> >::const_iterator end() const override {
		return rootObjects.end();
	}
	virtual void remove(std::shared_ptr<FileSystemObject> obj) override {
		for (auto it = rootObjects.begin(); it != rootObjects.end(); it++) {
			if (*it == obj) {
				rootObjects.erase(it);
				return;
			}
		}
	}

	virtual size_t getSize() const override {
		return rootObjects.size();
	};
	virtual ~RootDirectory() {}
	friend class Explorer;
};

class Explorer final {
private:
	std::shared_ptr<RootDirectory> rootPtr;
	std::shared_ptr<FileSystemObjectsContainer>currDirectoryPtr;
	std::vector< std::shared_ptr<FileSystemObject>>clipboard;
	std::shared_ptr<Shortcuts> shortcuts;

public:
	Explorer(std::vector<std::shared_ptr<FileSystemObject>>& rootObjects) : rootPtr(std::make_shared<RootDirectory>(rootObjects)), currDirectoryPtr(rootPtr), clipboard(), shortcuts(std::make_shared<Shortcuts>()) {}

	void createFile(const std::string& filename, const  std::string& bytes) {
		std::shared_ptr<FileSystemObject> obj = std::make_shared<File>(filename, bytes);
		currDirectoryPtr->add(obj);
	}

	void createDirectory(const std::string& filename) {
		std::shared_ptr<FileSystemObject> obj = std::make_shared<Directory>(filename);
		currDirectoryPtr->add(obj);
	}

	void cut(const std::string& lookingFor) {
		auto it = std::find_if(currDirectoryPtr->begin(), currDirectoryPtr->end(), [&lookingFor](const std::shared_ptr<FileSystemObject>& currOnj) {return currOnj->getName() == lookingFor; });
		if (it != currDirectoryPtr->end()) {
			clipboard.push_back(*it);
		}
	}

	void paste() {
		for (auto& clipboardObject : clipboard) {
			moveTo(clipboardObject, currDirectoryPtr);
		}
	}

	void createShortcut(const std::string lookingFor) {
		if (shortcuts == nullptr) {
			rootPtr->add(shortcuts);
		}
		auto it = std::find_if(currDirectoryPtr->begin(), currDirectoryPtr->end(), [&lookingFor](const std::shared_ptr<FileSystemObject>& currObj) {return currObj->getName() == lookingFor; });
		if (it != currDirectoryPtr->end()) {
			shortcuts->add(*it);
		}
	}

	void navigate(const std::string& path) {
		if (path == "..") {
			currDirectoryPtr = std::dynamic_pointer_cast<FileSystemObjectsContainer>(std::dynamic_pointer_cast<FileSystemObject>(currDirectoryPtr)->getParent().lock());
		}
		else {
			auto it = std::find_if(currDirectoryPtr->begin(), currDirectoryPtr->end(), [&path](const std::shared_ptr<FileSystemObject>& currObj) {return currObj->getName() == path; });
			if (it != currDirectoryPtr->end()) {
				currDirectoryPtr = std::dynamic_pointer_cast<FileSystemObjectsContainer>(*it);
			}
		}
	}
private:
	void moveTo(std::shared_ptr<FileSystemObject>& objectToMove, std::shared_ptr<FileSystemObjectsContainer> directoryToMoveTo) {
		std::shared_ptr<FileSystemObjectsContainer> parentContainer = std::dynamic_pointer_cast<FileSystemObjectsContainer>(objectToMove->getParent().lock());
		parentContainer->remove(objectToMove);
		directoryToMoveTo->add(objectToMove);
	}
};