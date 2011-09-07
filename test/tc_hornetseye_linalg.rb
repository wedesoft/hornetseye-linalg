# hornetseye-hypercomplex - Linalg integration for Hornetseye
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

require 'test/unit'
begin
  require 'rubygems'
rescue LoadError
end
Kernel::require 'hornetseye_linalg'

class TC_Hornetseye_Linalg < Test::Unit::TestCase

  D = Hornetseye::DFLOAT
  S = Hornetseye::SFLOAT

  def M( *args )
    Hornetseye::MultiArray *args
  end

  def setup
    @m1 = M(D, 2)[[1, 2, 3], [4, 5, 6]]
    @m2 = M(S, 2)[[1, 2, 3], [4, 5, 6]]
  end

  def teardown
  end

  def test_to_dmatrix
    d = @m1.to_dmatrix
    for j in 0 ... @m1.shape[1]
      for i in 0 ... @m1.shape[0]
        assert_equal @m1[j][i], d[j, i]
      end
    end
    assert_equal @m1, d.to_multiarray
  end

  def test_to_smatrix
    s = @m2.to_smatrix
    for j in 0 ... @m2.shape[1]
      for i in 0 ... @m2.shape[0]
        assert_equal @m2[j][i], s[j, i]
      end
    end
    assert_equal @m2, s.to_multiarray
  end

end

