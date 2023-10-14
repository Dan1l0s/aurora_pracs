# System Info

The project contains the usage examples
of the API that provides information about the execution environment:
the OS and the device.

The main purpose is to show not only what information can be obtained,
but also which ways to get it are correct.


The source code of the project is provided under
[the license](LICENSE.BSD-3-CLAUSE.md),
that allows it to be used in third-party applications.

The [contributor agreement](CONTRIBUTING.md)
documents the rights granted by contributors to the Open Mobile Platform.

[Code of conduct](CODE_OF_CONDUCT.md) is a current set of rules
of the Open Mobile Platform which informs you how we expect
the members of the community will interact while contributing and communicating.

For information about contributors see [AUTHORS](AUTHORS.md).

## Project Structure

The project has a common structure
of an application based on C++ and QML for Aurora OS.

* **[ru.auroraos.SystemInfo.pro](ru.auroraos.SystemInfo.pro)** file
  describes the project structure for the qmake build system.
* **[icons](icons)** directory contains application icons for different screen resolutions.
* **[qml](qml)** directory contains the QML source code and the UI resources.
  * **[cover](qml/cover)** directory contains the application cover implementations.
  * **[icons](qml/icons)** directory contains the custom UI icons.
  * **[pages](qml/pages)** directory contains the application pages.
  * **[SystemInfo.qml](qml/SystemInfo.qml)** file
    provides the application window implementation.
* **[rpm](rpm)** directory contains the rpm-package build settings.
  **[ru.auroraos.SystemInfo.spec](rpm/ru.auroraos.SystemInfo.spec)** file is used by rpmbuild tool.
  It is generated from **[ru.auroraos.SystemInfo.yaml](rpm/ru.auroraos.SystemInfo.yaml)** file.
* **[src](src)** directory contains the C++ source code.
  * **[main.cpp](src/main.cpp)** file is the application entry point.
* **[translations](translations)** directory contains the UI translation files.
* **[ru.auroraos.SystemInfo.desktop](ru.auroraos.SystemInfo.desktop)** file
  defines the display and parameters for launching the application.

## Examples

### Hardware

This category of examples is dedicated
to obtaining information about the device properties and components.
The corresponding pages with the examples are located
in the **[hardware](qml/pages/hardware)** directory.

[QtSystemInfo](https://github.com/sailfishos/qtsystems)
allows to get general information about the device.

Preliminary preparations are required to use the library:

*	Add `Qt5SystemInfo` to the `PkgConfigBR` section of the **.yaml** file
	or `BuildRequires: pkgconfig(Qt5SystemInfo)`to the **.spec** file.
*	Add `Qt5SystemInfo` to the `PKGCONFIG` list of the **.pro** file.

#### Device Info

This example shows how to use
[QDeviceInfo](https://github.com/sailfishos/qtsystems/blob/mer-dev/src/systeminfo/qdeviceinfo.h)
to get properties of the device and the OS build.
`QDeviceInfo` class is registered as `DeviceInfo` type for QML.

*	**[DeviceInfoPage.qml](qml/pages/hardware/DeviceInfoPage.qml)**
    is the example page.

#### Storage Info

This example shows how to use [QStorageInfo](https://doc.qt.io/archives/qt-5.6/qstorageinfo.html)
to get properties of the mounted volumes.
To access the `QStorageInfo` class,
you need include the library header file.
If the project does not use the `QtSystemInfo` library,
then it is sufficient to include the header file of the `QStorageInfo` class.
The problem is caused by two different interfaces of a class named `QStorageInfo`.
This project uses the Qt core `QStorageInfo` class.

*   **[StorageInfoPage.qml](qml/pages/hardware/StorageInfoPage.qml)**
    is the example page.
*   **[storageinfomodel.h](src/storageinfomodel.h)**
    and **[storageinfomodel.cpp](src/storageinfomodel.cpp)**
    implement a model that provides the information about the mounted volumes.

### Connections

This category of examples is dedicated
to obtaining information about the device connections.
The corresponding pages with examples are located
in the **[connections](qml/pages/connections)** directory.

[Connman](https://github.com/sailfishos/libconnman-qt)
is an Internet connection manager that, among other things,
allows you to get information about network connections, 
usig it DBus-service.

#### Network Status

This example shows how to use
to get status of the network connections.

*	**[NetworkManagerPage.qml](qml/pages/connections/NetworkManagerPage.qml)**
    is the example page.

### Packages

This category of is dedicated to the packages information of the device.
The corresponding pages with examples are located
in the **[packages](qml/pages/packages)** directory.

#### Package Info

This example shows how to use [PackageKitAdaptor](#packagekitadaptor)
to get detailed information about package.

*   **[PackageInfoPage.qml](qml/pages/packages/PackageInfoPage.qml)**
    is the example page.

#### Search Packages

This example shows how to use [PackageKitAdaptor](#packagekitadaptor)
to get the list of the device packages.

*   **[PackageSearchPage.qml](qml/pages/packages/PackageSearchPage.qml)**
    is the example page.

#### PackageKitAdaptor

To get information about the packages installed on the device, use the
PackageKit system. DBus Adapter was implemented to work with this system.
Its name is PackageKitAdaptor and it can be connected as a subproject
or as a library.
-   To connect it as a subproject, just add it to the your pro file:
    `include (3rdparty/packagekitadaptor/packagekitadaptor.pri)`.
-   If you want to use it as a library, then you need to build a project:
    `include (3rdparty/packagekitadaptor/packagekitadaptor.pro)`,
    and connect it to your pro file in the standard way.

The library includes the classes **[Demon](3rdparty/packagekitadaptor/daemon.h)** and
**[Transaction](3rdparty/packagekitadaptor/transaction.h)**, which provide information
about packages. You should use a package management system in your C++ code.

In this application, `Daemon` and `Transaction` are used within the
**[PackageSearcher](src/packagesearcher.h)** and **[PackageInfoProvider](src/packageinfoprovider.h)**.
They are registered as QML types, that are used in the **[PackagesSearchPage.qml](qml/pages/packages/PackagesSearchPage.qml)**
and **[PackageInfoPage.qml](qml/pages/packages/PackageInfoPage.qml)** pages to find the required
packages and generate detailed information about them.
