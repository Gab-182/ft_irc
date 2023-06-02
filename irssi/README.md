## Container to run irssi client inside
## Usage:

1. First edit the setting in config file:
```bash
    settings = {
      core = {
      real_name = "Your Real Name";
      user_name = "Your User Name";
      nick = "Your Nick";
      };
      "fe-text" = { actlist_sort = "refnum";
      };
      "fe-common/core" = { theme = "rain";
      };
};
```
2. Build container:
```bash
    docker build -t irssi .
```
3. Run container:
```bash
   docker run -it --rm --name irssi  -it irssi
```
4. Connect to server:
```bash
   /connect <your machine ip> <port> <password>
```
5. Join channel:
```bash
   /join <channel name>
```
6. Enjoy!
