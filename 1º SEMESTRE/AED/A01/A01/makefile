#
# Tomás Oliveira e Silva, AED, September 2022
#
# makefile to compile the A.01 assignment (speed run)
#

clean:
	rm -rf a.out example.pdf speed_run speed_run_with_zlib solution_speed_run solution_speed_run_with_zlib


speed_run:		speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=0 speed_run.c -o speed_run -lm

speed_run_with_zlib:	speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=1 speed_run.c -o speed_run_with_zlib -lm -lz


solution_speed_run:		solution_speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=0 solution_speed_run.c -o solution_speed_run -lm

solution_speed_run_with_zlib:	solution_speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=1 solution_speed_run.c -o solution_speed_run_with_zlib -lm -lz
