#include "../../include/commands/InviteCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

InviteCommand::InviteCommand() : ICommands() { }

InviteCommand::~InviteCommand() { }

/*
inviteUserToChannel
isChannelInviteOnly
*/

//write a function that return Client* clientToInvite

Client * getTargetClient(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command )
{
    // std::string nn = base->getParameters(command)[1];
    int targetSocket = server->getClientSocket(base->getParameters(command)[1]);
    std::cout << targetSocket  << "  "<< clientSocket << std::endl;
     std::map<int , Client *>::iterator itClient;
     itClient = server->serverClientsMap.find(targetSocket);
        // Client *clientToInvite = NULL;
        // (void) base;
        (void) client;
        (void) base;
        (void) command;
        (void) clientSocket;
        if (itClient == server->serverClientsMap.end())
        {
            //user does not exist
            std::cout << "user does not exist" << std::endl;
            return NULL;
        }
        else
            return(server->serverClientsMap[targetSocket]);
        
        return NULL;
}


void InviteCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command)
{
    //syntax : /invite <nickname> <channel>
    //check channel hash # and if it exists
    // std::cout << "InviteCommand::executeCommand+++++++"<< base->getParameters(command)[0] <<"  "<<  base->getParameters(command)[1]<< std::endl;
    std::string channelName = base->getParameters(command)[0];
    if(channelName[0] == '#')
    {
        channelName = channelName.substr(1);
    }
    if (server->serverChannelsMap.find(channelName) == server->serverChannelsMap.end())
    {
        //channel does not exist
        std::cout << channelName << std::endl;
        std::cout << server->serverClientsMap[clientSocket]->getNickName() << std::endl;
		std::string response = ERR_NOSUCHCHANNEL(server->serverClientsMap[clientSocket]->getNickName(),channelName);
		sendResponse(clientSocket, response);
    }
    else
    {
        Client * ClientToInvite = getTargetClient(base, clientSocket, server,client,command);
        if( getTargetClient(base, clientSocket, server,client,command) != NULL)
        {
            std::cout << "ClientToInvite: " << ClientToInvite->getNickName() << std::endl;
            std::cout << "Client: " << client->getNickName() << std::endl;
            server->serverChannelsMap[channelName]->inviteUserToChannel(client,ClientToInvite);
        }
        else
        {
            std::cout << "ClientToInvite: " << "NULL" << std::endl;
        }
    }


}