/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef COIN_SBSTRING_H
#define COIN_SBSTRING_H

#include <Inventor/system/inttypes.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbName.h>

#include <stdio.h>
#include <stdarg.h>

#define SB_STRING_STATIC_STORAGE_SIZE 128


class COIN_DLL_EXPORT SbString {
public:
  SbString(void);
  SbString(const char * str);
  SbString(const char * str, int start, int end);
  SbString(const SbString & str);
  SbString(const int digits);
  ~SbString();

  uint32_t hash(void);
  int getLength(void) const;
  void makeEmpty(SbBool freeold = TRUE);
  const char * getString(void) const;
  SbString getSubString(int startidx, int endidx = -1) const;
  void deleteSubString(int startidx, int endidx = -1);

  void addIntString(const int value);

  char operator [](int index) const;
  SbString & operator = (const char * str);
  SbString & operator = (const SbString & str);
  SbString & operator += (const char * str);
  SbString & operator += (const SbString & str);
  int operator ! (void) const;
  friend int operator == (const SbString & str, const char * s);
  friend int operator == (const char * s, const SbString & str);
  friend int operator == (const SbString & str1, const SbString & str2);
  friend int operator != (const SbString & str, const char * s);
  friend int operator != (const char * s, const SbString & str);
  friend int operator != (const SbString & str1, const SbString & str2);
  static uint32_t hash(const char * s);

  SbString & operator += (const char c);
  SbString & sprintf(const char * formatstr, ...);
  SbString & vsprintf(const char * formatstr, va_list args);

  void print(FILE * file = stdout) const;

private:
  char * sstring;
  int storagesize;
  char staticstorage[SB_STRING_STATIC_STORAGE_SIZE];
  void expand(int additional);
};

#endif // !COIN_SBSTRING_H
