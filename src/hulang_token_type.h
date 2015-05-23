#ifndef INCLUDED_HULANG_TOKEN_TYPE_H
#define INCLUDED_HULANG_TOKEN_TYPE_H

#include <hulang_token_type_def.h>
#include <string>

namespace hulang {

struct TokenType
{
    // TYPES
    enum Value
    {
        ID = HULANG_TOKEN_TYPE_ID,
        INTEGER = HULANG_TOKEN_TYPE_INTEGER,
        FLOAT = HULANG_TOKEN_TYPE_FLOAT,
        QMARK = HULANG_TOKEN_TYPE_QMARK,
        COLON = HULANG_TOKEN_TYPE_COLON,
        ASSIGN = HULANG_TOKEN_TYPE_ASSIGN,
        PLUS_ASSIGN = HULANG_TOKEN_TYPE_PLUS_ASSIGN,
        MINUS_ASSIGN = HULANG_TOKEN_TYPE_MINUS_ASSIGN,
        MULTIPLY_ASSIGN = HULANG_TOKEN_TYPE_MULTIPLY_ASSIGN,
        DIVIDE_ASSIGN = HULANG_TOKEN_TYPE_DIVIDE_ASSIGN,
        MOD_ASSIGN = HULANG_TOKEN_TYPE_MOD_ASSIGN,
        INC = HULANG_TOKEN_TYPE_INC,
        DEC = HULANG_TOKEN_TYPE_DEC,
        OR = HULANG_TOKEN_TYPE_OR,
        AND = HULANG_TOKEN_TYPE_AND,
        LT = HULANG_TOKEN_TYPE_LT,
        GT = HULANG_TOKEN_TYPE_GT,
        LE = HULANG_TOKEN_TYPE_LE,
        GE = HULANG_TOKEN_TYPE_GE,
        EQ = HULANG_TOKEN_TYPE_EQ,
        NE = HULANG_TOKEN_TYPE_NE,
        NOT = HULANG_TOKEN_TYPE_NOT,
        PLUS = HULANG_TOKEN_TYPE_PLUS,
        MINUS = HULANG_TOKEN_TYPE_MINUS,
        MULTIPLY = HULANG_TOKEN_TYPE_MULTIPLY,
        DIVIDE = HULANG_TOKEN_TYPE_DIVIDE,
        MOD = HULANG_TOKEN_TYPE_MOD,
        POWER = HULANG_TOKEN_TYPE_POWER,
        LPAR = HULANG_TOKEN_TYPE_LPAR,
        RPAR = HULANG_TOKEN_TYPE_RPAR,
        EOS = HULANG_TOKEN_TYPE_EOS,
        ERROR = HULANG_TOKEN_TYPE_ERROR
    };

    // CLASS METHODS
    static bool fromInt(Value* v, int i);
    static bool fromString(Value* v, const std::string& s);
    static int toInt(Value v);
    static std::string toString(Value v);
};

} // close namespace hulang

#endif // INCLUDED_HULANG_TOKEN_TYPE_H
