#ifndef FILTER_H
#define FILTER_H

#include "Image.h"


using namespace imaging;

class Filter {

public:

	Filter() {}

	virtual Image operator << (const Image & image) = 0;

};
#endif
