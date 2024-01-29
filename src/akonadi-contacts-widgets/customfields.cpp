/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
    return CustomField(map.value(QStringLiteral("key")).toString(),
                       map.value(QStringLiteral("title")).toString(),
                       stringToType(map.value(QStringLiteral("type")).toString()),
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
    if (type == QLatin1StringView("text")) {
        return CustomField::TextType;
    }
    if (type == QLatin1StringView("numeric")) {
        return CustomField::NumericType;
    }
    if (type == QLatin1StringView("boolean")) {
        return CustomField::BooleanType;
    }
    if (type == QLatin1StringView("date")) {
        return CustomField::DateType;
    }
    if (type == QLatin1StringView("time")) {
        return CustomField::TimeType;
    }
    if (type == QLatin1StringView("datetime")) {
        return CustomField::DateTimeType;
    }
    if (type == QLatin1StringView("url")) {
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
