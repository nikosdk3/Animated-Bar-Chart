// barchart.h
// BarChart class which stores all of the bars in one frame and prints all of the bars in a frame with color and data.

#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include "myrandom.h" // used in graders, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");

//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
//
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart
{
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar *bars; // pointer to a C-style array
    int capacity;
    int size;
    string frame;

public:
    // default constructor:
    BarChart()
    {
        bars = NULL;
        capacity = 0;
        size = 0;
        frame="";
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n)
    {
        bars = new Bar[n];//allocate memory for n bars on the heap;
        capacity = n;
        size = 0;
        frame="";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart &other)
    {
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;
        //copying all data
        for (int i = 0; i < other.size; i++)
        {
            this->bars[i] = other.bars[i];//copying each value from Bar object index to new Bar
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    // same as copy constructor except the initial object gets freed from memory
    BarChart &operator=(const BarChart &other)
    {
        // check if we are moving to ourself
        if (this == &other)
            return *this;
        delete[] bars; // bars already exists so free memory first then move data
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;
        for (int i = 0; i < other.size; i++)
        {
            this->bars[i] = other.bars[i];
        }
        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear()
    {
        delete[] bars;
        bars = NULL;
        capacity = 0;
        size = 0;
        frame = "";
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart()
    {
        if (bars != nullptr)
        {
            delete[] bars;
        }
    }

    // setFrame
    void setFrame(string frame)
    {
        this->frame = frame;
    }

    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame()
    {
        return frame;
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category)
    {
        if (size == capacity)
        {
            return false;
        }
        bars[size] = Bar(name, value, category);
        size++;
        return true;
    }

    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize()
    {
        return size;
    }

    int getCapacity()
    {
        return capacity;
    }

    Bar *getBars()
    {
        return bars;
    }

    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar &operator[](int i)
    {
        if (i < 0 || i >= size)
        {
            throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output)
    {
        sort(bars, bars + size, greater<Bar>());//sorting algorithm
        output << "frame: " << getFrame() << endl;
        for (int i = 0; i < size; ++i)
        {
            output << bars[i].getName() << " ";
            output << bars[i].getValue() << " ";
            output << bars[i].getCategory() << endl;
        }
    }
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top)
    {
        int lenMax = 60; // this is number of BOXs that should be printed
                         // for the top bar (max value)
        int count = 0;
        sort(bars, bars + size, greater<Bar>());
        for (int i = 0; i < top; i++)//looping for how many times user specified
        {
            string color = colorMap[bars[i].getCategory()]; // retrieved from colorMap
            string barstr = "";
            lenMax = double(bars[count].getValue()) / double(bars[0].getValue()) * 60;//update lenMax to be current value/highest value * 60
            for (int i = 0; i < lenMax; i++)//loops to print boxes for the bar
            {
                barstr += BOX;
            }
            output << color << barstr << " " << bars[count].getName() << " " << bars[count].getValue() << endl;
            count++;
        }
    }
};