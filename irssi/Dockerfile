FROM ubuntu:18.04

# Install necessary packages
RUN apt-get update && apt-get install -y irssi telnet zsh git curl

# Set up Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Copy irssi configuration files
COPY config /root/.irssi/config
COPY rain.theme /root/.irssi/rain.theme

CMD ["/bin/zsh"]