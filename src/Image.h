#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Image {
	char  idLength;
	char  colorMapType;
	char  dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char  colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char  bitsPerPixel;
	char  imageDescriptor;

public:
	struct Pixel {
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		Pixel() {
			red = 0;
			green = 0;
			blue = 0;
		}

		void SetRed(unsigned char r) {
			red = r;
		}

		void SetGreen(unsigned char g) {
			green = g;
		}

		void SetBlue(unsigned char b) {
			blue = b;
		}

		unsigned char GetRed() {
			return red;
		}

		unsigned char GetGreen() {
			return green;
		}

		unsigned char GetBlue() {
			return blue;
		}
	};

	vector<Pixel> pixels;

	Image() {
		idLength = 0;
		colorMapType = 0;
		dataTypeCode = 0;
		colorMapOrigin = 0;
		colorMapLength = 0;
		colorMapDepth = 0;
		xOrigin = 0;
		yOrigin = 0;
		width = 0;
		height = 0;
		bitsPerPixel = 0;
		imageDescriptor = 0;
		pixels.reserve(10000);
	}

	void SetIdLength(char l) {
		idLength = l;
	}

	void SetColorMapType(char t) {
		colorMapType = t;
	}

	void SetDataTypeCode(char c) {
		dataTypeCode = c;
	}

	void SetColorMapOrigin(short o) {
		colorMapOrigin = o;
	}

	void SetColorMapLength(short l) {
		colorMapLength = l;
	}

	void SetColorMapDepth(char d) {
		colorMapDepth = d;
	}

	void SetXOrigin(short x) {
		xOrigin = x;
	}

	void SetYOrigin(short y) {
		yOrigin = y;
	}

	void SetWidth(short w) {
		width = w;
	}

	void SetHeight(short h) {
		height = h;
	}

	void SetBitsPerPixel(char b) {
		bitsPerPixel = b;
	}

	void SetImageDescriptor(char d) {
		imageDescriptor = d;
	}

	vector<Pixel>& GetPixels() {
		return pixels;
	}

	char GetIdLength() {
		return idLength;
	}

	char GetColorMapType() {
		return colorMapType;
	}

	char GetDataTypeCode() {
		return dataTypeCode;
	}

	short GetColorMapOrigin() {
		return colorMapOrigin;
	}

	short GetColorMapLength() {
		return colorMapLength;
	}

	char GetColorMapDepth() {
		return colorMapDepth;
	}

	short GetXOrigin() {
		return xOrigin;
	}

	short GetYOrigin() {
		return yOrigin;
	}

	short GetWidth() {
		return width;
	}

	short GetHeight() {
		return height;
	}

	char GetBitsPerPixel() {
		return bitsPerPixel;
	}

	char GetImageDescriptor() {
		return imageDescriptor;
	}

	void Copy(Image& image) {
		this->idLength = image.GetIdLength();
		this->colorMapType = image.GetColorMapType();
		this->dataTypeCode = image.GetDataTypeCode();
		this->colorMapOrigin = image.GetColorMapOrigin();
		this->colorMapLength = image.GetColorMapLength();
		this->colorMapDepth = image.GetColorMapDepth();
		this->xOrigin = image.GetXOrigin();
		this->yOrigin = image.GetYOrigin();
		this->width = image.GetWidth();
		this->height = image.GetHeight();
		this->bitsPerPixel = image.GetBitsPerPixel();
		this->imageDescriptor = image.GetImageDescriptor();
	}

	void AddPixelToImage(unsigned char r, unsigned char g, unsigned char b) {
		Pixel pixel;
		pixel.SetRed(r);
		pixel.SetGreen(g);
		pixel.SetBlue(b);
		pixels.push_back(pixel);
	}
};

class Processor
{
	vector<Image> images;
public:
	Processor() {
		images.reserve(2);
	}
	vector<Image>& GetImages() {
		return images;
	}
	void ReadImage(string filename) {
		ifstream file(filename, ios_base::binary);

		Image img;
		char  tempIdLength;
		char  tempColorMapType;
		char  tempDataTypeCode;
		short tempColorMapOrigin;
		short tempColorMapLength;
		char  tempColorMapDepth;
		short tempXOrigin;
		short tempYOrigin;
		short tempWidth;
		short tempHeight;
		char  tempBitsPerPixel;
		char  tempImageDescriptor;

		file.read(&tempIdLength, sizeof(tempIdLength));
			img.SetIdLength(tempIdLength);
		file.read(&tempColorMapType, sizeof(tempColorMapType));
			img.SetColorMapType(tempColorMapType);
		file.read(&tempDataTypeCode, sizeof(tempDataTypeCode));
			img.SetDataTypeCode(tempDataTypeCode);
		file.read((char*)&tempColorMapOrigin, sizeof(tempColorMapOrigin));
			img.SetColorMapOrigin(tempColorMapOrigin);
		file.read((char*)&tempColorMapLength, sizeof(tempColorMapLength));
			img.SetColorMapLength(tempColorMapLength);
		file.read(&tempColorMapDepth, sizeof(tempColorMapDepth));
			img.SetColorMapDepth(tempColorMapDepth);
		file.read((char*)&tempXOrigin, sizeof(tempXOrigin));
			img.SetXOrigin(tempXOrigin);
		file.read((char*)&tempYOrigin, sizeof(tempYOrigin));
			img.SetYOrigin(tempYOrigin);
		file.read((char*)&tempWidth, sizeof(tempWidth));
			img.SetWidth(tempWidth);
		file.read((char*)&tempHeight, sizeof(tempHeight));
			img.SetHeight(tempHeight);
		file.read(&tempBitsPerPixel, sizeof(tempBitsPerPixel));
			img.SetBitsPerPixel(tempBitsPerPixel);
		file.read(&tempImageDescriptor, sizeof(tempImageDescriptor));
			img.SetImageDescriptor(tempImageDescriptor);

		for (unsigned int x = 0; x < img.GetWidth() * img.GetHeight(); x++) {
			char unsigned b;
			char unsigned g;
			char unsigned r;
			file.read((char*)&b, sizeof(b));
			file.read((char*)&g, sizeof(g));
			file.read((char*)&r, sizeof(r));
			img.AddPixelToImage(r, g, b);
		}
		images.push_back(img);
		file.close();
	}

	void writeFile(int index, string filename) {
		ofstream file(filename, ios_base::binary);

		char tempIdLength = images[index].GetIdLength();
		char tempColorMapType = images[index].GetColorMapType();
		char tempDataTypeCode = images[index].GetDataTypeCode();
		short tempColorMapOrigin = images[index].GetColorMapOrigin();
		short tempColorMapLength = images[index].GetColorMapLength();
		char tempColorMapDepth = images[index].GetColorMapDepth();
		short tempXOrigin = images[index].GetXOrigin();
		short tempYOrigin = images[index].GetYOrigin();
		short tempWidth = images[index].GetWidth();
		short tempHeight = images[index].GetHeight();
		char tempBitsPerPixel = images[index].GetBitsPerPixel();
		char tempImageDescriptor = images[index].GetImageDescriptor();

		file.write(&tempIdLength, sizeof(tempIdLength));
		file.write(&tempColorMapType, sizeof(tempColorMapType));
		file.write(&tempDataTypeCode, sizeof(tempDataTypeCode));
		file.write((char*)&tempColorMapOrigin, sizeof(tempColorMapOrigin));
		file.write((char*)&tempColorMapLength, sizeof(tempColorMapLength));
		file.write(&tempColorMapDepth, sizeof(tempColorMapDepth));
		file.write((char*)&tempXOrigin, sizeof(tempXOrigin));
		file.write((char*)&tempYOrigin, sizeof(tempYOrigin));
		file.write((char*)&tempWidth, sizeof(tempWidth));
		file.write((char*)&tempHeight, sizeof(tempHeight));
		file.write(&tempBitsPerPixel, sizeof(tempBitsPerPixel));
		file.write(&tempImageDescriptor, sizeof(tempImageDescriptor));

		for (unsigned int x = 0; x < images[index].GetPixels().size(); x++) {
			unsigned char r = images[index].GetPixels()[x].GetRed();
			unsigned char g = images[index].GetPixels()[x].GetGreen();
			unsigned char b = images[index].GetPixels()[x].GetBlue();
			file.write((char*)&b, sizeof(b));
			file.write((char*)&g, sizeof(g));
			file.write((char*)&r, sizeof(r));
		}
		file.close();
	}

	void Multiply(int img1, int img2) {
		if (images[img1].GetPixels().size() == images[img2].GetPixels().size()) {
			Image result;
			result.Copy(images[img1]);
			float tempColor;
			unsigned char r;
			unsigned char g;
			unsigned char b;

			for (unsigned int x = 0; x < (unsigned)images[img1].GetPixels().size(); x++) {
				tempColor = ((float)images[img1].GetPixels()[x].GetRed()) * (images[img2].GetPixels()[x].GetRed());
				tempColor /= 255.0f;
				tempColor += 0.5f;
				r = (unsigned char)tempColor;

				tempColor = ((float)images[img1].GetPixels()[x].GetGreen()) * (images[img2].GetPixels()[x].GetGreen());
				tempColor /= 255.0f;
				tempColor += 0.5f;
				g = (unsigned char)tempColor;

				tempColor = ((float)images[img1].GetPixels()[x].GetBlue()) * (images[img2].GetPixels()[x].GetBlue());
				tempColor /= 255.0f;
				tempColor += 0.5f;
				b = (unsigned char)tempColor;

				result.AddPixelToImage(r, g, b);
			}
			images.push_back(result);
		}
	}

	void Subtract(int img1, int img2) {
		if (images[img1].GetPixels().size() == images[img2].GetPixels().size()) {
			Image result;
			result.Copy(images[img1]);
			float tempColor;
			unsigned char r;
			unsigned char g;
			unsigned char b;

			for (unsigned int x = 0; x < (unsigned)images[img1].GetPixels().size(); x++) {
				tempColor = ((float)images[img2].GetPixels()[x].GetRed()) - ((float)images[img1].GetPixels()[x].GetRed());
				if (tempColor < 0)
					tempColor = 0;
				tempColor += 0.5f;
				r = (unsigned char)tempColor;

				tempColor = ((float)images[img2].GetPixels()[x].GetGreen()) - ((float)images[img1].GetPixels()[x].GetGreen());
				if (tempColor < 0)
					tempColor = 0;
				tempColor += 0.5f;
				g = (unsigned char)tempColor;

				tempColor = ((float)images[img2].GetPixels()[x].GetBlue()) - ((float)images[img1].GetPixels()[x].GetBlue());
				if (tempColor < 0)
					tempColor = 0;
				tempColor += 0.5f;
				b = (unsigned char)tempColor;

				result.AddPixelToImage(r, g, b);
			}
			images.push_back(result);
		}
	}

	void Screen(int img1, int img2) {
		if (images[img1].GetPixels().size() == images[img2].GetPixels().size()) {
			Image result;
			result.Copy(images[img1]);
			float tempColor;
			unsigned char r;
			unsigned char g;
			unsigned char b;

			for (unsigned int x = 0; x < (unsigned)images[img1].GetPixels().size(); x++) {
				tempColor = 1 - ((1 - (((float)images[img1].GetPixels()[x].GetRed()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetRed()) / 255.0f)));
				tempColor *= 255.0f;
				tempColor += 0.5f;
				r = (unsigned char)tempColor;

				tempColor = 1 - ((1 - (((float)images[img1].GetPixels()[x].GetGreen()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetGreen()) / 255.0f)));
				tempColor *= 255.0f;
				tempColor += 0.5f;
				g = (unsigned char)tempColor;

				tempColor = 1 - ((1 - (((float)images[img1].GetPixels()[x].GetBlue()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetBlue()) / 255.0f)));
				tempColor *= 255.0f;
				tempColor += 0.5f;
				b = (unsigned char)tempColor;

				result.AddPixelToImage(r, g, b);
			}
			images.push_back(result);
		}
	}

	void Overlay(int img1, int img2) {
		if (images[img1].GetPixels().size() == images[img2].GetPixels().size()) {
			Image result;
			result.Copy(images[img1]);
			float tempColor;
			unsigned char r;
			unsigned char g;
			unsigned char b;

			for (unsigned int x = 0; x < images[img1].GetPixels().size(); x++) {
				if ((short)images[img2].GetPixels()[x].GetRed() + (short)images[img2].GetPixels()[x].GetGreen() + (short)images[img2].GetPixels()[x].GetBlue() <= 381) {
					tempColor = 2 * (((float)images[img1].GetPixels()[x].GetRed()) / 255.0f) * (((float)images[img2].GetPixels()[x].GetRed()) / 255.0f);
					tempColor *= 255.0f;
					tempColor += 0.5f;
					r = (unsigned char)tempColor;

					tempColor = 2 * (((float)images[img1].GetPixels()[x].GetGreen()) / 255.0f) * (((float)images[img2].GetPixels()[x].GetGreen()) / 255.0f);
					tempColor *= 255.0f;
					tempColor += 0.5f;
					g = (unsigned char)tempColor;

					tempColor = 2 * (((float)images[img1].GetPixels()[x].GetBlue()) / 255.0f) * (((float)images[img2].GetPixels()[x].GetBlue()) / 255.0f);
					tempColor *= 255.0f;
					tempColor += 0.5f;
					b = (unsigned char)tempColor;
				}

				else {
					tempColor = 1 - 2 * (1 - (((float)images[img1].GetPixels()[x].GetRed()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetRed()) / 255.0f));
					if (tempColor < 0)
						tempColor = 0;
					tempColor *= 255.0f;
					tempColor += 0.5f;
					r = (unsigned char)tempColor;

					tempColor = 1 - (2 * (1 - (((float)images[img1].GetPixels()[x].GetGreen()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetGreen()) / 255.0f)));
					if (tempColor < 0)
						tempColor = 0;
					tempColor *= 255.0f;
					tempColor += 0.5f;
					g = (unsigned char)tempColor;

					tempColor = 1 - (2 * (1 - (((float)images[img1].GetPixels()[x].GetBlue()) / 255.0f)) * (1 - (((float)images[img2].GetPixels()[x].GetBlue()) / 255.0f)));
					if (tempColor < 0)
						tempColor = 0;
					tempColor *= 255.0f;
					tempColor += 0.5f;
					b = (unsigned char)tempColor;
				}
				result.AddPixelToImage(r, g, b);
			}
			images.push_back(result);
		}
	}

	void AddToChannel(int index, unsigned int r, unsigned int g, unsigned int b) {
		Image result;
		result.Copy(images[index]);
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		for (unsigned int x = 0; x < images[index].GetPixels().size(); x++) {
			if (images[index].GetPixels()[x].GetRed() + r <= 255)
				red = (unsigned char)images[index].GetPixels()[x].GetRed() + r;
			else
				red = 255;

			if (images[index].GetPixels()[x].GetGreen() + g <= 255)
				green = (unsigned char)images[index].GetPixels()[x].GetGreen() + g;
			else
				green = 255;

			if (images[index].GetPixels()[x].GetBlue() + b <= 255)
				blue = (unsigned char)images[index].GetPixels()[x].GetBlue() + b;
			else
				blue = 255;

			result.AddPixelToImage(red, green, blue);
		}
		images.push_back(result);
	}

	void MultiplyToChannel(int index, unsigned int r, unsigned int g, unsigned int b) {
		Image result;
		result.Copy(images[index]);
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		for (unsigned int x = 0; x < images[index].GetPixels().size(); x++) {
			if (images[index].GetPixels()[x].GetRed() * r <= 255)
				red = (unsigned char)images[index].GetPixels()[x].GetRed() * r;
			else
				red = 255;

			if (images[index].GetPixels()[x].GetGreen() * g <= 255)
				green = (unsigned char)images[index].GetPixels()[x].GetGreen() * g;
			else
				green = 255;

			if (images[index].GetPixels()[x].GetBlue() * b <= 255)
				blue = (unsigned char)images[index].GetPixels()[x].GetBlue() * b;
			else
				blue = 255;
			result.AddPixelToImage(red, green, blue);
		}
		images.push_back(result);
	}

	void SeparateIntoChannels(int index) {
		Image redChannel;
		Image greenChannel;
		Image blueChannel;
		redChannel.Copy(images[index]);
		greenChannel.Copy(images[index]);
		blueChannel.Copy(images[index]);
		unsigned char r;
		unsigned char g;
		unsigned char b;

		for (unsigned int x = 0; x < images[index].GetPixels().size(); x++) {
			r = images[index].GetPixels()[x].GetRed();
			g = images[index].GetPixels()[x].GetGreen();
			b = images[index].GetPixels()[x].GetBlue();
			redChannel.AddPixelToImage(r, r, r);
			greenChannel.AddPixelToImage(g, g, g);
			blueChannel.AddPixelToImage(b, b, b);
		}
		images.push_back(redChannel);
		images.push_back(greenChannel);
		images.push_back(blueChannel);
	}

	void CombineChannels(int redIndex, int greenIndex, int blueIndex) {
		if ((images[redIndex].GetPixels().size() == images[greenIndex].GetPixels().size()) && (images[redIndex].GetPixels().size() == images[blueIndex].GetPixels().size())) {
			Image result;
			result.Copy(images[redIndex]);
			unsigned char r;
			unsigned char g;
			unsigned char b;

			for (unsigned int x = 0; x < images[redIndex].GetPixels().size(); x++) {
				r = images[redIndex].GetPixels()[x].GetRed();
				g = images[greenIndex].GetPixels()[x].GetGreen();
				b = images[blueIndex].GetPixels()[x].GetBlue();
				result.AddPixelToImage(r, g, b);
			}
			images.push_back(result);
		}
	}

	void Rotate180(int index) {
		Image result;
		result.Copy(images[index]);
		unsigned char r;
		unsigned char g;
		unsigned char b;

		for (unsigned int x = 0; x < images[index].GetPixels().size(); x++) {
			r = images[index].GetPixels()[x].GetRed();
			g = images[index].GetPixels()[x].GetGreen();
			b = images[index].GetPixels()[x].GetBlue();
			result.AddPixelToImage(r, g, b);
		}
		reverse(result.GetPixels().begin(), result.GetPixels().end());
		images.push_back(result);
	}

	void CreateFourImageCombination(int img1, int img2, int img3, int img4) {
		Image result;
		result.Copy(images[img1]);
		result.SetHeight((images[img1].GetHeight()) * 2);
		result.SetWidth((images[img1].GetWidth()) * 2);
		unsigned char r;
		unsigned char g;
		unsigned char b;

		int pos1 = 0;
		int pos2 = 0;
		for (int x = 0; x < (result.GetHeight() / 2); x++) {
			for (int y = 0; y < (result.GetWidth() / 2); y++) {
				r = images[img1].GetPixels()[pos1].GetRed();
				g = images[img1].GetPixels()[pos1].GetGreen();
				b = images[img1].GetPixels()[pos1].GetBlue();
				result.AddPixelToImage(r, g, b);
				pos1++;
			}
			for (int y = (result.GetWidth() / 2); y < result.GetWidth(); y++) {
				r = images[img2].GetPixels()[pos2].GetRed();
				g = images[img2].GetPixels()[pos2].GetGreen();
				b = images[img2].GetPixels()[pos2].GetBlue();
				result.AddPixelToImage(r, g, b);
				pos2++;
			}
		}
		pos1 = 0;
		pos2 = 0;
		for (int x = (result.GetHeight() / 2); x < result.GetHeight(); x++) {
			for (int y = 0; y < (result.GetWidth() / 2); y++) {
				r = images[img3].GetPixels()[pos1].GetRed();
				g = images[img3].GetPixels()[pos1].GetGreen();
				b = images[img3].GetPixels()[pos1].GetBlue();
				result.AddPixelToImage(r, g, b);
				pos1++;
			}
			for (int y = (result.GetWidth() / 2); y < result.GetWidth(); y++) {
				r = images[img4].GetPixels()[pos2].GetRed();
				g = images[img4].GetPixels()[pos2].GetGreen();
				b = images[img4].GetPixels()[pos2].GetBlue();
				result.AddPixelToImage(r, g, b);
				pos2++;
			}
		}
		images.push_back(result);
	}

	void ClearImages() {
		images.clear();
	}
};