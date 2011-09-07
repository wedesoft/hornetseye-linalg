/* HornetsEye - Computer Vision with Ruby
   Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Jan Wedekind

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#include <algorithm>
#include <boost/shared_array.hpp>
#include "error.hh"
#include "rubytools.hh"
#include "dmatrix.hh"

using namespace std;

VALUE DMatrix::mModule = Qnil;

VALUE DMatrix::cRubyClass = Qnil;

VALUE DMatrix::registerRubyClass(VALUE module)
{
  mModule = module;
  cRubyClass = rb_define_class_under(module, "DMatrix", rb_cObject);
  // rb_define_method(cRubyClass, "to_dmatrix", RUBY_METHOD_FUNC(wrapToDMatrix), 0);
  return cRubyClass;
}

void DMatrix::deleteRubyObject(void *ptr)
{
  free((DMatrix *)ptr);
}


