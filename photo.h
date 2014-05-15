#ifndef PHOTO_H_
#define PHOTO_H_

#include <string>

class Photo
{
public:
	Photo();
Photo(std::string path) : CDN_path(path) {}
private:
	std::string CDN_path;
};
#endif
