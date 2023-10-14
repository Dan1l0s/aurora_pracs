## PackageKitAdaptor

To get information about the packages installed on the device,
use the PackageKit system. DBus Adapter was implemented to work
with this system. You can read more information about this system
here: `https://www.freedesktop.org/software/PackageKit/gtk-doc/`.
Its name is PackageKitAdaptor and it can be connected as a
subproject or as a library:
-   to connect it as a subproject, just add it to the your pro file:
    `include (packagekitadaptor.pri)`.
-   if you want to use it as a library, then you need to build a project:
    `include (packagekitadaptor.pro)`,
    and connect it to your pro file in the standard way.

The library includes the classes [Demon](include/daemon.h) and
[Transaction](include/transaction.h), which provide information
about packages. You should use a package management system 
in your C++ code.
