# libdbusmenu-qtilities

[![CI]](https://github.com/qtilities/libdbusmenu-qtilities/actions/workflows/build.yml)

## Overview

This library provides a Qt implementation of the DBusMenu protocol.

The DBusMenu protocol makes it possible for applications to export and import their menus over DBus.

## Dependencies

### Runtime

- Qt5/6 base

### Build

- CMake
- Git (optional, to pull latest VCS checkouts)

## Documentation

By default documentation is generated with Doxygen.
You can disable documentation generation by passing `-D DBUSMENU_WITH_DOC=OFF` to CMake.

## Packages

[![Packages]](https://repology.org/project/libdbusmenu-qtilities/versions)

## Licenses

- DBusMenu is licensed under the [LGPL-2.0-or-later] license.


[CI]:                https://github.com/qtilities/libdbusmenu-qtilities/actions/workflows/build.yml/badge.svg
[LGPL-2.0-or-later]: COPYING
[Packages]:          https://repology.org/badge/vertical-allrepos/libdbusmenu-qtilities.svg
