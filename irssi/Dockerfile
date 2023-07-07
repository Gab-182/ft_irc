FROM ubuntu:18.04

# Install necessary packages
RUN apt-get update \
	&& apt-get install -y \
	irssi \
	valgrind \
	make \
	g++ \
	telnet \
	zsh \
	git \
	curl\
	vim \
	netcat \
	&& apt-get clean autoclean \
	&& apt-get autoremove --yes \
	&& rm -rf /var/lib/{apt,dpkg,cache,log}

# Set up Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Copy irssi configuration files
COPY config /root/.irssi/config
COPY rain.theme /root/.irssi/rain.theme

WORKDIR /home/projects
CMD ["/bin/zsh"]