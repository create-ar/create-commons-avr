#ifndef CONVERTER_h
#define CONVERTER_h

union ShortUnion
{
	short short_value;
	unsigned char char_value[2];
};

union IntUnion
{
	int int_value;
	unsigned char char_value[4];
};

#endif