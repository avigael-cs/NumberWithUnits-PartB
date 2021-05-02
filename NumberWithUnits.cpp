#include "NumberWithUnits.hpp"

namespace ariel {

    unordered_map<string,unordered_map<string,double>> my_map;

    void NumberWithUnits::exsist1(string const & t1) const{
      if(my_map.find(t1) == my_map.end()){
        //exception not find
        string messeage= t1 + " Not exsist" ;
        throw invalid_argument( messeage );
      }
    }
    double NumberWithUnits::exsist2(string const & t1,string const & t2) const{
        NumberWithUnits::exsist1(t1);
        if(my_map[t1].find(t2) == my_map[t1].end()){
          //exception not find
          string messeage= t1 + " Not exsist" ;
          throw invalid_argument( messeage );
        }
      return my_map[t2][t1];
    }

    void NumberWithUnits::insert(string const & t1,string const & t2, double n1 ,double n2){
      my_map[t1][t2]=n2;
      my_map[t2][t1]=n1/n2;

      //example 1 m = 100 cm
      //example 1 km = 1000 m
      //[m][cm] = 100
      //[cm][m] = 1/100
      //[km][m] = 1000
      //[m][km] = 1/1000
      //result 1 km = 100000 cm
      for(auto & pair: my_map[t2]){
        double result= my_map[t1][t2]*pair.second;
        my_map[t1][pair.first]=result;
        my_map[pair.first][t1]=1/result;
      }
      for(auto & pair: my_map[t1]){
        double result= my_map[t2][t1]*pair.second;
        my_map[t2][pair.first]=result;
        my_map[pair.first][t2]=1/result;
      }
    }

    void NumberWithUnits::read_units(ifstream &file_name) {
        //example 1 m = 100 cm
          double n1=0;
          string t1;
          string temp;
          double n2=0;
          string t2;
          while(file_name >>n1>>t1>>temp>>n2>>t2){
            //line by line
            insert(t1,t2,n1,n2);
          }
    }
    NumberWithUnits NumberWithUnits::operator+( NumberWithUnits const & other_num ) {
    //  NumberWithUnits a(10, "km");
    //  NumberWithUnits b(1000, "m");
    //  a+b - >  11 km
        double convert=exsist2(this->type,other_num.type);
        NumberWithUnits result(this->howmuch + (convert*other_num.howmuch), this->type);
        return result;
    }

    NumberWithUnits NumberWithUnits::operator-( NumberWithUnits const & other_num ) {
    //  NumberWithUnits a(10, "km");
    //  NumberWithUnits b(1000, "m");
    //  a+b - >  11 km
        double convert=exsist2(this->type,other_num.type);
        NumberWithUnits result(this->howmuch - (convert*other_num.howmuch), this->type);
        return result;
    }

    NumberWithUnits NumberWithUnits::operator+ () const {
        NumberWithUnits result(this->howmuch, this->type);
        return result;
    }


    NumberWithUnits NumberWithUnits::operator- () const {
      NumberWithUnits result(-1*(this->howmuch), this->type);
      return result;
    }
    //--i
    NumberWithUnits & operator--( NumberWithUnits & value ){
        value.howmuch--;
        return value;
    }
    //i++
    NumberWithUnits operator--( NumberWithUnits & value, int ){
      return NumberWithUnits(value.howmuch-- ,value.type);
    }
    NumberWithUnits & operator++( NumberWithUnits & value ){
      value.howmuch++;
      return value;
    }
    NumberWithUnits operator++( NumberWithUnits & value, int ){
      return NumberWithUnits(value.howmuch++ ,value.type);
    }

    bool NumberWithUnits::operator> (const NumberWithUnits &other_num) const {
      double convert=exsist2(this->type,other_num.type);
      double result =other_num.howmuch * convert;
      if(this->howmuch>result){
        return true; return false;
      }
      return false;
    }
    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
          return *this>other_num || *this==other_num;
    }

    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
      double convert=exsist2(this->type,other_num.type);
      double result =other_num.howmuch * convert;
      if(this->howmuch<result){
        return true; return false;
      }
      return false;
    }
    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        return *this<other_num || *this==other_num;
    }

    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
      double convert=exsist2(this->type,other_num.type);
      double result =other_num.howmuch * convert;
      const double aps=0.001;
      if(abs(this->howmuch-result)<aps){
        return true; return false;
      }
      return false;
    }
    bool NumberWithUnits::operator!= (const NumberWithUnits &other_num) const {
        return !(*this==other_num);
    }

    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits &num) {
      double convert=exsist2(this->type,num.type);
      this->howmuch +=(convert*num.howmuch);
      return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
      double convert=exsist2(this->type,num.type);
      this->howmuch -=(convert*num.howmuch);
      return *this;
    }

    NumberWithUnits operator*(const NumberWithUnits& other_num,const double &value){
      NumberWithUnits result(other_num.howmuch*value, other_num.type);
      return result;
    }
    NumberWithUnits operator*(const double &value, const NumberWithUnits& other_num){
      NumberWithUnits result(other_num.howmuch*value, other_num.type);
      return result;
    }
    ostream& operator<< (ostream& stream, const NumberWithUnits& num) {
        // type  = km , hoemuch = 100 -> 100[km]
        return stream<<num.howmuch<<"["<<num.type<<"]";
    }
    istream& operator>>(istream& stream, NumberWithUnits& num) {
      // -900.0     [km      ]    7000 [g ]
      string s;
      getline(stream,s,']');
      string number;
      for (string::size_type i = 0; i < s.length() || s[i] == '['; i++) {
        if(isdigit(s[i])!=0 || s[i]=='-'||s[i]=='.'){
          number+=s[i];
        }
      }

      string type;
      for (string::size_type i = s.find('['); i < s.length() ; i++) {
        if(isalpha(s[i])!=0 || s[i]=='_'){
          type+=s[i];
        }
      }
      if(my_map.find(type) == my_map.end()){
        //exception not find
        string messeage= type + " Not exsist" ;
        throw invalid_argument( messeage );
      }
      num=NumberWithUnits(stod(number),type);
      return stream;
    }
}
