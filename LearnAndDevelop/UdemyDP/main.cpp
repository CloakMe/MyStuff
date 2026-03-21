#include "Bitmap.h"
#include "BitmapProxy.h"

int main() {
	Image * img = new BitmapProxy{ "./Smiley.txt" };
	img->Load();
	img->Display();
	img->Load("./banner.txt");
	img->Display();
	delete img;
}
