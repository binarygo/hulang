#ifndef INCLUDED_HULANG_PEG_PARSER_H
#define INCLUDED_HULANG_PEG_PARSER_H

#include <hulang_lexer.h>
#include <hulang_stream_reader.h>
#include <hulang_ast_node.h>
#include <iostream>

namespace hulang {

class PegParser
{
private:
    // DATA
    StreamReader d_streamReader;
    Lexer        d_lexer;
    
private:
    // NOT IMPLEMENTED
    PegParser(const PegParser& other);
    PegParser& operator= (const PegParser& rhs);        

public:
    // CREATORS
    PegParser(std::istream& in);
    ~PegParser();

    // MANIPULATORS
    AstNode::SP parse();
};

} // close namespace hulang

#endif // INCLUDED_HULANG_PEG_PARSER_H
