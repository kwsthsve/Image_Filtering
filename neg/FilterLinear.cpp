#include <string>
#include "Image.h"                                                                              
#include "Vec3.h"      
#include "ppm/ppm.h"
#include "Array.h"
#include "Filter.h"   
#include "FilterLinear.h"                    




using namespace std;
using namespace math;
using namespace imaging;



FilterLinear::FilterLinear() {				
	a.r = 0;								
	a.g = 0;
	a.b = 0;								
	c.r = 0;
	c.g = 0;
	c.b = 0;								
}

FilterLinear::FilterLinear(Vec3<float> a, Vec3<float> c) {		
	this->a = a;
	this->c = c;
}

FilterLinear::FilterLinear(float aR, float aG, float aB, float cR, float cG, float cB) {   
	a.r = aR;
	a.g = aG;
	a.b = aB;
	c.r = cR;
	c.g = cG;
	c.b = cB;
}

FilterLinear::FilterLinear(const FilterLinear &scrc){						
	a = scrc.a;
	c = scrc.c;
}

FilterLinear::~FilterLinear() {}


Image FilterLinear::operator << (const Image &image) {																				
	Image copy(image.getWidth(), image.getHeight());
	Vec3<float> temp(0);
	vector<Vec3<float>> proxy;

	for (int j = 0; j < image.getHeight(); j++) {
		for (int i = 0; i < image.getWidth(); i++) {
			temp = image.getPixel(i, j);
			temp = temp * a;
			temp = temp + c;
			temp = temp.clampToLowerBound(0);
			temp = temp.clampToUpperBound(1);

			proxy.push_back(temp);
		}
	}

	copy.setData(proxy);
	return copy;
}