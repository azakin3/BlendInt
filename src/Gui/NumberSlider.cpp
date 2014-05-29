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

#ifdef __UNIX__
#ifdef __APPLE__
#include <gl3.h>
#include <gl3ext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#endif  // __UNIX__

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <BlendInt/Gui/NumberSlider.hpp>
#include <BlendInt/Service/ShaderManager.hpp>
#include <BlendInt/Service/Theme.hpp>

namespace BlendInt {

	NumberSlider::NumberSlider (Orientation orientation)
	: AbstractSlider(orientation), m_vao(0)
	{
		InitOnce ();
	}

	NumberSlider::~NumberSlider ()
	{
		glDeleteVertexArrays(1, &m_vao);
	}

	bool NumberSlider::IsExpandX() const
	{
		return true;
	}
	
	void NumberSlider::UpdateSlider(const WidgetUpdateRequest& request)
	{

	}

	void NumberSlider::UpdateGeometry (const WidgetUpdateRequest& request)
	{
		switch (request.type()) {

			case WidgetSize: {
				const Size* size_p = static_cast<const Size*>(request.data());
				glBindVertexArray(m_vao);
				GenerateFormBuffer(*size_p, round_corner_type(),
								round_corner_radius(), m_inner_buffer.get(),
								m_outer_buffer.get(), 0);
				glBindVertexArray(0);
				Refresh();
				break;
			}

			case WidgetRoundCornerType: {
				const int* type_p = static_cast<const int*>(request.data());
				glBindVertexArray(m_vao);
				GenerateFormBuffer(size(), *type_p, round_corner_radius(),
								m_inner_buffer.get(), m_outer_buffer.get(), 0);
				glBindVertexArray(0);
				Refresh();
				break;
			}

			case WidgetRoundCornerRadius: {
				const float* radius_p =
								static_cast<const float*>(request.data());
				glBindVertexArray(m_vao);
				GenerateFormBuffer(size(), round_corner_type(), *radius_p,
								m_inner_buffer.get(), m_outer_buffer.get(), 0);
				glBindVertexArray(0);
				Refresh();
				break;
			}

			default:
				AbstractSlider::UpdateGeometry(request);
		}

	}
	
	ResponseType NumberSlider::Draw (const RedrawEvent& event)
	{
		glBindVertexArray(m_vao);

		RefPtr<GLSLProgram> program =
						ShaderManager::instance->default_triangle_program();
		program->Use();

		glm::vec3 pos((float) position().x(), (float) position().y(),
						(float) z());
		glm::mat4 mvp = glm::translate(event.projection_matrix() * event.view_matrix(), pos);

		program->SetUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(mvp));

		Theme* tm = Theme::instance;

		Color color = tm->number_slider().inner_sel;

		program->SetVertexAttrib4fv("Color", color.data());
		program->SetUniform1i("AA", 0);

		glEnableVertexAttribArray(0);

		DrawTriangleFan(0, m_inner_buffer.get());

		color = tm->number_slider().outline;
		program->SetVertexAttrib4fv("Color", color.data());
		program->SetUniform1i("AA", 1);

		DrawTriangleStrip(0, m_outer_buffer.get());

		glDisableVertexAttribArray(0);
		program->Reset();

		glBindVertexArray(0);

		return Accept;
	}

	void NumberSlider::InitOnce()
	{
		set_round_corner_type(RoundAll);
		set_round_corner_radius(10);
		set_size(90, 20);

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_inner_buffer.reset(new GLArrayBuffer);
		m_outer_buffer.reset(new GLArrayBuffer);

		GenerateFormBuffer(
						size(),
						round_corner_type(),
						round_corner_radius(),
						m_inner_buffer.get(),
						m_outer_buffer.get(),
						0);

		glBindVertexArray(0);
	}
}
