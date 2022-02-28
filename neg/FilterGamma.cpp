#include <string>
#include "FilterGamma.h"                                                                                                                 
#include "Image.h"                                                                               
#include "Vec3.h"      
#include "ppm/ppm.h"
#include "Array.h"
#include "Filter.h"   



using namespace std;
using namespace math;
using namespace imaging;



FilterGamma::FilterGamma(){
	y = 0;
}

FilterGamma::FilterGamma(float y){
	this->y = y;
}

FilterGamma::FilterGamma(const FilterGamma &scrc){
	y = scrc.y;
}

FilterGamma::~FilterGamma() {}


Image FilterGamma::operator<<(const Image &image){
	Image  copy(image.getWidth(), image.getHeight());
	Vec3<float> temp(0);
	vector<Vec3<float>> proxy;

	for (int j = 0; j < image.getHeight(); j++) {
		for (int i = 0; i < image.getWidth(); i++) {
			temp = image.getPixel(i, j);
			temp.r = pow(temp.r, y);
			temp.g = pow(temp.g, y);
			temp.b = pow(temp.b, y);

			proxy.push_back(temp);
		}
	}

	copy.setData(proxy);
	return  copy;
}

