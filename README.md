# ft_irc

A lightweight IRC server implementation in C++

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Contact](#contact)

## Introduction

ft_irc is a lightweight IRC (Internet Relay Chat) server written in C++. It allows multiple clients to connect and communicate with each other in real-time using the IRC protocol.

The server provides essential features of IRC, including joining channels, sending messages, private messaging, and user authentication. It aims to be efficient, scalable, and easy to use.

## Installation

To use ft_irc, follow these steps:

1. Clone the repository:
  `$ git clone https://github.com/Gab-182/ft_irc`

2. Build the project:
  `$ cd ft_irc`
  `$ make all`

3. Run the server:
  `$ ./ircserv <port> <password> `
  Replace `<port>` with the desired port number and `<password>` with the server password.

## Usage

Once the server is running, clients can connect to it using any IRC client application. Set the server address and port to establish a connection. Use standard IRC commands such as JOIN, NICK, PRIVMSG, etc., to interact with the server and communicate with other connected clients.

Example usage:
`$ telnet localhost <port>`


For detailed information on IRC commands and their usage, refer to the IRC protocol documentation.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributers:


