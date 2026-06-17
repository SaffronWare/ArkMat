#pragma once

// This library allows us to use some extra registers
/*	TWO IMPORTAN TYPES OF REGISTERS: SIMD VS SISD
*		SIMD: Single instruction, multiple data. This allows the CPU to run a single operation like
*			addition on multiple data points at the same time by packing them into wide registers.
*				Examples of registers: XMM registers are 128-bit registers used exactly for these SIMD operations
					on vector math operations or other flaoting point operations on multiple datapoints.
*					
*		SISD: Sigle instruction, single data. The default when running an operation on one value:
*			example x + y;
* 
*			
*/
#include <immintrin.h>


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

	NaiveVec4& operator+=(const NaiveVec4& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->x += other.z;
		this->w += other.w;
		return *this;
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


// alignas(16) tellsthe compiler to make sure that the program always forces this
// struct to be aligned to 16 bytes on the cpu. This allows us to usethe ever so slightly faster
// _mm_load_ps stuff instead of using the unaligned versions

// Another way to do this with Vs is __declspec(align(16))
// I assume __declspec tells the compiler its giving a specification to the struct and well align(16) is self-explanatory.
struct alignas(16) Vec4
{
	/*
	* Union tells the program the make sure the members defined in the union share the EXACT same memory adress.
	* This means both our x,y,z,w floats and data are sharing memory which gives us the best of both worlds:
	*	A way to acces members with Vec4.x
	*	A way the full vector data as one object (data)
	* Why use struct inside union?
	*	Becuase if we just did float x; float y; float z; it would think
	*	we are saying to make sure,x,y,z,w,data all share memory adress (NOT what we want!)
	* 
	* Nuances with struct/class/unnion Name {}; sutrct/class/union {} name; and struct/class/union {}
	*	The first one creates a sort of templae struct/class/union object which can be used to create different instances of it
	*	The second one creates one instance of that struct but you cant delcare more structs of that type
	*	The third is an anynoymous sturct/class/union and actually literally just creates those fields in the local scope without 
	*	actually even creating a union object or struct oject or class object.
	*/
	union
	{
		struct {
			float x, y, z, w;
		};
		float data[4];


		// important note about __m128
		/*
		* This is not an actual registry which store our object's data, it is a conainer for our data which WILL get 
		* put into a registry when we call an operation like _mm_add_ps()
		*!It is literally just a container to our data, aka an ojbect thats 128 bits and has same memory adress as our data!
		* Because of this we can just put it in here (union), and it will be as if we loaded the object into it already! and it does not
		* take up space in a register cus its simply a CONTAINER acting like a "fake" register that gets put into the register when needed.
		* Why not just do __m128 reg = *(__m128reg*)(data*);
		* Simply because the compiler might not knwo reg and data share same data, and it might do weird optimizations
		* So the two ways to fix this is:
		*	A) Use union: Our program will make them share same adress whilst warning the compiler not to optimize it
		*	B) Use _mm_load_ps(data) which as an intrisic operator implemented by the compiler itself, so the ocompiler itself
		*		will auto generate the code to make it have same adress and it will thus obviously know.
		* 
		* To prevent claling _mm_load_ps(data) multiple times, we just use union here and its data will update automatically with xyzw as
		* it shares same memory!
		* 
		* WARNING: we can only really use union cause we know our data is already algined and right size!
		*/
		__m128 reg;
	};

	Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w) {}

	Vec4& operator+=(const Vec4& other)
	{
		// this creates an XMM_n register with 128 bits of storage and loads our vector onto it
		// ignore _mm_load convention for now but know that there exists loadu if data is unaligned
		// Before this was slightly slower than wih aligned data but now its essentially the same.

		// p standsfor packed (aka its multiple data points and not one big scalar
		// s stands for single-precision floating point (what we are using)
		// so together the p,s and the fact it returns 128bit regiser it allows it know that:
		//    one float (sinel precision floating point) is 32bits and were packing them into 128 bits,so there must be 4 boundaries

		/*-----OLD WAY----
		__m128 this_vector = _mm_load_ps(data);
		__m128 other_vector = _mm_load_ps(other.data);
		this_vector = _mm_add_ps(this_vector, other_vector);
		_mm_store_ps(data, this_vector);
		return *this;
		*/

		// We can do = since i think the __m128 operator for = just copies the data into itself, not genuinely creating/copying/storing
		// a reference to the other __m128 object! // Since we used union, this automatically updates data AND xyzw
		reg = _mm_add_ps(reg, other.reg);
		
		return *this;
	}

	Vec4 operator+(const Vec4& other) const
	{
		
		/*--------OLD WAY-----
		__m128 v1 = _mm_load_ps(data);
		__m128 v2 = _mm_load_ps(other.data);
		v1 = _mm_add_ps(v1,v2);
		Vec4 out;
		_mm_store_ps(out.data, v1);
		return out;
		*/

		Vec4 res;
		res.reg = _mm_add_ps(reg, other.reg);
		return res;
	}

};


