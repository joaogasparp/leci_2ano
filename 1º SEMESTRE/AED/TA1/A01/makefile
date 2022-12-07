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

speed_run_1:		speed_run_1.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=0 speed_run_1.c -o speed_run_1 -lm

speed_run_1_with_zlib:	speed_run_1.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=1 speed_run_1.c -o speed_run_1_with_zlib -lm -lz

speed_run_2:		speed_run_2.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=0 speed_run_2.c -o speed_run_2 -lm

speed_run_2_with_zlib:	speed_run_2.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=1 speed_run_2.c -o speed_run_2_with_zlib -lm -lz

solution_speed_run:		solution_speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=0 solution_speed_run.c -o solution_speed_run -lm

solution_speed_run_with_zlib:	solution_speed_run.c make_custom_pdf.c
	cc -Wall -O2 -D_use_zlib_=1 solution_speed_run.c -o solution_speed_run_with_zlib -lm -lz
