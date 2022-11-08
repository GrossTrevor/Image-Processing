#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Image.h"
using namespace std;

struct Test {
	bool Compare(string file1, string file2) {
		Processor processor;
		processor.ReadImage(file1);
		processor.ReadImage(file2);
		
		if (processor.GetImages()[0].GetIdLength() != processor.GetImages()[1].GetIdLength())
			return false;
		if (processor.GetImages()[0].GetColorMapType() != processor.GetImages()[1].GetColorMapType())
			return false;
		if (processor.GetImages()[0].GetDataTypeCode() != processor.GetImages()[1].GetDataTypeCode())
			return false;
		if (processor.GetImages()[0].GetColorMapOrigin() != processor.GetImages()[1].GetColorMapOrigin())
			return false;
		if (processor.GetImages()[0].GetColorMapLength() != processor.GetImages()[1].GetColorMapLength())
			return false;
		if (processor.GetImages()[0].GetColorMapDepth() != processor.GetImages()[1].GetColorMapDepth())
			return false;
		if (processor.GetImages()[0].GetXOrigin() != processor.GetImages()[1].GetXOrigin())
			return false;
		if (processor.GetImages()[0].GetYOrigin() != processor.GetImages()[1].GetYOrigin())
			return false;
		if (processor.GetImages()[0].GetWidth() != processor.GetImages()[1].GetWidth())
			return false;
		if (processor.GetImages()[0].GetHeight() != processor.GetImages()[1].GetHeight())
			return false;
		if (processor.GetImages()[0].GetBitsPerPixel() != processor.GetImages()[1].GetBitsPerPixel())
			return false;
		if (processor.GetImages()[0].GetImageDescriptor() != processor.GetImages()[1].GetImageDescriptor())
			return false;
		if (processor.GetImages()[0].GetPixels().size() != processor.GetImages()[0].GetPixels().size())
			return false;
		else {	
			for (unsigned int x = 0; x < processor.GetImages()[0].GetPixels().size(); x++) {
				if (processor.GetImages()[0].GetPixels()[x].GetRed() != processor.GetImages()[1].GetPixels()[x].GetRed())
					return false;
				if (processor.GetImages()[0].GetPixels()[x].GetGreen() != processor.GetImages()[1].GetPixels()[x].GetGreen())
					return false;
				if (processor.GetImages()[0].GetPixels()[x].GetBlue() != processor.GetImages()[1].GetPixels()[x].GetBlue())
					return false;
			}
		}
		return true;
	}
};

int main() {
	Processor processor;
	Test tester;
	
	//Test 1
	processor.ReadImage("input/layer1.tga"); 
	processor.ReadImage("input/pattern1.tga");
	processor.Multiply(0, 1);
	processor.writeFile(2, "output/part1.tga");
	processor.ClearImages();

	//Test 2
	processor.ReadImage("input/layer2.tga");
	processor.ReadImage("input/car.tga");
	processor.Subtract(0, 1);
	processor.writeFile(2, "output/part2.tga");
	processor.ClearImages();

	//Test 3
	processor.ReadImage("input/layer1.tga");
	processor.ReadImage("input/pattern2.tga");
	processor.Multiply(0, 1);
	processor.ReadImage("input/text.tga");
	processor.Screen(3, 2);
	processor.writeFile(4, "output/part3.tga");
	processor.ClearImages();

	//Test 4
	processor.ReadImage("input/layer2.tga");
	processor.ReadImage("input/circles.tga");
	processor.Multiply(0, 1);
	processor.ReadImage("input/pattern2.tga");
	processor.Subtract(3, 2);
	processor.writeFile(4, "output/part4.tga");
	processor.ClearImages();

	//Test 5
	processor.ReadImage("input/layer1.tga");
	processor.ReadImage("input/pattern1.tga");
	processor.Overlay(0, 1);
	processor.writeFile(2, "output/part5.tga");
	processor.ClearImages();
	
	//Test 6
	processor.ReadImage("input/car.tga");
	processor.AddToChannel(0, 0, 200, 0);
	processor.writeFile(1, "output/part6.tga");
	processor.ClearImages();
	
	//Test 7
	processor.ReadImage("input/car.tga");
	processor.MultiplyToChannel(0, 4, 1, 0);
	processor.writeFile(1, "output/part7.tga");
	processor.ClearImages();
	
	//Test 8
	processor.ReadImage("input/car.tga");
	processor.SeparateIntoChannels(0);
	processor.writeFile(1, "output/part8_r.tga");
	processor.writeFile(2, "output/part8_g.tga");
	processor.writeFile(3, "output/part8_b.tga");
	processor.ClearImages();

	//Test 9
	processor.ReadImage("input/layer_red.tga");
	processor.ReadImage("input/layer_green.tga");
	processor.ReadImage("input/layer_blue.tga");
	processor.CombineChannels(0, 1, 2);
	processor.writeFile(3, "output/part9.tga");
	processor.ClearImages();
	
	//Test 10
	processor.ReadImage("input/text2.tga");
	processor.Rotate180(0);
	processor.writeFile(1, "output/part10.tga");
	processor.ClearImages();
	
	//Extra Credit
	processor.ReadImage("input/text.tga");
	processor.ReadImage("input/pattern1.tga");
	processor.ReadImage("input/car.tga");
	processor.ReadImage("input/circles.tga");
	processor.CreateFourImageCombination(0, 1, 2, 3);
	processor.writeFile(4, "output/extracredit.tga");
	processor.ClearImages();
	
	//Compare outputs to examples
	bool value;
	unsigned int total = 0;
	value = tester.Compare("output/part1.tga", "examples/EXAMPLE_part1.tga");
	if (value) {
		cout << "Test #1......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #1......Failed!" << endl;

	value = tester.Compare("output/part2.tga", "examples/EXAMPLE_part2.tga");
	if (value) {
		cout << "Test #2......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #2......Failed!" << endl;

	value = tester.Compare("output/part3.tga", "examples/EXAMPLE_part3.tga");
	if (value) {
		cout << "Test #3......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #3......Failed!" << endl;

	value = tester.Compare("output/part4.tga", "examples/EXAMPLE_part4.tga");
	if (value) {
		cout << "Test #4......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #4......Failed!" << endl;

	value = tester.Compare("output/part5.tga", "examples/EXAMPLE_part5.tga");
	if (value) {
		cout << "Test #5......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #5......Failed!" << endl;

	value = tester.Compare("output/part6.tga", "examples/EXAMPLE_part6.tga");
	if (value) {
		cout << "Test #6......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #6......Failed!" << endl;

	value = tester.Compare("output/part7.tga", "examples/EXAMPLE_part7.tga");
	if (value) {
		cout << "Test #7......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #7......Failed!" << endl;

	value = tester.Compare("output/part8_r.tga", "examples/EXAMPLE_part8_r.tga");
	if (value) {
		cout << "Test #8r......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #8r......Failed!" << endl;

	value = tester.Compare("output/part8_g.tga", "examples/EXAMPLE_part8_g.tga");
	if (value) {
		cout << "Test #8g......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #8g......Failed!" << endl;

	value = tester.Compare("output/part8_b.tga", "examples/EXAMPLE_part8_b.tga");
	if (value) {
		cout << "Test #8b......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #8b......Failed!" << endl;

	value = tester.Compare("output/part9.tga", "examples/EXAMPLE_part9.tga");
	if (value) {
		cout << "Test #9......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #9......Failed!" << endl;

	value = tester.Compare("output/part10.tga", "examples/EXAMPLE_part10.tga");
	if (value) {
		cout << "Test #10......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #10......Failed!" << endl;

	value = tester.Compare("output/extracredit.tga", "examples/EXAMPLE_extracredit.tga");
	if (value) {
		cout << "Test #11 (Extra Credit)......Passed!" << endl;
		total++;
	}
	else
		cout << "Test #11 (Extra Credit)......Failed!" << endl;

	cout << "Test Results: " << total << "/13" << endl;
		
	return 0;
}