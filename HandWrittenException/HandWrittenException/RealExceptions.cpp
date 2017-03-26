#include <iostream>
#include <vector>

#include "RealException.h"

namespace RealException
{
	int Inner2()
	{
		throw 20;
		return 0;
	}


	int Inner1()
	{
		try
		{
			std::cout << "inner1: before inner2()\n";
			Inner2();
			std::cout << "inner1: after inner2()\n";
		}
		catch (...)
		{
			std::cout << "inner1: catch exception from inner2()\n";
			throw 30;
		}
		return 0;
	}

	int Inner0()
	{
		try
		{
			std::cout << "inner0: before inner1()\n";
			Inner1();
			std::cout << "inner0: after inner1()\n";
		}
		catch (...)
		{
			std::cout << "inner0: catch exception from inner1()\n";
		}
		return 0;
	}
}