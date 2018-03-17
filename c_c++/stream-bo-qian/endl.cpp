/*
endl implementation

https://www.youtube.com/watch?v=yMseUJm1604&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=20
*/

ostream& endl(ostream& os){
	os.put('\n');
	os.flush();
	return os;
}


// paramter: ptr to function with same signiture as endl
ostream& ostream::operator<<(ostream& (*func)(ostream&)){
	return (*func)(*this); // invoke function(endl) on this stream, and then return the returned value
}
