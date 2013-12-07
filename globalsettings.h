#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

class GlobalSettings {
public:
  static void init(bool doSanityChecks);
  static const GlobalSettings* GS();
  explicit GlobalSettings();
  ~GlobalSettings();

  bool doSanityChecks;

private:
  static GlobalSettings* s_instance;
};

#endif // GLOBALSETTINGS_H
