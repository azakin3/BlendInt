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

#ifndef _BLENDINT_INPUTEVENT_HPP_
#define _BLENDINT_INPUTEVENT_HPP_

#include <BlendInt/Window/Input.hpp>
#include <BlendInt/Window/DeviceEvent.hpp>

namespace BlendInt {

	/**
	 * @brief Events for input devices including keyboard, mouse
	 *
	 * @ingroup device_events
	 */
	class InputEvent: public DeviceEvent
	{
	public:
		
		/**
		 * @brief Default Constructor
		 * @param modifiers Bitwise conbination of KeyModifier
		 */
		InputEvent(int modifiers = ModifierNone)
			: m_modifiers(modifiers)
		{
		}

		virtual ~InputEvent()
		{
		}

		int modifiers () const {return m_modifiers;}

		void set_modifiers (int mods) {m_modifiers = mods;}

	protected:

		int m_modifiers;

	};

} /* namespace BlendInt */

#endif	/* _BIL_INPUTEVENT_H_ */