#include <iostream>
#include <vector>
#include <setjmp.h>

#include "RealException.h"

std::vector<jmp_buf*> envBuffers;

#define TRY { envBuffers.push_back(new jmp_buf[_JBLEN]); if( !setjmp(*envBuffers.back()) ) {
#define CATCH } else { delete[] envBuffers.back(); envBuffers.pop_back();
#define ETRY } }
#define THROW longjmp(*envBuffers.back(), 1)


int Inner3()
{
	THROW;
	return 0;
}

int Inner2()
{
	std::cout << "Inner2: Before Inner3()\n";
	int result = Inner3();
	std::cout << "Inner2: After Inner3()\n";
	return Inner3();
}

int Inner1()
{
	TRY
	{
		std::cout << "Inner1: Before Inner2()\n";
		Inner2();
		std::cout << "Inner1: After Inner2()\n";
	}
	CATCH
	{
		std::cout << "Inner1: Catch exception from Inner2()\n";
		THROW;
	}
	ETRY
	return 0;
}

int Inner0()
{
	TRY
	{
		std::cout << "Inner0: Before Inner1()\n";
		Inner1();
		std::cout << "Inner0: After Inner1()\n";
	}
	CATCH
	{
		std::cout << "Inner0: Catch exception from Inner1()\n";
	}
	ETRY
	return 0;
}

int main(int argc, char** argv)
{
	Inner0();
	system("pause");
	return 0;
}
