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
  rb_define_method(cRubyClass, "to_multiarray", RUBY_METHOD_FUNC(wrapToMultiArray), 0);
  return cRubyClass;
}

void DMatrix::deleteRubyObject(void *ptr)
{
  free((DMatrix *)ptr);
}

VALUE DMatrix::wrapToMultiArray(VALUE rbSelf)
{
  VALUE rbRetVal = Qnil;
  try {
    VALUE mHornetseye = rb_define_module( "Hornetseye" );
    DMatrix_ *dmatrix;
    dataGetStruct(rbSelf, cRubyClass, DMatrix_, dmatrix);
    int width = dmatrix->hsize;
    int height = dmatrix->vsize;
    VALUE cMalloc = rb_define_class_under(mHornetseye, "Malloc", rb_cObject);
    VALUE rbMemory = Data_Wrap_Struct(cMalloc, 0, 0, dmatrix->data);
    rb_ivar_set(rbMemory, rb_intern("@size"), INT2NUM(width * height * sizeof(double)));
    VALUE rbTypecode = rb_const_get(mHornetseye, rb_intern("DFLOAT"));
    rbRetVal = rb_funcall(rb_const_get(mHornetseye, rb_intern("MultiArray")),
      rb_intern("import"), 4, rbTypecode, rbMemory, INT2NUM(height), INT2NUM(width));
  } catch( std::exception &e ) {
    rb_raise( rb_eRuntimeError, "%s", e.what() );
  };
  return rbRetVal;
}
