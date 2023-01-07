// bar.h
// Bar class which stores data for each bar displayed on the graph such as the name, category and value.

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    string name;
    string category;
    int value;
 public:

    // default constructor:
    Bar() {
        name = "";
        category = "";
        value = 0;
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        this->name = name;
        this->category = category;
        this->value = value;
    }

    // destructor:
    virtual ~Bar() {
        // no memory allocation
    }

    // getName:
	string getName() {
        return name;
	}

    // getValue:
	int getValue() {
        return value;
	}

    // getCategory:
	string getCategory() {
        return category;
	}

	// operators
	bool operator<(const Bar &other) const {
        return this->value<other.value;
	}

	bool operator<=(const Bar &other) const {
        return this->value<=other.value;
	}

	bool operator>(const Bar &other) const {
        return this->value>other.value;
	}

	bool operator>=(const Bar &other) const {
        return this->value>=other.value;
	}
};