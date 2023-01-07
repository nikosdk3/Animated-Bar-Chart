#include <iostream>
#include "barchartanimate.h"
using namespace std;

// test to make sure Bar default constructor and its functions work
bool testBarDefaultConstructor()
{
	Bar b;
	if (b.getName() != "")
	{
		cout << "testBarDefaultConstructor: getName failed" << endl;
		return false;
	}
	else if (b.getValue() != 0)
	{
		cout << "testBarDefaultConstructor: getValue failed" << endl;
		return false;
	}
	else if (b.getCategory() != "")
	{
		cout << "testBarDefaultConstructor: getCategory failed" << endl;
		return false;
	}
	// if default constructor initializes values correctly the test case will pass
	cout << "testBarDefaultConstructor: all passed!" << endl;
	return true;
}

// test to make sure Bar paramaterized constructor and its functions work correctly
bool testBarParamConstructor()
{
	Bar b("Chicago", 9234324, "US");
	if (b.getName() != "Chicago")
	{
		cout << "testBarParamConstructor: getName failed" << endl;
		return false;
	}
	else if (b.getValue() != 9234324)
	{
		cout << "testBarParamConstructor: getValue failed" << endl;
		return false;
	}
	else if (b.getCategory() != "US")
	{
		cout << "testBarParamConstructor: getCategory failed" << endl;
		return false;
	}
	// if all values match this test case will pass
	cout << "testBarParamConstructor: all passed!" << endl;
	return true;
}

// test for Bar operator overloading
bool testBarOperators()
{
	Bar b1("a", 1, "cat");
	Bar b2("b", 2, "dog");
	if (b1 > b2)
	{
		cout << "testBarOperators: operator> failed" << endl;
		return false;
	}
	else if (b2 < b1)
	{
		cout << "testBarOperators: operator< failed" << endl;
		return false;
	}
	else if (b2 <= b1)
	{
		cout << "testBarOperators: operator<= failed" << endl;
		return false;
	}
	else if (b1 >= b2)
	{
		cout << "testBarOperators: operator>= failed" << endl;
		return false;
	}
	cout << "testBarOperators: all passed!" << endl;
	return true;
}

// test to make sure BarChart default constructor and its functions work
bool testBarChartDefaultConstructor()
{
	BarChart bc;
	if (bc.getSize() != 0)
	{
		cout << "testBarChartDefaultConstructor: getSize failed" << endl;
		return false;
	}
	if (bc.getCapacity() != 0)
	{
		cout << "testBarChartDefaultConstructor: getCapacity failed" << endl;
		return false;
	}
	if (bc.getBars() != nullptr)
	{
		cout << "testBarChartDefaultConstructor: Bar assignment failed" << endl;
		return false;
	}
	cout << "testBarChartDefaultConstructor: all passed!" << endl;
	return true;
}

// test to make sure BarChart parametrized constructor and its functions work
bool testBarChartParamConstructor()
{
	BarChart bc(10);
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	bc.setFrame("1950");
	if (bc.getFrame() != "1950") // setFrame set the frame to 1950
	{
		cout << "testBarChartParamConstructor: setFrame failed" << endl;
		return false;
	}
	if (bc.getSize() != 3) // since I called addBar 3 times, size should be 3
	{
		cout << "testBarChartParamConstructor: getSize failed" << endl;
		return false;
	}
	if (bc.getCapacity() != 10) // bc initialized to 10 in the constructor
	{
		cout << "testBarChartParamConstructor: getCapacity failed" << endl;
		return false;
	}
	stringstream ss;
	string line;
	bc.dump(ss); // test for dump
	getline(ss, line);
	// reading line by line and checking if line matches the expected output
	if (line != "frame: 1950")
	{
		cout << "testBarChartParamConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "NYC 1300 US")
	{
		cout << "testBarChartParamConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "Paris 1200 France")
	{
		cout << "testBarChartParamConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "Chicago 1020 US")
	{
		cout << "testBarChartParamConstructor: dump failed" << endl;
		return false;
	}
	bc.clear();
	// test for clear
	if (bc.getBars() != nullptr && bc.getFrame() != "" && bc.getSize() != 0 && bc.getCapacity() != 0)
	{
		cout << "testBarChartParamConstructor: clear failed" << endl;
		return false;
	}
	cout << "testBarChartParamConstructor: all passed!" << endl;
	return true;
}

// test for BarChart copy constructor and functions associated with it
bool testBarChartCopyConstructor()
{
	BarChart bc(10);
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	bc.setFrame("1950");
	BarChart bcCopy(bc);
	// tests below will determine if the copy constructor copied the values correctly by comparing private data fields
	if (bcCopy.getSize() != bc.getSize())
	{
		cout << "testBarChartCopyConstructor: getSize failed" << endl;
		return false;
	}
	if (bcCopy.getCapacity() != bc.getCapacity())
	{
		cout << "testBarChartCopyConstructor: getCapacity failed" << endl;
		return false;
	}
	if (bcCopy[0].getName() != bc[0].getName() && bcCopy[0].getValue() != bc[0].getValue() && bcCopy[0].getCategory() != bc[0].getCategory())
	{
		cout << "testBarChartCopyConstructor: addBar failed at first index" << endl;
		return false;
	}
	if (bcCopy[2].getName() != bc[2].getName() && bcCopy[2].getValue() != bc[2].getValue() && bcCopy[2].getCategory() != bc[2].getCategory())
	{
		cout << "testBarChartCopyConstructor: addBar failed at last index" << endl;
		return false;
	}
	stringstream ss;
	string line;
	bcCopy.dump(ss);
	getline(ss, line);
	// dump test for copy constructor
	if (line != "frame: 1950")
	{
		cout << "testBarChartCopyConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "NYC 1300 US")
	{
		cout << "testBarChartCopyConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "Paris 1200 France")
	{
		cout << "testBarChartCopyConstructor: dump failed" << endl;
		return false;
	}
	getline(ss, line);
	if (line != "Chicago 1020 US")
	{
		cout << "testBarChartCopyConstructor: dump failed" << endl;
		return false;
	}
	bcCopy.clear();
	bc.clear();
	// make sure clear sets both equal to the same value
	if (bc.getBars() != bcCopy.getBars() && bc.getFrame() != bcCopy.getFrame() && bc.getSize() != bcCopy.getSize() && bc.getCapacity() != bcCopy.getCapacity())
	{
		cout << "testBarChartCopyConstructor: clear failed" << endl;
		return false;
	}
	cout << "testBarChartCopyConstructor: all passed!" << endl;
	return true;
}

// visual test for BarChart's addBar and graph functions
bool testBarChartGraph()
{
	BarChart bc(4);
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	map<string, string> map;
	map["US"] = RED;
	map["France"] = BLUE;
	// check visually to see if graph matches expected output
	cout << "First Graph:" << endl;
	bc.graph(cout, map, 3);
	// add another bar to make sure sorting works as intended
	bc.addBar("Miami", 1500, "US");
	// test visually again
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"Second Graph:"<<endl;
	bc.graph(cout, map, 4);
	return true;
}

//testing BarChartAnimate's constructor and all of its functions
bool testBarChartAnimate()
{
	ifstream file("brands.txt");
	string title;
	getline(file, title);
	string xlabel;
	getline(file, xlabel);
	string source;
	getline(file, source);
	BarChartAnimate bca(title, xlabel, source);
	if (bca.getSize() != 0)
	{
		cout << "testBarChartAnimate: getSize failed" << endl;
		return false;
	}
	bca.addFrame(file);
	if (bca.getSize() != 1)//making sure size gets updated
	{
		cout << "testBarChartAnimate: getSize failed" << endl;
		return false;
	}
	if (bca[0].getFrame() != "2000-01-01")//make sure frame gets stored correctly
	{
		cout << "testBarChartAnimate: getFrame failed" << endl;
		return false;
	}
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	//more tests for getSize and getFrame
	if (bca.getSize() != 4)
	{
		cout << "testBarChartAnimate: getSize failed" << endl;
		return false;
	}
	if (bca[3].getFrame() != "2000-04-01")
	{
		cout << "testBarChartAnimate: getFrame failed" << endl;
		return false;
	}
	bca.animate(cout, 5, -1);//call animate for visual testing
	cout << "Animation testing complete" << endl;
	return true;
}

int main()
{
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarOperators();
	testBarChartDefaultConstructor();
	testBarChartParamConstructor();
	testBarChartCopyConstructor();
	testBarChartGraph();
	//testBarChartAnimate(); // comment out this test to see other tests since animate clears terminal each time it is called.
	return 0;
}