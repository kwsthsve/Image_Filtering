#ifndef _IMAGE
#define _IMAGE

//#include "Color.h"
#include <string>
#include "Vec3.h"
#include "Array.h"

using namespace math;
using namespace std;

namespace imaging
{
	class Image : public Array<Vec3<float>>
	{

	public:

	public:
		Image();

		Image(unsigned int w, unsigned int h);

		Image(unsigned int w, unsigned int h, const vector<Vec3<float>> data_ptr);

		~Image();



		bool load(const std::string & filename, const std::string & format);

		bool save(const std::string & filename, const std::string & format);

	};
		

} //namespace imaging
#endif
