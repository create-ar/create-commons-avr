#ifndef CONVERTER_h
#define CONVERTER_h

union ShortUnion
{
	short shortValue;
	unsigned char charValue[2];
};

union IntUnion
{
	int intValue;
	unsigned char charValue[4];
};

#endif