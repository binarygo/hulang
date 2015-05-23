#include <gtest/gtest.h>
#include <hulang_parser.h>
#include <hulang_indenter.h>
#include <hulang_error.h>
#include <sstream>
#include <iostream>

namespace hulang {

TEST(Parser, condExpr)
{
    std::istringstream iss("(12 && 9 ? (_x+_y ? 1:2) : _z*5) ? 1 : 2");
    // std::istringstream iss("1 ? a?c:d : 3 ? 4 : 5");

    Parser parser(iss);
    AstNode::SP root;
    EXPECT_TRUE(parser.parse(root));
    EXPECT_TRUE(0 != root);
    
    root->print(std::cout, Indenter());
    std::cout << std::endl;
}
    
TEST(Parser, expr)
{
    std::istringstream iss("(12.2+0*-3.2)/\n5.6^3^y*9+_x+15");
    
    Parser parser(iss);
    AstNode::SP root;
    EXPECT_TRUE(parser.parse(root));
    EXPECT_TRUE(0 != root);
    
    root->print(std::cout, Indenter());
    std::cout << std::endl;
}

TEST(Parser, error)
{
    std::istringstream iss("1+*2");
    
    Parser parser(iss);
    AstNode::SP root;
    try
    {
        parser.parse(root);
        if(root)
        {
            root->print(std::cout, Indenter());
            std::cout << std::endl;
        }
    }
    catch(const Error& e)
    {
        std::cout << e.what() << std::endl;
    }
}
    
} // close namespace hulang

