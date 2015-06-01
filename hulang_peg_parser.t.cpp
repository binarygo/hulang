#include <gtest/gtest.h>
#include <hulang_peg_parser.h>
#include <sstream>
#include <iostream>

namespace hulang {

TEST(PegParser, expr1)
{
    std::string s = "a = b = 1";
    std::cout << s << std::endl;
    
    std::istringstream iss(s);
    
    PegParser parser(iss);
    AstNode::SP root = parser.parse();
    EXPECT_TRUE(0 != root);
    
    root->print(std::cout, Indenter());
    std::cout << std::endl;
}

TEST(PegParser, expr2)
{
    std::string s = "(12.2+0*-3.2)/\n5.6^3^y*9+_x+15 //yyy\n + \"xyz\"* 3";
    std::cout << s << std::endl;
    
    std::istringstream iss(s);
    
    PegParser parser(iss);
    AstNode::SP root = parser.parse();
    EXPECT_TRUE(0 != root);
    
    root->print(std::cout, Indenter());
    std::cout << std::endl;
}
    
} // close namespace hulang

