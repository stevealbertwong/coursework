//include guard prevent duplicate header includes in prepossessing
#ifndef SHAPE_H
#define SHAPE_H

class Shape{
	public:

		void setValues(int a, int b);

	// protected: only inherited class could directly amend
	// what about instance ??
	protected:
		int height;
		int width;
};

#endif