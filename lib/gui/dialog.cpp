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

#include <glm/gtx/transform.hpp>

#include <blendint/core/rect.hpp>

#include <blendint/opengl/opengl.hpp>
#include <blendint/opengl/gl-framebuffer.hpp>

#include <blendint/gui/push-button.hpp>
#include <blendint/gui/close-button.hpp>
#include <blendint/gui/label.hpp>
#include <blendint/gui/separator.hpp>
#include <blendint/gui/linear-layout.hpp>

#include <blendint/gui/dialog.hpp>
#include <blendint/gui/abstract-window.hpp>

namespace BlendInt {

Dialog::Dialog (const String& title, AbstractLayout* layout, int flags)
    : AbstractDialog(flags), content_layout_(0), main_layout_(0)
{
  LinearLayout* title_layout = new LinearLayout(Horizontal);
  title_layout->SetMargin(Margin(0, 0, 0, 0));

  CloseButton* close_button = new CloseButton;
  close_button->clicked().connect(this,
                    &Dialog::OnCloseButtonClicked);
  Label* title_label = new Label(title, AlignCenter);

  title_layout->AddWidget(close_button);
  title_layout->AddWidget(title_label);

  LinearLayout* bottom_layout = 0;
  if (flags & (DialogButtonApply | DialogButtonOK)) {
    bottom_layout = new LinearLayout(Horizontal);
    bottom_layout->SetMargin(Margin(0, 0, 0, 0));
    Separator* sp = new Separator(true);
    bottom_layout->AddWidget(sp);
  }

  if (flags & DialogButtonApply) {
    PushButton* apply_button = new PushButton("Apply");
    bottom_layout->AddWidget(apply_button);
    apply_button->clicked().connect(this,
                      &Dialog::OnApplyButtonClicked);
  }

  if (flags & DialogButtonOK) {
    PushButton* ok_button = new PushButton("OK");
    bottom_layout->AddWidget(ok_button);
    ok_button->clicked().connect(this, &Dialog::OnOKButtonClicked);
  }

  main_layout_ = new LinearLayout(Vertical);

  if (layout == nullptr) {
    content_layout_ = new LinearLayout(Vertical);
  } else {
    content_layout_ = layout;
  }

  main_layout_->AddWidget(title_layout);
  main_layout_->AddWidget(content_layout_);
  main_layout_->AddWidget(bottom_layout);

  main_layout_->Resize(500, 400);

  PushBackSubView(main_layout_);

  set_round_type(RoundAll);
  set_round_radius(5.f);
  set_size(500, 400);
  set_refresh(true);
  EnableViewBuffer();

  projection_matrix_ = glm::ortho(0.f, (float) size().width(), 0.f,
                                  (float) size().height(), 100.f, -100.f);
  model_matrix_ = glm::mat3(1.f);

  std::vector<GLfloat> inner_verts;
  std::vector<GLfloat> outer_verts;

  if (AbstractWindow::theme()->dialog().shaded) {
    GenerateRoundedVertices(Vertical,
                            AbstractWindow::theme()->dialog().shadetop,
                            AbstractWindow::theme()->dialog().shadedown,
                            &inner_verts, &outer_verts);
  } else {
    GenerateRoundedVertices(&inner_verts, &outer_verts);
  }

  glGenVertexArrays(2, vao_);
  vbo_.generate();

  glBindVertexArray(vao_[0]);

  vbo_.bind(0);
  vbo_.set_data(sizeof(GLfloat) * inner_verts.size(), &inner_verts[0]);

  glEnableVertexAttribArray(AttributeCoord);
  glVertexAttribPointer(AttributeCoord, 3,
  GL_FLOAT,
                        GL_FALSE, 0, 0);

  glBindVertexArray(vao_[1]);

  vbo_.bind(1);
  vbo_.set_data(sizeof(GLfloat) * outer_verts.size(), &outer_verts[0]);
  glEnableVertexAttribArray(AttributeCoord);
  glVertexAttribPointer(AttributeCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

  shadow_.reset(new FrameShadow(size(), round_type(), round_radius()));
}

Dialog::~Dialog ()
{
  glDeleteVertexArrays(2, vao_);
}

AbstractWidget* Dialog::AddWidget (AbstractWidget* widget)
{
  if (content_layout_->AddWidget(widget)) {
    main_layout_->Adjust();
    return widget;
  }

  return 0;
}

AbstractWidget* Dialog::InsertWidget (int index, AbstractWidget* widget)
{
  if (content_layout_->InsertWidget(index, widget)) {
    main_layout_->Adjust();
    return widget;
  }

  return 0;
}

Size Dialog::GetPreferredSize () const
{
  return main_layout_->GetPreferredSize();
}

void Dialog::PerformSizeUpdate (const AbstractView* source,
                                const AbstractView* target,
                                int width,
                                int height)
{
  if (target == this) {

    set_size(width, height);

    projection_matrix_ = glm::ortho(0.f, 0.f + (float) size().width(), 0.f,
                                    0.f + (float) size().height(), 100.f,
                                    -100.f);

    if (view_buffer()) {
      view_buffer()->Resize(size());
    }

    shadow_->Resize(size());

    std::vector<GLfloat> inner_verts;
    std::vector<GLfloat> outer_verts;

    if (AbstractWindow::theme()->dialog().shaded) {
      GenerateRoundedVertices(Vertical,
                              AbstractWindow::theme()->dialog().shadetop,
                              AbstractWindow::theme()->dialog().shadedown,
                              &inner_verts, &outer_verts);
    } else {
      GenerateRoundedVertices(&inner_verts, &outer_verts);
    }

    vbo_.bind(0);
    vbo_.set_data(sizeof(GLfloat) * inner_verts.size(), &inner_verts[0]);
    vbo_.bind(1);
    vbo_.set_data(sizeof(GLfloat) * outer_verts.size(), &outer_verts[0]);
    vbo_.reset();

    ResizeSubView(main_layout_, size());

    RequestRedraw();
  }

  if (source == this) {
    report_size_update(source, target, width, height);
  }
}

bool Dialog::PreDraw (AbstractWindow* context)
{
  DeclareActiveFrame(context, this);

  if (refresh() && view_buffer()) {
    RenderToTexture(this, context, projection_matrix_, model_matrix_,
                             view_buffer()->texture());
  }

  return true;
}

Response Dialog::Draw (AbstractWindow* context)
{
  shadow_->Draw(position().x(), position().y());

  AbstractWindow::shaders()->frame_inner_program()->use();

  glUniform2f(
      AbstractWindow::shaders()->location(Shaders::FRAME_INNER_POSITION),
      position().x(), position().y());
  glUniform1i(AbstractWindow::shaders()->location(Shaders::FRAME_INNER_GAMMA),
              0);
  glUniform4fv(AbstractWindow::shaders()->location(Shaders::FRAME_INNER_COLOR),
               1, AbstractWindow::theme()->dialog().inner.data());

  glBindVertexArray(vao_[0]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, outline_vertex_count(round_type()) + 2);

  if (view_buffer()) {

    AbstractWindow::shaders()->frame_image_program()->use();

    glUniform2f(
        AbstractWindow::shaders()->location(Shaders::FRAME_IMAGE_POSITION),
        position().x(), position().y());
    glUniform1i(
        AbstractWindow::shaders()->location(Shaders::FRAME_IMAGE_TEXTURE), 0);
    glUniform1i(AbstractWindow::shaders()->location(Shaders::FRAME_IMAGE_GAMMA),
                0);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    view_buffer()->Draw(0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  } else {

    glViewport(position().x(), position().y(), size().width(), size().height());

    AbstractWindow::shaders()->SetWidgetProjectionMatrix(projection_matrix_);
    AbstractWindow::shaders()->SetWidgetModelMatrix(model_matrix_);

    DrawSubViewsOnce(context);

    glViewport(0, 0, context->size().width(), context->size().height());

  }

  AbstractWindow::shaders()->frame_outer_program()->use();

  glUniform2f(
      AbstractWindow::shaders()->location(Shaders::FRAME_OUTER_POSITION),
      position().x(), position().y());
  glUniform4fv(AbstractWindow::shaders()->location(Shaders::FRAME_OUTER_COLOR),
               1, AbstractWindow::theme()->dialog().outline.data());

  glBindVertexArray(vao_[1]);
  glDrawArrays(GL_TRIANGLE_STRIP, 0,
               outline_vertex_count(round_type()) * 2 + 2);

  return Finish;
}

void Dialog::OnCloseButtonClicked ()
{
  AbstractView* parent = super();
  //DBG_ASSERT(button == decoration_->close_button());
  Destroy(this);

  parent->RequestRedraw();
}

void Dialog::OnApplyButtonClicked ()
{
  fire_applied_event();
}

void Dialog::OnOKButtonClicked ()
{
  AbstractView* parent = super();
  fire_applied_event();

  Destroy(this);
  parent->RequestRedraw();
}

}
