#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "my_counter.h"
#include "my_list.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<MyCounter>("myModule", 1, 0, "MyCounter");
    qmlRegisterType<MyList>("myModule", 1, 0, "MyList");
    return SailfishApp::main(argc, argv);
}
