/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2014 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

// mapnik
#if defined(HAVE_JPEG)
#include <mapnik/jpeg_io.hpp>
#endif

#include <mapnik/image_util_jpeg.hpp>
#include <mapnik/image_data.hpp>

// boost
#include <boost/tokenizer.hpp>

// stl
#include <string>
#include <iostream>

namespace mapnik
{

jpeg_saver::jpeg_saver(std::ostream & stream, std::string const& t):
    stream_(stream), t_(t) {}

void jpeg_saver::operator() (image_data_null const& image) const
{
    throw ImageWriterException("null images not supported");
}

template <typename T>
void jpeg_saver::operator() (T const& image) const
{
#if defined(HAVE_JPEG)
    int quality = 85;
    std::string val = t.substr(4);
    if (!val.empty())
    {
        if (!mapnik::util::string2int(val,quality) || quality < 0 || quality > 100)
        {
            throw ImageWriterException("invalid jpeg quality: '" + val + "'");
        }
    }
    save_as_jpeg(stream, quality, image);
#else
    throw ImageWriterException("jpeg output is not enabled in your build of Mapnik");
#endif
}

template void jpeg_saver::operator()<image_data_rgba8> (image_data_rgba8 const& image) const;
template void jpeg_saver::operator()<image_data_gray8> (image_data_gray8 const& image) const;
template void jpeg_saver::operator()<image_data_gray16> (image_data_gray16 const& image) const;
template void jpeg_saver::operator()<image_data_gray32f> (image_data_gray32f const& image) const;
template void jpeg_saver::operator()<image_view<image_data_rgba8>> (image_view<image_data_rgba8> const& image) const;
template void jpeg_saver::operator()<image_view<image_data_gray8>> (image_view<image_data_gray8> const& image) const;
template void jpeg_saver::operator()<image_view<image_data_gray16>> (image_view<image_data_gray16> const& image) const;
template void jpeg_saver::operator()<image_view<image_data_gray32f>> (image_view<image_data_gray32f> const& image) const;

} // end ns