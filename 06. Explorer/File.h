#pragma once
#include "ByteContainer.h"

class File final : public ByteConteiner {
public:
	File(const std::string& name, const std::string& byte) :ByteConteiner(name, byte) {}
};