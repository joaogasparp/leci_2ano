//
// AED, August 2022 (Tomás Oliveira e Silva)
//
// make a custom uncompressed PDF file with the spiral figure for the solution of a 2002_A01 problem 
//
// https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/pdfreference1.4.pdf
//
// PDF/A conformance tested using veraPDF (a few tests fail, but they are not important)
//
// this file can, and should, be included directly in the main program (speed_run.c)
//
// some PDF commands:
//  [width] w                            set line width
//  [x] [y] m                            move to
//  [x] [y] l                            line to
//  h                                    close path
//  S                                    stroke
//  s                                    close path and stroke
//  F                                    fill
//  f                                    fill
//  B                                    fill and stroke
//  b                                    close, fill, and stroke
//  n                                    end path
//  [r] [g] [b] RG                       set stroke color
//  [r] [g] [b] rg                       set fill color
//  BT ... ET                            text contents
//  [a1] [a2] [b1] [b2] [c1] [c2] Tm     set text coordinate transformation matrix
//  [(string)] Tj                        draw text
//


//
// static configuration
//

#ifndef _use_zlib_
# define _use_zlib_  1  // a positive value allows stream contents to be compressed (smaller PDF files...)
#endif

#define _n_spiral_cells_  802  // must be even (802 is good for a _max_road_size_ of 801)
#define _oversampling_      4  // must be even and at least 2; it should not be large, as the size of the PDF file is approximately proportional to this value
#define _spiral_min_t_    0.5  // should end in .5, but that is not strictly necessary
#define _spiral_max_t_    8.5  // must end in .5
#define _figure_width_    500  // in points (there are 72 points in an inch)
#define _figure_height_   260  // in points (there are 72 points in an inch)


//
// include files
//

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#if _use_zlib_ > 0
# include <zlib.h>
#endif


//
// private spiral stuff
//
// spiral formulas (surprise: calculus is useful!):
//   x(t) = t*cos(2*pi*t)                     --------------------------------------- parametric coordinates of the spiral
//   y(t) = t*sin(2*pi*t)                     --------------------------------------- parametric coordinates of the spiral
//   dx/dt = cos(2*pi*t)-2*pi*t*sin(2*pi*t)   --------------------------------------- for the tangent
//   dy/dt = sin(2*pi*t)+2*pi*t*cos(2*pi*t)   --------------------------------------- for the tangent
//   ds/dt = sqrt((dx/dt)^2+(dy/dt)^2) = sqrt(1+4*pi^2*t^2)
//   s(t) = (2*pi*t*sqrt(1+4*pi^2*t^2)+log(2*pi*t+sqrt(1+4*pi^2*t^2)))/(4*pi)+C   --- arc length
//

typedef struct
{
  double t;     // the t coordinate
  double s;     // the arc lenght
  double x;     // the x coordinate of the arc
  double y;     // the y coordinate of the arc
  double x_in;  // the x coordinate of the inside arc
  double y_in;  // the y coordinate of the inside arc
  double x_out; // the x coordinate of the outside arc
  double y_out; // the y coordinate of the outside arc
  double angle; // cell angle
}
spiral_point_t;

static spiral_point_t spiral_points[1 + _n_spiral_cells_ * _oversampling_];

static double spiral_s(double t)
{ // t -> length
  double t1,t2;

  t1 = 2.0 * M_PI * t;
  t2 = sqrt(1.0 + t1 * t1);
  return (t1 * t2 + log(t1 + t2)) / (4.0 * M_PI);
}

static double spiral_t(double s)
{ // length -> t
  double t0,t1;

  t0 = sqrt(s / M_PI); // initial approximation
  do
  { // Newton-Raphson zero finder
    t1 = t0;
    t0 -= (spiral_s(t0) - s) / sqrt(1.0 + 4.0 * M_PI * M_PI * t0 * t0);
  }
  while(fabs(t1 - t0) > 1.0e-12);
  return 0.5 * (t0 + t1);
}

static void spiral_point_data(double t,double *x,double *y,double *nx,double *ny,double *angle)
{ // coordinates, normal and text angle
  double t1,c,s,dx,dy;

  t1 = 2.0 * M_PI * t;
  c = cos(t1);
  s = sin(t1);
  *x = t * c;
  *y = t * s;
  dx = c - t1 * s;
  dy = s + t1 * c;
  t1 = 1.0 / sqrt(dx * dx + dy * dy);
  *nx = -t1 * dy;        // normal vector: 90 degrees rotation of the
  *ny = t1 * dx;         // tangent (normalized to have unit length)
  *angle = atan2(dy,dx); // tangent angle
}

static void create_spiral(void)
{
  double s0,s1,x,y,nx,ny,angle,l;
  int i,n2;

  if(_n_spiral_cells_ % 2 != 0)
  {
    fprintf(stderr,"create_spiral: _n_spiral_cells_ must be an even number\n");
    exit(1);
  }
  if(_oversampling_ % 2 != 0)
  {
    fprintf(stderr,"create_spiral: _oversampling_ must be an even number\n");
    exit(1);
  }
  if(_spiral_max_t_ - floor(_spiral_max_t_) != 0.5)
  {
    fprintf(stderr,"create_spiral: the fractional part of _spiral_max_t_ must be 0.5\n");
    exit(1);
  }
  // make the right-hand side spiral
  s0 = spiral_s(_spiral_min_t_);
  s1 = spiral_s(_spiral_max_t_);
  n2 = (_oversampling_ * _n_spiral_cells_) / 2u;
  l = 0.5 * (double)_oversampling_ * (s1 - s0) / (double)n2;
  for(i = 0;i <= n2;i++)
  {
    spiral_points[i].s = ((double)(n2 - i) * s0 + (double)i * s1) / (double)n2;
    spiral_points[i].t = spiral_t(spiral_points[i].s);
    spiral_point_data(spiral_points[i].t,&x,&y,&nx,&ny,&angle);
    spiral_points[i].x = x;
    spiral_points[i].y = y;
    spiral_points[i].x_in = x + l * nx;
    spiral_points[i].y_in = y + l * ny;
    spiral_points[i].x_out = x - l * nx;
    spiral_points[i].y_out = y - l * ny;
    spiral_points[i].angle = angle;
  }
  // make the left-hand side spiral
  for(i = 0;i < n2;i++)
  {
    spiral_points[2 * n2 - i].x = -2.0 * (double)_spiral_max_t_ - spiral_points[i].x;
    spiral_points[2 * n2 - i].y = -spiral_points[i].y;
    spiral_points[2 * n2 - i].x_in = -2.0 * (double)_spiral_max_t_ - spiral_points[i].x_out;
    spiral_points[2 * n2 - i].y_in = -spiral_points[i].y_out;
    spiral_points[2 * n2 - i].x_out = -2.0 * (double)_spiral_max_t_ - spiral_points[i].x_in;
    spiral_points[2 * n2 - i].y_out = -spiral_points[i].y_in;
    spiral_points[2 * n2 - i].angle = -spiral_points[i].angle;
  }
}


//
// private PDF stuff
//

#define max_pdf_objects 10

typedef enum { is_pdf_object,is_pdf_stream } pdf_object_type_t;

typedef struct
{
  int file_offset;        // the byte number where the start of the object is located in the PDF file (computed)
  int contents_size;      // the number of bytes of the content (computed, only used for contents that grow on demand)
  int contents_max_size;  // the maximum number of bytes of the content (computed, only used for contents that grow on demand)
  pdf_object_type_t type; // the type of the PDF object (given)
  char *contents;         // the contents of the object (given)
}
pdf_object_t;

static pdf_object_t pdf_objects[max_pdf_objects];
static int n_pdf_objects;

#ifdef __GNUC__
__attribute__((__format__(printf,2,3)))
#endif
static void add_pdf_content(pdf_object_t *pdf_object,const char *format,...)
{
  int size_increment;
  va_list ap;

  if(pdf_object->contents_size + 256 > pdf_object->contents_max_size)
  {
    pdf_object->contents_max_size = 256 + pdf_object->contents_max_size + pdf_object->contents_max_size / 2;
    pdf_object->contents = (char *)realloc(pdf_object->contents,(size_t)pdf_object->contents_max_size);
    if(pdf_object->contents == NULL)
    {
      fprintf(stderr,"add_pdf_content: out of memory\n");
      exit(1);
    }
  }
  va_start(ap,format);
  size_increment = vsnprintf(&pdf_object->contents[pdf_object->contents_size],(size_t)(pdf_object->contents_max_size - pdf_object->contents_size),format,ap);
  va_end(ap);
  if(size_increment >= pdf_object->contents_max_size - pdf_object->contents_size)
  {
    fprintf(stderr,"add_pdf_content: internal error (too much data added in one go)\n");
    exit(1);
  }
  pdf_object->contents_size += size_increment;
}


//
// the public PDF stuff
//

void make_custom_pdf_file(char *pdf_file_name,int road_size,int max_road_speed[1 + road_size],int n_moves,int positions[1 + n_moves],double elapsed_time,unsigned long effort,char *title)
{
  double figure_x_offset,figure_y_offset,figure_scale,min_x,max_x,min_y,max_y,s0,s1;
  int i,j,k,n,file_offset;
  char info[64];
  FILE *fp;

  if(1 + road_size > _n_spiral_cells_)
  {
    fprintf(stderr,"make_custom_pdf_file: road_size is too large\n");
    exit(1);
  }
  fp = fopen(pdf_file_name,"wb");
  if(fp == NULL)
  {
    fprintf(stderr,"make_custom_pdf_file: unable to create file %s\n",pdf_file_name);
    exit(1);
  }
  //
  // create spiral and compute coordinate transformation data
  //   figure_x = width/2 + figure_scale * (x - figure_x_offset)
  //   figure_y = height/2 + figure_scale * (y - figure_y_offset)
  //
# define figure_x(x)  (0.5 * (double)_figure_width_ + figure_scale * ((x) - figure_x_offset))
# define figure_y(y)  (0.5 * (double)_figure_height_ + figure_scale * ((y) - figure_y_offset))
  create_spiral();
  n = _oversampling_ * _n_spiral_cells_;
  min_x = max_x = min_y = max_y = 0.0;
  for(i = 0;i <= n;i++)
  {
#define update_bounding_box(x,y) do              \
                                 {               \
                                   if(x < min_x) \
                                     min_x = x;  \
                                   if(x > max_x) \
                                     max_x = x;  \
                                   if(y < min_y) \
                                     min_y = y;  \
                                   if(y > max_y) \
                                     max_y = y;  \
                                 }               \
                                 while(0)
    update_bounding_box(spiral_points[i].x,spiral_points[i].y);
    update_bounding_box(spiral_points[i].x_in,spiral_points[i].y_in);
    update_bounding_box(spiral_points[i].x_out,spiral_points[i].y_out);
#undef update_bounding_box
  }
  s0 = (double)_figure_width_ / (max_x - min_x);
  s1 = (double)_figure_height_ / (max_y - min_y);
  figure_scale = 0.99 * ((s0 < s1) ? s0 : s1);
  figure_x_offset = 0.5 * (max_x + min_x);
  figure_y_offset = 0.5 * (max_y + min_y);
  //
  // create the PDF objects
  //
  // the catalog (object #1)
  pdf_objects[0].type = is_pdf_object;
  pdf_objects[0].contents_size = 0;
  pdf_objects[0].contents_max_size = 0;
  pdf_objects[0].contents = "<< /Type /Catalog /Pages 2 0 R >>";
  // the list of pages (object #2)
  pdf_objects[1].type = is_pdf_object;
  pdf_objects[1].contents_size = 0;
  pdf_objects[1].contents_max_size = 0;
  pdf_objects[1].contents = "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";
  // the description of the page (object #3)
  pdf_objects[2].type = is_pdf_object;
  pdf_objects[2].contents_size = 0;
  pdf_objects[2].contents_max_size = 0;
  pdf_objects[2].contents = NULL;
  add_pdf_content(&pdf_objects[2],"<< /Type /Page /Parent 2 0 R /MediaBox [0 0 %d %d] /Contents [5 0 R 6 0 R 7 0 R] /Resources << /Font << /MyFont 4 0 R >> /ProcSet [/PDF /Text] >> >>",_figure_width_,_figure_height_);
  // the font used by the page (object #4)
  pdf_objects[3].type = is_pdf_object;
  pdf_objects[3].contents_size = 0;
  pdf_objects[3].contents_max_size = 0;
  pdf_objects[3].contents = "<< /Type /Font /Subtype /Type1 /Name /MyFont /BaseFont /Courier-Bold /Encoding /StandardEncoding >>";
  // the spiral cell highlights (object #5)
  pdf_objects[4].type = is_pdf_stream;
  pdf_objects[4].contents_size = 0;
  pdf_objects[4].contents_max_size = 0;
  pdf_objects[4].contents = NULL;
  // the spiral cell borders (object #6)
  pdf_objects[5].type = is_pdf_stream;
  pdf_objects[5].contents_size = 0;
  pdf_objects[5].contents_max_size = 0;
  pdf_objects[5].contents = NULL;
  // the speed data (object #7)
  pdf_objects[6].type = is_pdf_stream;
  pdf_objects[6].contents_size = 0;
  pdf_objects[6].contents_max_size = 0;
  pdf_objects[6].contents = NULL;
  // no more objects
  n_pdf_objects = 7;
  // add the highlight cells to object #5
  add_pdf_content(&pdf_objects[4],"0.8 0.8 0.8 rg\n"); // fill color is gray
  for(k = 0;k <= n_moves;k++)
  {
    i = _oversampling_ * positions[k];
    add_pdf_content(&pdf_objects[4],"%.3f %.3f m",figure_x(spiral_points[i].x_in),figure_y(spiral_points[i].y_in));
    for(j = 1;j <= _oversampling_;j++)
      add_pdf_content(&pdf_objects[4]," %.3f %.3f l",figure_x(spiral_points[i + j].x_in),figure_y(spiral_points[i + j].y_in));
    for(j = _oversampling_;j >= 0;j--)
      add_pdf_content(&pdf_objects[4]," %.3f %.3f l",figure_x(spiral_points[i + j].x_out),figure_y(spiral_points[i + j].y_out));
    add_pdf_content(&pdf_objects[4]," h f\n");
  }
  // add the spiral cell borders to object #6
  add_pdf_content(&pdf_objects[5],"0 0 0 RG 0.4 w\n"); // stroke color is black, linewidth is 0.4pt
  add_pdf_content(&pdf_objects[5],"%.3f %.3f m %.3f %.3f l S\n",figure_x(spiral_points[0].x_in),figure_y(spiral_points[0].y_in),figure_x(spiral_points[0].x_out),figure_y(spiral_points[0].y_out));
  for(i = 0;i < n;i += _oversampling_)
  {
    if(i == _oversampling_ * (1 + positions[n_moves]))
      add_pdf_content(&pdf_objects[5],"0.8 0.8 0.8 RG\n"); // switch to gray
    add_pdf_content(&pdf_objects[5],"%.3f %.3f m",figure_x(spiral_points[i].x_in),figure_y(spiral_points[i].y_in));
    for(j = 1;j <= _oversampling_;j++)
      add_pdf_content(&pdf_objects[5]," %.3f %.3f l",figure_x(spiral_points[i + j].x_in),figure_y(spiral_points[i + j].y_in));
    for(j = _oversampling_;j >= 0;j--)
      add_pdf_content(&pdf_objects[5]," %.3f %.3f l",figure_x(spiral_points[i + j].x_out),figure_y(spiral_points[i + j].y_out));
    add_pdf_content(&pdf_objects[5]," S\n");
  }
  // add the cell numbers to object #7
  s0 = 0.8 * figure_scale * (spiral_points[n / 2].s - spiral_points[0].s) / (double)(_n_spiral_cells_ / 2); // the font size (the spiral length data is only good in the first half...)
  add_pdf_content(&pdf_objects[6],"BT 0 0 0 rg /MyFont %.3f Tf\n",s0); // fill color is black, set the font
  sprintf(info,"%d move%s",n_moves,(n_moves == 1) ? "" : "s");
  add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%s) Tj\n",0.5 * _figure_width_ - 0.3 * (double)strlen(info) * s0,2.2 * s0,info);
  sprintf(info,"%.3e seconds",elapsed_time);
  add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%s) Tj\n",0.5 * _figure_width_ - 0.3 * (double)strlen(info) * s0,1.2 * s0,info);
  sprintf(info,"effort: %lu",effort);
  add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%s) Tj\n",0.5 * _figure_width_ - 0.3 * (double)strlen(info) * s0,0.2 * s0,info);
  add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%s) Tj\n",0.5 * _figure_width_ - 0.3 * (double)strlen(title) * s0,(double)_figure_height_ - s0,title);
  sprintf(info,"road size: %d",road_size);
  add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%s) Tj\n",0.5 * _figure_width_ - 0.3 * (double)strlen(info) * s0,(double)_figure_height_ - 2.0 * s0,info);
  for(i = 0;i <= road_size;i++)
  {
    j = i * _oversampling_ + _oversampling_ / 2; // the index corresponding to the center of the cell
    add_pdf_content(&pdf_objects[6],"1 0 0 1 %.3f %.3f Tm (%d) Tj\n",figure_x(spiral_points[j].x) - 0.3 * s0,figure_y(spiral_points[j].y) - 0.35 * s0,max_road_speed[i]);
  }
  add_pdf_content(&pdf_objects[6],"ET");
  //
  // dump the PDF file (warning, no tests are performed to check if individual writes fail)
  //
  file_offset = fprintf(fp,"%%PDF-1.4\n");
  file_offset += fprintf(fp,"%%\xC3\xA1\xC3\xA1\n");
  for(i = 0;i < n_pdf_objects;i++)
    if(pdf_objects[i].contents != NULL)
    {
      // remove \n at the end of the contents (because one will be added automatically below)
      for(j = (int)strlen(pdf_objects[i].contents);j >= 1 && pdf_objects[i].contents[j - 1] == '\n';j--)
        pdf_objects[i].contents[j - 1] = '\0';
      // dump the object
      pdf_objects[i].file_offset = file_offset;
      file_offset += fprintf(fp,"%d 0 obj\n",1 + i);
      switch(pdf_objects[i].type)
      {
        case is_pdf_object:
          file_offset += fprintf(fp,"%s\n",pdf_objects[i].contents);
          break;
        case is_pdf_stream:
#if _use_zlib_ > 0
          {
            // documentation on how to use the zlib compression library in /usr/include/zlib.h
            size_t buffer_size;
            unsigned char *buffer;
            z_stream z;

            // prepare the buffer to hold the compressed data
            buffer_size = (size_t)strlen(pdf_objects[i].contents);
            buffer_size += buffer_size / 4;
            buffer_size += (size_t)1000; // this should be much more than enough space for the compressed data --- could have used the deflateBound() function instead, but that would have to be done after deflateInit()...
            buffer = (unsigned char *)malloc(buffer_size);
            if(buffer == NULL)
            {
              fprintf(stderr,"make_custom_pdf_file: out of memory\n");
              exit(1);
            }
            // prepare the compressor
            z.next_in = (unsigned char *)pdf_objects[i].contents;
            z.avail_in = strlen(pdf_objects[i].contents);
            z.total_in = 0;
            z.next_out = buffer;
            z.avail_out = buffer_size;
            z.total_out = 0;
            z.zalloc = Z_NULL;
            z.zfree = Z_NULL;
            z.opaque = Z_NULL;
            // compress (and cleanup the compressor)
            if(deflateInit(&z,9) != Z_OK)
            {
              fprintf(stderr,"make_custom_pdf_file: deflateInit() failed");
              exit(1);
            }
            if(deflate(&z,Z_FINISH) != Z_STREAM_END)
            {
              fprintf(stderr,"make_custom_pdf_file: deflate() failed");
              exit(1);
            }
            if(deflateEnd(&z) != Z_OK)
            {
              fprintf(stderr,"make_custom_pdf_file: deflateEnd() failed");
              exit(1);
            }
            // output stream
            file_offset += fprintf(fp,"<< /Length %d /Filter /FlateDecode >> stream\n",(int)z.total_out);
            file_offset += fwrite((void *)buffer,sizeof(unsigned char),(size_t)z.total_out,fp);
            file_offset += fprintf(fp,"\nendstream\n");
            // clean up
            free(buffer);
          }
#else
          file_offset += fprintf(fp,"<< /Length %d >> stream\n",(int)strlen(pdf_objects[i].contents));
          file_offset += fprintf(fp,"%s",pdf_objects[i].contents);
          file_offset += fprintf(fp,"\nendstream\n");
#endif
          break;
      }
      file_offset += fprintf(fp,"endobj\n");
    }
  fprintf(fp,"xref\n");
  fprintf(fp,"0 %d\n",n_pdf_objects + 1);
  fprintf(fp,"0000000000 65535 f \n"); // note the space before the new line!
  for(i = 0;i < n_pdf_objects;i++)
    fprintf(fp,"%010d 00000 n \n",pdf_objects[i].file_offset);
  fprintf(fp,"trailer << /Size %d /Root 1 0 R /ID [<AED02022> <AED02022>]>>\n",1 + n_pdf_objects);
  fprintf(fp,"startxref\n");
  fprintf(fp,"%d\n",file_offset);
  fprintf(fp,"%%%%EOF\n");
  //
  // clean up
  fclose(fp);
  for(i = 0;i < n_pdf_objects;i++)
    if(pdf_objects[i].contents_max_size > 0)
      free(pdf_objects[i].contents);
# undef figure_x
# undef figure_y
}
