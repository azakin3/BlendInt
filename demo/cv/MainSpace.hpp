/**
 * Main Layout
 */

#ifndef _BLENDINT_DEMO_IMGPROC_MAIN_LAYOUT_HPP_
#define _BLENDINT_DEMO_IMGPROC_MAIN_LAYOUT_HPP_

#include <BlendInt/Gui/VLayout.hpp>

#include <BlendInt/Gui/MenuBar.hpp>
#include <BlendInt/Gui/ToolBar.hpp>
#include <BlendInt/Gui/Viewport3D.hpp>

#include <BlendInt/Gui/TextEntry.hpp>
#include <BlendInt/Gui/ToolButton.hpp>
#include <BlendInt/Gui/Expander.hpp>
#include <BlendInt/Gui/ToolBox.hpp>
#include <BlendInt/Gui/Tab.hpp>
#include <BlendInt/Gui/FileButton.hpp>
#include <BlendInt/Gui/ImageView.hpp>
#include <BlendInt/Gui/Label.hpp>

#include <BlendInt/Gui/ImagePlane2D.hpp>

#include <BlendInt/Gui/Workspace.hpp>

namespace BI = BlendInt;

class MainSpace: public BI::VLayout
{
public:

	MainSpace ();

	virtual ~MainSpace ();

protected:

	virtual void PerformSizeUpdate (const BI::SizeUpdateRequest& request);

	virtual BI::ResponseType Draw (BI::Profile& profile);

private:

	void RenderToBuffer (BI::Profile& profile);

	void InitOnce ();

	void OnResize (AbstractWidget* context, int type);

	BI::ToolBar* CreateToolBar ();

	// BI::ToolBox* CreateSideBox ();

	BI::Expander* CreateTransformExpander ();

	BI::Expander* CreateLightExpander ();

	BI::Expander* CreateColorExpander ();

	BI::ToolBar* CreateBottomBar ();

	BI::ToolBar* m_toolbar;

	BI::Workspace* workspace_;

	BI::Label* message_;

	BI::ImagePlane2D buffer_;
};

#endif