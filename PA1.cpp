#include <iostream>
#include "lex.h"
#include <fstream>
#include <set>
#include <unordered_set>
#include <string>
#include <regex>
#include <map>
using namespace std;

char a = '-';
char b = '\n';
char c = '_';
char d = '.';
ostream& operator<<(ostream& out, const LexItem& tok);

LexItem id_or_kw(const string& lexeme, int linenum) {
  if (lexeme == "IF") {
    return LexItem(IF, lexeme, linenum);
  } else if (lexeme == "WRITELN") {
    return LexItem(WRITELN, lexeme, linenum);
  } else if (lexeme == "ELSE") {
    return LexItem(ELSE, lexeme, linenum);
  } else {
    return LexItem(IDENT, lexeme, linenum);
  }
}


string find(string i) {
    regex identPattern("^(\\$|\\@)[a-zA-Z_][a-zA-Z0-9_]*$");
    if (regex_match(i, identPattern)) {
        switch (i.front()) {
            case '$':
                return "numeric";
            case '@':
                return "string";
        }
    }
    return "";
}

//#3 bool
bool number(const string& num) {return all_of(num.begin(), num.end(), [](char x) { return isdigit(x); });}

bool space(string x) {
    for (char i : x) {
        if (!isspace(i)) {return false;}
    }
    return true;
}

bool rconst(const string& x) {
  bool point= false, num = false, nonum =false;
 
  for (auto i = x.begin(); i != x.end(); ++i) {
    if (*i == d) {
      if (point) if(nonum){return false;}
      point = true;
    } else if (isdigit(*i)) {num = true;} 
      else {return false;}
  }

  return num;
}

bool sconst(const string& y) {
  if (y.size() < 2 || y.front() != '\'' || y.back() != '\'') {return false;}
  bool accept = true;
  for (size_t x = 1; accept && x < y.size() - 1; ++x) {
    if (y[x] == '\'') {
      accept = (x != y.size() - 2 && y[x+1] == '\'');
      ++x;
    } else {accept = (y[x] >= 32 && y[x] <= 126);}
  }

  return accept;
}

bool comment(const string& comment) {
  if (comment.size() < 2 || comment.front() != '#') {return false;}

  for (auto i = comment.begin() + 1; i != comment.end(); ++i) {
    if (!isalnum(*i) && *i != c) {return false;}
  }
  return true;
}

int count(const string& in) {
  int num = 0;
  string t;
  istringstream iss(in);
  while (iss >> t) {
    num++;
  }
  return num;
}

bool ident(string i) {
    if (i.empty() || (!isalpha(i.front()) && i.front() != c)) {return false;}
    if (any_of(i.begin() + 1, i.end(), [](char x) { return !isalnum(x) && x != c; })) {return false;}
    return true;
}

map<Token, string> one = {

{CAT, "CAT"},{MULT,"MULT"},{ASSOP, "ASSOP"},{LPAREN, "LPAREN"},{ICONST, "ICONST"},{SEMICOL, "SEMICOL"},{LBRACES,"LBRACES"},{SIDENT, "SIDENT"},{SREPEAT, "SREPEAT"},{WRITELN, "WRITELN"},{RBRACES, "RBRACES"},{NIDENT, "NIDENT"},{NLTHAN, "NLTHAN"},{IF, "IF"},{RCONST, "RCONST"},{ELSE, "ELSE"},{SCONST, "SCONST"},{MINUS, "MINUS"},{NGTHAN, "NGTHAN"},{SLTHAN, "SLTHAN"}, {RPAREN, "RPAREN"},{EXPONENT, "EXPONENT"},{COMMA, "COMMA"},{SGTHAN, "SGTHAN"},{SEQ, "SEQ"},{ERR, "ERR"},{PLUS, "PLUS"},{NEQ, "NEQ"},
{DIV, "DIV"},{IDENT, "IDENT"},{DONE, "DONE"}};

ostream& operator<<(std::ostream& out, const LexItem& token) {
    Token t = token.GetToken();
    string fp = "(";
    string sp = ")";
    string errorinl = "Error in line ";
    string emp = " ";
    switch (t) {
        case ERR:
            out << errorinl << token.GetLinenum() << emp << fp  << token.GetLexeme() << sp;
            break;
        case SCONST:
            out << one[t] << fp << token.GetLexeme().substr(1, token.GetLexeme().length() - 2) << sp;
            break;
        case RCONST:
      out << one[t] << fp << token.GetLexeme() << sp;
            break;
        case IDENT:
      out << one[t] << fp << token.GetLexeme() << sp;
            break;
        case NIDENT:
      out << one[t] << fp << token.GetLexeme() << sp;
            break;
      case ICONST:
            out << one[t] << fp << token.GetLexeme() << sp;
            break;
      case SIDENT:
      out << one[t] << fp << token.GetLexeme() << sp;
            break;
        
        default:
            out << one[t];
            break;
    }

    return out;
}

map<char, Token> op = {
{'-', MINUS},{'+', PLUS},{'}', RBRACES},{',', COMMA},{'>', NGTHAN},{'*', MULT},{')', RPAREN}, {'^', EXPONENT},{';', SEMICOL},{'(', LPAREN},{'/', DIV},{'.', CAT},{'<', NLTHAN},{'{',LBRACES},{'=', ASSOP}};

  unordered_set<char> l = {'+', '-', '*', '^', '/', '(', ')', '=', '{', '}', '<', '>', '\'', ';', ',', '&', '$', '@', EOF};

ifstream file;

LexItem getNextToken (istream& in, int& lnum){ 
    char character;
    bool comment = false;bool sconst = false;bool nums = true;bool dec = false;
    stringstream buf;
    
    while (in.get(character)) {
      if(character == EOF) {return LexItem(DONE, "", lnum);}
      if(comment){ if(character == b) {comment = false;lnum++;}continue;}
       if(character == b){if(sconst){return LexItem(ERR, buf.str(), lnum);}lnum++;}
      if(character == '#' && !sconst){comment = true;continue;}
      if(!sconst && space(string(1, character))){continue;}
        
      buf << character;
      string w = buf.str();
      if(character == '&'){return LexItem(ERR, w, lnum);}
      if(character == '\''){if(sconst){return LexItem(SCONST, w, lnum);}sconst= true;}

      if(sconst){continue;}
      if(nums){
        if(character == d){
          if(dec){return LexItem(ERR, w, lnum);}
          dec = true;
        }
      }
      if(!(character == d || number(string(1, character)))){nums = false;}
      char after = in.peek();
      if(character == '-'){
        if(after != 'e' && after != 'l' && after != 'g' && after != 'E' && after != 'L' && after != 'G' ){return LexItem(MINUS, "-", lnum);}
      }
      bool h = space(string(1, after)) || l.find(after) != l.end();
      if(h || (nums && (after == c || !(after == d || number(string(1, after)))))){
        if(number(w)){return LexItem(ICONST, w, lnum);}
        else if(rconst(w)){return LexItem(RCONST, w, lnum);}
        string one = find(w);
        string two = find(w);
        if(one == "numeric"){return LexItem(NIDENT, w, lnum);}
        else if(two == "string"){return LexItem(SIDENT, w, lnum);}
        if(w == "if"){return LexItem(IF, w, lnum);}
        else if(w == "else"){return LexItem(ELSE, w, lnum);}
        else if(w == "writeln"){return LexItem(WRITELN, w, lnum);}
        if(ident(w)){return LexItem(IDENT, w, lnum); }
        if(w == "-eq" || w == "-Eq" || w == "-eQ" || w == "-EQ"){return LexItem(SEQ, w, lnum);}
        else if(w == "-lt" || w == "-Lt" || w == "-lT" || w == "-LT"){return LexItem(SLTHAN, w, lnum);}
        else if(w == "-gt" || w == "-Gt" || w == "-gT" || w == "-GT"){return LexItem(SGTHAN, w, lnum);}
      }
      if (op.find(character) != op.end()) {
        if((character != a && character != '*' && character != '=') || h){
          if(character == '=' && after == '='){
            in.get(character);
            return LexItem(NEQ, "==", lnum);
          }
          if(character == '*' && after == '*'){
            in.get(character);
            return LexItem(SREPEAT, "**", lnum);
          }
          if(character == '.' && (w.length()>1 && number(string(1, w[w.length()-2])))){continue;}
          return LexItem(op[character], w, lnum);
        }
        if(character == '*'){return LexItem(op[character], w, lnum);}
      }
    }
     return LexItem(DONE, "", lnum);
   }

int main(int argc, char *argv[]) {
    if (argc < 2) {cout << "NO SPECIFIED INPUT FILE." << endl;
    return 5;
  }

  string f = argv[1];
  ifstream file(f);
  if (!file.is_open()) {
    cout << "CANNOT OPEN THE FILE " << f << endl;
    return 0;
  }
  vector<string> flag;
  bool v = false;
  bool ident = false;
  bool sconst = false;
  bool nconst = false;
  
  for (int i = 2; i < argc; i++) {
    string arg = string(argv[i]);
    if (arg[0] == '-') {flag.push_back(arg);
      if (arg == "-v") {v = true;}
       else if (arg == "-ident") {ident = true;}
       else if (arg == "-sconst") {sconst = true;}
       else if (arg == "-nconst") {nconst = true;}
       else {cerr << "UNRECOGNIZED FLAG {" << arg << "}" << endl;
        return 1;
      }
    }
    else {cerr << "ONLY ONE FILE NAME IS ALLOWED." << endl;
      return 1;
    }
  }

  if (file.peek() == EOF) {
    cout << "Lines: 0" << endl;
    cout << "Empty File." << endl;
    return 0;
  }
  set<string> id;
  set<double> nums;
  set<string> words;
  

  int count = 1;
  int tokcount = 1;

  while (true) {
    auto r = getNextToken(file, count);
    if (r.GetToken() == DONE) {break;}
    else if (r.GetToken() == ERR) {cout << r << endl;
      return 0;
    }
    tokcount++;
    switch (r.GetToken()) {
      case ICONST:
      nums.insert(stod(r.GetLexeme()));
        break;
      case NIDENT:
      id.insert(r.GetLexeme());
        break;
      case RCONST:
        nums.insert(stod(r.GetLexeme()));
        break;
      case SCONST:
        words.insert(r.GetLexeme());
        break;
      case SIDENT:
        id.insert(r.GetLexeme());
        break;
      case IDENT:
      id.insert(r.GetLexeme());
        break;
      default:
        break;
    }
    if (v) {
      cout << r << endl;
    }
  }

  count--;
string liness = "Lines: ";
string totalTokens = "Total Tokens: ";
string identiifiers = "Identifiers: ";
string nummbberrs = "Numbers: ";
string stringgsss = "Strings: ";
  cout << endl;
  cout << liness << count << endl;
  cout << totalTokens << tokcount -1  << endl;
  cout << identiifiers << id.size() << endl;
  cout << nummbberrs << nums.size() << endl;
  cout << stringgsss << words.size() << endl;
  
  if (ident) {
    cout << "IDENTIFIERS:" << endl;
    bool one = true;
    for (auto& x : id) {
      if (one) {
        cout << x;
        one = false;
      }
      else {
        cout << ", " << x;
      }
    }
    cout << endl;
  }
  if (nconst) {
    string nubr = "NUMBERS:";
    cout << nubr << endl;
    for (auto& y : nums) {
      cout << y << endl;
    }
  }
  if (sconst) {
    string stng = "STRINGS:";
    cout << stng << endl;
    for (auto& z : words) {
      cout << z << endl;
    }
  }

}