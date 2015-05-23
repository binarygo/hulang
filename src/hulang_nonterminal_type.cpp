#include <hulang_nonterminal_type.h>
#include <hulang_error.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool NonterminalType::fromInt(Value* v, int i)
{
    assert(v);    
    switch(i) {
        case EXPR: {
            *v = EXPR;
            return true;
        } break;
        case ASSIGN_EXPR: {
            *v = ASSIGN_EXPR;
            return true;
        } break;
        case COND_EXPR: {
            *v = COND_EXPR;
            return true;
        } break;
        case OR_EXPR: {
            *v = OR_EXPR;
            return true;
        } break;
        case AND_EXPR: {
            *v = AND_EXPR;
            return true;
        } break;
        case EQ_EXPR: {
            *v = EQ_EXPR;
            return true;
        } break;
        case REL_EXPR: {
            *v = REL_EXPR;
            return true;
        } break;
        case ADD_EXPR: {
            *v = ADD_EXPR;
            return true;
        } break;
        case MULTIPLY_EXPR: {
            *v = MULTIPLY_EXPR;
            return true;
        } break;
        case POWER_EXPR: {
            *v = POWER_EXPR;
            return true;
        } break;
        case UNARY_EXPR: {
            *v = UNARY_EXPR;
            return true;
        } break;
        case POSTFIX_EXPR: {
            *v = POSTFIX_EXPR;
            return true;
        } break;
        case PRIMARY_EXPR: {
            *v = PRIMARY_EXPR;
            return true;
        } break;
    }
    return false;
}

bool NonterminalType::fromString(Value* v, const std::string& s)
{
    assert(v);
    if(s == "EXPR")
    {
        *v = EXPR;
        return true;
    }
    if(s == "ASSIGN_EXPR")
    {
        *v = ASSIGN_EXPR;
        return true;
    }
    if(s == "COND_EXPR")
    {
        *v = COND_EXPR;
        return true;
    }
    if(s == "OR_EXPR")
    {
        *v = OR_EXPR;
        return true;
    }
    if(s == "AND_EXPR")
    {
        *v = AND_EXPR;
        return true;
    }
    if(s == "EQ_EXPR")
    {
        *v = EQ_EXPR;
        return true;
    }
    if(s == "REL_EXPR")
    {
        *v = REL_EXPR;
        return true;
    }
    if(s == "ADD_EXPR")
    {
        *v = ADD_EXPR;
        return true;
    }
    if(s == "MULTIPLY_EXPR")
    {
        *v = MULTIPLY_EXPR;
        return true;
    }
    if(s == "POWER_EXPR")
    {
        *v = POWER_EXPR;
        return true;
    }
    if(s == "UNARY_EXPR")
    {
        *v = UNARY_EXPR;
        return true;
    }
    if(s == "POSTFIX_EXPR")
    {
        *v = POSTFIX_EXPR;
        return true;
    }
    if(s == "PRIMARY_EXPR")
    {
        *v = PRIMARY_EXPR;
        return true;
    }
    return false;
}

int NonterminalType::toInt(Value v)
{
    return v;
}

std::string NonterminalType::toString(Value v)
{
    switch(v) {
        case EXPR: return "EXPR";
        case ASSIGN_EXPR: return "ASSIGN_EXPR";
        case COND_EXPR: return "COND_EXPR";
        case OR_EXPR: return "OR_EXPR";
        case AND_EXPR: return "AND_EXPR";
        case EQ_EXPR: return "EQ_EXPR";
        case REL_EXPR: return "REL_EXPR";
        case ADD_EXPR: return "ADD_EXPR";
        case MULTIPLY_EXPR: return "MULTIPLY_EXPR";
        case POWER_EXPR: return "POWER_EXPR";
        case UNARY_EXPR: return "UNARY_EXPR";
        case POSTFIX_EXPR: return "POSTFIX_EXPR";
        case PRIMARY_EXPR: return "PRIMARY_EXPR";
    }
    assert(0);
    return "";
}
    
} // close namespace hulang
