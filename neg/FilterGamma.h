#include "Filter.h"
#include "Image.h"

using namespace imaging;

class FilterGamma : public Filter{


public:
	float y;



	FilterGamma();

	FilterGamma(float y);

	FilterGamma(const FilterGamma &scrc);

	~FilterGamma();



	Image operator << (const Image &image);
};
