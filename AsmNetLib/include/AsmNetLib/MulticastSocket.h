#pragma once

#include <vector>
#include "NetworkHeaders.hpp"

namespace anl
{

   class MulticastSocket
   {
      friend class UDPServerSocket;
   public:
      MulticastSocket(ILogger* logger);

      ~MulticastSocket();


      void closeSocket();

      void initilizeRecv(const InetAddress& addr);
      void sendData(const Data& data, const InetAddress& addr) const;
      void recvData(Data& data) const;
      sockaddr_in getRawSettings() const;

   private:
      void reusePortEnabled();
      void disableMulticastLoop();


      bool receiveInitialized = false;
      ILogger* logger;
      sockaddr_in addrr;
      SOCKET socketHandler;
   };

}
