#ifndef INCLUDED_HULANG_NONTERMINAL_TYPE_H
#define INCLUDED_HULANG_NONTERMINAL_TYPE_H

#include <string>

namespace hulang {

struct NonterminalType
{
    // TYPES
    enum Value
    {
        EXPR = 0,
        ASSIGN_EXPR = 1,
        COND_EXPR = 2,
        OR_EXPR = 3,
        AND_EXPR = 4,
        EQ_EXPR = 5,
        REL_EXPR = 6,
        ADD_EXPR = 7,
        MULTIPLY_EXPR = 8,
        POWER_EXPR = 9,
        UNARY_EXPR = 10,
        POSTFIX_EXPR = 11,
        PRIMARY_EXPR = 12
    };

    // CLASS METHODS
    static bool fromInt(Value* v, int i);
    static bool fromString(Value* v, const std::string& s);
    static int toInt(Value v);
    static std::string toString(Value v);
};

} // close namespace hulang

#endif // INCLUDED_HULANG_NONTERMINAL_TYPE_H
