#include "globalsettings.h"

GlobalSettings* GlobalSettings::s_instance(nullptr);

void GlobalSettings::init(bool doSanityChecks)
{
  if (s_instance == nullptr) {
    s_instance = new GlobalSettings;

    s_instance->doSanityChecks = doSanityChecks;
  }
}

const GlobalSettings* GlobalSettings::GS() {
  return s_instance;
}

GlobalSettings::GlobalSettings()
{}

GlobalSettings::~GlobalSettings()
{
  delete s_instance;
  s_instance = nullptr;
}
