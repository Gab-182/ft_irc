<div align="center">

![irc_logo_2.png](Extras%2Firc_logo_2.png)

# <span style="color: orange; font-family: 'Times New Roman';">FT_IRC</span>

## <span style="color: gray; font-family: 'Times New Roman';">A lightweight IRC server implemented in C++</span>

----------------------------------------------------------------------------------------
![GitHub contributors](https://img.shields.io/github/contributors/Gab-182/ft_irc?color=blue&style=flat-square&logo=github)
![GitHub stars](https://img.shields.io/github/stars/Gab-182/ft_irc?color=yellow&style=flat-square&logo=github)
![GitHub code size](https://img.shields.io/github/languages/code-size/Gab-182/ft_irc?color=red&style=flat-square&logo=github)

![GitHub commits](https://img.shields.io/github/commits-since/Gab-182/ft_irc/latest?color=orange&style=flat-square&logo=git)
![GitHub pull requests](https://img.shields.io/github/issues-pr/Gab-182/ft_irc?color=purple&style=flat-square&logo=github)

</div>

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">Table of Contents</span>

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Contributers](#contributers)

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">Introduction</span>

ft_irc is a lightweight IRC (Internet Relay Chat) server written in C++. It allows multiple clients to connect and communicate with each other in real-time using the IRC protocol.

The server provides essential features of IRC, including joining channels, sending messages, private messaging, and user authentication. It aims to be efficient, scalable, and easy to use.

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">Installation</span>


To use ft_irc, follow these steps:

1. Clone the repository:
   <br>`$ git clone https://github.com/Gab-182/ft_irc`

<br>

2. Build the project:
   <br>`$ cd ft_irc`
   <br>`$ make all`
   <br> This will create an executable file called `ircserv`.<br>

<br>

4. Run the server:
   <br>`$ ./ircserv <port> <password> `
     Replace `<port>` with the desired port number and `<password>` with the server password.

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">Usage</span>

Once the server is running, clients can connect to it using any IRC client application. Set the server address and port to establish a connection. Use standard IRC commands such as JOIN, NICK, PRIVMSG, etc., to interact with the server and communicate with other connected clients.

Example usage:
`$ telnet localhost <port>`


For detailed information on IRC commands and their usage, refer to the IRC protocol documentation.

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">License</span>

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

----------------------------------------------------------------------------------------

## <span style="color: gray; font-family: 'Times New Roman';">Contributers</span>



