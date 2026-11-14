/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "abstractcontactformatter.h"
#include "abstractcontactgroupformatter.h"
#include "akonadi_contact_core_private_export.h"
#include "attributes/contactmetadataattribute_p.h"
#include "collectionfiltermodel_p.h"
#include "contactcompletionmodel_p.h"
#include "contactgroupmodel_p.h"
#include "contactparts.h"
#include "contactsfilterproxymodel.h"
#include "contactstreemodel.h"
#include "emailaddressselection.h"
#include "emailaddressselection_p.h"
#include "emailaddressselectionmodel.h"
#include "emailaddressselectionproxymodel_p.h"
#include "grantlee/contactgrantleewrapper.h"
#include "grantlee/grantleecontactformatter.h"
#include "grantlee/grantleecontactgroupformatter.h"
#include "grantlee/grantleeprint.h"
#include "job/contactgroupexpandjob.h"
#include "job/contactgroupsearchjob.h"
#include "job/contactsearchjob.h"
#include "leafextensionproxymodel_p.h"
#include "standardcontactformatter.h"
#include "standardcontactgroupformatter.h"
