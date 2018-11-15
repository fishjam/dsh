# DSH enhanced version

 - [DSH](https://www.netfort.gr.jp/~dancer/software/dsh.html.en): dancer's shell / distributed shell, 
 - [Pssh](https://www.tecmint.com/execute-commands-on-multiple-linux-servers-using-pssh/): Execute Commands on Multiple Remote Linux Servers Using Single Terminal

# Base Version:
 - dsh-0.22: https://www.netfort.gr.jp/~dancer/software/downloads/dsh-0.22.0.tar.gz
 - libdshconfig-0.20.10.cvs.1: https://www.netfort.gr.jp/~dancer/software/downloads/libdshconfig-0.20.10.cvs.1.tar.gz
 
# Build & Configuration
```
cd libdshconfig
./configure --prefix=$HOME/local && make && make install

cd ../dsh
./configure --prefix=$HOME/local \
  LDFLAGS=-L$HOME/local/lib \
  CPPFLAGS=-I$HOME/local/include \
  && make \
  && make install
```

 
# Change list:
 - 1.add -u --user [username] Provide login user name
 - 2.change default shell from rsh to ssh
 
 
