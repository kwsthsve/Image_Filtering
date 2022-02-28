#include "Image.h"
#include <iostream>
//#include "Color.h"
#include "ppm/ppm.h"
#include "functions.h"
#include <string>
#include <cstring>


using namespace imaging;

//------------------------------------ class Image ------------------------------------------------

/*! It is the class that represents a generic data container for an image.
*
* It holds the actual buffer of the pixel values and provides methods for accessing them,
* either as individual pixels or as a memory block. The Image class alone does not provide
* any functionality for loading and storing an image, as it is the result or input to such a procedure.
*
* The internal buffer of an image object stores the actual bytes (data) of the color image as
* a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
* width X height X sizeof(Color) bytes.
*
* All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
* intensity ranges, each color component is within the range [0.0, 1.0].
*/


Image::Image() :Array<math::Vec3<float>>(0, 0) {}


Image::Image(unsigned int width, unsigned int height) : Array<math::Vec3<float>>(width, height) {}


Image::Image(unsigned int width, unsigned int height, const vector<Vec3<float>> data_ptr) :Array<math::Vec3<float>>(width, height) {
	for (unsigned int i = 0; i < data_ptr.size(); i++) {
		buffer.push_back(data_ptr.at(i));
	}
}

/*! The Image destructor.
*/
Image::~Image() {}


/*!
* Loads the image data from the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
* Image object is initialized, its contents are wiped out before initializing it to the width, height and data
* read from the file.
*
* \param filename is the string of the file to read the image data from.
* \param format specifies the file format according to which the image data should be decoded from the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the loading completes successfully, false otherwise.
*/
bool Image::load(const std::string & filename, const std::string & format) {
	std::string f;
	size_t found = filename.find_last_of(".");

	if (found != std::string::npos) {            
		f = filename.substr(found + 1);
		if (!comp(format, f)) {
			return false;
		}

		int* h = new int; 
		int* w = new int;
		float * data = ReadPPM(&filename[0], w, h);

		
		for (int i = 0; i < ((*w)*(*h) * 3); i += 3) {
			buffer.push_back(Vec3<float>(data[i], data[i + 1], data[i + 2]));
		}

		this->width = *w;
		this->height = *h;

		return true;
	}
	else {
		return false;
	}
}

/*!
* Stores the image data to the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
* Image object is not initialized, the method should return immediately with a false return value.
*
* \param filename is the string of the file to write the image data to.
* \param format specifies the file format according to which the image data should be encoded to the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the save operation completes successfully, false otherwise.
*/
bool Image::save(const std::string & filename, const std::string & format) {
	std::string f;
	int w = getWidth();
	int h = getHeight();
	size_t found = filename.find_last_of(".");

	if (found != std::string::npos) {             
		f = filename.substr(found + 1);

		if (!comp(format, f)) {
			printf("Invalid file extension");
			return false;
		}
		if (h == 0 && w == 0) {
			printf("The image object is not initialized");	
			return false;
		}

		if (!WritePPM(toRaw(this->buffer, w, h), w, h, &filename[0])) {
			printf("Something went wrong with the WritePPM! ");
			return false;
		}

		return true;
	}
	else {
		printf("Invalid file name ");
		return false;
	}
}
