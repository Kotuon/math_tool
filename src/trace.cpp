/**
 * @file trace.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-29
 *
 *
 *
 */

// std includes //
#include <iostream>
#include <cstdarg>

// Engine includes //
#include "trace.hpp"

/**
 * @brief Construct a new Trace:: Trace object
 *
 */
Trace::Trace() {
    trace_stream.open( "trace.log", std::ofstream::out );
    if ( !trace_stream ) std::cout << "Trace file wasn't opened successfully.\n";
}

Trace &Trace::Instance() {
    static Trace trace_instance;
    return trace_instance;
}

/**
 * @brief Prints a message into the output file
 *
 * @param message Message to be printed
 * @param filename Should always be FILENAME
 * @return void
 */
void Trace::Message( std::string message, std::string filename, int linenumber ) {
    if ( !trace_stream ) return;

    std::string output = filename.substr( 0, std::string::npos ) + "( " + std::to_string( linenumber ) + " )" + ": " + message;

    trace_stream << output << std::endl;
    std::cout << output << std::endl;
}

/**
 * @brief Destroy the Trace:: Trace object
 *
 */
Trace::~Trace() {
    if ( trace_stream ) trace_stream.close();
}