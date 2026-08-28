#pragma once
#include "FileSystemObject.h"

#include <string>

class ByteConteiner : public FileSystemObject {
protected:
	std::string byte;
public:
	ByteConteiner(const std::string& name, const  std::string& Byte) :byte(Byte), FileSystemObject(name) {}
	virtual size_t getSize() const override { return byte.size(); };
};