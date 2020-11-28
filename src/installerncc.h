/*
Copyright (C) 2012 Sebastian Herbord. All rights reserved.

This file is part of Mod Organizer.

Mod Organizer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mod Organizer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mod Organizer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INSTALLERNCC_H
#define INSTALLERNCC_H


#include <iplugininstallercustom.h>
#include <iplugindiagnose.h>

#include <QXmlStreamReader>


class InstallerNCC : public MOBase::IPluginInstallerCustom, public MOBase::IPluginDiagnose
{
  Q_OBJECT
  Q_INTERFACES(MOBase::IPlugin MOBase::IPluginInstaller MOBase::IPluginInstallerCustom MOBase::IPluginDiagnose)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  Q_PLUGIN_METADATA(IID "org.tannin.InstallerNCC" FILE "installerncc.json")
#endif

public:

  InstallerNCC();

public: // IPlugin

  virtual bool init(MOBase::IOrganizer *moInfo);
  virtual QString name() const override;
  virtual QString localizedName() const override;
  virtual QString author() const override;
  virtual QString description() const override;
  virtual MOBase::VersionInfo version() const override;
  virtual std::vector<std::shared_ptr<const MOBase::IPluginRequirement>> requirements() const override;
  virtual QList<MOBase::PluginSetting> settings() const override;

public: // IPluginInstaller

  virtual unsigned int priority() const override;
  virtual bool isManualInstaller() const override;
  virtual bool isArchiveSupported(std::shared_ptr<const MOBase::IFileTree> tree) const override;

public: // IPluginInstallerCustom

  virtual std::set<QString> supportedExtensions() const override;
  virtual bool isArchiveSupported(const QString &archiveName) const override;
  virtual EInstallResult install(MOBase::GuessedValue<QString> &modName, QString gameName, const QString &archiveName,
                                 const QString &version, int modID) override;

public: // IPluginDiagnose

  virtual std::vector<unsigned int> activeProblems() const override;
  virtual QString shortDescription(unsigned int key) const override;
  virtual QString fullDescription(unsigned int key) const override;
  virtual bool hasGuidedFix(unsigned int key) const override;
  virtual void startGuidedFix(unsigned int key) const override;

private:

  bool isNCCInstalled() const;
  bool isNCCCompatible() const;
  bool isDotNetInstalled() const;
  QString nccPath() const;
  std::wstring getSEVersion(const QString &seloader);

  IPluginInstaller::EInstallResult invokeNCC(MOBase::IModInterface *modInterface, const MOBase::IPluginGame *game, const QString &archiveName);

private:

  static const unsigned int COMPATIBLE_MAJOR_VERSION = 0x05;

  static const unsigned int PROBLEM_NCCMISSING = 1;
  static const unsigned int PROBLEM_NCCINCOMPATIBLE = 2;
  static const unsigned int PROBLEM_DOTNETINSTALLED = 3;

private:

  MOBase::IOrganizer *m_MOInfo;
  bool pluginShouldWork;
};

#endif // INSTALLERNCC_H
