FLAGS= -Wall -Wextra -pedantic -O2
OBJS=$(patsubst %.c ,%.o ,$(wildcard *.c))
EXEC=rogue
$(EXEC) : $(OBJS)
	$(CC) $(FLAGS) -o $(EXEC) $(OBJS)
	sudo cp imagens/* /var/www/html/
	sudo touch /var/www/html/estadojogo.txt
	sudo chmod 666 /var/www/html/estadojogo.txt
	sudo touch /var/www/html/continua.txt
	sudo chmod 666 /var/www/html/continua.txt
	sudo touch /var/www/html/highscore6.txt
	sudo chmod 666 /var/www/html/highscore6.txt
	sudo cp -f $(EXEC) /usr/lib/cgi-bin
doc:
	doxygen -g
	doxygen
limpar: 
	rm -f $(EXEC)
