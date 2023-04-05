#include "message.hpp"

irc::message::message(){}
irc::message::~message(){}
void irc::message::set_msg(std::string msg){this->msg = msg;}
void irc::message::set_prefix(std::string prefix){this->prefix = prefix;}
void irc::message::set_command(std::string command){this->command = command;}
void irc::message::set_params(std::string params){this->params.push_back(params);}

std::string irc::message::get_msg(){return this->msg;}
std::string irc::message::get_prefix(){return this->prefix;}
std::string irc::message::get_command(){return this->command;}
std::vector<std::string> irc::message::get_params(){return this->params;}
