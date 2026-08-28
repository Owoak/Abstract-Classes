#pragma once
#include "FileSystemObject.h"
#include <string>
class ByteContainer : public FileSystemObject {
private:
	std::string contents;
public:
	ByteContainer(const std::string& filename, const std::string& contents) :FileSystemObject(filename), contents(contents) {}
	virtual size_t getSize() const override {
		return contents.size();
	}
};