## make file for libbase64

MAINFILE=libbase64.so
LIBVER=1.0.1
LIBFILE=$(MAINFILE).$(LIBVER)
SONAME=$(MAINFILE).3

MANPATH=/usr/local/man


all: $(LIBFILE)


LIBS=
ARGS=-g -Wall
REQH=



libbase64.o: libbase64.c base64.h $(REQH)
	gcc -c -fPIC libbase64.c -o $@ $(ARGS)

libbase64.a: libbase64.o
	@>$@
	@rm $@
	ar rcs $@ $^

$(LIBFILE): libbase64.o
	gcc -shared -Wl,-soname,$(SONAME) -o $@ $^


install: $(LIBFILE) base64.h 
	cp base64.h /usr/include/
	cp $(LIBFILE) /usr/lib/
	@-test -e /usr/lib/$(MAINFILE) && rm /usr/lib/$(MAINFILE)
	ln -s /usr/lib/$(LIBFILE) /usr/lib/$(MAINFILE)
	nice ldconfig
	@echo "Install complete."

manpages: man/libbase64.3 man/ll_free.3 man/ll_get_head.3 man/ll_get_tail.3 man/ll_init.3 man/ll_pop_head.3 man/ll_pop_tail.3 man/ll_push_head.3 man/ll_push_tail.3 man/ll_count.3 man/ll_join_str.3 man/ll_move_head.3 man/ll_move_tail.3
	@mkdir tmp.install
	@cp man/* tmp.install/
	@gzip tmp.install/*.3
	cp tmp.install/*.3.gz $(MANPATH)/man3/
	@rm -r tmp.install


clean:
	@-rm libbase64.o
	@-rm libbase64.so*

