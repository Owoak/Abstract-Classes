#pragma once
#include <string>

class ByteContainer : public FileSystemObject {
protected:
	std::string bytes;
	ByteContainer(const std::string& filename, const std::string& bytes) :FileSystemObject(filename), bytes(bytes) {}

public:
	virtual size_t getSize() const override {
		return bytes.size();
	}
	const std::string& getBytes() const {
		return bytes;
	}
	virtual ~ByteContainer() = default;
};