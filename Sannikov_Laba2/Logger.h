#pragma once
#include <iostream>
#include <fstream>
class Logger
{
private:
	std::ostream& potok;
	std::streambuf* staryBuf;
public:
	void vFile(std::ofstream& fail)
	{
		potok.rdbuf(fail.rdbuf());
	}
	Logger(std::ostream& peremennaya) : potok(peremennaya)
	{
		staryBuf = peremennaya.rdbuf();
	}
	~Logger()
	{
		potok.rdbuf(staryBuf);
	}
};