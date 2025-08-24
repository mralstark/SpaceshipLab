#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2 {
    float x, y;
    
    Vector2(float x = 0, float y = 0);
    
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator*=(float scalar);
    
    float length() const;
    float lengthSquared() const;
    Vector2 normalized() const;
    
    static float distance(const Vector2& a, const Vector2& b);
};

#endif