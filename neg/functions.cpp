#include <string>
#include "functions.h"
//#include "Color.h"

using namespace std;
//using namespace imaging;

bool comp(const string& a, const string& b)   
{
	if (b.size() != a.size())
		return false;
	for (unsigned int i = 0; i < b.size(); ++i) {
		if (tolower(a[i]) != tolower(b[i])) {
			return false;
		}
	}
	return true;
}

float * toRaw(vector<Vec3<float>> &buffer, int width , int height) {
	int size = width * height * 3;
	float * data = new float[size];

	for (int i = 0; i < size; i += 3) {
		Vec3<float> c = buffer[i / 3];
		data[i] = c.r;
		data[i + 1] = c.g;
		data[i + 2] = c.b;
	}
	return data;
}