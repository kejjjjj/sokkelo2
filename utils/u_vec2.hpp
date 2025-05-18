#pragma once

#include <type_traits>

template<typename T>
concept ArithmeticConstraint = requires { std::is_arithmetic_v<T>; };

template<ArithmeticConstraint T>
struct vec2
{
	constexpr vec2(T _x, T _y) : x(_x), y(_y){}
	constexpr vec2(T v) : x(v), y(v) {}

	constexpr vec2 operator+(const vec2& other) const noexcept { return { x + other.x, y + other.y }; }
	constexpr vec2 operator-(const vec2& other) const noexcept { return { x - other.x, y - other.y }; }
	constexpr vec2 operator*(const vec2& other) const noexcept { return { x * other.x, y * other.y }; }
	constexpr vec2 operator/(const vec2& other) const noexcept { return { x / other.x, y / other.y }; }

	T x{}, y{};
};

using ivec2 = vec2<int>;
using uvec2 = vec2<std::size_t>;
using fvec2 = vec2<float>;
using dvec2 = vec2<double>;
