/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Rect
*/

#pragma once

#include <bits/stdc++.h>

namespace Engine {
    template <typename T>
    class Rect {
        public:
            Rect(T x = 0, T y = 0, T width = 0, T height = 0) : x(x), y(y), width(width), height(height) {};
            virtual ~Rect() = default;

            // Attributes
            T x = 0;
            T y = 0;
            T width = 0;
            T height = 0;

            // Getters
            T getX() const { return x; }
            T getY() const { return y; }
            T getWidth() const { return width; }
            T getHeight() const { return height; }

            // Setters
            void setX(T x) { x = x; }
            void setY(T y) { y = y; }
            void setWidth(T width) { width = width; }
            void setHeight(T height) { height = height; }

            // Operators
            operator std::string() const {
                return std::string("Rect(") + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(width) + ", " + std::to_string(height) + ")";
            }

            operator std::tuple<T, T, T, T>() const {
                return std::tuple<T, T, T, T>(x, y, width, height);
            }

            // Operators
            bool operator==(const Rect<T> &rect) const {
                return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
            }
            bool operator!=(const Rect<T> &rect) const {
                return !(*this == rect);
            }
            Rect<T> operator+(const Rect<T> &rect) const {
                return Rect<T>(x + rect.x, y + rect.y, width + rect.width, height + rect.height);
            }
            Rect<T> operator-(const Rect<T> &rect) const {
                return Rect<T>(x - rect.x, y - rect.y, width - rect.width, height - rect.height);
            }
            Rect<T> operator*(const Rect<T> &rect) const {
                return Rect<T>(x * rect.x, y * rect.y, width * rect.width, height * rect.height);
            }
            Rect<T> operator/(const Rect<T> &rect) const {
                return Rect<T>(x / rect.x, y / rect.y, width / rect.width, height / rect.height);
            }
            Rect<T> operator+(const T &val) const {
                return Rect<T>(x + val, y + val, width + val, height + val);
            }
            Rect<T> operator-(const T &val) const {
                return Rect<T>(x - val, y - val, width - val, height - val);
            }
            Rect<T> operator*(const T &val) const {
                return Rect<T>(x * val, y * val, width * val, height * val);
            }
            Rect<T> operator/(const T &val) const {
                return Rect<T>(x / val, y / val, width / val, height / val);
            }
            Rect<T> &operator+=(const Rect<T> &rect) {
                x += rect.x;
                y += rect.y;
                width += rect.width;
                height += rect.height;
                return *this;
            }
            Rect<T> &operator-=(const Rect<T> &rect) {
                x -= rect.x;
                y -= rect.y;
                width -= rect.width;
                height -= rect.height;
                return *this;
            }
            Rect<T> &operator*=(const Rect<T> &rect) {
                x *= rect.x;
                y *= rect.y;
                width *= rect.width;
                height *= rect.height;
                return *this;
            }
            Rect<T> &operator/=(const Rect<T> &rect) {
                x /= rect.x;
                y /= rect.y;
                width /= rect.width;
                height /= rect.height;
                return *this;
            }
            Rect<T> &operator+=(const T &val) {
                x += val;
                y += val;
                width += val;
                height += val;
                return *this;
            }
            Rect<T> &operator-=(const T &val) {
                x -= val;
                y -= val;
                width -= val;
                height -= val;
                return *this;
            }
            Rect<T> &operator*=(const T &val) {
                x *= val;
                y *= val;
                width *= val;
                height *= val;
                return *this;
            }
            Rect<T> &operator/=(const T &val) {
                x /= val;
                y /= val;
                width /= val;
                height /= val;
                return *this;
            }

            // Methods
            bool contains(const Rect<T> &rect) const {
                return x <= rect.x && y <= rect.y && width >= rect.width && height >= rect.height;
            }
            bool contains(const T &x, const T &y) const {
                return x >= this->x && y >= this->y && x <= this->x + width && y <= this->y + height;
            }
            bool intersects(const Rect<T> &rect) const {
                return x < rect.x + rect.width && x + width > rect.x && y < rect.y + rect.height && y + height > rect.y;
            }
            Rect<T> intersection(const Rect<T> &rect) const {
                T x = std::max(this->x, rect.x);
                T y = std::max(this->y, rect.y);
                T width = std::min(this->x + this->width, rect.x + rect.width) - x;
                T height = std::min(this->y + this->height, rect.y + rect.height) - y;
                return Rect<T>(x, y, width, height);
            }
            Rect<T> unite(const Rect<T> &rect) const {
                T x = std::min(this->x, rect.x);
                T y = std::min(this->y, rect.y);
                T width = std::max(this->x + this->width, rect.x + rect.width) - x;
                T height = std::max(this->y + this->height, rect.y + rect.height) - y;
                return Rect<T>(x, y, width, height);
            }
    };
}
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Engine::Rect<T> &rect) {
    os << (std::string)rect;
    return os;
}