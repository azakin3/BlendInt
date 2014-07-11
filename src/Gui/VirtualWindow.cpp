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
 * License along with BlendInt.	 If not, see
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
#endif	// __UNIX__

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <BlendInt/Gui/VertexTool.hpp>
#include <BlendInt/Gui/VirtualWindow.hpp>
#include <BlendInt/Gui/Decoration.hpp>

#include <BlendInt/Stock/Shaders.hpp>
#include <BlendInt/Stock/Theme.hpp>

namespace BlendInt {

	VirtualWindow::VirtualWindow ()
	: AbstractVectorContainer(2)
	{
		set_round_corner_type(RoundTopLeft | RoundTopRight);
		set_round_corner_radius(10.f);
		set_size(400, 300);
		set_margin(0, 0, 0, 0);

		set_drop_shadow(true);

		InitializeVirtualWindow();
	}

	VirtualWindow::~VirtualWindow ()
	{
		glDeleteVertexArrays(1, m_vao);
	}

	void VirtualWindow::Setup (AbstractWidget* widget)
	{
		if(SetSubWidget(ContentIndex, widget)) {
			FillSubWidgets(position(), size());
		}
	}

	void VirtualWindow::UpdateContainer (
	        const ContainerUpdateRequest& request)
	{
	}

	bool VirtualWindow::UpdateGeometryTest (
	        const GeometryUpdateRequest& request)
	{
		return true;
	}

	void VirtualWindow::BroadcastUpdate (
	        const GeometryUpdateRequest& request)
	{
	}

	ResponseType VirtualWindow::Draw (const RedrawEvent& event)
	{
		using Stock::Shaders;

		RefPtr<GLSLProgram> program =
						Shaders::instance->default_triangle_program();
		program->Use();

		program->SetUniform3f("u_position", (float) position().x(), (float) position().y(), 0.f);
		program->SetUniform1i("u_gamma", 0);
		program->SetUniform1i("u_AA", 0);

		program->SetVertexAttrib4f("a_color", 0.447f, 0.447f, 0.447f, 1.f);

		glBindVertexArray(m_vao[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		glBindVertexArray(0);

		program->Reset();
		return Accept;
	}

	ResponseType VirtualWindow::FocusEvent (bool focus)
	{
		return Ignore;
	}

	ResponseType VirtualWindow::CursorEnterEvent (bool entered)
	{
		return Ignore;
	}

	ResponseType VirtualWindow::KeyPressEvent (const KeyEvent& event)
	{
		return Ignore;
	}

	ResponseType VirtualWindow::ContextMenuPressEvent (
	        const ContextMenuEvent& event)
	{
		return Ignore;
	}

	ResponseType BlendInt::VirtualWindow::ContextMenuReleaseEvent (
	        const ContextMenuEvent& event)
	{
		return Ignore;
	}

	ResponseType BlendInt::VirtualWindow::MousePressEvent (const MouseEvent& event)
	{
		return Ignore;
	}

	ResponseType BlendInt::VirtualWindow::MouseReleaseEvent (
	        const MouseEvent& event)
	{
		return Ignore;
	}

	ResponseType BlendInt::VirtualWindow::MouseMoveEvent (const MouseEvent& event)
	{
		return Ignore;
	}

	void VirtualWindow::UpdateGeometry (const GeometryUpdateRequest& request)
	{
		if(request.target() == this) {
			switch (request.type()) {

				case WidgetPosition: {

					const Point* pos_p = static_cast<const Point*>(request.data());

					int x = pos_p->x() - position().x();
					int y = pos_p->y() - position().y();

					MoveSubWidgets(x, y);

					set_position(*pos_p);

					Refresh();
					break;
				}

				case WidgetSize: {
					const Size* size_p =
					        static_cast<const Size*>(request.data());

					int h = size_p->height() - sub_widget(0)->size().height();
					if (h < 0) h = 0;

					Size vw_size (size_p->width(), h);
					VertexTool tool;
					tool.Setup(vw_size, 0, RoundNone, 0.f);

					m_inner->Bind();
					tool.SetInnerBufferData(m_inner.get());

					set_size(*size_p);

					FillSubWidgets(position(), *size_p);
					Refresh();
					break;
				}

				case WidgetRoundCornerType: {
					/*
					const int* type_p = static_cast<const int*>(request.data());
					VertexTool tool;
					tool.Setup(size(), DefaultBorderWidth(), *type_p,
					        round_corner_radius());
					m_inner->Bind();
					tool.SetInnerBufferData(m_inner.get());

					set_round_corner_type(*type_p);
					*/
					Refresh();
					break;
				}

				case WidgetRoundCornerRadius: {
					/*
					const float* radius_p =
					        static_cast<const float*>(request.data());

					VertexTool tool;
					tool.Setup(size(), DefaultBorderWidth(),
					        round_corner_type(), *radius_p);
					m_inner->Bind();
					tool.SetInnerBufferData(m_inner.get());

					set_round_corner_radius(*radius_p);
					*/
					Refresh();
					break;
				}

				default:
					break;
			}
		}

		ReportGeometryUpdate(request);
	}

	void VirtualWindow::FillSubWidgets(const Point& out_pos, const Size& size)
	{
		FillSubWidgets(out_pos.x(), out_pos.y(), size.width(), size.height());
	}

	void VirtualWindow::FillSubWidgets(int x, int y, int w, int h)
	{
		AbstractWidget* dec = sub_widget(DecorationIndex);
		AbstractWidget* content = sub_widget(ContentIndex);

		Size dec_prefer = dec->GetPreferredSize();

		y = y + h;

		if(content) {

			if(h > dec_prefer.height()) {
				ResizeSubWidget(dec, w, dec_prefer.height());
				ResizeSubWidget(content, w, h - dec_prefer.height());
			} else {
				ResizeSubWidget(dec, w, h);
				ResizeSubWidget(content, w, 0);
			}

			y = y - dec->size().height();
			SetSubWidgetPosition(dec, x, y);
			y = y - content->size().height();
			SetSubWidgetPosition(content, x, y);

		} else {

			if(h > dec_prefer.height()) {
				ResizeSubWidget(dec, w, dec_prefer.height());
			} else {
				ResizeSubWidget(dec, w, h);
			}

			y = y - dec->size().height();
			SetSubWidgetPosition(dec, x, y);

		}
	}

	void VirtualWindow::InitializeVirtualWindow ()
	{
		// set decoration
		Decoration* dec = Manage(new Decoration);
		DBG_SET_NAME(dec, "Decoration");
		SetSubWidget(DecorationIndex, dec);

		FillSubWidgets (position(), size());

		Size area_size(size().width(), size().height() - dec->size().height());

		VertexTool tool;
		tool.Setup (area_size, 0, RoundNone, 0.f);

		glGenVertexArrays(1, m_vao);
		glBindVertexArray(m_vao[0]);

		m_inner.reset(new GLArrayBuffer);
		m_inner->Generate();
		m_inner->Bind();
		tool.SetInnerBufferData(m_inner.get());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2,	GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
		GLArrayBuffer::Reset();
	}

}
