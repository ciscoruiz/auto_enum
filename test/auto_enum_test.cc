// auto_enum_test - test for auto numerations.
//
// (c) Copyright 2012 Francisco Ruiz Rayo
//
// https://github.com/ciscoruiz/auto_enum
//
// Copyright (c) 2012 Francisco A. Ruiz Rayo (cisco.tierra@gmail.com)

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//and associated documentation files (the "Software"), to deal in the Software without restriction,
//including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial
//portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <boost/test/unit_test.hpp>

#include "../auto_enum.h"


struct Transport {
   enum _v { None = -1, TCP, UDP, STCP };
   auto_enum_declare(Trasnport);
};

auto_enum_assign(Transport) = { "tcp", "udp", "stcp", NULL };

BOOST_AUTO_TEST_CASE( get_value )
{
   BOOST_REQUIRE_EQUAL(Transport::None, Transport::enumValue("undefined"));

   BOOST_REQUIRE_EQUAL(Transport::TCP, Transport::enumValue("Tcp"));
   BOOST_REQUIRE_EQUAL(Transport::UDP, Transport::enumValue("UDP"));
   BOOST_REQUIRE_EQUAL(Transport::STCP, Transport::enumValue("stcp"));
}

BOOST_AUTO_TEST_CASE( get_value_ex )
{
   BOOST_REQUIRE_EQUAL(Transport::TCP, Transport::enumValueEx("Tcp"));
   BOOST_REQUIRE_EQUAL(Transport::UDP, Transport::enumValueEx("UDP"));
   BOOST_REQUIRE_EQUAL(Transport::STCP, Transport::enumValueEx("stcp"));

   BOOST_REQUIRE_THROW  (Transport::enumValueEx("undefined"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( get_name )
{
   BOOST_CHECK(strcmp ("tcp", Transport::enumName (Transport::TCP)) == 0);
   BOOST_CHECK(strcmp ("udp", Transport::enumName (Transport::UDP)) == 0);
   BOOST_CHECK(strcmp ("stcp", Transport::enumName (Transport::STCP)) == 0);
   BOOST_REQUIRE_EQUAL((const char*) NULL, Transport::enumName(Transport::None));
}

BOOST_AUTO_TEST_CASE( get_name_ex )
{
   BOOST_REQUIRE_EQUAL ("tcp", Transport::enumNameEx (Transport::TCP));
   BOOST_REQUIRE_EQUAL ("udp", Transport::enumNameEx (Transport::UDP));
   BOOST_REQUIRE_EQUAL ("stcp", Transport::enumNameEx (Transport::STCP));

   BOOST_REQUIRE_THROW (Transport::enumNameEx(Transport::None), std::invalid_argument)
}

BOOST_AUTO_TEST_CASE( list)
{
   BOOST_CHECK(strcmp ("tcp", auto_enum_access (Transport, Transport::TCP)) == 0);
   BOOST_CHECK(strcmp ("udp", auto_enum_access (Transport, 1)) == 0);

   BOOST_REQUIRE_EQUAL ("'tcp''udp' 'stcp'", Transport::asList());
}
