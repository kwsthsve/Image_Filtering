#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include "ppm.h"

using namespace imaging;

float * imaging::ReadPPM(const char * filename, int * w, int * h)
{
	std::ifstream file(filename,  std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Could not open Image file!" << std::endl;
		system("PAUSE");
		return nullptr;
	}

	std::string key;
	int max = 0;

	file >> key >> *w >> *h >> max;

	file.ignore(256, '\n');
	
	

	if (key != "P6") {
		std::cerr << "Wrong image format.Try a ppm format..." << std::endl;
		system("PAUSE");
		return nullptr;
	}
	else if (*w == NULL || *h == NULL) {
		std::cerr << "Image dimensions are missing.Please check your file." << std::endl;
		system("PAUSE");
		return nullptr;
	}
	else if (max = 0 || max > 255) {
		std::cerr << "Image with false information.Please check your file." << std::endl;
		system("PAUSE");
		return nullptr;
	}
	else {
		int size = (*w)*(*h) * 3;
		unsigned char * buffer = new unsigned char[size];
		float * data = new float[size];
		file.read((char *)buffer, size);
		for (int i = 0; i < size; i++) {
			data[i] = buffer[i] / 255.0f;
		}

		delete[]buffer;
		file.close();
		return data;
	}
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	int size = w * h * 3;


	if (!file.is_open() || (data == nullptr)) {
		std::cerr << "Could not open file!" << std::endl;
		system("PAUSE");
		return false;
	}


	file << "P6" << std::endl
		<< w << std::endl
		<< h << std::endl
		<< "255" << std::endl;


	unsigned char * Raw = new unsigned char[size];


	for (unsigned int i = 0; i < size; i++) {
		Raw[i] = data[i] * 255.0f;
	}

	file.write((char *)Raw, size);

	if (file.good()) {
		file.flush();
		file.close();
		delete[]Raw; 
		return true;
	}
	else {
		std::cerr << "Something went wrong while writting on file..." << std::endl;
		system("PAUSE");
		return false;
	}
}
