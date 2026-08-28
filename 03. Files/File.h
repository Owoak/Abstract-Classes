#pragma once
#include "ByteContainer.h"
#include <string>

class File :public ByteContainer {
public:
	virtual ~File() = default;
	File(const std::string& filename, const std::string& bytes) :ByteContainer(filename, bytes) {}
};