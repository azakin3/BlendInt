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

#include <GL/glew.h>

#include <BlendInt/ToggleButton.hpp>
#include <BlendInt/ShaderManager.hpp>
#include <BlendInt/Theme.hpp>

namespace BlendInt {

	ToggleButton::ToggleButton ()
			: AbstractButton()
	{
		set_checkable(true);
		set_round_type(RoundAll);
		resize(90, 25);
	}

	ToggleButton::ToggleButton (const String& text)
			: AbstractButton()
	{
		set_checkable(true);
		set_round_type(RoundAll);
		set_text(text);
	}

	ToggleButton::ToggleButton (AbstractWidget* parent)
			: AbstractButton(parent)
	{
		set_checkable(true);
		set_round_type(RoundAll);
		resize (90, 25);
	}

	ToggleButton::ToggleButton (const String& text, AbstractWidget* parent)
			: AbstractButton(parent)
	{
		set_checkable(true);
		set_round_type(RoundAll);
		set_text(text);
	}

	ToggleButton::~ToggleButton ()
	{

	}

	void ToggleButton::render ()
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslatef(position().x(), position().y(), z());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		ThemeManager* tm = ThemeManager::instance();

		// draw inner, simple fill
		if (m_status_hover) {
			if(m_status_checked) {
				glColor4ub(tm->themes()->regular.inner_sel.highlight_red(),
				        tm->themes()->regular.inner_sel.highlight_green(),
				        tm->themes()->regular.inner_sel.highlight_blue(),
				        tm->themes()->regular.inner_sel.a());
			} else {
				glColor4ub(tm->themes()->regular.inner.highlight_red(),
						tm->themes()->regular.inner.highlight_green(),
						tm->themes()->regular.inner.highlight_blue(),
						tm->themes()->regular.inner.a());
			}
		} else {
			if (m_status_checked) {
				glColor4ub(tm->themes()->regular.inner_sel.r(),
				        tm->themes()->regular.inner_sel.g(),
				        tm->themes()->regular.inner_sel.b(),
				        tm->themes()->regular.inner_sel.a());
			} else {
				glColor4ub(tm->themes()->regular.inner.r(),
				        tm->themes()->regular.inner.g(),
				        tm->themes()->regular.inner.b(),
				        tm->themes()->regular.inner.a());
			}
		}

		glbuffer()->select(WidgetBufferKeyInner);

		glbuffer()->bind();
		glVertexPointer(2, GL_FLOAT, 0, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_POLYGON, 0, glbuffer()->vertices());
		glDisableClientState(GL_VERTEX_ARRAY);
		glbuffer()->unbind();

		// draw outline
		glbuffer()->select(WidgetBufferKeyOuter);

		unsigned char tcol[4] = { themes()->regular.outline.r(),
		        themes()->regular.outline.g(),
		        themes()->regular.outline.b(),
		        themes()->regular.outline.a()};
		tcol[3] = tcol[3] / WIDGET_AA_JITTER;
		glbuffer()->bind();
		/* outline */
		glEnableClientState(GL_VERTEX_ARRAY);
		glColor4ubv(tcol);
		for (int j = 0; j < WIDGET_AA_JITTER; j++) {
			glTranslatef(jit[j][0], jit[j][1], 0.0f);
			glVertexPointer(2, GL_FLOAT, 0, 0);
			glDrawArrays(GL_QUAD_STRIP, 0, glbuffer()->vertices());
			glTranslatef(-jit[j][0], -jit[j][1], 0.0f);
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glbuffer()->unbind();

		if(emboss()) {
			glbuffer()->select(WidgetBufferKeyEmboss);
			glbuffer()->bind();
			glEnableClientState(GL_VERTEX_ARRAY);
			for (int j = 0; j < WIDGET_AA_JITTER; j++) {
				glTranslatef(jit[j][0], jit[j][1], 0.0f);
				glColor4f(1.0f, 1.0f, 1.0f, 0.02f);
				glVertexPointer(2, GL_FLOAT, 0, 0);
				glDrawArrays(GL_QUAD_STRIP, 0, glbuffer()->vertices());
				glTranslatef(-jit[j][0], -jit[j][1], 0.0f);
			}
			glDisableClientState(GL_VERTEX_ARRAY);
			glbuffer()->unbind();
		}

		FontCache::create(m_font)->print(
		        m_text_outline.left() + padding().left(),
		        padding().bottom() + std::abs(m_text_outline.bottom()), m_text);

		glDisable(GL_BLEND);

		glPopMatrix();
	}

}
