#include <client.hpp>

client::client(){}
client::~client(){}

void client::set_user(std::string user){this->user = user;}
void client::set_pass(std::string pass){this->pass = pass;}
void client::set_nick(std::string nick){this->nick = nick;}
void client::set_host(std::string host){this->host = host;}

std::string client::get_user(){return this->user;}
std::string client::get_pass(){return this->pass;}
std::string client::get_nick(){return this->nick;}
std::string client::get_host(){return this->host;}

void client::print()
{
	std::cout << "User: " << this->user << std::endl;
	std::cout << "Pass: " << this->pass << std::endl;
	std::cout << "Nick: " << this->nick << std::endl;
	std::cout << "Host: " << this->host << std::endl;
}