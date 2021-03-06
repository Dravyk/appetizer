/*
  Copyright (C) 2008-2010 Laurent Cozic. All right reserved.
  Use of this source code is governed by a GNU/GPL license that can be
  found in the LICENSE file.
*/

#include <stable.h>

#ifndef Appetizer_UserSettings_H
#define Appetizer_UserSettings_H


namespace appetizer {



typedef std::vector<std::pair<QString, QString>> UserSettingOptions;


class UserSetting: public QObject {

  Q_OBJECT
  
public:

  enum ControlType {
    Undefined,
    CheckBox,
    TextBox,
    SpinBox,
    ComboBox,
    FileSelector,
    FolderSelector
  };

  UserSetting(const QString& name);

  inline QString name() const { return name_; }
  inline QVariant value() const { return value_; }
  inline QString label() const { return label_; }
  inline QString group() const { return group_; }
  inline int minValue() const { return minValue_; }
  inline int maxValue() const { return maxValue_; }
  ControlType controlType() const;
  inline UserSettingOptions options() const { return options_; }

  void setValue(const QVariant& variant);
  void setLabel(const QString& label);
  void setGroup(const QString& group);
  void setControlType(UserSetting::ControlType type);
  void setOptions(const UserSettingOptions& options);
  void setMinValue(int v);
  void setMaxValue(int v);

signals:

  void valueChanged();

private:

  QString name_;
  QVariant value_;
  QString label_;
  QString group_;
  ControlType controlType_;
  UserSettingOptions options_;
  int minValue_;
  int maxValue_;

};


typedef std::map<QString, UserSetting*> UserSettingsMap;
typedef std::vector<UserSetting*> UserSettingsVector;

class UserSettings: public QObject {

  Q_OBJECT

public:

  static UserSettings* instance();
  static void destroyInstance();

  UserSettings();
  ~UserSettings();

  void Save();
  void Load();

  TiXmlElement* ToXml();
  void FromXml(TiXmlElement* xml);

  UserSetting* getSetting(const QString& name) const;
  
  QVariant::Type getSettingType(const QString& name) const;
  QString typeToString(QVariant::Type type) const;

  int getInt(const QString& name) const;
  QString getString(const QString& name) const;
  bool getBool(const QString& name) const;
  QDateTime getDateTime(const QString& name) const;
  QColor getColor(const QString& name) const;

  UserSetting* setSetting(const QString& name, const QVariant& variant);
  UserSetting* setInt(const QString& name, int value);
  UserSetting* setString(const QString& name, const QString& value);
  UserSetting* setBool(const QString& name, bool value);
  UserSetting* setDateTime(const QString& name, const QDateTime& dateTime);
  UserSetting* setColor(const QString& name, const QColor& color);

  std::vector<QString> getGroupLabels() const;
  QString getGroupLabelAt(int index) const;
  UserSettingsVector getSettingsByGroup(const QString& groupName);  

  inline UserSettingsMap settings() const { return settings_; }

signals:

  void settingChanged(UserSetting* setting);

private:

  void AppendSettingToXml_(TiXmlElement* element, const char* name, const char* value, int type);

  mutable UserSettingsMap settings_;
  static UserSettings* instance_;

private slots:

  void setting_valueChanged();

};

}

#endif // __UserSettings_H