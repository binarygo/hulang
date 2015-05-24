#include <gtest/gtest.h>
#include <hulang_parser.h>
#include <hulang_indenter.h>
#include <hulang_error.h>
#include <sstream>
#include <iostream>

namespace hulang {

TEST(Parser, lexer)
{
    std::istringstream iss("(12.2+0*-3.2)/\n5.6^3^y*9+_x+15 //yyy");
    StreamReader streamReader(iss);
    Lexer lexer(&streamReader);

    Lexer::Iter it = lexer.begin();
    while(it != lexer.end())
    {
        std::cout << it.token() << std::endl;
        ++it;
    }
}
    
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
    std::istringstream iss("(12.2+0*-3.2)/\n5.6^3^y*9+_x+15 //yyy");
    
    Parser parser(iss);
    AstNode::SP root;
    EXPECT_TRUE(parser.parse(root));
    EXPECT_TRUE(0 != root);
    
    root->print(std::cout, Indenter());
    std::cout << std::endl;
}

TEST(Parser, error)
{
    std::string s = "//abc\n//cde\n/* x\nxy\nxyz */\n//aksdf9\n1+*2";
    std::cout << s << std::endl;
    
    std::istringstream iss(s);
    
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

