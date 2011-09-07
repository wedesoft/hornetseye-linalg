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
#include "error.hh"
#include "rubytools.hh"
#include "dmatrix.hh"
#include "smatrix.hh"
#include "node.hh"

using namespace std;

VALUE Node::mModule = Qnil;

VALUE Node::cRubyClass = Qnil;

VALUE Node::registerRubyClass(VALUE module)
{
  mModule = module;
  cRubyClass = rb_define_class_under(module, "Node", rb_cObject);
  rb_define_method(cRubyClass, "to_dmatrix", RUBY_METHOD_FUNC(wrapToDMatrix), 0);
  rb_define_method(cRubyClass, "to_smatrix", RUBY_METHOD_FUNC(wrapToSMatrix), 0);
  return cRubyClass;
}

VALUE Node::wrapToDMatrix(VALUE rbSelf)
{
  VALUE rbRetVal = Qnil;
  try {
    VALUE rbMalloc = rb_funcall(rbSelf, rb_intern("memory"), 0);
    VALUE rbTypecode = rb_funcall(rbSelf, rb_intern("typecode"), 0);
    VALUE rbShape = rb_funcall(rbSelf, rb_intern("shape"), 0);
    Check_Type(rbShape, T_ARRAY);
    int rank = RARRAY_LEN(rbShape);
    ERRORMACRO(rank == 2, Error, ,
               "Array needs to have two dimensions for conversion to "
               "DMatrix (but had " << rank << " dimension(s))");
    int
      width = NUM2INT(RARRAY_PTR(rbShape)[0]),
      height = NUM2INT(RARRAY_PTR(rbShape)[1]);
    ERRORMACRO(rb_funcall(rbTypecode, rb_intern("=="), 1,
                          rb_const_get(mModule, rb_intern("DFLOAT"))) == Qtrue, Error, ,
	       "Element-type of array must be DFLOAT");
    VALUE cMalloc = rb_define_class_under(mModule, "Malloc", rb_cObject);
    unsigned char *source;
    dataGetStruct(rbMalloc, cMalloc, unsigned char, source);
    VALUE rbLinalg = rb_define_module("Linalg");
    DMatrix_ *dmatrix = (DMatrix_ *)ALLOC(DMatrix_);
    dmatrix->hsize = height;
    dmatrix->vsize = width;
    dmatrix->data = (double *)source;
    rbRetVal = Data_Wrap_Struct(DMatrix::cRubyClass, 0, DMatrix::deleteRubyObject, dmatrix);
  } catch ( std::exception &e ) {
    rb_raise( rb_eRuntimeError, "%s", e.what() );
  };
  return rbRetVal;
}

VALUE Node::wrapToSMatrix(VALUE rbSelf)
{
  VALUE rbRetVal = Qnil;
  try {
    VALUE rbMalloc = rb_funcall(rbSelf, rb_intern("memory"), 0);
    VALUE rbTypecode = rb_funcall(rbSelf, rb_intern("typecode"), 0);
    VALUE rbShape = rb_funcall(rbSelf, rb_intern("shape"), 0);
    Check_Type(rbShape, T_ARRAY);
    int rank = RARRAY_LEN(rbShape);
    ERRORMACRO(rank == 2, Error, ,
               "Array needs to have two dimensions for conversion to "
               "SMatrix (but had " << rank << " dimension(s))");
    int
      width = NUM2INT(RARRAY_PTR(rbShape)[0]),
      height = NUM2INT(RARRAY_PTR(rbShape)[1]);
    ERRORMACRO(rb_funcall(rbTypecode, rb_intern("=="), 1,
                          rb_const_get(mModule, rb_intern("SFLOAT"))) == Qtrue, Error, ,
	       "Element-type of array must be SFLOAT");
    VALUE cMalloc = rb_define_class_under(mModule, "Malloc", rb_cObject);
    unsigned char *source;
    dataGetStruct(rbMalloc, cMalloc, unsigned char, source);
    VALUE rbLinalg = rb_define_module("Linalg");
    SMatrix_ *smatrix = (SMatrix_ *)ALLOC(SMatrix_);
    smatrix->hsize = height;
    smatrix->vsize = width;
    smatrix->data = (float *)source;
    rbRetVal = Data_Wrap_Struct(SMatrix::cRubyClass, 0, SMatrix::deleteRubyObject, smatrix);
  } catch ( std::exception &e ) {
    rb_raise( rb_eRuntimeError, "%s", e.what() );
  };
  return rbRetVal;
}

