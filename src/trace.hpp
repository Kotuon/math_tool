/**
 * @file trace.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-29
 *
 *
 *
 */

#pragma once
#ifndef TRACE_HPP
#define TRACE_HPP

#define FILENAME __FILE__
#define LINENUMBER __LINE__

// std includes //
#include <string>
#include <fstream>

/*! Trace class */
class Trace {
public:
    static Trace& Instance();
    void Message( std::string message, std::string filename, int linenumber );
    ~Trace();

private:
    Trace();

private:
    std::fstream trace_stream; //!< Output file
};

#endif