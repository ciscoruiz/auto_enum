#ifndef _AUTO_ENUM_H_
#define _AUTO_ENUM_H_

#include <string.h>
#include <exception>
#include <string>

/**
 * \page declare_enum
 *
  * Makes easier to declare enumerations by offering methods to translate between name and numerical value.
 *
 * Sequences must contain a null-value called \em None which has the numerical value -1, all the other numbers must be sequential,
 * from zero to N.
 *
 * The next code shows how could be a defined a enumeration:
 *
 * \code
 * struct Transport {
 *    enum _v { None = -1, TCP, SCTP, UDP };
 *     auto_enum_declare (Transport);
 * };
 * \endcode
 *
 * That code offers you the next list of methods:
 *
 * \li Transport::_v Transport::enumValue (const char* str): Translates the string to the numerical value. If str is not defined as valid name
 * It will return the Transport::None value.
 * \li Transport::_v Transport::enumValue (const std::string& str): Returns Transport::enumValue (str.c_str ()).
 * \li Transport::_v Transport::enumValueEx (const char* str): Translates the string to the numerical value. If str is not defined as valid name
 * It will throw a std::invalid_argument exception.
 * \li Transport::_v Transport::enumValueEx (const std::string& str): Returns Transport::enumValueEx (str.c_str ()).
 * \li const char* enumName (const Transport::_v v): Translates the numerical value to name. If \em v is the value \em Transport::None it will
 * return NULL.
 * \li std::string enumNameEx (const Transport::_v v): Translates the numerical value to name. If \em v is the value \em Transport::None it will
 * throw a  std::invalid_argument exception.
 * \ref assign_enum
 * \ref item_enum
 */
#define auto_enum_declare(name) \
   static const char* literal []; \
   \
   static _v enumValue (const char* str) throw () { \
      for (int ii = 0; literal [ii] != NULL; ++ ii) { \
         if (strcasecmp (str, literal [ii]) == 0) \
            return (_v) ii; \
      } \
      return None; \
   } \
   \
   static _v enumValue (const std::string& str) throw () { return enumValue (str.c_str ()); } \
   \
   static _v enumValueEx (const char* str) throw (std::invalid_argument) { \
      if (str == NULL) { \
         std::string msg (#name); \
         msg += "::enumValueEx | String can not be null"; \
         throw std::invalid_argument (msg); \
      } \
      _v result = enumValue (str); \
      if (result == None) { \
         std::string msg (#name); \
         msg += " | Value: '"; \
         msg += str; \
         msg += "' is not valid | Valid values: "; \
         msg += asList (); \
         throw std::invalid_argument (msg); \
      } \
      return result; \
   } \
   \
   static _v enumValueEx (const std::string& str) throw (std::invalid_argument) { return enumValueEx (str.c_str ()); } \
   \
   static const char* enumName (const _v v) throw () { return (v != None) ? literal [v]: NULL; } \
   \
   static std::string enumNameEx (const _v v) throw (std::invalid_argument) { \
      const char* name = enumName (v); \
      if (name == NULL) { \
         std::string msg (#name); \
         msg += " does not have an assigned value"; \
         throw std::invalid_argument (msg); \
      }\
      return std::string (name);    \
   } \
   \
   static std::string asList () throw () {\
      std::string result;\
      for (register int ii = 0; literal [ii] != NULL; ++ ii) { \
         if (ii > 1) result += ' '; \
         result += "'"; result += literal [ii]; result += "'"; \
      } \
      return result; \
   }

/**
 * \page assign_enum
 *
 * Sets the names of every numeric value on the sequence. You must indicate the end of the list by mean
 * the of NULL value.
 *
 * There is not way to verify that every enumeration value has its corresponding name, please verify each value.
 *
 * \code
 * auto_enum_assign (Transport) = { "tcp", "sctp", "udp", NULL };
 * \endcode
 *
 * \ref auto_enum_declare
 * \warning You must indicate the end of the list by mean the of NULL value.
 */
#define auto_enum_assign(name) const char* name::literal []

/**
 * \page item_enum
 * Accesses to the literal defined by the enumeration and the position received as parameter.
 */
#define auto_enum_access(name,ii) name::literal[ii]

#endif
