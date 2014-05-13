/**
 * Main Layout
 */

#include <BlendInt/Gui/Widget.hpp>
#include <BlendInt/Core/String.hpp>
#include <BlendInt/Gui/Menu.hpp>
#include <BlendInt/Service/StockItems.hpp>

#include "MainLayout.hpp"

MainLayout::MainLayout ()
	: m_view3d(0), m_ok(0)
{
	InitOnce();
}

MainLayout::~MainLayout ()
{

}

void MainLayout::InitOnce ()
{
	using namespace BI;

	m_view3d = Manage(new BI::Viewport3D);
	m_view3d->set_name("Viewport3D");
	m_view3d->Resize(630, 445);
	m_view3d->SetPosition(5, 30);

	m_ok = Manage(new BI::Button("OK"));
	m_ok->set_name("OK");
	m_ok->SetExpandX(false);

	Add(m_view3d);
	Add(m_ok);
}

void MainLayout::OnOpenClick()
{
}

void MainLayout::OnResize (AbstractWidget* context, int type)
{
	Resize(context->size());
}