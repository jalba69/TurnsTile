#ifndef __Interface_H__
#define __Interface_H__



//          TurnsTile 0.3.2 for AviSynth 2.5.x
//
//  Provides customizable mosaic and palette effects. Latest release
//  hosted at http://www.gyroshot.com/turnstile.htm
//
//          Copyright 2010, 2011, 2013 Robert Martens  robert.martens@gmail.com
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.



#include <Windows.h>
#if defined(TURNSTILE_HOST_AVISYNTH_26)
  // SEt's 32 bit 2.6.0 MT, March 9th, 2013
  // http://forum.doom9.org/showthread.php?t=148782
  #include "../include/avs/avisynth-260MT-x86.h"
#else
  // SEt's 32 bit 2.5.8 MT, July 12th, 2009
  // http://forum.doom9.org/showthread.php?t=148117
  #include "../include/avs/avisynth-258MT-x86.h"
#endif



#endif // __Interface_H__