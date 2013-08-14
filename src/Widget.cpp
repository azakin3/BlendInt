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

#include <GL/glew.h>
#include <GL/gl.h>

#include <BIL/Widget.h>

namespace BIL {

	Widget::Widget (Traceable *parent)
			: Drawable(parent)
	{
		// TODO Auto-generated constructor stub

		// Set the default padding and margin
		setPadding(Vec4i(1, 1, 1, 1));
		setMargin(Vec4i(1, 1, 1, 1));
	}

	Widget::~Widget ()
	{
		// TODO Auto-generated destructor stub
	}

	void Widget::KeyPressEvent (KeyEvent* event)
	{
	}

	void Widget::MousePressEvent (MouseEvent* event)
	{

	}

	void Widget::MouseReleaseEvent (MouseEvent* event)
	{

	}
/*
	void Widget::mouseEvent (MouseEvent* event)
	{
	}
*/
	void Widget::CharEvent (unsigned int character)
	{
	}

	void Widget::MouseButtonEvent (int button, int action, int modes)
	{
	}

	void Widget::CursorPosEvent (double xpos, double ypos)
	{
	}

	void Widget::CursorEnterEvent (int entered)
	{
	}

	void Widget::render (void)
	{

	}

} /* namespace BIL */
