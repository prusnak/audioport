#ifndef AUDIOPORT_COMMON_H
#define AUDIOPORT_COMMON_H

enum AudioPortMode
{
	MODE_RS232,
	MODE_CUSTOM
};

void convertSendRS232(short *buf, short character, int bitlen);
void convertSendCustom(short *buf, short character, int bitlen);

class CyclicBuffer
{
public:
	CyclicBuffer(int size);
	~CyclicBuffer();
	void put(const char c);
	void put(const char *str);
	short get();

private:
	int size, start, end;
	char *buf;
};

#endif
