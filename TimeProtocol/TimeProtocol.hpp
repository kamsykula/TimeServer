#pragma once
#include <optional>

#include "AsmNetLib/Types.hpp"

class TimeProtocol
{
public:
   TimeProtocol() = delete;
   TimeProtocol(const TimeProtocol& other) = delete;
   TimeProtocol(TimeProtocol&& other) noexcept = delete;
   TimeProtocol& operator=(const TimeProtocol& other) = delete;
   TimeProtocol& operator=(TimeProtocol&& other) noexcept = delete;

   enum Command
   {
      DISCOVERY,
      SEND_OFFER,  
      INVALID
   };


   //parse
   static Command parseBuffer(const anl::Data& data);
   static std::optional<anl::InetAddress> parseOfferAddress(const anl::Data& data);

   //make functions
   static anl::Data makeDiscoveryCmd();
   static anl::Data makeOfferCmd(const anl::InetAddress& address);

};
