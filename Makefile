#
# ---------- header -----------------------------------------------------------
#
# project       infinit
#
# license       infinit
#
# file          /home/mycure/infinit/Makefile
#
# created       julien quintard   [wed oct  6 12:58:36 2010]
# updated       julien quintard   [mon may  2 16:55:13 2011]
#

#
# ---------- variables --------------------------------------------------------
#

BUILD		:=		build

REPOSITORY	:=		ssh://git@repositories.passeism.org

CONFIG		:=		config.mk

ECHO		:=		echo
MAKE		:=		make
TEST		:=		test
RM		:=		rm -Rf
GIT		:=		git
GREP		:=		grep
WC		:=		wc -l

CONFIGURE	:=		./configure

COMPONENTS	:=		elle					\
				comet					\
				nucleus					\
				etoile					\
				agent					\
				pig					\
				applications				\
				lune					\
				hole

#
# ---------- includes ---------------------------------------------------------
#

-include $(CONFIG)

#
# ---------- rules ------------------------------------------------------------
#

all:			build

build:
	$(TEST) -d $(BUILD) || $(CONFIGURE) --build-dir=$(BUILD)
	$(MAKE) -C $(BUILD)

install:		build
	$(MAKE) -C $(BUILD) install

documentation:
#	$(DOXYGEN) doc/Doxyfile

clean:
	$(MAKE) -C $(BUILD) clean
	$(RM) $(BUILD) $(CONFIG)

pull:
	@echo "---[ infinit"
	@$(GIT) pull

	@for component in $(COMPONENTS); do				\
	  echo "---[ $${component}"					&& \
	  if [ -d $${component} ] ; then				\
	    cd $${component}						&& \
	    $(GIT) pull							&& \
	    cd ..							; \
	  else								\
	    $(GIT) clone $(REPOSITORY)/$${component}			; \
	  fi								\
	done

status:
	@echo "---[ infinit"
	@$(GIT) status --porcelain

	@for component in $(COMPONENTS); do				\
	  echo "---[ $${component}"					&& \
	  cd $${component}						&& \
	  $(GIT) status --porcelain					&& \
	  cd ..								; \
	done

push:
	@echo "---[ infinit"
	@$(GIT) status --porcelain | $(GREP) -v "?" | $(GREP) ".*"
	@if [ $${?} -eq 0 ] ; then					\
	  $(GIT) commit -a && $(GIT) push				; \
	fi

	@for component in $(COMPONENTS); do				\
	  echo "---[ $${component}"					&& \
	  cd $${component}						&& \
	  $(GIT) status --porcelain | $(GREP) -v "?" | $(GREP) ".*"	&& \
	  if [ $${?} -eq 0 ] ; then					\
	    $(GIT) commit -a && $(GIT) push				; \
	  fi								; \
	  cd ..								; \
	done
