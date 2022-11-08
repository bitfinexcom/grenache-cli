############################################################################
# This file is part of Grenache Command Line Interface.                    #
#                                                                          #
# Copyright (C) 2017-2022 Davide Scola <davide@bitfinex.com>               #
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

dist_man1_MANS = \
grenache-get.1 \
grenache-put.1 \
grenache-keygen.1 \
grenache-lookup.1 \
grenache-announce.1

MAINTAINERCLEANFILES = \
$(dist_man1_MANS)

%.1: $(top_srcdir)/src/%.in $(top_srcdir)/doc/Makefile.am
	$(HELP2MAN) --no-info --output=$@ --version-string="$(PACKAGE_VERSION)" \
		--name="manual page for $(notdir $(basename $<)) ($(PACKAGE_NAME)) $(PACKAGE_VERSION) on $(host_cpu)-$(host_os)" \
		"${SHELL} $(top_builddir)/src/$(notdir $(basename $<))$(EXEEXT)"
