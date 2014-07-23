/*
 * This file is part of BlendInt (a Blender-like Interface Library in
 * OpenGL).
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is free software:
 * you can redistribute it and/or modify it under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BlendInt.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#ifdef __UNIX__
#ifdef __APPLE__
#include <gl3.h>
#include <gl3ext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#endif  // __UNIX__

#include <algorithm>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <BlendInt/Gui/VertexTool.hpp>
#include <BlendInt/Gui/AbstractSlider.hpp>
#include <BlendInt/Stock/Theme.hpp>
#include <BlendInt/Stock/Shaders.hpp>

namespace BlendInt {

	using Stock::Shaders;

	SlideIcon::SlideIcon ()
	: AbstractRoundForm(), m_highlight(false)
	{
		set_size(14, 14);
		set_round_type(RoundAll);
		set_radius(7.0);

		InitializeSliderIcon();
	}

	SlideIcon::~SlideIcon ()
	{
		glDeleteVertexArrays(2, m_vao);
	}

	void SlideIcon::UpdateGeometry (const UpdateRequest& request)
	{
		switch (request.type()) {

			case FormSize: {
				const Size* size_p = static_cast<const Size*>(request.data());
				Orientation shadedir =
								size_p->width() < size_p->height() ?
												Horizontal : Vertical;
				const Color& color = Theme::instance->scroll().item;
				short shadetop = Theme::instance->scroll().shadetop;
				short shadedown = Theme::instance->scroll().shadedown;

				VertexTool tool;
				tool.Setup(*size_p, DefaultBorderWidth(), round_type(), radius(), color, shadedir, shadetop, shadedown);
				m_inner_buffer->Bind();
				tool.SetInnerBufferData(m_inner_buffer.get());
				m_outer_buffer->Bind();
				tool.SetOuterBufferData(m_outer_buffer.get());
				GLArrayBuffer::Reset();
				break;
			}

			case FormRoundType: {
				Orientation shadedir =
								size().width() < size().height() ?
												Horizontal : Vertical;
				const int* round_p =
								static_cast<const int*>(request.data());
				const Color& color = Theme::instance->scroll().item;
				short shadetop = Theme::instance->scroll().shadetop;
				short shadedown = Theme::instance->scroll().shadedown;

				VertexTool tool;
				tool.Setup(size(), DefaultBorderWidth(), *round_p, radius(), color, shadedir, shadetop, shadedown);
				m_inner_buffer->Bind();
				tool.SetInnerBufferData(m_inner_buffer.get());
				m_outer_buffer->Bind();
				tool.SetOuterBufferData(m_outer_buffer.get());
				GLArrayBuffer::Reset();
				break;
			}

			case FormRoundRadius: {
				Orientation shadedir =
								size().width() < size().height() ?
												Horizontal : Vertical;
				const float* radius_p =
								static_cast<const float*>(request.data());
				const Color& color = Theme::instance->scroll().item;
				short shadetop = Theme::instance->scroll().shadetop;
				short shadedown = Theme::instance->scroll().shadedown;

				VertexTool tool;
				tool.Setup(size(), DefaultBorderWidth(), round_type(), *radius_p, color, shadedir, shadetop, shadedown);
				m_inner_buffer->Bind();
				tool.SetInnerBufferData(m_inner_buffer.get());
				m_outer_buffer->Bind();
				tool.SetOuterBufferData(m_outer_buffer.get());
				GLArrayBuffer::Reset();
				break;
			}

			default:
				break;
		}

	}

	void SlideIcon::Draw (const glm::vec3& pos, short gamma)
	{
		RefPtr<GLSLProgram> program =
						Shaders::instance->triangle_program();
		program->Use();

		glUniform3f(Shaders::instance->triangle_uniform_position(), pos.x, pos.y, 0.f);

		if (m_highlight) {
			glUniform1i(Shaders::instance->triangle_uniform_gamma(), 15);
		} else {
			glUniform1i(Shaders::instance->triangle_uniform_gamma(), 0);
		}

		glUniform1i(Shaders::instance->triangle_uniform_antialias(), 0);

		glBindVertexArray(m_vao[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, GetOutlineVertices(round_type()) + 2);

		glUniform1i(Shaders::instance->triangle_uniform_gamma(), 0);
		glUniform1i(Shaders::instance->triangle_uniform_antialias(), 1);
		glVertexAttrib4fv(Shaders::instance->triangle_attrib_color(), Theme::instance->scroll().outline.data());

		glBindVertexArray(m_vao[1]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, GetOutlineVertices(round_type()) * 2 + 2);

		glBindVertexArray(0);
		program->Reset();
	}

	void SlideIcon::InitializeSliderIcon ()
	{
		glGenVertexArrays(2, m_vao);

		Orientation shadedir =
						size().width() < size().height() ?
										Horizontal : Vertical;
		const Color& color = Theme::instance->scroll().item;
		short shadetop = Theme::instance->scroll().shadetop;
		short shadedown = Theme::instance->scroll().shadedown;

		VertexTool tool;
		tool.Setup(size(), DefaultBorderWidth(), round_type(), radius(), color, shadedir, shadetop, shadedown);

		glBindVertexArray(m_vao[0]);
		m_inner_buffer.reset(new GLArrayBuffer);
		m_inner_buffer->Generate();
		m_inner_buffer->Bind();
		tool.SetInnerBufferData(m_inner_buffer.get());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, BUFFER_OFFSET(0));

		glVertexAttribPointer(1, 4,	GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, BUFFER_OFFSET(2 * sizeof(GLfloat)));

		glBindVertexArray(m_vao[1]);
		m_outer_buffer.reset(new GLArrayBuffer);
		m_outer_buffer->Generate();
		m_outer_buffer->Bind();
		tool.SetOuterBufferData(m_outer_buffer.get());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
		GLArrayBuffer::Reset();
	}

}
