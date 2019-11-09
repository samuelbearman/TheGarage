#include "NoCopyString.h"
#include <string.h>
#include <stdlib.h>

NoCopyString::NoCopyString() {
   m_str = NULL ;
}

NoCopyString::NoCopyString(const char *str) {
   m_str = str ;
}

bool NoCopyString::operator<  (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) <  0) return true ;
   return false ;
}

bool NoCopyString::operator<= (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) <= 0) return true ;
   return false ;
}

bool NoCopyString::operator== (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) == 0) return true ;
   return false ;
}

bool NoCopyString::operator!= (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) != 0) return true ;
   return false ;
}

bool NoCopyString::operator>= (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) >= 0) return true ;
   return false ;
}

bool NoCopyString::operator>  (const NoCopyString& other) const {
   if (strcmp(m_str, other.m_str) >  0) return true ;
   return false ;
}


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) {
   sout << s.m_str ;
   return sout ;
}
