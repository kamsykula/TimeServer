#include "TimeProtocol.hpp"

#include <string>
#include "AsmNetLib/InetAddress.hpp"

const std::string discoveryCmdStr = "DISCOVERY";
const std::string offerCmdStr = "OFFER ADDRESS ";
const std::string sendServerTimeCmdStr = "SERVER TIME ";
const std::string getServerTimeCmdStr = "GET SERVER TIME ";

const anl::Data discoveryCmd = { discoveryCmdStr.begin(), discoveryCmdStr.end() };
const anl::Data getServerTimeCmd = { getServerTimeCmdStr.begin(), getServerTimeCmdStr.end() };

TimeProtocol::Command TimeProtocol::parseBuffer(const anl::Data& data)
{
   if(true == std::equal(data.begin(), data.begin() + discoveryCmdStr.size(), discoveryCmdStr.begin(), discoveryCmdStr.end()))
   {
      return Command::DISCOVERY;
   }
   else if(true == std::equal(data.begin(), data.begin() + offerCmdStr.size(), offerCmdStr.begin(), offerCmdStr.end()))
   {
      return Command::SEND_OFFER;
   }
   else if(true == std::equal(data.begin(), data.begin() + getServerTimeCmdStr.size(), getServerTimeCmdStr.begin(), getServerTimeCmdStr.end()))
   {
      return Command::GET_SERVER_TIME;
   }
   else if(true == std::equal(data.begin(), data.begin() + sendServerTimeCmdStr.size(), sendServerTimeCmdStr.begin(), sendServerTimeCmdStr.end()))
   {
      return Command::SEND_SERVER_TIME;
   }


   return Command::INVALID;
}

std::optional<anl::InetAddress> TimeProtocol::parseOfferAddress(const anl::Data& data)
{
   std::optional<anl::InetAddress> rV = std::nullopt;

   if(data.size() > offerCmdStr.size())
   {
      std::string command = std::string{ data.begin() + offerCmdStr.size(), data.end() };
      command.erase(std::find(command.begin(), command.end(), '\0'), command.end());
      const auto& tokens = ctt::StringTools::split(command, ":");

      if(tokens.size() == 2)
      {
         const auto& optIp = anl::Ip4Addr::fromString(tokens[0].c_str());

         if(true == optIp.has_value())
         {
            rV = anl::InetAddress( optIp.value(), std::stoi(tokens[1]) );
         }
      }
   }

   return rV;
}

uint64_t TimeProtocol::parseTimeFromServer(const anl::Data& data)
{
   uint64_t ms = 0;

   if(data.size() > sendServerTimeCmdStr.size())
   {
      std::string command = std::string{ data.begin() + sendServerTimeCmdStr.size(), data.end() };
      command.erase(std::find(command.begin(), command.end(), '\0'), command.end());

      ms = std::stoll(command);
   }

   return ms;
}

anl::Data TimeProtocol::makeDiscoveryCmd()
{
   return discoveryCmd;
}

anl::Data TimeProtocol::makeGetServerTimeCmd()
{
   return getServerTimeCmd;
}

anl::Data TimeProtocol::makeOfferCmd(const anl::InetAddress& address)
{
   const std::string temp = offerCmdStr + address.toString();
   const anl::Data offerCmd = { temp.begin(), temp.end() };
   return offerCmd;
}

anl::Data TimeProtocol::makeSendServerTimeCmd(uint64_t ms)
{
   const std::string temp = sendServerTimeCmdStr + std::to_string(ms);
   const anl::Data cmd = { temp.begin(), temp.end() };
   return cmd;

}
