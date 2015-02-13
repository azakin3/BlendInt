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

#include <gui/abstract-decoration.hpp>
#include <gui/close-button.hpp>

namespace BlendInt {

	/**
	 * @brief A special widget used as a title/decoration of a dialog
	 */
	class Decoration:  public AbstractDecoration
	{
		DISALLOW_COPY_AND_ASSIGN(Decoration);

	public:

		Decoration ();

		Decoration (const String& title);

		virtual ~Decoration ();

		virtual bool IsExpandX () const;

		virtual bool IsExpandY () const;

		virtual Size GetPreferredSize () const;

	protected:

		virtual Response Draw (AbstractWindow* context);

	private:

		virtual void PerformSizeUpdate (const SizeUpdateRequest& request);

		void OnCloseButtonClicked (AbstractButton* button);

		CloseButton* close_button_;

	};

}
