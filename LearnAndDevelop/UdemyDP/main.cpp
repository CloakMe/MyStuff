#include "Bitmap.h"
#include "BitmapProxy.h"

int main() {
	Image * img = new BitmapProxy{ "D:/wkspaces/yStuff/LearnAndDevelop/UdemyDP/ImageProxy/banner.txt" };
	img->Load();
	img->Display();
	img->Load("D:/workspaces/yStuff/LearnAndDevelop/UdemyDP/ImageProxy/Smiley.txt");
	img->Display();
	delete img;
}
