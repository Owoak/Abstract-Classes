#pragma once
#include <sstream>
#include <vector>
#include <algorithm>

std::vector < std::shared_ptr<FileSystemObject>> buildVectorByIt(std::vector <std::shared_ptr<FileSystemObject>>::const_iterator begin, std::vector <std::shared_ptr<FileSystemObject>>::const_iterator end) {
	std::vector < std::shared_ptr<FileSystemObject>> vector(end - begin);
	std::copy(begin, end, vector.begin());
	return vector;
}

std::string getTreeView(std::vector <std::shared_ptr<FileSystemObject>>::const_iterator begin, std::vector <std::shared_ptr<FileSystemObject>>::const_iterator end, std::string indent) {
	std::vector <std::shared_ptr<FileSystemObject>> currentContainer = buildVectorByIt(begin, end);
	std::sort(currentContainer.begin(), currentContainer.end(), [](const std::shared_ptr<FileSystemObject> a, const std::shared_ptr<FileSystemObject> b) {
		return a->getName() < b->getName(); });

	std::ostringstream treeOutput;
	for (auto it = currentContainer.begin(); it != currentContainer.end(); it++) {
		treeOutput << indent << (*it)->getName() << std::endl;
		FileSystemObjectsContainer* container = dynamic_cast<FileSystemObjectsContainer*>((*it).get());
		if (container != nullptr) {
			treeOutput << getTreeView(container->begin(), container->end(), indent + "--->");
		}
	}

	return treeOutput.str();
}

std::string getTreeView(const std::vector<std::shared_ptr<FileSystemObject> >& rootObjects) {
	std::ostringstream treeOutput;

	treeOutput << getTreeView(rootObjects.begin(), rootObjects.end(), "");

	return treeOutput.str();
}
