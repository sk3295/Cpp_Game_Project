#pragma once

class Vector {
public: 
	float x, y;

	Vector(float wantX, float wantY) {
		x = wantX;
		y = wantY;
	}
	Vector() { x = y = 0; }

	// 벡터의 "크기"
	float Magnitude() {
		// SQuare RooT Float
		return sqrtf( (x * x) + (y * y) );
	}

	// Normalize
	// > 정규화
	Vector& Normalize() {
		float mag = Magnitude(); 
							
		x /= mag;
		y /= mag;				

		return *this;			
	};

	Vector normalized() {
		float mag = Magnitude();

		return Vector(x / mag, y / mag);
	}

	Vector operator  +  (Vector other) {
		return Vector(  x + other.x,    y + other.y  );
	}
	Vector& operator += (Vector other) {
		x += other.x;
		y += other.y;

		return *this;
	}
	Vector operator  -  (Vector other) {
		return Vector(x - other.x, y - other.y);
	}
	Vector& operator -= (Vector other) {
		x -= other.x;
		y -= other.y;
		
		return *this;
	}
	Vector operator  *  (Vector other) {
		return Vector(x * other.x, y * other.y);
	}
	Vector& operator *= (Vector other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vector operator  *  (float other) {
		return Vector(x * other, y * other);
	}
	Vector& operator *= (float other) {
		x *= other;
		y *= other;
		
		return *this;
	}
	Vector operator  /  (Vector other) {
		return Vector(x / other.x, y / other.y);
	}
	Vector& operator /= (Vector other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector operator  /  (float other) {
		return Vector(x / other, y / other);
	}
	Vector& operator /= (float other) {
		x /= other;
		y /= other;
		return *this;
	}
};