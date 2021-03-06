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

#include <iostream>
#include <boost/filesystem.hpp>

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

#include <blendint/core/types.hpp>

#include <blendint/opengl/opengl.hpp>
#include <blendint/opengl/gl-texture2d.hpp>

namespace BlendInt {

GLTexture2D::GLTexture2D ()
    : Object(),
      id_(0)
{

}

GLTexture2D::~GLTexture2D ()
{
  if(id_) {
    glDeleteTextures(1, &id_);
  }
}

GLint GLTexture2D::GetBaseLevel()
{
  return 0;
}

void GLTexture2D::SetBaseLevel (GLint level)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, level);
}

void GLTexture2D::SetImage (GLint level, GLint internalFormat, GLsizei width,
                            GLsizei height, GLint border, GLenum format, GLenum type,
                            const GLvoid* data)
{
  glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width,
               height, 0, format, type, data);
}

void GLTexture2D::SetSubImage (GLint level, GLint xoffset, GLint yoffset,
                               GLsizei width, GLsizei height, GLenum format, GLenum type,
                               const GLvoid* data)
{
  glTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, type, data);
}

void GLTexture2D::CopySubimage(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  glCopyTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, x, y, width, height);
}

void GLTexture2D::SetMinFilter (GLint filter)
{
  set_parameter(GL_TEXTURE_MIN_FILTER, filter);
}

void GLTexture2D::SetMagFilter (GLint filter)
{
  set_parameter(GL_TEXTURE_MAG_FILTER, filter);
}

void GLTexture2D::SetWrapMode (GLint s_mode, GLint t_mode)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_mode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_mode);
}

void GLTexture2D::SetWrapModeS (GLint mode)
{
  set_parameter(GL_TEXTURE_WRAP_S, mode);
}

void GLTexture2D::SetWrapModeT (GLint mode)
{
  set_parameter(GL_TEXTURE_WRAP_T, mode);
}

GLint GLTexture2D::GetWidth (GLint level) const
{
  GLint width = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D,
                           level,
                           GL_TEXTURE_WIDTH,
                           &width);

  return width;
}

GLint GLTexture2D::GetHeight (GLint level) const
{
  GLint height = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D,
                           level,
                           GL_TEXTURE_HEIGHT,
                           &height);

  return height;
}

Size GLTexture2D::GetSize(GLint level) const
{
  GLint width = 0;
  GLint height = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D,
                           level,
                           GL_TEXTURE_WIDTH,
                           &width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D,
                           level,
                           GL_TEXTURE_HEIGHT,
                           &height);

  return Size(width, height);
}

bool GLTexture2D::WriteToFile (const std::string& filename,
                               GLint level,
                               GLenum format,
                               GLenum type) const
{
  //if(!m_flag[2]) return false;

  using namespace boost;

  filesystem::path pathname (filename);

  if(filesystem::exists(pathname)) {
    if(filesystem::is_directory(pathname)) {
    }
    if(filesystem::is_regular_file(pathname)) {

    }

    std::cerr << "Warning: file \""
              << pathname
              << "\" exists, overwrite to this file!"
              << std::endl;
    //return false;
  } else {

  }

  GLint width = 0, height = 0;

  get_level_parameter(level, GL_TEXTURE_WIDTH, &width);
  get_level_parameter(level, GL_TEXTURE_HEIGHT, &height);

  // demo code
  unsigned char pixels[width * height * 4];

  glGetTexImage (GL_TEXTURE_2D, level, format, type, pixels);

  ImageOutput* out = ImageOutput::create(filename);
  if(!out)
    return false;

  ImageSpec spec (width, height, 4, TypeDesc::UINT8);
  out->open(filename, spec);
  out->write_image(TypeDesc::UINT8, pixels);
  out->close();
  delete out;

  return true;
}

GLuint GLTexture2D::GetTextureBinding()
{
  GLint tex = 0;

  glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);

  return static_cast<GLuint>(tex);
}

inline void GLTexture2D::set_parameter (GLenum name, GLint value)
{
  glTexParameteri(GL_TEXTURE_2D, name, value);
}

inline void GLTexture2D::set_parameter (GLenum name, GLfloat value)
{
  glTexParameterf(GL_TEXTURE_2D, name, value);
}

inline void GLTexture2D::get_parameter(GLenum pname, GLfloat* params) const
{
  glGetTexParameterfv(GL_TEXTURE_2D, pname, params);
}

inline void GLTexture2D::get_parameter(GLenum pname, GLint* params) const
{	
  glGetTexParameteriv(GL_TEXTURE_2D, pname, params);
}

inline void GLTexture2D::get_level_parameter(GLint level, GLenum pname, GLfloat* params) const
{	
  glGetTexLevelParameterfv(GL_TEXTURE_2D, level, pname, params);
}

inline void GLTexture2D::get_level_parameter(GLint level, GLenum pname, GLint* params) const
{	
  glGetTexLevelParameteriv(GL_TEXTURE_2D, level, pname, params);
}

}
