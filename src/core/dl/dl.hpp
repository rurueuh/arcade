/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** dl
*/

#pragma once

#include <bits/stdc++.h>
#include <dlfcn.h>

class dl {
    public:
        dl(const std::string &path);
        ~dl();
        void *getSym(const std::string &sym);
        void *getHandle() const;

        void *dlsym(void *handle, const char *symbol);

        static class Error : public std::exception {
            public:
                Error(const std::string &msg) : _msg(msg) {}
                const char *what() const noexcept override { return _msg.c_str(); }
            private:
                std::string _msg;
        } error;

    private:
        void *_handle;
        std::string _path;
};