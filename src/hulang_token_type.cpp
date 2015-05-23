#include <hulang_token_type.h>
#include <hulang_error.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool TokenType::fromInt(Value* v, int i)
{
    assert(v);    
    switch(i) {
        case ID: {
            *v = ID;
            return true;
        } break;
        case INTEGER: {
            *v = INTEGER;
            return true;
        } break;
        case FLOAT: {
            *v = FLOAT;
            return true;
        } break;
        case QMARK: {
            *v = QMARK;
            return true;
        } break;
        case COLON: {
            *v = COLON;
            return true;
        } break;
        case ASSIGN: {
            *v = ASSIGN;
            return true;
        } break;
        case PLUS_ASSIGN: {
            *v = PLUS_ASSIGN;
            return true;
        } break;
        case MINUS_ASSIGN: {
            *v = MINUS_ASSIGN;
            return true;
        } break;
        case MULTIPLY_ASSIGN: {
            *v = MULTIPLY_ASSIGN;
            return true;
        } break;
        case DIVIDE_ASSIGN: {
            *v = DIVIDE_ASSIGN;
            return true;
        } break;
        case MOD_ASSIGN: {
            *v = MOD_ASSIGN;
            return true;
        } break;
        case INC: {
            *v = INC;
            return true;
        } break;
        case DEC: {
            *v = DEC;
            return true;
        } break;
        case OR: {
            *v = OR;
            return true;
        } break;
        case AND: {
            *v = AND;
            return true;
        } break;
        case LT: {
            *v = LT;
            return true;
        } break;
        case GT: {
            *v = GT;
            return true;
        } break;
        case LE: {
            *v = LE;
            return true;
        } break;
        case GE: {
            *v = GE;
            return true;
        } break;
        case EQ: {
            *v = EQ;
            return true;
        } break;
        case NE: {
            *v = NE;
            return true;
        } break;
        case NOT: {
            *v = NOT;
            return true;
        } break;
        case PLUS: {
            *v = PLUS;
            return true;
        } break;
        case MINUS: {
            *v = MINUS;
            return true;
        } break;
        case MULTIPLY: {
            *v = MULTIPLY;
            return true;
        } break;
        case DIVIDE: {
            *v = DIVIDE;
            return true;
        } break;
        case MOD: {
            *v = MOD;
            return true;
        } break;
        case POWER: {
            *v = POWER;
            return true;
        } break;
        case LPAR: {
            *v = LPAR;
            return true;
        } break;
        case RPAR: {
            *v = RPAR;
            return true;
        } break;
        case EOS: {
            *v = EOS;
            return true;
        } break;
        case ERROR: {
            *v = ERROR;
            return true;
        } break;
    }
    return false;
}

bool TokenType::fromString(Value* v, const std::string& s)
{
    assert(v);
    if(s == "ID")
    {
        *v = ID;
        return true;
    }
    if(s == "INTEGER")
    {
        *v = INTEGER;
        return true;
    }
    if(s == "FLOAT")
    {
        *v = FLOAT;
        return true;
    }
    if(s == "QMARK")
    {
        *v = QMARK;
        return true;
    }
    if(s == "COLON")
    {
        *v = COLON;
        return true;
    }
    if(s == "ASSIGN")
    {
        *v = ASSIGN;
        return true;
    }
    if(s == "PLUS_ASSIGN")
    {
        *v = PLUS_ASSIGN;
        return true;
    }
    if(s == "MINUS_ASSIGN")
    {
        *v = MINUS_ASSIGN;
        return true;
    }
    if(s == "MULTIPLY_ASSIGN")
    {
        *v = MULTIPLY_ASSIGN;
        return true;
    }
    if(s == "DIVIDE_ASSIGN")
    {
        *v = DIVIDE_ASSIGN;
        return true;
    }
    if(s == "MOD_ASSIGN")
    {
        *v = MOD_ASSIGN;
        return true;
    }
    if(s == "INC")
    {
        *v = INC;
        return true;
    }
    if(s == "DEC")
    {
        *v = DEC;
        return true;
    }
    if(s == "OR")
    {
        *v = OR;
        return true;
    }
    if(s == "AND")
    {
        *v = AND;
        return true;
    }
    if(s == "LT")
    {
        *v = LT;
        return true;
    }
    if(s == "GT")
    {
        *v = GT;
        return true;
    }
    if(s == "LE")
    {
        *v = LE;
        return true;
    }
    if(s == "GE")
    {
        *v = GE;
        return true;
    }
    if(s == "EQ")
    {
        *v = EQ;
        return true;
    }
    if(s == "NE")
    {
        *v = NE;
        return true;
    }
    if(s == "NOT")
    {
        *v = NOT;
        return true;
    }
    if(s == "PLUS")
    {
        *v = PLUS;
        return true;
    }
    if(s == "MINUS")
    {
        *v = MINUS;
        return true;
    }
    if(s == "MULTIPLY")
    {
        *v = MULTIPLY;
        return true;
    }
    if(s == "DIVIDE")
    {
        *v = DIVIDE;
        return true;
    }
    if(s == "MOD")
    {
        *v = MOD;
        return true;
    }
    if(s == "POWER")
    {
        *v = POWER;
        return true;
    }
    if(s == "LPAR")
    {
        *v = LPAR;
        return true;
    }
    if(s == "RPAR")
    {
        *v = RPAR;
        return true;
    }
    if(s == "EOS")
    {
        *v = EOS;
        return true;
    }
    if(s == "ERROR")
    {
        *v = ERROR;
        return true;
    }
    return false;
}

int TokenType::toInt(Value v)
{
    return v;
}

std::string TokenType::toString(Value v)
{
    switch(v) {
        case ID: return "ID";
        case INTEGER: return "INTEGER";
        case FLOAT: return "FLOAT";
        case QMARK: return "QMARK";
        case COLON: return "COLON";
        case ASSIGN: return "ASSIGN";
        case PLUS_ASSIGN: return "PLUS_ASSIGN";
        case MINUS_ASSIGN: return "MINUS_ASSIGN";
        case MULTIPLY_ASSIGN: return "MULTIPLY_ASSIGN";
        case DIVIDE_ASSIGN: return "DIVIDE_ASSIGN";
        case MOD_ASSIGN: return "MOD_ASSIGN";
        case INC: return "INC";
        case DEC: return "DEC";
        case OR: return "OR";
        case AND: return "AND";
        case LT: return "LT";
        case GT: return "GT";
        case LE: return "LE";
        case GE: return "GE";
        case EQ: return "EQ";
        case NE: return "NE";
        case NOT: return "NOT";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case MOD: return "MOD";
        case POWER: return "POWER";
        case LPAR: return "LPAR";
        case RPAR: return "RPAR";
        case EOS: return "EOS";
        case ERROR: return "ERROR";
    }
    assert(0);
    return "";
}
    
} // close namespace hulang
