//include guard prevent duplicate header includes in prepossessing
#ifndef PARENT_H
#define PARENT_H

#include <string>
#include <iostream>

using namespace std;

class Parent{
	// public: accessible by other class
	public:
		void setParentProtectedVariable(int a, int b);
		
		// virtual => child COULD overwrite or just call this original function
		// pure virtual e.g. virtual func()=0 -> child MUST override
		// child's setParentPublicVariable() MUST be same as parent i.e. take string c as parameter
		virtual void setParentPublicVariable(string c); 
		virtual void setName(); // not overriden

		string color;
		string name;

		// get() is for access of both protected or private in main()
		int getProtected() const {return protected_var;}
		// this == const Shape * == const ptr at class Shape
		// int getProtected() const {return this->protected_var;} // same as above		
		int getPrivate() const {return this->private_var;}


	// protected: accessible by child class 
	protected:
		int height;
		int width;
		int protected_var = 5;
		void protected_func() {cout << "parent's protected_func" << endl;}

	// private: accessible only by parent.cpp
	private:	

		int private_var = 10;		
};

#endif