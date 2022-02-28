#ifndef _ARRAY_
#define _ARRAY_

#include <iostream>
#include <vector>


using namespace std;

namespace math
{



	template<typename T> class Array {


	public:
		vector<T> buffer;

		unsigned int width,
			height;

	public:
		vector<T> getRawDataPtr();

		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		T  getPixel(unsigned int x, unsigned int y) const;

		void setPixel(unsigned int x, unsigned int y, T & value);

		void setData(const vector<T>  data_ptr);



		Array();

		Array(unsigned int width, unsigned int height);

		Array(unsigned int width, unsigned int height, const vector<T> data_ptr);

		Array(const Array<T> &src);



		T & operator () (int x, int y);

		Array & operator = (const Array<T> & right);

	};


	template<typename T> vector<T> Array<T>::getRawDataPtr() {
		return this->buffer;
	}


	template <typename T> T Array<T>::getPixel(unsigned int x, unsigned int y) const {
		T temp;

		if (!((x < 0 || x >= width) || (y < 0 || y >= height))) {
			temp = buffer.at(x + y * width);
			return temp;
		}
		else {
			return 0;
		}
	}


	template <typename T>void Array<T>::setPixel(unsigned int x, unsigned int y, T & value) {
		if ((x < 0 || x >= width) || (y < 0 || y >= height)) {
			return;
		}
		buffer[(y*width + x)] = value;
	}


	template <typename T>void Array<T>::setData(const vector<T> data_ptr) {
		if (width * height == 0) {
			return;
		}
		buffer.clear();
		for (unsigned int i = 0; i < (int)(height*width); i++) {
			buffer.push_back(data_ptr[i]);
		}
	}


	template <typename T>Array<T>::Array() {
		this->width = 0;
		this->height = 0;
	}


	template <typename T> Array<T>::Array(unsigned int width, unsigned int height) {
		this->width = width;
		this->height = height;
	}


	template <typename T> Array<T>::Array(unsigned int width, unsigned int height, const vector<T> data_ptr) {
		unsigned int i, size;
		this->width = width;
		this->height = height;
		for (i = 0; i < data_ptr.size(); i++) {
			buffer.push_back(data_ptr.at(i));
		}
	}


	template <typename T> Array<T>::Array(const Array<T> &src) {
		width = src.width;
		height = src.height;
		setData(const_cast <Array<T>&>(src).getRawDataPtr());
	}


	template <typename T>T & Array<T>::operator () (int x, int y) {
		return buffer.at(y*width + x);
	}


	template <typename T>Array<T> & Array<T>::operator= (const Array<T> & right) {
		operator=(right);
		return *this;
	}
}
#endif