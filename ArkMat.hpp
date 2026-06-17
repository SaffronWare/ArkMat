#pragma once


struct NaiveVec4
{
	float x,y,z,w;

	NaiveVec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w)
	{

		/*
		* Much better to use a member initializer list.
		*	Usually you have two phases when creating an object: 
					Phase A) Allocation & Initialization
					Phase B) Constructor Body
			When using the method below, the program, before running construcor body will allocate memory for its fields
			without giving them a set initial value, it will be filled with garbage. Your body then overwrides it.

			By using a member initializer list, you tell the compiler to write the 
			program in a way that it never initializes it to
			garbage, the moment it allocates memory for its members, it initializes them with your values, 
			removinga whole step.

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		*/
	}

	// Use const NaiveVec4& other for a simple reason,
	// By using just NaiveVec4, our function will have to take a shallow copy of what we pass to it
	// This wastes precious time, instead we can pass a reference which we promise not to modify with the const keyword.
	// This allows us to read heavy variables without wasting time copying them.
	NaiveVec4 operator+(const NaiveVec4& other) const
	{
		return NaiveVec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}


	// Since these operator functions are so short and constantly used,
	// the function call cost is actually significant compared to the fuction body,
	// we can save a lot of performance by making them inline
	// NEAT QUIRK!: C++ makes methodes declared AND implemented in the struct's body inline by defualt
	// When we spli this function, we would have to add inline in the implementation (NOT DELCARATION)!
	NaiveVec4 operator-(const NaiveVec4& other) const
	{
		return NaiveVec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
	}


	~NaiveVec4()
	{
	}
};

struct Vec4
{
	float x, y, z, w;
	Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w)
	{

	}
};


