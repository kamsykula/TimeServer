﻿#include "TimeClient.hpp"
#include "AsmNetLib/AsmNetwork.hpp"
#include "cpptinytools/BasicLogger.hpp"
#include "cpptinytools/ILogger.hpp"

int main()
{
   ctt::log::BasicLogger logger{ "[%TIME%]: " };

   if(true == anl::AsmNetwork::initialize())
   {
      logger.info("Initialized Winsock library...");

      TimeClient client{ logger };
      client.run();

      anl::AsmNetwork::cleanup();
      logger.info("Cleanup...");

      return 0;
   }

   return -1;
}
