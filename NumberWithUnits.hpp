
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdexcept>
using namespace std;

namespace ariel {
    class NumberWithUnits {
        private:
            double howmuch;
            string type;
            static void insert(string const & t1,string const & t2, double n1 ,double n2);
            void exsist1(string const & t1) const ;
            double exsist2(string const & t1,string const & t2) const;
        public:
            NumberWithUnits(double howmuch, string type){
              exsist1(type);
              this->howmuch=howmuch;
              this->type=type;
            }
		        static void read_units(ifstream &file_name);
            NumberWithUnits operator- () const;
            NumberWithUnits operator-( NumberWithUnits const & other_num ) ;
            NumberWithUnits operator+ () const;
            NumberWithUnits operator+( NumberWithUnits const & other_num ) ;

            friend NumberWithUnits & operator--( NumberWithUnits & value );
            friend NumberWithUnits operator--( NumberWithUnits & value, int );
            friend NumberWithUnits & operator++( NumberWithUnits & value );
            friend NumberWithUnits operator++( NumberWithUnits & value, int );

            bool operator> (const NumberWithUnits &other_num) const;
            bool operator>= (const NumberWithUnits &other_num) const;
            bool operator< (const NumberWithUnits &other_num) const;
            bool operator<= (const NumberWithUnits &other_num) const;
            bool operator== (const NumberWithUnits &other_num) const;
            bool operator!= (const  NumberWithUnits &other_num) const;
            NumberWithUnits& operator+= (const NumberWithUnits &num);
            NumberWithUnits& operator-= (const NumberWithUnits &num);
            friend NumberWithUnits operator*(const NumberWithUnits& other_num,const double &value);
            friend NumberWithUnits operator*(const double &value, const NumberWithUnits& other_num);
            friend ostream& operator<< (ostream& stream, const NumberWithUnits& num);
            friend istream& operator>> (istream& stream, NumberWithUnits& num);
	};
}
