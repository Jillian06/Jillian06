#include <algorithm>
#include <charconv>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
// Teaching example, not LLVM/MLIR. Straight-line assignments and print only.
struct Arg { bool constant=false; int64_t value=0; std::string name; };
struct Ins { enum Op { MOV, ADD, SUB, MUL, PRINT } op; std::string dst; Arg a,b; };
using IR=std::vector<Ins>;
bool ident(const std::string& s){
 if(s.empty()||!(std::isalpha((unsigned char)s[0])||s[0]=='_'))return false;
 return std::all_of(s.begin()+1,s.end(),[](unsigned char c){return std::isalnum(c)||c=='_';});
}
std::vector<std::string> tokens(const std::string& s){
 std::vector<std::string> t;
 for(size_t i=0;i<s.size();){
  if(std::isspace((unsigned char)s[i])){++i;continue;}
  if(s[i]=='='||s[i]=='+'||s[i]=='*'||(s[i]=='-'&&(i+1==s.size()||!std::isdigit((unsigned char)s[i+1])))){t.emplace_back(1,s[i++]);continue;}
  size_t j=i;
  if(s[j]=='-'&&j+1<s.size()&&std::isdigit((unsigned char)s[j+1]))++j;
  if(j<s.size()&&std::isdigit((unsigned char)s[j])){while(j<s.size()&&std::isdigit((unsigned char)s[j]))++j;}
  else if(std::isalpha((unsigned char)s[j])||s[j]=='_'){while(j<s.size()&&(std::isalnum((unsigned char)s[j])||s[j]=='_'))++j;}
  else throw std::runtime_error("unsupported character");
  t.push_back(s.substr(i,j-i));i=j;
 }
 return t;
}
Arg argument(const std::string& s,const std::set<std::string>& defined){
 if(ident(s)){if(!defined.count(s))throw std::runtime_error("undefined variable: "+s);return {false,0,s};}
 int64_t val=0;auto r=std::from_chars(s.data(),s.data()+s.size(),val);
 if(r.ec!=std::errc{}||r.ptr!=s.data()+s.size())throw std::runtime_error("invalid integer: "+s);
 return {true,val,""};
}
IR parse(std::istream& in){
 IR p;std::set<std::string> defined;std::string line;
 for(int n=1;std::getline(in,line);++n){
  if(auto k=line.find('#');k!=std::string::npos)line.resize(k);
  auto t=tokens(line);if(t.empty())continue;
  try{
   if(t[0]=="print"&&t.size()==2){p.push_back({Ins::PRINT,"",argument(t[1],defined),{}});continue;}
   if((t.size()!=3&&t.size()!=5)||!ident(t[0])||t[0]=="print"||t[1]!="=")
    throw std::runtime_error("expected assignment or print");
   Arg a=argument(t[2],defined),b;Ins::Op op=Ins::MOV;
   if(t.size()==5){
    if(t[3]=="+")op=Ins::ADD;else if(t[3]=="-")op=Ins::SUB;
    else if(t[3]=="*")op=Ins::MUL;else throw std::runtime_error("unknown operator");
    b=argument(t[4],defined);
   }
   p.push_back({op,t[0],a,b});defined.insert(t[0]);
  }catch(const std::exception& e){throw std::runtime_error("line "+std::to_string(n)+": "+e.what());}
 }
 return p;
}
std::optional<int64_t> evaluate(Ins::Op op,int64_t a,int64_t b){
 int64_t out=0;bool err=false;
 if(op==Ins::ADD)err=__builtin_add_overflow(a,b,&out);
 else if(op==Ins::SUB)err=__builtin_sub_overflow(a,b,&out);
 else if(op==Ins::MUL)err=__builtin_mul_overflow(a,b,&out);
 else return std::nullopt;
 if(err) return std::nullopt;
 return out;
}
IR fold(const IR& p){
 IR out;std::map<std::string,std::optional<int64_t>> env;
 for(auto x:p){
  auto sub=[&](Arg& a){if(!a.constant){auto it=env.find(a.name);if(it!=env.end()&&it->second)a={true,*it->second,""};}};
  sub(x.a);if(x.op!=Ins::MOV&&x.op!=Ins::PRINT)sub(x.b);
  if(x.op!=Ins::PRINT){
   if(x.op!=Ins::MOV&&x.a.constant&&x.b.constant)
    if(auto v=evaluate(x.op,x.a.value,x.b.value)){x.op=Ins::MOV;x.a={true,*v,""};x.b={};}
   env[x.dst]=x.op==Ins::MOV&&x.a.constant?std::optional<int64_t>(x.a.value):std::nullopt;
  }
  out.push_back(x);
 }
 return out;
}
IR dce(const IR& p){
 std::set<std::string> live;IR reversed;
 auto use=[&](const Arg& a){if(!a.constant)live.insert(a.name);};
 for(auto it=p.rbegin();it!=p.rend();++it){
  const auto& x=*it;
  if(x.op==Ins::PRINT){reversed.push_back(x);use(x.a);continue;}
  if(!live.count(x.dst))continue;
  live.erase(x.dst);use(x.a);if(x.op!=Ins::MOV)use(x.b);reversed.push_back(x);
 }
 std::reverse(reversed.begin(),reversed.end());return reversed;
}
std::string str(const Arg& a){return a.constant?std::to_string(a.value):a.name;}
void print_ir(const IR& p){
 for(const auto& x:p){
  if(x.op==Ins::PRINT){std::cout<<"print "<<str(x.a)<<"\n";continue;}
  std::cout<<x.dst<<" = "<<str(x.a);
  if(x.op!=Ins::MOV)std::cout<<" "<<(x.op==Ins::ADD?"+":x.op==Ins::SUB?"-":"*")<<" "<<str(x.b);
  std::cout<<"\n";
 }
}
void execute(const IR& p){
 std::map<std::string,int64_t> variables;
 auto get=[&](const Arg& a)->int64_t{if(a.constant)return a.value;return variables.at(a.name);};
 for(const auto& x:p){
  auto a=get(x.a);
  if(x.op==Ins::PRINT){std::cout<<a<<"\n";continue;}
  if(x.op==Ins::MOV){variables[x.dst]=a;continue;}
  auto value=evaluate(x.op,a,get(x.b));
  if(!value)throw std::runtime_error("signed 64-bit arithmetic overflow");
  variables[x.dst]=*value;
 }
}
int main(int argc,char** argv){
 try{
  if(argc>2||(argc==2&&std::string(argv[1])!="--no-opt"))throw std::runtime_error("usage: mini_ir [--no-opt] < sample.ir");
  IR original=parse(std::cin);
  IR optimized=dce(fold(original));
  const IR& selected=argc==1?optimized:original;
  std::cout<<"=== IR ===\n";print_ir(selected);std::cout<<"=== Output ===\n";execute(selected);
  return 0;
 }catch(const std::exception& e){std::cerr<<"error: "<<e.what()<<"\n";return 1;}
}
