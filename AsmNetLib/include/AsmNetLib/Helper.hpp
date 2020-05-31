#pragma once
#include <string>
#include <vector>
#include <optional>
#include <winsock2.h>

namespace anl
{
   class InetAddress;

   // Function to validate an IP address
   bool validateIP(const std::string& ip);

   void getLocalInterface(in_addr& localInterface);

   std::string hostNameToIP(const std::string& hostName);
   std::optional<std::string> parseAddress(const std::string& hostName);
   std::string socketAddr2String(const sockaddr_in& addr);
   std::string socketAddr2String(const InetAddress& addr);
}
