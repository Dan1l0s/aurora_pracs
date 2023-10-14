/****************************************************************************
**
** Copyright (C) 2021 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the PackageKitAdaptor project.
**
** $QT_BEGIN_LICENSE:BSD$
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of copyright holder nor the names of its contributors
**     may be used to endorse or promote products derived from this software
**     without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PKA_TYPES_H
#define PKA_TYPES_H

#include "global.h"
#include "bitfields.h"

PKA_NAMESPACE_BEGIN

enum class Filter : quint32
{
    Unknown        = 0x0000001,
    None           = 0x0000002,
    Installed      = 0x0000004,
    NotInstalled   = 0x0000008,
    Devel          = 0x0000010,
    NotDevel       = 0x0000020,
    Gui            = 0x0000040,
    NotGui         = 0x0000080,
    Free           = 0x0000100,
    NotFree        = 0x0000200,
    Visible        = 0x0000400,
    NotVisible     = 0x0000800,
    Supported      = 0x0001000,
    NotSupported   = 0x0002000,
    Basename       = 0x0004000,
    NotBasename    = 0x0008000,
    Newest         = 0x0010000,
    NotNewest      = 0x0020000,
    Arch           = 0x0040000,
    NotArch        = 0x0080000,
    Source         = 0x0100000,
    NotSource      = 0x0200000,
    Collections    = 0x0400000,
    NotCollections = 0x0800000,
    Application    = 0x1000000,
    NotApplication = 0x2000000,
    Downloaded     = 0x4000000,
    NotDownloaded  = 0x8000000,
    Last           = 0x10000000
};
DECLARE_FLAGS(Filters, Filter)

enum class Group : quint64
{
    Unknown,
    Accessibility,
    Accessories,
    AdminTools,
    Communication,
    DesktopGnome,
    DesktopKde,
    DesktopOther,
    DesktopXfce,
    Education,
    Fonts,
    Games,
    Graphics,
    Internet,
    Legacy,
    Localization,
    Maps,
    Multimedia,
    Network,
    Office,
    Other,
    PowerManagement,
    Programming,
    Publishing,
    Repos,
    Security,
    Servers,
    System,
    Virtualization,
    Science,
    Documentation,
    Electronics,
    Collections,
    Vendor,
    Newest
};
DECLARE_BITFIELDS(Groups, Group)

enum class Role : quint64
{
    Unknown,
    Cancel,
    DependsOn,
    GetDetails,
    GetFiles,
    GetPackages,
    GetRepoList,
    RequiredBy,
    GetUpdateDetail,
    GetUpdates,
    InstallFiles,
    InstallPackages,
    InstallSignature,
    RefreshCache,
    RemovePackages,
    RepoEnable,
    RepoSetData,
    Resolve,
    SearchDetails,
    SearchFile,
    SearchGroup,
    SearchName,
    UpdatePackages,
    WhatProvides,
    AcceptEula,
    DownloadPackages,
    GetDistroUpgrades,
    GetCategories,
    GetOldTransactions,
    RepairSystem,
    GetDetailsLocal,
    GetFilesLocal,
    RepoRemove,
    UpgradeSystem
};
DECLARE_BITFIELDS(Roles, Role)

enum class Network : quint32
{
    Unknown,
    Offline,
    Online,
    Wired,
    WiFi,
    Mobile
};

enum class Info : quint32
{
    Unknown,
    Installed,
    Available,
    Low,
    Enhancement,
    Normal,
    Bugfix,
    Important,
    Security,
    Blocked,
    Downloading,
    Updating,
    Installing,
    Removing,
    Cleanup,
    Obsoleting,
    CollectionInstalled,
    CollectionAvailable,
    Finished,
    Reinstalling,
    Downgrading,
    Preparing,
    Decompressing,
    Untrusted,
    Trusted,
    Unavailable
};

enum class Error : quint32
{
    Unknown,
    OutOfMemory,
    NoNetwork,
    NotSupported,
    InternalError,
    GpgFailure,
    PackageIdInvalid,
    PackageNotInstalled,
    PackageNotFound,
    PackageAlreadyInstalled,
    PackageDownloadFailed,
    GroupNotFound,
    GroupListInvalid,
    DepResolutionFailed,
    FilterInvalid,
    CreateThreadFailed,
    TransactionError,
    TransactionCancelled,
    NoCache,
    RepoNotFound,
    CannotRemoveSystemPackage,
    ProcessKill,
    FailedInitialization,
    FailedFinalise,
    FailedConfigParsing,
    CannotCancel,
    CannotGetLock,
    NoPackagesToUpdate,
    CannotWriteRepoConfig,
    LocalInstallFailed,
    BadGpgSignature,
    MissingGpgSignature,
    CannotInstallSourcePackage,
    RepoConfigurationError,
    NoLicenseAgreement,
    FileConflicts,
    PackageConflicts,
    RepoNotAvailable,
    InvalidPackageFile,
    PackageInstallBlocked,
    PackageCorrupt,
    AllPackagesAlreadyInstalled,
    FileNotFound,
    NoMoreMirrorsToTry,
    NoDistroUpgradeData,
    IncompatibleArchitecture,
    NoSpaceOnDevice,
    MediaChangeRequired,
    NotAuthorized,
    UpdateNotFound,
    CannotInstallRepoUnsigned,
    CannotUpdateRepoUnsigned,
    CannotGetFilelist,
    CannotGetRequires,
    CannotDisableRepository,
    RestrictedDownload,
    PackageFailedToConfigure,
    PackageFailedToBuild,
    PackageFailedToInstall,
    PackageFailedToRemove,
    UpdateFailedDueToRunningProcess,
    PackageDatabaseChanged,
    ProvideTypeNotSupported,
    InstallRootInvalid,
    CannotFetchSources,
    CancelledPriority,
    UnfinishedTransaction,
    LockRequired
};

enum class Exit : quint32
{
    Unknown,
    Success,
    Failed,
    Cancelled,
    KeyRequired,
    EulaRequired,
    Killed,
    MediaChangeRequired,
    NeedUntrusted,
    CancelledPriority,
    RepairRequired
};

class PKA_LIBRARY DaemonInfo final : public QVariantMap
{
public:
    DaemonInfo();
    DaemonInfo(const QVariantMap &details);

    QString backendAuthor() const;
    QString backendDescription() const;
    QString backendName() const;
    QString distroId() const;
    QStringList mimeTypes() const;
    QVersionNumber version() const;
    Network network() const;
    Filters filters() const;
    Groups groups() const;
    Roles roles() const;
    bool locked() const;
};

class PKA_LIBRARY PackageInfo final : public QVariantMap
{
public:
    PackageInfo();
    PackageInfo(const QVariantMap &details);

    QString packageId() const;
    QString description() const;
    QString summary() const;
    QString license() const;
    QString url() const;
    quint64 size() const;
    Group group() const;
};

PKA_NAMESPACE_END

#endif // PKA_TYPES_H
