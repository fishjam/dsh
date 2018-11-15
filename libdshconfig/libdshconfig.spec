%define name	libdshconfig
%define ver		0.20.9
%define rel		1

Summary		: Library for parsing dsh-style configuration files.
Name			: %{name}
Version		: %{ver}
Release		: %{rel}
Copyright	: GPL
Group			: Applications/Internet
URL			: http://www.netfort.gr.jp/~dancer/software/downloads/list.cgi
Source		: %{name}-%{ver}.tar.gz
BuildRoot	: /var/tmp/%{name}-buildroot
#Requires		: 

%package devel
Summary: Library for parsing dsh-style configuration files.
Requires: libdshconfig = %{version}-%{release}
Group: Applications/Internet

%description
Library for parsing dsh-style configuration files.
Required by dsh and other applications.

%description devel
Library for parsing dsh-style configuration files.
Required by dsh and other applications.

%prep
%setup -q

%build
%configure
make

%install
rm -rf "$RPM_BUILD_ROOT"
make DESTDIR="$RPM_BUILD_ROOT" install
mkdir -p $RPM_BUILD_ROOT/usr/share/doc/libdshconfig-%{ver}
cp -p AUTHORS COPYING ChangeLog INSTALL NEWS README $RPM_BUILD_ROOT/usr/share/doc/libdshconfig-%{ver}

%files
%defattr(-,root,root)
%attr(0755,root,root) /usr/lib/libdshconfig.so.1.0.0
%attr(0755,root,root) /usr/lib/libdshconfig.so.1
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/AUTHORS
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/COPYING
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/ChangeLog
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/INSTALL
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/NEWS
%attr(0644,root,root) /usr/share/doc/libdshconfig-0.20.9/README

%files devel
%defattr(-,root,root)
%attr(0755,root,root) /usr/lib/libdshconfig.a
%attr(0755,root,root) /usr/lib/libdshconfig.la
%attr(0755,root,root) /usr/lib/libdshconfig.so
%attr(0644,root,root) /usr/include/libdshconfig.h

%changelog
* Mon May 10 2004 Erik Wasser <ew@iquer.net>
- Initial spec-file
- Please don't hurt me.

