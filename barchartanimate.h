// barchartanimate.h
// BarChartAnimate class which constantly makes calls to the graph() function in barchart.h to update the graph frame-by-frame and
// make it look like the bars are animated.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate
{
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart *barcharts; // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;//map of colors
    string title;
    string xlabel;
    string source;
    int colorIndex = 0;//used for getting the index from COLORS

public:
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source)
    {
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
        size = 0;
        capacity = 4;
        barcharts = new BarChart[capacity];//allocates 'capacity' amount of memory to the heap for BarChart
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate()
    {
        if (barcharts != nullptr)
        {
            delete[] barcharts;
        }
    }

    //helper function for addFrame to update capacity once the barchart gets full
    void updateCapacity()
    {
        if (size == capacity)
        {
            int newCapacity = capacity * 2;//doubling capacity
            BarChart *newBarCharts = new BarChart[newCapacity];//allocating new capacity
            for (int i = 0; i < size; i++)
            {
                newBarCharts[i] = barcharts[i];//each element in old array gets copied into new array
            }
            delete[] barcharts; //free memory
            barcharts = newBarCharts;
            capacity = newCapacity; 
        }
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file)
    {
        updateCapacity();//checks if size==capacity and doubles capacity to allow more room for BarCharts
        vector<string> dataFields;
        string line, numBarsStr;
        getline(file, line);
        if (file.eof())//used at the end of the file to skip the empty space or else it will seg fault.
            return;
        getline(file, numBarsStr);
        int numBars = stoi(numBarsStr);
        string frame;
        int count = 0;
        BarChart newBarChart(numBars);//initializing a Barchart of the size listed in the txt file
        while (count < numBars)
        {
            getline(file, line);
            stringstream ss(line);
            while (getline(ss, line, ','))
            {
                dataFields.push_back(line);//pushing each data value in separated by deliminator
            }
            if (colorMap.count(dataFields.at(4)) == 0)//index 4 represents the category
            {
                colorMap[dataFields.at(4)] = COLORS.at(colorIndex);
                colorIndex++;
                if (colorIndex >= COLORS.size())
                {
                    colorIndex = 0;
                }
            }
            frame = dataFields.at(0);//index 0 represents the date/year
            newBarChart.addBar(dataFields.at(1), stoi(dataFields.at(3)), dataFields.at(4));//index 1 represents the name and index 3 represents the value
            dataFields.clear();//clear to prepare for next loop iteration
            count++;
        }
        newBarChart.setFrame(frame);
        barcharts[size] = newBarChart;
        size++;
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
    void animate(ostream &output, int top, int endIter)
    {
        string currFrame;
        unsigned int microsecond = 50000;

        if (endIter == -1)
            endIter = size;
        for (int i = 0; i < endIter; i++)
        {
            this_thread::sleep_for(chrono::microseconds(3 * microsecond));//sleep used to better depict an animation
            output << CLEARCONSOLE;
            output << WHITE << title << endl;//used white for my color since I am on a dark console
            output << source << endl;
            barcharts[i].graph(output, colorMap, top);//graphs each index of barcharts gotten from addFrame
            currFrame = barcharts[i].getFrame();
            output << WHITE << xlabel << endl;
            output << WHITE << "Frame: " << currFrame << endl;
        }
    }

    //same as above function but overloaded with playbackspeed parameter to allow user to change playbackspeed
    void animate(ostream &output, int top, int endIter, int playbackspeed)
    {
        string currFrame;
        unsigned int microsecond = playbackspeed*1000;

        if (endIter == -1)
            endIter = size;
        for (int i = 0; i < endIter; i++)
        {
            this_thread::sleep_for(chrono::microseconds(microsecond));
            output << CLEARCONSOLE;
            output << WHITE << title << endl;
            output << source << endl;
            barcharts[i].graph(output, colorMap, top);
            currFrame = barcharts[i].getFrame();
            output << WHITE << xlabel << endl;
            output << WHITE << "Frame: " << currFrame << endl;
        }
    }

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize()
    {
        return size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart &operator[](int i)
    {
        if (i < 0 || i >= size)
        {
            throw out_of_range("ourvector: i out of bounds");
        }
        return barcharts[i];
    }
};
