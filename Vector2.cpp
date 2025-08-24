#include "Vector2.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::normalized() const {
    float len = length();
    if (len == 0) return Vector2(0, 0);
    return Vector2(x / len, y / len);
}

float Vector2::distance(const Vector2& a, const Vector2& b) {
    Vector2 diff = a - b;
    return diff.length();
}