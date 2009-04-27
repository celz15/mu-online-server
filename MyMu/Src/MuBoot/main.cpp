//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "packages.h"
#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif
#if defined (HAVE_BOOST_ASIO)

using boost::asio::ip::tcp;

enum { max_length = 0xffff };

int main(int argc, char* argv[])
{




  try
    {
      if (argc != 3)
	{
	  std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
	  return 1;
	}

      boost::asio::io_service io_service;

      tcp::resolver resolver(io_service);
      tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
      tcp::resolver::iterator iterator = resolver.resolve(query);

      tcp::socket s(io_service);
      s.connect(*iterator);

      using namespace std; // For strlen.
      char reply[max_length];
      char request[max_length];
      size_t request_length = strlen(request);   
      size_t reply_length = boost::asio::read(s,
					      boost::asio::buffer(reply, request_length));
      std::cout << "Reply is: ";
      std::cout.write(reply, reply_length);
      std::cout << "\n";

      std::cout << "Enter message: ";
   
   
      boost::asio::write(s, boost::asio::buffer(login, 0x30));


    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}
#else
int main()
{
  //nothing here
  return 0;
}

#endif
