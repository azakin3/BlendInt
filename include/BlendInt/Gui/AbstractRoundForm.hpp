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

#ifndef _BLENDINT_ABSTRACTROUNDFORM_HPP_
#define _BLENDINT_ABSTRACTROUNDFORM_HPP_

#include <BlendInt/Gui/AbstractForm.hpp>

namespace BlendInt {

	class AbstractRoundForm: public AbstractForm
	{
	public:

		AbstractRoundForm();

		virtual ~AbstractRoundForm();

		void SetRoundType (int type);

		void SetRadius (float radius);

		int round_type () const {return m_round_type;}

		float radius () const {return m_radius;}

		static int GetOutlineVertices (int round_type);

	protected:

		void set_round_type (int type)
		{
			m_round_type = type;
		}

		void set_radius (float radius)
		{
			m_radius = radius;
		}

	private:

		int m_round_type;

		float m_radius;
	};

}

#endif /* _BLENDINT_ABSTRACTROUNDFORM_HPP_ */
