#include <string>
#include "Array.h"
#include "Vec3.h"


using namespace math;
using namespace std;


bool comp(const std::string& a, const std::string& b);

float * toRaw(vector<Vec3<float>> &buffer, int width, int height);