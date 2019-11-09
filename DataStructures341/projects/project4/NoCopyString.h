#ifndef _NOCOPYSTRING_H_
#define _NOCOPYSTRING_H_

#include <iostream>

class NoCopyString {
public:
   NoCopyString() ;
   NoCopyString(const char *) ;

   bool operator<  (const NoCopyString& other) const ;
   bool operator<= (const NoCopyString& other) const ;
   bool operator== (const NoCopyString& other) const ;
   bool operator!= (const NoCopyString& other) const ;
   bool operator>  (const NoCopyString& other) const ;
   bool operator>= (const NoCopyString& other) const ;

   const char *m_str ;

} ;


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) ;

#endif
