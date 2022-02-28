#include <iostream>
#include <string>
#include <cstddef>
#include "Image.h"
#include "ppm/ppm.h"
#include "Filter.h"
#include "FilterLinear.h"
#include "FilterGamma.h"

using namespace std;
using namespace imaging;



int main(int argc, char *argv[]) {

	string fileName;
	string format = "ppm";

	fileName = argv[argc - 1];

	size_t found = fileName.find_last_of("/\\");
	string path = fileName.substr(0, found);
	string file = fileName.substr(found + 1);

	size_t found2 = fileName.find_last_of(".");
	string name = fileName.substr(0, found2);


	Image *photo = new Image();


	if (photo->load(fileName, format)) {
		unsigned int width = photo->getWidth();
		unsigned int height = photo->getHeight();
		printf("Image dimensions are: %d X %d ", width, height);
		cout << endl;
		for (int i = 1; i < argc - 1; i++) {
			string arg(argv[i]);
			if (arg == "-f") {
				string arg2(argv[i + 1]);
				if (arg2 == "linear") {
					FilterLinear fl(stof(argv[i + 2]), stof(argv[i + 3]), stof(argv[i + 4]), stof(argv[i + 5]), stof(argv[i + 6]), stof(argv[i + 7]));
					photo = new Image(fl << *photo);
				}
				else if (arg2 == "gamma") {
					FilterGamma fg(stof(argv[i + 2]));
					photo = new Image(fg << *photo);
				}
				else {
					printf("PLease be sure to choose between linear or gamma filters...");
					cout << endl;
					break;
				}
			}
		}
		if (photo->save("filtered_" + file, format)) {
			printf("We are done! Please check the result :)");
			cout << endl;
		}
		else {
			printf("Saving the filtered image was unsuccessful!");
		}
	}else {
		printf("Image loading was unsuccessful!");
	}


	delete photo;
	system("PAUSE");
	return 0;
}
