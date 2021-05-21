all: shell.exe
shell.exe: myls mymkdir mycat mydate myrm shell.c
	gcc shell.c -lreadline -o shell.exe
myls: myls.c
	gcc myls.c -o myls
mymkdir: mymkdir.c
	gcc mymkdir.c -o mymkdir
mycat: mycat.c
	gcc mycat.c -o mycat
mydate: mydate.c
	gcc mydate.c -o mydate
myrm: myrm.c
	gcc myrm.c -o myrm
