//include guard prevent duplicate header includes in prepossessing
#ifndef PARENT_H
#define PARENT_H

#include <string>
#include <iostream>

using namespace std;

class Parent{
	// public: visible to main, other class
	public:
		void setParentProtectedVariable(int a, int b);
		
		// virtual => child to overwrite
		// setParentPublicVariable() has to be same as children n take parameters
		virtual void setParentPublicVariable(string c); // overriden by subclass
		virtual void setName(); // not overriden

		string color;
		string name;

		// get() is for access of both protected or private in main()
		int getProtected() const {return protected_var;}
		// this == const Shape * == const ptr at class Shape
		// int getProtected() const {return this->protected_var;} // same as above		
		int getPrivate() const {return this->private_var;}


	// protected: visible to child class 
	protected:
		int height;
		int width;
		int protected_var = 5;
		void protected_func() {cout << "parent's protected_func" << endl;}

	// private: visible to parent.cpp
	private:	

		int private_var = 10;		
};

#endif