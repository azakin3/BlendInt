/*
 * GLFWContext.cpp
 */

#include "CVContext.hpp"

#include <BlendInt/Gui/Screen.hpp>

using namespace BlendInt;

CVContext::CVContext()
: BI::Context(), m_layout(0)
{
	activate_events();

	m_layout = Manage (new MainSpace);
	m_layout->Resize(size());

	Screen* screen = Manage(new Screen);
	screen->Resize(m_layout->size());
	screen->Setup(m_layout);

	AddScreen(screen);

	events()->connect(resized(), this , &CVContext::OnResizeLayout);
}

CVContext::~CVContext ()
{

}

void CVContext::OnResizeLayout(const BI::Size& size)
{
	m_layout->Resize(size);
}
