#include "parserInt.h"

map<string, bool> mahrez; map<string, Token> haaland; map<string, Value> sterling; queue <Value> * maguire;

bool hi = false; bool error = false;

namespace Parser {
	bool lewis = false;
	LexItem	debruyne;
	static LexItem GetNextToken(istream& in, int& line) {if( lewis ) {lewis = false;return debruyne;}return getNextToken(in, line);}
	static void PushBackToken(LexItem & t) {if( lewis ) {abort();}lewis = true; debruyne = t;	}}

static int walker = 0;
int ErrCount(){return walker;}

void ParseError(int l, string m){++walker;cout << walker << ". Line # " << l << ": " << m << endl;}

bool IdentList(istream& in, int& line);

bool Prog(istream& in, int& line){bool foden;LexItem tahmim = Parser::GetNextToken(in, line);
	if(tahmim.GetToken() == DONE && tahmim.GetLinenum() <= 1){ParseError(line, "Empty File");return true;}
	Parser::PushBackToken(tahmim); foden = StmtList(in, line); 		
	if(!foden || error) {ParseError(line, "Missing Program"); return false;}
	else 
		return true;
}
bool StmtList(istream& in, int& line){
	bool striker; LexItem st;striker = Stmt(in, line);
	while(striker ){st = Parser::GetNextToken(in, line);
		if(st == DONE){cout << endl;cout << "(" << "DONE" << ")" << endl;Parser::PushBackToken(st);return true;}
		else if(st == RBRACES){Parser::PushBackToken(st);return true;}
		if(st != SEMICOL){ParseError(line, "Missing semicolon at end of Statement."); return false;}
		striker = Stmt(in, line);}		
	st = Parser::GetNextToken(in, line);
	if(st == ELSE ){ParseError(line, "Missing right brace.");return false;}
	else if(st == RBRACES){Parser::PushBackToken(st);return true;}
	else {ParseError(line, "Syntactic error in Program Body.");return false;}
}

bool Stmt(istream& in, int& line){
  bool striker=false; LexItem defender = Parser::GetNextToken(in, line);
	switch( defender.GetToken() ) {case NIDENT: case SIDENT:  
		Parser::PushBackToken(defender);
		striker = AssignStmt(in, line);
		if(!striker){ParseError(line, "Incorrect Assignment Statement.");return striker;}
		break;
  case IF:  
		striker = IfStmt(in, line);
		if(!striker){ParseError(line, "Incorrect If-Statement."); error = true; return striker;}
		break;
	case WRITELN:
		striker = WritelnStmt(in, line);
		if(!striker){ParseError(line, "Incorrect Writeln Statement.");return striker;}
		break;
  case IDENT:
		ParseError(line, "Invalid variable name");
		Parser::PushBackToken(defender);
		return false;
		break;
	case ELSE:
		Parser::PushBackToken(defender);
		return false;
		break;
	default:
		Parser::PushBackToken(defender);
		return true;
	}
	return striker;
}


bool WritelnStmt(istream& in, int& line) {
	LexItem rodri; maguire = new queue<Value>;rodri = Parser::GetNextToken(in, line);
	if( rodri != LPAREN ) {ParseError(line, "Missing Left Parenthesis of Writeln Statement");return false;}
	bool ake = ExprList(in, line);
	if( !ake ) {ParseError(line, "Missing expression list after Print");return false;}
	rodri = Parser::GetNextToken(in, line);
	if(rodri != RPAREN ) {ParseError(line, "Missing Right Parenthesis of Writeln Statement"); return false;}
  if(!hi){
    while (!(*maguire).empty()){
      Value edison = (*maguire).front();if(edison.IsInt()){cout << (int)floor(edison.GetInt()) << ".0";}
      else if(edison.IsString()){cout << edison.GetString();}
      else if(edison.IsReal()){
        if(edison.GetReal() == 50){cout << "50";}
        else{cout << edison.GetReal() << ((floor(edison.GetReal())==edison.GetReal())?".0":"");}
      }else{cout << (*maguire).front();}
      maguire->pop();
    }
    cout << endl;
  }
	return true;
}

bool IfStmt(istream& in, int& line) {
	bool sancho = false, striker ; LexItem tim;tim = Parser::GetNextToken(in, line);
	if( tim != LPAREN ) {ParseError(line, "Missing Left Parenthesis of If condition"); return false;}
	Value rage; sancho = Expr(in, line, rage);
	if( !sancho ) {ParseError(line, "Missing if statement Logic Expression");return false;}
  if(!rage.IsBool()){ParseError(line, "Illegal Type for If statement condition."); return false;}
	tim = Parser::GetNextToken(in, line);
	if(tim != RPAREN ) {ParseError(line, "Missing Right Parenthesis of If condition");return false;}
  hi = !rage.GetBool(); tim = Parser::GetNextToken(in, line);
	if(tim != LBRACES){ParseError(line, "If Statement Syntax Error: Missing left brace"); return false;}
	striker = StmtList(in, line);
	if(!striker){ParseError(line, "Missing Statement for If-Stmt Clause"); return false;}
	tim = Parser::GetNextToken(in, line);
	if( tim != RBRACES){ParseError(line, "If Statement Syntax Error: Missing right brace.");return false;}
	tim = Parser::GetNextToken(in, line);
	if( tim == ELSE ) {tim = Parser::GetNextToken(in, line);
		if(tim != LBRACES){ParseError(line, "If Statement Syntax Error: Missing left brace"); return false;}
    hi = rage.GetBool();striker = StmtList(in, line);
		if(!striker){ParseError(line, "Missing Statement for Else-Clause");return false;}
		tim = Parser::GetNextToken(in, line);
		if( tim != RBRACES){Parser::PushBackToken(tim);ParseError(line, "If Statement Syntax Error: Missing right brace.");return false;
		}
	}
	else{hi = false; Parser::PushBackToken(tim);return true;}
  hi = false; return true;
}

bool Var(istream& in, int& line, LexItem & city){
	string guardiola; LexItem ray = Parser::GetNextToken(in, line);
	if (ray == NIDENT || ray == SIDENT){guardiola = ray.GetLexeme();
			mahrez[guardiola] = true; haaland[guardiola] = ray.GetToken();
    city = ray; return true;
	}
	else if(ray.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	return false;
}

bool AssignStmt(istream& in, int& line) {
	bool varstriker = false, striker = false; LexItem time; LexItem city;varstriker = Var(in, line, city); Value bye;
	if (varstriker){time = Parser::GetNextToken(in, line);
		if (time == ASSOP){striker = Expr(in, line, bye);
			if(!striker) {ParseError(line, "Missing Expression in Assignment Statement"); return striker;}}
		else if(time.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << time.GetLexeme() << ")" << endl; return false;}
		else {ParseError(line, "Missing Assignment Operator"); return false;}
	}
	else {ParseError(line, "Missing Left-Hand Side Variable in Assignment statement"); return false;}
  if(haaland[city.GetLexeme()] == NIDENT && !bye.IsInt() && !bye.IsReal()){ParseError(line, "Invalid assignment statement conversion of a string value to a double variable."); return false;}
  if(bye.IsBool()){ParseError(line, "Illegal Assignment of a boolean value to a numeric or string variable."); return false;}
  if(!hi){sterling[city.GetLexeme()] = bye;}
	return striker;	}
bool ExprList(istream& in, int& line) {
	bool striker = false;Value fire;striker = Expr(in, line, fire);
	if(!striker){ParseError(line, "Missing Expression");return false;}
	LexItem game = Parser::GetNextToken(in, line); maguire->push(fire);
	if (game == COMMA) {striker = ExprList(in, line);}
	else if(game.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << game.GetLexeme() << ")" << endl;return false;}
	else{Parser::PushBackToken(game);return true;}
	return striker;}

bool Expr(istream& in, int& line, Value & value) {
	LexItem man; Value div;bool wonka = RelExpr(in, line, div);
	if( !wonka ) {return false;}
	man = Parser::GetNextToken(in, line);
	if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}
	if ( man == SEQ || man == NEQ ) {Value tracey; wonka = RelExpr(in, line, tracey);
		if( !wonka ) {ParseError(line, "Missing operand after operator");return false;}
    if(man == NEQ){div = div == tracey;}
    else{div = div.SEqual(tracey);}
    if(div.IsErr()){ParseError(line, "Illegal operand type for the operation."); return false;}
		man = Parser::GetNextToken(in, line);
		if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}		
	}
	Parser::PushBackToken(man); value = div; return true;
}

bool RelExpr(istream& in, int& line, Value & value) {
	LexItem man; Value race; bool wonka = AddExpr(in, line, race);
	if( !wonka ) {return false;}
	man = Parser::GetNextToken(in, line);
	if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}
	if ( man == NGTHAN || man == NLTHAN || man == SGTHAN || man == SLTHAN ) {Value tracey; wonka = AddExpr(in, line, tracey);
		if( !wonka ) {ParseError(line, "Missing operand after operator"); return false;}
		if(man == NGTHAN){race = race > tracey;}
    else if(man == NLTHAN){race = race < tracey;}
    else if(man == SLTHAN){race = race.SLthan(tracey);}
    else if(man == SGTHAN){race = race.SGthan(tracey);}
    if(race.IsErr()){ParseError(line, "Illegal operand type for the operation."); return false;}
		man = Parser::GetNextToken(in, line);
		if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}		
	}
	Parser::PushBackToken(man); value = race; return true;
}

bool AddExpr(istream& in, int& line, Value & value) {
	Value cate;bool wonka = MultExpr(in, line, cate);LexItem man;
	if( !wonka ) {return false;}
	man = Parser::GetNextToken(in, line);
	if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;} 
	while ( man == MINUS || man == PLUS || man == CAT) {
    Value tracey; wonka = MultExpr(in, line, tracey);
		if( !wonka ) {ParseError(line, "Missing operand after operator"); return false;}
		cate = (man==PLUS)?(cate+tracey):((man==MINUS)?(cate-tracey):(cate.Catenate(tracey)));
		if(cate.IsErr()){ParseError(line, "Illegal operand type for the operation."); return false;}
    man = Parser::GetNextToken(in, line);
		if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}		
	}
	Parser::PushBackToken(man); value = cate; return true;
}

bool MultExpr(istream& in, int& line, Value & value) {
	Value lil; bool wonka = ExponExpr(in, line, lil);LexItem man;
	if( !wonka ) {return false;}
	man	= Parser::GetNextToken(in, line);
	if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}
	while ( man == DIV || man == MULT  || man == SREPEAT){
    Value tracey; wonka = ExponExpr(in, line, tracey);
		if( !wonka ) {ParseError(line, "Missing operand after operator");return false;}
    if(man == MULT){lil = lil*tracey;}
    else if(man == DIV){lil = lil/tracey;}
    else{lil = lil.Repeat(tracey);}
    if(lil.IsErr()){
      ParseError(line, "Illegal operand type for the operation.");return false;}
		man	= Parser::GetNextToken(in, line);
		if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl;return false;}
	}
	Parser::PushBackToken(man); value = lil; return true;
}

bool ExponExpr(istream& in, int& line, Value & value){
	bool striker; Value p;
	striker = UnaryExpr(in, line, p);
	if( !striker ) {return false;}
	LexItem man = Parser::GetNextToken(in, line);
	if (man == EXPONENT){
    Value tracey; striker = ExponExpr(in, line, tracey);
		if( !striker ) {
			ParseError(line, "Missing operand after operator");return false;
		}
		p = p^tracey; man	= Parser::GetNextToken(in, line);
		if(man.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << man.GetLexeme() << ")" << endl;return false;
		}
	}
	else if(man.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern"); cout << "(" << man.GetLexeme() << ")" << endl; return false;
	}
	Parser::PushBackToken(man); value = p; return true;
}
bool UnaryExpr(istream& in, int& line, Value & value){
	LexItem f = Parser::GetNextToken(in, line); bool striker; int chara = 0;
	if(f == MINUS ){chara = -1;}
	else if(f == PLUS){chara = 1;}
	else
	Parser::PushBackToken(f);Value rec;
	striker = PrimaryExpr(in, line, chara, rec);
  if((f == MINUS || f == PLUS) && striker && !rec.IsInt() && !rec.IsReal()){ParseError(line, "Illegal Operand Type for Sign Operator");return false;}
  value = rec; return striker;
}

bool PrimaryExpr(istream& in, int& line, int chara, Value & value) {
	LexItem man = Parser::GetNextToken(in, line);
	if(chara == 0){chara = 1;}
	if( man == NIDENT || man == SIDENT) {string lexeme = man.GetLexeme();
		if (!(mahrez.find(lexeme)->second)){ParseError(line, "Using Undefined Variable"); return false;	}
    if(man == NIDENT){value = sterling[lexeme]*Value(chara);}
    else{value = sterling[lexeme];}
		return true;
	}
	else if( man == ICONST ){value = Value(chara*stoi(man.GetLexeme())); return true;}
  else if( man == RCONST ) {value = Value(chara*stod(man.GetLexeme())); return true;}
	else if( man == SCONST ){value = Value(man.GetLexeme()); return true;}
	else if( man == LPAREN ) {Value will; bool deep = Expr(in, line, will);
		if( !deep ) {ParseError(line, "Missing expression after Left Parenthesis"); return false;}
		if( Parser::GetNextToken(in, line) == RPAREN ){if(chara == -1){will = will*-1;}
      value = will;return deep;}
		else {Parser::PushBackToken(man);ParseError(line, "Missing right Parenthesis after expression");return false;}
	}
	else if(man.GetToken() == ERR){ParseError(line, "Unrecognized Input Pattern");cout << "(" << man.GetLexeme() << ")" << endl; return false;}
	return false;
}