/* This file is part of the dbusmenu-qt library
   SPDX-FileCopyrightText: 2009 Canonical
   Author: Aurelien Gateau <aurelien.gateau@canonical.com>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef DBUSMENUTYPES_P_H
#define DBUSMENUTYPES_P_H

// Qt
#include <QList>
#include <QStringList>
#include <QVariant>

#include <dbusmenu_export.h>

class QDBusArgument;

//// DBusMenuItem
/**
 * Internal struct used to communicate on DBus
 */
struct DBUSMENU_EXPORT DBusMenuItem
{
    int id;
    QVariantMap properties;
};

Q_DECLARE_METATYPE(DBusMenuItem)

DBUSMENU_EXPORT QDBusArgument &operator<<(QDBusArgument &argument, const DBusMenuItem &item);
DBUSMENU_EXPORT const QDBusArgument &operator>>(const QDBusArgument &argument, DBusMenuItem &item);

typedef QList<DBusMenuItem> DBusMenuItemList;

Q_DECLARE_METATYPE(DBusMenuItemList)


//// DBusMenuItemKeys
/**
 * Represents a list of keys for a menu item
 */
struct DBUSMENU_EXPORT DBusMenuItemKeys
{
    int id;
    QStringList properties;
};

Q_DECLARE_METATYPE(DBusMenuItemKeys)

DBUSMENU_EXPORT QDBusArgument &operator<<(QDBusArgument &argument, const DBusMenuItemKeys &);
DBUSMENU_EXPORT const QDBusArgument &operator>>(const QDBusArgument &argument, DBusMenuItemKeys &);

typedef QList<DBusMenuItemKeys> DBusMenuItemKeysList;

Q_DECLARE_METATYPE(DBusMenuItemKeysList)

//// DBusMenuLayoutItem
/**
 * Represents an item with its children. GetLayout() returns a
 * DBusMenuLayoutItemList.
 */
struct DBusMenuLayoutItem;
struct DBUSMENU_EXPORT DBusMenuLayoutItem
{
    int id;
    QVariantMap properties;
    QList<DBusMenuLayoutItem> children;
};

Q_DECLARE_METATYPE(DBusMenuLayoutItem)

DBUSMENU_EXPORT QDBusArgument &operator<<(QDBusArgument &argument, const DBusMenuLayoutItem &);
DBUSMENU_EXPORT const QDBusArgument &operator>>(const QDBusArgument &argument, DBusMenuLayoutItem &);

typedef QList<DBusMenuLayoutItem> DBusMenuLayoutItemList;

Q_DECLARE_METATYPE(DBusMenuLayoutItemList)

void DBusMenuTypes_register();
#endif /* DBUSMENUTYPES_P_H */
