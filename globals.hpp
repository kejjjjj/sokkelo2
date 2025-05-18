#pragma once

enum Status : char { failure, success };
enum struct EDirection : unsigned char { N, E, S, W };

#define NONCOPYABLE(className) \
        className(const className&) = delete; \
        className& operator=(const className&) = delete; \
        className(className&&) = default; \
        className& operator=(className&&) = default
