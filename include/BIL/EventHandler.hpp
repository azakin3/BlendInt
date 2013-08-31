/*
 * This file is part of BIL (Blender Interface Library).
 *
 * BIL (Blender Interface Library) is free software: you can
 * redistribute it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * BIL (Blender Interface Library) is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BIL.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#ifndef _BIL_EVENTHANDLER_H_
#define _BIL_EVENTHANDLER_H_

#include <BIL/MouseEvent.hpp>
#include <BIL/KeyEvent.hpp>
#include <BIL/ContextMenuEvent.hpp>

namespace BIL {

	class Window;
	class AbstractLayout;
	class Interface;

	class EventHandler
	{
	public:

		friend class Window;
		friend class Interface;

		EventHandler () {}
		virtual ~EventHandler () {}

	protected:

		virtual void keyPressEvent (KeyEvent* event) = 0;

		virtual void contextMenuPressEvent (ContextMenuEvent* event) = 0;

		virtual void contextMenuReleaseEvent (ContextMenuEvent* event) = 0;

		virtual void mousePressEvent (MouseEvent* event) = 0;

		virtual void mouseReleaseEvent (MouseEvent* event) = 0;

		virtual void mouseMoveEvent (MouseEvent* event) = 0;

		virtual void render () = 0;
	};

} /* namespace BIL */
#endif /* _BIL_EVENTHANDLER_H_ */
