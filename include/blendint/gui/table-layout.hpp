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

#pragma once

#include <blendint/gui/abstract-layout.hpp>

namespace BlendInt {

/**
 * @brief A special widget used in some layout. e.g. TableLayout
 */
class Cell: public AbstractWidget
{
public:

  Cell ();

  virtual ~Cell ();

  void SetWidget (AbstractWidget* widget);

  virtual bool IsExpandX () const;

  virtual bool IsExpandY () const;

  virtual Size GetPreferredSize () const;

protected:

  virtual void PerformSizeUpdate (const AbstractView* source,
                                  const AbstractView* target,
                                  int width,
                                  int height);

  virtual Response Draw (AbstractWindow* context);
};

// ------------------------------------

class TableLayout: public AbstractLayout
{
public:

  TableLayout (unsigned int row, unsigned int column, int space = 4);

  TableLayout (int width,
               int height,
               unsigned int row,
               unsigned int column,
               const Margin& margin,
               int space = 4);

  virtual ~TableLayout ();

  virtual AbstractWidget* AddWidget (AbstractWidget* widget);

  virtual AbstractWidget* InsertWidget (int index, AbstractWidget* widget);

  virtual AbstractWidget* InsertWidget (int row,
                                        int column,
                                        AbstractWidget* widget);

  virtual void Adjust ();

  void SetSpace (int space);

  virtual bool IsExpandX () const;

  virtual bool IsExpandY () const;

  virtual Size GetPreferredSize () const;

protected:

  virtual void PerformSizeUpdate (const AbstractView* source,
                                  const AbstractView* target,
                                  int width,
                                  int height);

  virtual void PerformMarginUpdate (const Margin& margin);

private:

  unsigned int row_;

  unsigned int column_;

  int space_;
};

}
