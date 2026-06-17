#include "ArkMat.hpp"
#include <chrono>
#include <iostream>


int main()
{	
	NaiveVec4 v1(1.0f, -12.0f, 0.0f, 1.20f);
	NaiveVec4 v2(-5.0f, 8412.0f, 102381.0f, 0.01f);
	NaiveVec4 res;

	auto start = std::chrono::high_resolution_clock::now();

	
	for (int i = 0; i < 100000000; i++) 
	{
		res += v1 + v2;
	}

	std::cout << res.x << std::endl;

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Naive Vec4 Addition test took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " of runtime!\n";

	Vec4 a(1.0f, -12.0f, 0.0f, 1.20f);
	Vec4 b(-5.0f, 8412.0f, 102381.0f, 0.01f);
	Vec4 c;

	start = std::chrono::high_resolution_clock::now();


	for (int i = 0; i < 100000000; i++)
	{
		c += a + b;
	}

	std::cout << c.x << std::endl;

	end = std::chrono::high_resolution_clock::now();

	std::cout << "Vec4 Addition test took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " of runtime!";

	Vec4 a_(1.0f, -12.0f, 0.0f, 1.20f);
	Vec4 b_(-5.0f, 8412.0f, 102381.0f, 0.01f);
	Vec4 c_;

	start = std::chrono::high_resolution_clock::now();


	for (int i = 0; i < 100000000 / 4; i++)
	{
		c_ += a_ + b_;
		c_ += a_ + b_;
		c_ += a_ + b_;
		c_ += a_ + b_;
		
	}

	std::cout << c_.x << std::endl;

	end = std::chrono::high_resolution_clock::now();

	std::cout << "Vec4 Addition test with UNROLLING took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " of runtime!";

	return 0;
}
