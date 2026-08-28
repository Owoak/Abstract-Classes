#pragma once
#include "ByteContainer.h"
#include <string>

class File final :public ByteContainer {
public:
	File(const std::string& filename, const std::string& contents) :ByteContainer(filename, contents) {}
};