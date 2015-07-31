/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "sdl2ffbeffect.h"
#include "globalsettings.h"
#include <QtWidgets/QMessageBox>

const QString SDL2FFBEffect::CAPTION("Invalid FFB parameter");

SDL_HapticEffect* SDL2FFBEffect::createFFstruct()
{
  SDL_HapticEffect* effect = new SDL_HapticEffect;
  if (effect == nullptr)
    return nullptr;

  memset(effect, 0, sizeof(SDL_HapticEffect));

  return effect;
}

bool SDL2FFBEffect::checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkBoundsInclusive(attackLength, 0, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Attack length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(attackLevel, 0, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Attack level must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(fadeLength, 0, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Fade length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(fadeLevel, 0, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Fade level must be within <0; 32767>");
    return false;
  }

  return true;
}

bool SDL2FFBEffect::checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkBoundsInclusive(params->direction, 0, 35999)) {
    QMessageBox::warning(nullptr, CAPTION, "Direction must be within <0; 35999)");
    return false;
  }

  if (!checkBoundsInclusive(params->replayLength, static_cast<int64_t>(0), static_cast<int64_t>(0x7FFF))) {
    QMessageBox::warning(nullptr, CAPTION, "Replay length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->replayDelay, 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Replay delay must be within <0; 65535>");
    return false;
  }

  return true;
}


