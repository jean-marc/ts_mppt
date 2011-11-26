CC = gcc
BIN = /usr/local/bin
WWW = /var/www

ts_mppt: ts_mppt.c
	$(CC) -lmodbus ts_mppt.c -o ts_mppt
install:
	cp ts_mppt ts_mppt.awk ts_mppt.sh $(BIN)
	cp plot.gnu svg.gnu png.gnu plot.png.cgi plot.svg.cgi $(WWW)/cgi-bin/
#	crontabs add
#	* * * * * /usr/local/bin/ts_mppt.sh
uninstall:
	rm -f $(BIN)/ts_mppt $(BIN)/ts_mppt.awk $(BIN)/ts_mppt.sh
	rm -f $(WWW)/plot.gnu $(WWW)/svg.gnu $(WWW)/png.gnu $(WWW)/plot.png.cgi $(WWW)/plot.svg.cgi
#	crontabs remove
#	* * * * * /usr/local/bin/ts_mppt.sh
