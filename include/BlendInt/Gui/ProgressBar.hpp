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

#ifndef _BLENDINT_GUI_PROGRESSBAR_HPP_
#define _BLENDINT_GUI_PROGRESSBAR_HPP_

#include <BlendInt/Gui/Widget.hpp>

namespace BlendInt {

	class ProgressBar: public Widget
	{
		DISALLOW_COPY_AND_ASSIGN(ProgressBar);

	public:

		ProgressBar (Orientation orientation = Horizontal);

		virtual ~ProgressBar ();

		virtual bool IsExpandX () const;

		virtual bool IsExpandY () const;

		virtual Size GetPreferredSize () const;

	protected:

		virtual ResponseType Draw (const RedrawEvent& event);

	private:

		GLuint m_vao[2];

		Orientation m_orientation;

		RefPtr<GLArrayBuffer> m_inner;
		RefPtr<GLArrayBuffer> m_outer;
	};

}


#endif /* _BLENDINT_GUI_PROGRESSBAR_HPP_ */
