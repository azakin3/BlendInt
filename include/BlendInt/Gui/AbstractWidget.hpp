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

#ifndef _BLENDINT_GUI_ABSTRACTWIDGET_HPP_
#define _BLENDINT_GUI_ABSTRACTWIDGET_HPP_

#include <bitset>

#include <boost/smart_ptr.hpp>

#include <BlendInt/Types.hpp>
#include <BlendInt/Core/Point.hpp>
#include <BlendInt/Core/Size.hpp>

#include <BlendInt/Core/RefPtr.hpp>
#include <BlendInt/Window/MouseEvent.hpp>
#include <BlendInt/Window/KeyEvent.hpp>
#include <BlendInt/Window/ContextMenuEvent.hpp>
#include <BlendInt/Window/RedrawEvent.hpp>

#include <BlendInt/Gui/AbstractExtraForm.hpp>

#include <Cpp/Events.hpp>

#ifdef DEBUG
#include <map>
using std::map;
#endif

namespace BlendInt {

	class ContextManager;
	class AbstractWidget;
	class Rect;
	class GLTexture2D;

	struct WidgetTheme;

	typedef RefPtr<AbstractWidget> AbstractWidgetPtr;

	template<typename T>
	T* Manage (T* obj, bool val = true)
	{
		obj->set_manage(val);
		return obj;
	}

	/**
	 * @brief The base abstract class for widgets
	 *
	 * @ingroup gui
	 */
	class AbstractWidget: public AbstractExtraForm
	{
		DISALLOW_COPY_AND_ASSIGN(AbstractWidget);

	public:

		friend class ContextManager;
		friend class Interface;
		friend class AbstractContainer;

		template <typename T> friend T* Manage (T* obj, bool val);

		/**
		 * @brief The default constructor
		 */
		AbstractWidget ();

		/**
		 * @brief Destructor
		 */
		virtual ~AbstractWidget ();

		/**
		 * @brief Resize the widget
		 * @param[in] width The new width of the widget
		 * @param[in] height The new height of the widget
		 *
		 * Call Update() to check the parameters, if valid, resize the
		 * widget.
		 */
		void Resize (unsigned int width, unsigned int height);

		/**
		 * @brief Resize the widget
		 * @param[in] size The new size of the widget
		 *
		 * Call Update() to check the parameters, if valid, resize the
		 * widget.
		 */
		void Resize (const Size& size);

		/**
		 * @brief Get the widget size
		 * @return
		 * 	- The size of widget
		 * 	- (0, 0) if the widget is hiden
		 */
		const Size& GetVisibleSize () const;

		const Size& GetVisiblePreferredSize () const;

		const Size& GetVisibleMinimalSize () const;

		const Size& GetVisibleMaximalSize () const;

		void SetPosition (int x, int y);

		void SetPosition (const Point& pos);

		void SetPreferredSize (unsigned int widt, unsigned int height);

		void SetPreferredSize (const Size& size);

		void SetMinimalSize (unsigned int width, unsigned int height);

		void SetMinimalSize (const Size& size);

		void SetMaximalSize (unsigned int width, unsigned int height);

		void SetMaximalSize (const Size& size);

		void SetLayer (int z);

		void SetVisible (bool visible);

		void Refresh ();

		void RenderToFile (const char* filename, unsigned int border = 10);

		const int& layer () const
		{
			return m_z;
		}

		const int& z () const
		{
			return m_z;
		}

		inline bool locked () const
		{
			return m_flag[WidgetFlagLockGeometry];
		}

		inline bool in_context_manager() const
		{
			return m_flag[WidgetFlagInContextManager];
		}

		inline bool in_container () const
		{
			return m_flag[WidgetFlagInContainer];
		}

		void activate_events ()
		{
			m_flag.set(WidgetFlagFireEvents);
		}

		void deactivate_events ()
		{
			m_flag.reset(WidgetFlagFireEvents);
		}

		bool fire_events () const
		{
			return m_flag[WidgetFlagFireEvents];
		}

		inline bool focused () const
		{
			return m_flag[WidgetFlagFocus];
		}

		inline bool hover () const
		{
			return m_flag[WidgetFlagContextHoverList];
		}

		inline bool visiable () const
		{
			return m_flag[WidgetFlagVisibility];
		}

		inline bool managed () const
		{
			return m_flag[WidgetFlagManaged];
		}

		/**
		 * @brief move this object along x axis
		 * @param offset_x
		 */
		inline void move_x (int offset_x)
		{
			SetPosition(position().x() + offset_x, position().y());
		}

		/**
		 * @brief move this object along y axis
		 * @param offset_y
		 */
		inline void move_y (int offset_y)
		{
			SetPosition(position().x(), position().y() + offset_y);
		}

		/**
		 * @brief move this object
		 * @param offset_x
		 * @param offset_y
		 */
		inline void move (int offset_x, int offset_y)
		{
			SetPosition(position().x() + offset_x, position().y() + offset_y);
		}

		Cpp::EventRef<AbstractWidget*, int> property_changed() {return m_property_changed;}

		Cpp::EventRef<AbstractWidget*> destroyed () {return m_destroyed;}

		AbstractWidget* container() const {return m_container;}

	protected:	// member functions

		virtual void CursorEnterEvent (bool entered) = 0;

		virtual void KeyPressEvent (KeyEvent* event) = 0;

		virtual void ContextMenuPressEvent (ContextMenuEvent* event) = 0;

		virtual void ContextMenuReleaseEvent (ContextMenuEvent* event) = 0;

		virtual void MousePressEvent (MouseEvent* event) = 0;

		virtual void MouseReleaseEvent (MouseEvent* event) = 0;

		virtual void MouseMoveEvent (MouseEvent* event) = 0;

		/**
		 * @brief Update opengl data (usually the GL buffer) for Render
		 * @param[in] type the enumeration defined by each form class, e.g.
		 * FormPropertySize
		 * @param[in] data the pointer to the new property data
		 *
		 * This virtual function should be implemented in each derived class,
		 * and should only use the form's property to draw opengl elements once.
		 */
		virtual bool Update (const UpdateRequest& request) = 0;

		virtual void Draw (RedrawEvent* event) = 0;

		void LockGeometry (AbstractWidget* obj, bool status)
		{
			obj->m_flag[WidgetFlagLockGeometry] = status ? 1 : 0;
		}

		Cpp::ConnectionScope* events() const {return m_events.get();}

		/**
		 * @brief fire event to inform the property of this object is changed
		 * @param[in] type the property type, defined in FormPropertyType
		 */
		inline void fire_property_changed_event (int type)
		{
			if (m_flag[WidgetFlagFireEvents])
				m_property_changed.fire(this, type);
		}

		static void SetPosition (AbstractWidget* obj, int x, int y);

		static void SetPosition (AbstractWidget* obj, const Point& pos);

		/**
		 * @brief resize other object's size
		 * @param obj
		 * @param w
		 * @param h
		 *
		 * @note should be used in layout only
		 */
		static void Resize (AbstractWidget* obj, unsigned int w, unsigned int h);

		/**
		 * @brief resize other object's size
		 * @param obj
		 * @param size
		 *
		 * @note should be used in layout only
		 */
		static void Resize (AbstractWidget* obj, const Size& size);

		static void DispatchRender (AbstractWidget* obj);

		static void dispatch_key_press_event (AbstractWidget* obj, KeyEvent* event);

		static void dispatch_mouse_move_event (AbstractWidget* obj, MouseEvent* event);

		static void dispatch_mouse_press_event (AbstractWidget* obj, MouseEvent* event);

		static void dispatch_mouse_release_event (AbstractWidget* obj, MouseEvent* event);

	private:

		enum WidgetFlagIndex {
			WidgetFlagLockGeometry = 0,
			WidgetFlagFireEvents,
			WidgetFlagInContextManager,
			WidgetFlagFocus,

			/** If this widget is in container */
			WidgetFlagInContainer,

			/** If this widget is in cursor hover list in ContextManager */
			WidgetFlagContextHoverList,

			/** If the widget need to be refresh in the render loop */
			WidgetFlagRefresh,

			WidgetFlagVisibility,

			WidgetFlagManaged
		};

		void set_manage (bool val)
		{
			m_flag[WidgetFlagManaged] = val ? 1 : 0;
		}

		/**
		 * @brief Used in Interface class to render the widget to a screenbuffer
		 * @param tex
		 * @param border
		 */
		bool CompositeToScreenBuffer (GLTexture2D* tex, unsigned int border = 0);

		/**
		 * @brief the depth(layer) of the widget
		 */
		int m_z;

		/**
		 * @brief The bit flag of this widget
		 *
		 * - bit 0: lock geometry
		 * - bit 1: fire events
		 * - bit 2: registered in context manager
		 */
		std::bitset<32> m_flag;

		boost::scoped_ptr<Cpp::ConnectionScope> m_events;

		Cpp::Event<AbstractWidget*, int> m_property_changed;

		Cpp::Event<AbstractWidget*> m_destroyed;

		AbstractWidget* m_container;

		/**
		 * The size for hiden widget, always should be (0, 0), use static for performance
		 */
		static Size invisible_size;

		static AbstractWidget* focused_widget;

#ifdef DEBUG
	public:

		inline void lock (bool status)
		{
			m_flag[0] = status ? 1 : 0;
		}

#endif
	};

} /* namespace BlendInt */
#endif /* _BLENDINT_GUI_ABSTRACTWIDGET_HPP_ */