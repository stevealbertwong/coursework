/*

https://www.youtube.com/watch?v=q4vZIF-uMzs

*/
#include "sally.h"


// 1st constructor
Sally::Sally(){}

// 2nd constructor same but could add number as member
Sally::Sally(int a){
	num = a;
}

// return type: Sally
Sally Sally::operator+(Sally another_sally_obj){
	Sally new_sally_object; // Sally c
	new_sally_object.num = num + another_sally_obj.num; // Sally c = a + b

	return new_sally_object;
}