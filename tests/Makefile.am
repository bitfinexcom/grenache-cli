############################################################################
# This file is part of Grenache Command Line Interface.                    #
#                                                                          #
# Copyright (C) 2017-2021 Davide Scola <davide@bitfinex.com>               #
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

AM_TESTS_ENVIRONMENT = \
  export \
        AWK='$(AWK)' \
        EGREP='$(EGREP)' \
        GRENACHE_SIGN='$(abs_top_builddir)/src/grc-sign' \
        GRENACHE_VERIFY='$(abs_top_builddir)/src/grc-verify' \
        GRENACHE_KEYGEN='$(abs_top_builddir)/src/grc-keygen' \
  ;

TESTS = \
sign-test-vector-1.sh \
sign-test-vector-2.sh \
verify-test-vector-1.sh \
verify-test-vector-2.sh

TEST_EXTENSIONS = .sh

SH_LOG_COMPILER = $(SHELL)
AM_SH_LOG_FLAGS =

EXTRA_DIST = \
sign-test-vector-1.sh.in \
sign-test-vector-2.sh.in \
verify-test-vector-1.sh.in \
verify-test-vector-2.sh.in
