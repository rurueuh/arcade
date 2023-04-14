/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Vector2
*/

#pragma once

#include <bits/stdc++.h>

namespace Engine {
    template <typename T>
    class Vector2 {
        public:
            Vector2() = default;
            Vector2(T x, T y) : x(x), y(y) {};
            virtual ~Vector2() = default;

            // Getters
            T getX() const { return x; }
            T getY() const { return y; }

            // Setters
            void setX(T _x) { x = _x; }
            void setY(T _y) { y = _y; }

            // Operators
            operator std::string() const {
                return std::string("Vector2(") + std::to_string(x) + ", " + std::to_string(y) + ")";
            }

            operator std::pair<T, T>() const {
                return std::pair<T, T>(x, y);
            }

            // Operators
            bool operator==(const Vector2<T> &vec) const {
                return x == vec.x && y == vec.y;
            }
            bool operator!=(const Vector2<T> &vec) const {
                return !(*this == vec);
            }
            Vector2<T> operator+(const Vector2<T> &vec) const {
                return Vector2<T>(x + vec.x, y + vec.y);
            }
            Vector2<T> operator-(const Vector2<T> &vec) const {
                return Vector2<T>(x - vec.x, y - vec.y);
            }
            Vector2<T> operator*(const Vector2<T> &vec) const {
                return Vector2<T>(x * vec.x, y * vec.y);
            }
            Vector2<T> operator/(const Vector2<T> &vec) const {
                return Vector2<T>(x / vec.x, y / vec.y);
            }
            Vector2<T> operator+(const T &val) const {
                return Vector2<T>(x + val, y + val);
            }
            Vector2<T> operator-(const T &val) const {
                return Vector2<T>(x - val, y - val);
            }
            Vector2<T> operator*(const T &val) const {
                return Vector2<T>(x * val, y * val);
            }
            Vector2<T> operator/(const T &val) const {
                return Vector2<T>(x / val, y / val);
            }
            Vector2<T> &operator+=(const Vector2<T> &vec) {
                x += vec.x;
                y += vec.y;
                return *this;
            }
            Vector2<T> &operator-=(const Vector2<T> &vec) {
                x -= vec.x;
                y -= vec.y;
                return *this;
            }
            Vector2<T> &operator*=(const Vector2<T> &vec) {
                x *= vec.x;
                y *= vec.y;
                return *this;
            }
            Vector2<T> &operator/=(const Vector2<T> &vec) {
                x /= vec.x;
                y /= vec.y;
                return *this;
            }
            Vector2<T> &operator+=(const T &val) {
                x += val;
                y += val;
                return *this;
            }
            Vector2<T> &operator-=(const T &val) {
                x -= val;
                y -= val;
                return *this;
            }
            Vector2<T> &operator*=(const T &val) {
                x *= val;
                y *= val;
                return *this;
            }
            Vector2<T> &operator/=(const T &val) {
                x /= val;
                y /= val;
                return *this;
            }
            Vector2<T> &operator=(const Vector2<T> &vec) {
                x = vec.x;
                y = vec.y;
                return *this;
            }

            T x = 0;
            T y = 0;
        protected:
        private:
    };
}
inline std::ostream& operator<<(std::ostream& os, const Engine::Vector2<int>& vec) {
    os << static_cast<std::string>(vec);
    return os;
}

// #define Vector2i Engine::Vector2<int>
// #define Vector2f Engine::Vector2<float>
// #define Vector2d Engine::Vector2<double>
