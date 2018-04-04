#!/bin/bash
############################################################################
# This file is part of Grenache Command Line Interface.                    #
#                                                                          #
# Copyright (C) 2017, 2018 Davide Scola <davide@bitfinex.com>              #
#                                                                          #
# Licensed under the Apache License,  Version 2.0 (the "License"); you may #
# not use this file except in  compliance with the License. You may obtain #
# a copy of the License at                                                 #
#                                                                          #
#       http://www.apache.org/licenses/LICENSE-2.0                         #
#                                                                          #
# Unless  required by  applicable law  or agreed  to in  writing, software #
# distributed  under the  License  is  distributed on  an  "AS IS"  BASIS, #
# WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either  express  or #
# implied. See the License for the specific language governing permissions #
# and limitations under the License.                                       #
############################################################################

case "${1}" in
  '--reverse')
    [[ -f Makefile ]] && make maintainer-clean
    rm -rf build-aux/
    rm -f {aclocal.m4,config.h.in,configure,shtool}
    find . -type f -name 'Makefile.in' -print0 | xargs -r0 rm -f
  ;;
  * )
    autoreconf --force --install --include 'm4'
    [[ -x shtool ]] || shtoolize -q 'echo'
    [[ -d autom4te.cache ]] && rm -rf autom4te.cache
  ;;
esac
