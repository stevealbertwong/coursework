//include guard prevent duplicate header includes in prepossessing
#ifndef SHAPE_H
#define SHAPE_H

#include <string>

using namespace std;

class Shape{
	public:
		void setValues(int a, int b);
		// virtual => base class function allowed to be overriden
		// setColor has to be same as children n take parameters
		virtual void setColor(string c); // overriden by subclass
		virtual void setName(); // not overriden
		string color;
		string name;

	// protected: only inherited class could directly amend
	// what about instance ??
	protected:
		int height;
		int width;
		
};

#endif