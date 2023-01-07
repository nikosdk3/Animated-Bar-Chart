// Bar Chart Animation
// Nikos Kotsopulos
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Creative Component - Edit playback speed
// Using this creative component is self-explanatory because when you run the program it will prompt the user
// to enter the playback speed they desire which will change the speed at which the BarChart gets animated.
// To disable the creative component, just delete the playbackspeed parameter on line 63.
//
// Adam Koehler
// U. of Illinois, Chicago
// Fall 2022
//
// Original iteration of program developed by:
// Shanon Reckinger
// U. of Illinois, Chicago

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;

int main()
{
	string filename;
	int playbackspeed;
	cout << "List of available files:";
	cout << "\nbaby-names.txt";
	cout << "\nbrands.txt";
	cout << "\ncities-usa.txt";
	cout << "\ncities.txt";
	cout << "\ncountries.txt";
	cout << "\nendgame.txt";
	cout << "\nfootball.txt";
	cout << "\ngame-of-thrones.txt";
	cout << "\ninfinity-war.txt";
	cout << "\nmovies.txt";
	cout << "\npatents.txt";
	cout << "\ntrademarks.txt";
	cout << "\nEnter filename : ";
	cin >> filename;
	//cout << "Enter playback speed (in microseconds): "; //uncomment to use creative component
	//cin >> playbackspeed;							      //uncomment to use creative component
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);

	while (!inFile.eof())
	{
		bca.addFrame(inFile);
	}

	bca.animate(cout, 12, -1);//creative component used here. Add playbackspeed as a parameter at the end to use.

	return 0;
}
