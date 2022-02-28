#include "Filter.h"
#include "Vec3.h"
#include "Image.h"


using namespace math;
using namespace imaging;


class FilterLinear : public Filter{

public:
	Vec3<float> a;
	Vec3<float> c;



	FilterLinear();

	FilterLinear(Vec3<float> a, Vec3<float> c);

	FilterLinear(float aR, float aG, float aB, float cR, float cG, float cB);

	FilterLinear(const FilterLinear &scrc);

	~FilterLinear();



	Image operator << (const Image &image);
};
