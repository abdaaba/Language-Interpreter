#include "val.h"

double convert(const Value& val);
  string g = "Invalid conversion from string to double.";
Value Value::operator+(const Value& abe) const {
    if( abe.IsErr() || this->IsErr()){return Value();}
    try{double soc = convert(*this); double foo = convert(abe); return Value(soc+foo); }
    catch(const std::exception& e){if(string(e.what()) == g){cout << e.what() << endl;}return Value();}
}
Value Value::operator-(const Value& hi) const {
    if(this->IsErr() || hi.IsErr()){return Value();}
    try{double soc = convert(*this); double foo = convert(hi); return Value(soc-foo); }
    catch(const std::exception& exp){if(string(exp.what()) == g){cout << exp.what() << endl;}return Value();}
}
Value Value::operator*(const Value& lime) const {
    if(lime.IsErr() || this->IsErr() ){return Value();}
    try{double soc = convert(*this); double foo = convert(op); return Value(soc*foo); }
    catch(const std::exception& exp){if(string(e.what()) == g){cout << e.what() << endl;}return Value();}
}
Value Value::operator/(const Value& dime) const {
    if(this->IsErr() || dime.IsErr()){return Value();}
    try{ double soc = convert(*this); double foo = convert(dime);
      if(foo == 0){return Value();}
      return Value(soc/foo); }
    catch(const std::exception& exp){if(string(exp.what()) == g){cout << exp.what() << endl;}return Value();}
}
Value Value::operator==(const Value& si) const {
    if(this->IsErr() || si.IsErr()){return Value();}
    try{double soc = convert(*this); double foo = convert(si); return Value(soc==foo); }
    catch(const std::exception& exp){if(string(exp.what()) == g){cout << exp.what() << endl;}return Value();}
}
Value Value::operator>(const Value& wii) const {
    if(this->IsErr() || wii.IsErr()){return Value();}
    try{double soc = convert(*this); double foo = convert(wii); return Value(soc>foo); }
    catch(const std::exception& exp){if(string(exp.what()) == g){cout << exp.what() << endl;}return Value();}
}
Value Value::operator<(const Value& lok) const {
    if(this->IsErr() || lok.IsErr()){return Value();}
    try{double soc = convert(*this); double foo = convert(lok); return Value(soc<foo); }
    catch(const std::exception& exp){if(string(exp.what()) == g){cout << exp.what() << endl;}return Value();}
}
Value Value::operator^(const Value& que) const {
    try{if((!que.IsInt() && !que.IsReal()) || (!(this->IsInt()) && !(this->IsReal()))){return Value();}
      double one = convert(*this); double two = convert(que); return Value(pow(one, two)); }
    catch(const std::exception& e){return Value();}
}

Value Value::Catenate(const Value& them) const {
    stringstream broth;
    if(this->IsReal()){if(floor(this->GetReal()) == this->GetReal()){broth << (int)floor(this->GetReal());}else{broth << this->GetReal();}}
    else if(this->IsErr()){return Value();}
    else if(this->IsString()){broth << this->GetString();}
    else{broth << *this;}
    if(them.IsReal()){if(floor(them.GetReal()) == them.GetReal()){broth << (int)floor(them.GetReal());}else{broth << them.GetReal();}}
    else if(them.IsErr()){return Value();}
    else if(them.IsString()){broth << them.GetString();}
    else{broth << them;}
    return Value(broth.str());
}
Value Value::Repeat(const Value& cate) const {
    stringstream broth;
    if(this->IsReal()){if(floor(this->GetReal()) == this->GetReal()){broth << (int)floor(this->GetReal());}else{broth << this->GetReal();}}
    else if(this->IsErr()){return Value();}
    else if(this->IsString()){broth << this->GetString();}
    else{broth << *this;}
    try{double lee = convert(cate);if(lee == 0){return Value("");}string ign = broth.str();for(; lee>2; lee--){broth << ign;}}
    catch(const std::exception& e){if(string(e.what()) == g){cout << e.what() << endl;}return Value();}
    return Value(broth.str());
}
Value Value::SEqual(const Value& foi) const {
    if (this->IsErr() || foi.IsErr()) {return Value();}
    if (this->IsReal() && foi.IsReal()) {return Value(this->GetReal() < foi.GetReal());}
    stringstream broth1, broth2;
    if (this->IsString()) {broth1 << this->GetString();} 
    else {if(this->IsReal() && floor(this->GetReal()) == this->GetReal()){broth1 << (int)floor(this->GetReal());}
        else{broth1 << *this;}}
    if (foi.IsString()) {broth2 << foi.GetString();} 
    else {if(foi.IsReal() && floor(foi.GetReal()) == foi.GetReal()){broth2 << (int)floor(foi.GetReal());}else{broth2 << foi;}}
    return Value(broth1.str().compare(broth2.str()) == 0);
}
Value Value::SGthan(const Value& xi) const {
    if (xi.IsErr() ||this->IsErr()) {return Value();}
    if (this->IsReal() && xi.IsReal()) {return Value(this->GetReal() < xi.GetReal());}
    stringstream broth1, broth2;
    if (this->IsString()) {broth1 << this->GetString();} 
    else {if(this->IsReal() && floor(this->GetReal()) == this->GetReal()){broth1 << (int)floor(this->GetReal());}else{broth1 << *this;}}
    if (xi.IsString()) {broth2 << xi.GetString();} 
    else {if(xi.IsReal() && floor(xi.GetReal()) == xi.GetReal()){broth2 << (int)floor(xi.GetReal());}else{broth2 << xi;}}
    return Value(broth1.str().compare(broth2.str()) > 0);
}
Value Value::SLthan(const Value& yout) const {
    if (this->IsErr() || yout.IsErr()) {return Value();}
    if (yout.IsReal() && this->IsReal()) {return Value(this->GetReal() < yout.GetReal());}
    stringstream broth1, broth2;
    if (this->IsString()) {broth1 << this->GetString();} 
    else {if(this->IsReal() && floor(this->GetReal()) == this->GetReal()){broth1 << (int)floor(this->GetReal());}else{broth1 << *this;}}
    if (yout.IsString()) {broth2 << yout.GetString();} 
    else {if(yout.IsReal() && floor(yout.GetReal()) == yout.GetReal()){broth2 << (int)floor(yout.GetReal());}else{broth2 << yout;}}
    return Value(broth1.str().compare(broth2.str()) < 0);
}

double convert(const Value& val) {
    if (val.IsInt()){return val.GetInt();}
    else if(val.IsReal()){return val.GetReal();}
    else if (val.IsString()){
        try{return stod(val.GetString());}
        catch (const std::exception& exp){throw runtime_error(g);}}
    throw runtime_error("Invalid conversion.");
}