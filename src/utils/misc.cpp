#include "misc.h"

#include <QtGlobal>
#include <QString>
#include <QDebug>

#if (defined(Q_OS_UNIX) && !defined(Q_OS_MACOS)) && defined(QT_DBUS_LIB)
#include <QDBusInterface>
#endif

void Utils::Misc::shutdownComputer(const ShutdownDialogAction &action)
{

#if (defined(Q_OS_UNIX) && defined(QT_DBUS_LIB))
    // Use dbus to power off / suspend the system
    if (action != ShutdownDialogAction::Shutdown)
    {
        // Some recent systems use systemd's logind
        QDBusInterface login1Iface(QString("org.freedesktop.login1"), QString("/org/freedesktop/login1"),
                                   QString("org.freedesktop.login1.Manager"), QDBusConnection::systemBus());
        if (login1Iface.isValid())
        {
            if (action == ShutdownDialogAction::Suspend)
                login1Iface.call(QString("Suspend"), false);
            else if (action == ShutdownDialogAction::Reboot)
                login1Iface.call(QString("Reboot"), false);
            else
                login1Iface.call(QString("Hibernate"), false);
            return;
        }
        // Else, other recent systems use UPower
        QDBusInterface upowerIface(QString("org.freedesktop.UPower"), QString("/org/freedesktop/UPower"),
                                   QString("org.freedesktop.UPower"), QDBusConnection::systemBus());
        if (upowerIface.isValid())
        {
            if (action == ShutdownDialogAction::Suspend)
                upowerIface.call(QString("Suspend"));
            else if (action == ShutdownDialogAction::Reboot)
                upowerIface.call(QString("Reboot"));
            else
                upowerIface.call(QString("Hibernate"));
            return;
        }
        // HAL (older systems)
        QDBusInterface halIface(QString("org.freedesktop.Hal"), QString("/org/freedesktop/Hal/devices/computer"),
                                QString("org.freedesktop.Hal.Device.SystemPowerManagement"),
                                QDBusConnection::systemBus());
        if (action == ShutdownDialogAction::Suspend)
            halIface.call(QString("Suspend"), 5);
        else
            halIface.call(QString("Hibernate"));
    }
    else
    {
        // Some recent systems use systemd's logind
        QDBusInterface login1Iface(QString("org.freedesktop.login1"), QString("/org/freedesktop/login1"),
                                   QString("org.freedesktop.login1.Manager"), QDBusConnection::systemBus());
        if (login1Iface.isValid())
        {
            login1Iface.call(QString("PowerOff"), false);
            return;
        }
        // Else, other recent systems use ConsoleKit
        QDBusInterface consolekitIface(QString("org.freedesktop.ConsoleKit"), QString("/org/freedesktop/ConsoleKit/Manager"),
                                       QString("org.freedesktop.ConsoleKit.Manager"), QDBusConnection::systemBus());
        if (consolekitIface.isValid())
        {
            consolekitIface.call(QString("Stop"));
            return;
        }
        // HAL (older systems)
        QDBusInterface halIface(QString("org.freedesktop.Hal"), QString("/org/freedesktop/Hal/devices/computer"),
                                QString("org.freedesktop.Hal.Device.SystemPowerManagement"),
                                QDBusConnection::systemBus());
        halIface.call(QString("Shutdown"));
    }

#else
    Q_UNUSED(action);
#endif

}
