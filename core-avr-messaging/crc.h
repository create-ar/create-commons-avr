#ifndef _CRC16_h
#define _CRC16_h

// retrieves a crc16 for a buffer
unsigned short crc16(
	unsigned char* buffer,
	unsigned int start,
	unsigned int size)
{
	unsigned short crc = 0xFFFF;

	unsigned char* ptr = buffer + start;

	if (buffer && size)
	{
		while (size--)
		{
			crc = (crc >> 8) | (crc << 8);
			crc ^= *ptr++;
			crc ^= ((char)crc) >> 4;
			crc ^= crc << 12;
			crc ^= (crc & 0xFF) << 5;
		}
	}

	return crc;
}

#endif