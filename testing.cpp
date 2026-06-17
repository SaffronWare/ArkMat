#include "ArkMat.hpp"
#include <chrono>
#include <iostream>


int main()
{	
	NaiveVec4 v1(1.0f, -12.0f, 0.0f, 1.20f);
	NaiveVec4 v2(-5.0f, 8412.0f, 102381.0f, 0.01f);
	NaiveVec4 res;

	auto start = std::chrono::high_resolution_clock::now();

	
	for (int i = 0; i < 1000000; i++) 
	{
		res = v1 + v2;
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Naive Vec4 Addition test took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " of runtime!";

	return 0;
}
