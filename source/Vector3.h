#ifndef GRAVITY_SIMULATION_VECTOR
#define GRAVITY_SIMULATION_VECTOR

constexpr float VECTOR_FLOAT_ACCURACY = 0.0000001f;

struct Vector3 {

	float x;
	float y;
	float z;

	Vector3(float x = 0.f, float y = 0.f, float z = 0.f);
	~Vector3() = default;

	// work with other vectors
	float distanceSquared(const Vector3& other) const;
	float distance(const Vector3& other) const;
	Vector3 direction(const Vector3& other) const;
	Vector3 direction(const Vector3& other, float distanceSqr) const;

	float scalarMult(const Vector3& other) const;

	// work only with this vector

	float length() const;
	
	// makes module of vector equal one
	void normalize();
	Vector3 normal() const;

	// scales each coordinate respectively
	Vector3 scale(const Vector3& other) const;


	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float a) const;
	Vector3 operator/(float a) const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);
	Vector3& operator=(const Vector3& other) = default;
};


#endif // !GRAVITY_SIMULATION_VECTOR
