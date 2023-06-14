#include "parser.h"
#include <unordered_set>

unordered_set<string> vars = {}; map<string, bool> one; map<string, Token> two;

namespace P {
	bool pb = false; LexItem pt;

	static LexItem gettok(istream& in, int& line) {
		if( pb ) {pb = false; return pt;}
		return getNextToken(in, line);
	}

	static void pushtok(LexItem & t) {
		if( pb ) {abort();}
		pb = true; pt = t;	
	}

}
static int ec = 0;

int ErrCount(){return ec;}

void pe(int l, string message){
	string a =  ". Line # "; ++ec;
	cout << ec << a << l << ": " << message << endl;
}

bool WritelnStmt(istream& in, int& line) {
	LexItem item;
	item = P::gettok(in, line);
  if(item != RPAREN ) {pe(line, "Missing Right Parenthesis of Writeln Statement");return false;}
  item = P::gettok(in, line);
	if( item != LPAREN ) {pe(line, "Missing Left Parenthesis of Writeln Statement");return false;}
	bool expression = ExprList(in, line);
	if( !expression ) {pe(line, "Missing expression list after Print");return false;}
  bool r = true;
	return r;
}


bool ExprList(std::istream& in, int& line) {
    bool st = false;
    while (true) {
        st = Expr(in, line);
        if (!st) {pe(line, "Missing Expression");return false;}

        LexItem tok = P::gettok(in, line);
        if (tok.GetToken() == ERR) {
            pe(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        } else if (tok == COMMA) {
            continue;
        } else {
            P::pushtok(tok);
            return true;
        }
    }
}

bool Expr(std::istream& in, int& line) {
    bool st = false;
    st = RelExpr(in, line);
    if (!st) {return false;}
    LexItem tok = P::gettok(in, line);

    switch (tok.GetToken()) {
        case SEQ:
        case NEQ:
            st = RelExpr(in, line);
            if (!st) {pe(line, "Missing Relational Expression");return false;}
            break;
        default:
            P::pushtok(tok);
            break;
    }
    return true;
}

bool RelExpr(std::istream& in, int& line) {
    bool st = false;st = AddExpr(in, line);
    if (!st) {return false;}
    LexItem t = P::gettok(in, line);
    switch (t.GetToken()) {
        case SLTHAN:
        case SGTHAN:
        case NLTHAN:
        case NGTHAN:
            st = AddExpr(in, line);
            if (!st) {pe(line, "Missing operand after operator");return false;}
            break;
        default:
            P::pushtok(t);
            break;
    }
    return true;
}

bool AddExpr(std::istream& in, int& line) {
    bool st = false;
    st = MultExpr(in, line);
    if (!st) {return false;}
    LexItem t;
    while (true) {
        t = P::gettok(in, line);
        switch (t.GetToken()) {
            case PLUS:
            case MINUS:
            case CAT:
                st = MultExpr(in, line);
                if (!st) {pe(line, "Missing operand after operator");return false;}
                break;
            default:
                P::pushtok(t);
                return true;
        }
    }
}

bool MultExpr(std::istream& in, int& line) {
    bool st = false;
    st = ExponExpr(in, line);
    if (!st) {return false;}
    LexItem t;
    while (true) {
        t = P::gettok(in, line);
        switch (t.GetToken()) {
            case MULT:
            case DIV:
            case SREPEAT:
                st = ExponExpr(in, line);
                if (!st) {pe(line, "Missing Expon Expression");return false;}
                break;
            default:
                P::pushtok(t);
                return true;
        }
    }
}

bool ExponExpr(istream& in, int& line) {
    bool st = false;
    st = UnaryExpr(in, line);
    if (!st) {return false;}
    LexItem t;
    do {
        t = P::gettok(in, line);
        if (t.GetToken() == EXPONENT) {
            st = UnaryExpr(in, line);
            if (!st) {pe(line, "Missing Unary Expression");return false;
            }
        }
        else {
            P::pushtok(t);
            break;
        }
    } while (true);

    return true;
}


bool UnaryExpr(istream& in, int& line) {
LexItem t = P::gettok(in, line);
int sym = 1;
if(t.GetToken() == MINUS){sym = -1;}
else if (t.GetToken() != PLUS) {P::pushtok(t);}
bool st = false;
st = PrimaryExpr(in, line, sym);
if(!st){return false;}
return true;
}

bool PrimaryExpr(istream& in, int& line, int sign) {
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok == IDENT || tok == SIDENT || tok == NIDENT ||  tok == ICONST || tok == RCONST || tok == SCONST){
    if(tok == SIDENT || tok == NIDENT){
      if (vars.find(token.GetLexeme()) == vars.end()){pe(line, "Using Undefined Variable");return false;}
    }
    return true;
  }
  if(tok != LPAREN){pe(line, "Missing LPAREN Expression");return false;}
  bool st = Expr(in, line);
  if(!st){pe(line, "Missing Expression"); return false;}
  token = P::gettok(in, line);
  tok = token.GetToken();
  if(tok != RPAREN){pe(line, "Missing RPAREN Expression");return false;}
  return true;
}

string last = "";

bool Var(istream& in, int& line) {
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok == NIDENT || tok == SIDENT){last = token.GetLexeme();return true;}
  pe(line, "Missing NIDENT or SIDENT"); return false;
}


bool AssignmentStmt(istream& in, int& line) {
  bool st = Var(in, line);
  if(!st){pe(line, "Missing Statement");return false;}
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok != ASSOP){pe(line, "Missing assignment operator");return false;}
  st = Expr(in, line);
	if(!st){pe(line, "Missing Expression in Assignment Statement"); return false;}
 vars.insert(last);
  return true;
}

bool IfStmt(istream& in, int& line) {
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok != LPAREN){pe(line, "Missing LPAREN"); return false;}
  bool status = Expr(in, line);
  if(!status){pe(line, "Missing Expression");  return false;}
  token = P::gettok(in, line);tok = token.GetToken();
  if(token != RPAREN){pe(line, "Missing RPAREN"); return false;}
  token = P::gettok(in, line);tok = token.GetToken();
  if(tok != LBRACES){pe(line, "Missing LBRACES"); return false;}
  status = StmtList(in, line);
  if(!status){pe(line, "Missing statement list");return false;}
  token = P::gettok(in, line);tok = token.GetToken();
  if(tok != RBRACES){pe(line, "Missing");return false;}
  token = P::gettok(in, line);tok = token.GetToken();
  if(tok == ELSE){token = P::gettok(in, line);tok = token.GetToken();
    if(tok != LBRACES){pe(line, "Missing LBRACES"); return false;}
    status = StmtList(in, line);
    if(!status){pe(line, "Missing statement list");return false;}
    token = P::gettok(in, line);tok = token.GetToken();
    if(tok != RBRACES){pe(line, "Missing RBRACES"); return false;}
  }else{P::pushtok(token);}
  return true;
}

bool WriteLnStmt(istream& in, int& line) {
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok != LPAREN){pe(line, "Missing Left Parenthesis of Writeln Statement");return false;}
  bool st = ExprList(in, line);
  if(!st){pe(line, "Missing Expression List");return false;}
  token = P::gettok(in, line);
  tok = token.GetToken();
  if(tok != RPAREN){pe(line, "Missing RPAREN Expression");return false;}
  return true;
}

bool Stmt(istream& in, int& line) {
  LexItem token = P::gettok(in, line);
  Token tok = token.GetToken();
  if(tok == WRITELN){
    if(WriteLnStmt(in, line)){return true;}
    pe(line, "Incorrect Writeln Statement.");
		return false;
  }else if(tok == IF){return IfStmt(in, line);}
  else{P::pushtok(token);
    if(!AssignmentStmt(in, line)){pe(line, "Incorrect Assignment Statement.");return false;}
    return true;
  }
  return true;
}

bool StmtList(istream& in, int& line) {
  bool a = false;
  while (true) {LexItem token = P::gettok(in, line);
    P::pushtok(token);
    if (token.GetToken() != IF && token.GetToken() != WRITELN && token.GetToken() != SIDENT && token.GetToken() != NIDENT) {
      if (!a) {pe(line, "Missing statement");
        return false;
      }
      return true;
    }
    bool st = Stmt(in, line);
    if (!st) {return false;}
    a = true;
    token = P::gettok(in, line);
    if (token.GetToken() != SEMICOL) {pe(line, "Missing semicolon");
      return false;
    }
    token = P::gettok(in, line);
    if (token.GetToken() == DONE) {
      return true;
    }
    P::pushtok(token);
  }
}

bool Prog(istream& in, int& line) {
  bool st = StmtList(in, line);
  if (!st) {
    pe(line, "Missing program");
    return false;
  }
  LexItem tok = P::gettok(in, line);
  if (tok.GetToken() != DONE) {
    pe(line, "Missing 'done' at the end of program");
    return false;
  }
  cout << "(DONE)" << endl;
  return true;
}