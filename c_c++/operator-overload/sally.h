#ifndef _sally_h_
#define _sally_h_

class Sally{

	public:
		Sally();
		Sally(int a);
		Sally operator+(Sally another_sally_obj);

		int num;
};

#endif
