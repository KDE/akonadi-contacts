/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "customfields_p.h"

CustomField::CustomField()
    : mType(TextType)
    , mScope(LocalScope)
{
}

CustomField::CustomField(const QString &key, const QString &title, Type type, Scope scope)
    : mKey(key)
    , mTitle(title)
    , mType(type)
    , mScope(scope)
{
}

CustomField CustomField::fromVariantMap(const QVariantMap &map, Scope scope)
{
    return CustomField(map.value(QLatin1String("key")).toString(),
                       map.value(QLatin1String("title")).toString(),
                       stringToType(map.value(QLatin1String("type")).toString()),
                       scope);
}

void CustomField::setKey(const QString &key)
{
    mKey = key;
}

QString CustomField::key() const
{
    return mKey;
}

void CustomField::setTitle(const QString &title)
{
    mTitle = title;
}

QString CustomField::title() const
{
    return mTitle;
}

void CustomField::setType(Type type)
{
    mType = type;
}

CustomField::Type CustomField::type() const
{
    return mType;
}

void CustomField::setScope(Scope scope)
{
    mScope = scope;
}

CustomField::Scope CustomField::scope() const
{
    return mScope;
}

void CustomField::setValue(const QString &value)
{
    mValue = value;
}

QString CustomField::value() const
{
    return mValue;
}

QVariantMap CustomField::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("key"), mKey);
    map.insert(QStringLiteral("title"), mTitle);
    map.insert(QStringLiteral("type"), typeToString(mType));

    return map;
}

CustomField::Type CustomField::stringToType(const QString &type)
{
    if (type == QLatin1String("text")) {
        return CustomField::TextType;
    }
    if (type == QLatin1String("numeric")) {
        return CustomField::NumericType;
    }
    if (type == QLatin1String("boolean")) {
        return CustomField::BooleanType;
    }
    if (type == QLatin1String("date")) {
        return CustomField::DateType;
    }
    if (type == QLatin1String("time")) {
        return CustomField::TimeType;
    }
    if (type == QLatin1String("datetime")) {
        return CustomField::DateTimeType;
    }
    if (type == QLatin1String("url")) {
        return CustomField::UrlType;
    }

    return CustomField::TextType;
}

QString CustomField::typeToString(CustomField::Type type)
{
    switch (type) {
    case CustomField::TextType:
    default:
        return QStringLiteral("text");
    case CustomField::NumericType:
        return QStringLiteral("numeric");
    case CustomField::BooleanType:
        return QStringLiteral("boolean");
    case CustomField::DateType:
        return QStringLiteral("date");
    case CustomField::TimeType:
        return QStringLiteral("time");
    case CustomField::DateTimeType:
        return QStringLiteral("datetime");
    case CustomField::UrlType:
        return QStringLiteral("url");
    }
}
