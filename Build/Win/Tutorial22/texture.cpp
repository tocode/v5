/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "texture.h"

static float tex_data[]=
{
	255,	0,		0,		1,
	0,		255,	0,		1,
	0,		0,		255,	1,
	255,	255,	0,		1,
};

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    tx_target = TextureTarget;
	tx_name = FileName;
	//m_textureTarget = TextureTarget;
    //m_fileName      = FileName;
//    m_pImage        = NULL;
}

bool Texture::Load()
{
	glGenTextures(1,&tx_id);
	glBindTexture(tx_target,tx_id);
	glTexImage2D(tx_target,0,GL_RGBA,2,2,0,GL_RGBA,GL_FLOAT,tex_data);
	glTexParameterf(tx_target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(tx_target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	/*
    try {
        m_pImage = new Magick::Image(m_fileName);
        m_pImage->write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(tx_target,tx_id);
}
