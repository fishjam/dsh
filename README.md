# DSH enhanced version
 - [DSH](https://www.netfort.gr.jp/~dancer/software/dsh.html.en): dancer's shell / distributed shell, 

# Change list:
 - 1.change default shell from rsh to ssh
 - 2.add command parameter to provide login user name: -u | --user username 
   - this is very important for me. So I can change remote user without modify the group conifgruation file or ssh_config file on kerberos server. 
   - Login user are considered in the following order:
     - 1.new added param: -u|--user username
     - 2.username@machinename in dsh configuration file(group or machines)
     - 3.ssh_config file(~/.ssh/config)
     - 4.current username

# Base Version:
 - dsh-0.22: https://www.netfort.gr.jp/~dancer/software/downloads/dsh-0.22.0.tar.gz
 - libdshconfig-0.20.10.cvs.1: https://www.netfort.gr.jp/~dancer/software/downloads/libdshconfig-0.20.10.cvs.1.tar.gz
 
# Build & Configuration

 - 1.build(consider you are in kerberos server, can not install to default position)
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
 - 2.add ~/local/bin to your PATH environment variable.


 
 
