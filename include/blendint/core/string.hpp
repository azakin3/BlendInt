/*
 * This file is part of BlendInt (a Blender-like Interface Library in
 * OpenGL).
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is free
 * software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is
 * distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BlendInt.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#pragma once

#include <string>
#include <stdint.h>
#include <cwchar>

namespace BlendInt {

/**
 * @brief Strings
 *
 * @ingroup blendint_core
 */
class String: public std::u32string
{
 public:

  String ();

  String (const char* str);

  String (const wchar_t* str);

  String (const char* str, size_t n);

  String (const wchar_t* str, size_t n);

  String (const std::string& str);

  String (const std::wstring& str);

  String (const String& orig);

  String& operator = (const char* str);

  String& operator = (const wchar_t* str);

  String& operator = (const std::string& str);

  String& operator = (const std::wstring& str);

  String& operator = (const String& orig);

};

extern std::string ConvertFromString (const String& src);

}
