# hornetseye-linalg - Linalg integration for Hornetseye
# Copyright (C) 2011 Jan Wedekind
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
module Hornetseye

  class Node

    alias_method :orig_to_dmatrix, :to_dmatrix

    def to_dmatrix
      source = to_dfloat.memorise
      retval = source.orig_to_dmatrix
      retval.instance_eval { @source = source }
      retval
    end

    alias_method :orig_to_smatrix, :to_smatrix

    def to_smatrix
      source = to_sfloat.memorise
      retval = source.orig_to_smatrix
      retval.instance_eval { @source = source }
      retval
    end

  end

end

