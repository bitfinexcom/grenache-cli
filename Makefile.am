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

ACLOCAL_AMFLAGS = -I m4

GRC_SUBDIRS = . doc src tests

SUBDIRS = $(GRC_SUBDIRS)
DIST_SUBDIRS = $(GRC_SUBDIRS) include m4

@GENERATE_CHANGELOG_RULES@

EXTRA_DIST = \
LICENSE \
README.md \
autogen.sh \
shtool \
ed25519/readme.md \
ed25519/license.txt

DISTCLEANFILES = \
config.h.in~

MAINTAINERCLEANFILES = \
$(DISTCLEANFILES)

dist-hook: dist-ChangeLog

maintainer-clean-local: maintainer-clean-local-check

maintainer-clean-local-check:
	-$(RM) $(distdir).tar.xz

.PHONY: maintainer-clean-local-check
