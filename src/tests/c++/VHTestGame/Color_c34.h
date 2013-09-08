#ifndef COLOR_C34_H_
#define COLOR_C34_H_

class Color_c34{
public:
	Color_c34(int = 0, int = 0, int = 0);

	int& operator[](size_t);
	const int& operator[](size_t) const;

private:
	int _val[3];
};

#endif
