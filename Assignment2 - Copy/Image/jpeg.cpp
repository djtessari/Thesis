#include "jpeg.h"
#include <assert.h>
#include <stdlib.h>
#include <JPEG/jpeglib.h>
#include <setjmp.h>

struct my_error_mgr {
	struct jpeg_error_mgr pub;    /* "public" fields */
	
	jmp_buf setjmp_buffer;        /* for return to caller */
};
typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	
	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);
	
	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

int JPEGReadImage(char* fileName,Image32& img){
	FILE* fp=fopen(fileName,"rb");
	if(!fp){return 0;}
	int ret=JPEGReadImage(fp,img);
	fclose(fp);
	return ret;
}
int JPEGWriteImage(Image32& img,char* fileName,int quality){
	FILE* fp=fopen(fileName,"wb");
	if(!fp){return 0;}
	int ret=JPEGWriteImage(img,fp,quality);
	fclose(fp);
	return ret;
}
int JPEGReadImage(FILE* fp,Image32& img){
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	JSAMPARRAY buffer;            /* Output row buffer */
	int row_stride;               /* physical row width in output buffer */
	int width,height;
	Pixel32 p;
	
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fprintf(stderr,"JPEG error occured\n");
		return 0;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	
	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);
	
	row_stride = cinfo.output_width * cinfo.output_components;
	
	// my code (MK borrowed from PM)
	if(cinfo.output_components!=1 && cinfo.output_components!=3){
		fprintf(stderr,"Wrong number of components: %d\n",cinfo.output_components);
		return 0;
	}
	width=cinfo.output_width;
	height=cinfo.output_height;

	if(!img.setSize(width,height)){return 0;}
	
	buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		for(int i=0; i < row_stride; i++) {
			p.a=255;
			if(cinfo.output_components == 1){
				p.r=buffer[0][i];
				p.g=buffer[0][i];
				p.b=buffer[0][i];
			}
			else{
				if		(i%3==0){p.r = buffer[0][i];}
				else if	(i%3==1){p.g = buffer[0][i];}
				else if	(i%3==2){p.b = buffer[0][i];}
			}
			if(cinfo.output_components==1){img(i,cinfo.output_scanline-1)=p;}
			else{img(i/3,cinfo.output_scanline-1)=p;}
		}
	}
	
	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	return 1;
}
int JPEGWriteImage(Image32& img,FILE* fp,int quality){
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	unsigned char* pixels;
	int i;
	
	JSAMPROW row_pointer[1];      /* pointer to JSAMPLE row[s] */
	int row_stride;               /* physical row width in image buffer */
	
	/* Step 1: allocate and initialize JPEG compression object */
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	
	jpeg_stdio_dest(&cinfo,fp);
	
	/* Step 3: set parameters for compression */
	
	/* First we supply a description of the input image.                                                    
	* Four fields of the cinfo struct must be filled in:
	*/
	cinfo.image_width = img.width();    /* image width and height, in pixels */
	cinfo.image_height = img.height();
	cinfo.input_components = 3;           /* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */
	
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);
	
	jpeg_start_compress(&cinfo, TRUE);
	
	row_stride = img.width() * 3;       /* JSAMPLEs per row in image_buffer */
	pixels=new unsigned char[row_stride];
	if(!pixels){return 0;}
	
	while (cinfo.next_scanline < cinfo.image_height) {
		for(i=0;i<row_stride/3;i++){
			pixels[i*3+0]=img(i,cinfo.next_scanline).r;
			pixels[i*3+1]=img(i,cinfo.next_scanline).g;
			pixels[i*3+2]=img(i,cinfo.next_scanline).b;
		}
    /* jpeg_write_scanlines expects an array of pointers to scanlines.                                    
	* Here the array is only one element long, but you could pass                                        
	* more than one scanline at a time if that's more convenient.                                        
		*/
		row_pointer[0] = pixels;
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	return 1;
}
