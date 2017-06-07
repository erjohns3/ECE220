#include "functions.h"

/*
 * getRadius - returns the radius based on the sigma value
 * INPUTS: sigma - sigma in the Guassian distribution
 * OUTPUTS: none
 * RETURN VALUE: radius - radius of the filter
 */
int getRadius(double sigma)
{
  // return radius
  return ceil(3*sigma);
}

/*
 * calculateGausFilter - calculates the Gaussian filter
 * INTPUTS: gausFitler - pointer to the array for the gaussian filter
 *          sigma - the sigma in the Gaussian distribution
 * OUTPUTS: none
 * RETURN VALUE: none
 */
void calculateGausFilter(double *gausFilter,double sigma)
{
  double sum = 0.0;
  // get radius
  int radius = getRadius(sigma);
  // create gaussian function used
  double tempVal = sqrt(2*M_PI*sigma*sigma);
  int row,col,idx=0;
  // make gaussian filter with given radius
  for(row = -radius;row<=radius;row++){
    for(col = -radius;col<=radius;col++){
      gausFilter[idx] = exp(-((row*row)+(col*col))/(2*sigma*sigma))/tempVal;
      // sum up all values in the gaussian filter
      sum += gausFilter[idx++];
    }
  }
  int i;
  for(i=0;i<idx;i++){
    // divide all values in gaussian filter by the sum of all values in gaussian filter
    gausFilter[i]/=sum;
  }
  return;
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         filter - pointer to the convolution filter
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convolveImage(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
                   uint8_t *inAlpha, uint8_t *outRed,uint8_t *outBlue,
                   uint8_t *outGreen,uint8_t *outAlpha,const double *filter,
                   int radius,int width,int height)
{
  int picY,picX,filY,filX;
  double sumRed,sumBlue,sumGreen;
  //2 for loops to go through all the pixels row by row
  for(picY=0;picY<height;picY++){
    for(picX=0;picX<width;picX++){
      //reset the sums of the filter and image parts
      sumRed = 0.0;
      sumBlue = 0.0;
      sumGreen = 0.0;
      //loop through the filter values
      for(filY = -radius;filY<=radius;filY++){
	if(picY+filY>=0 && picY+filY<height){
	  for(filX = -radius;filX<=radius;filX++){
	    if(picX+filX>=0 && picX+filX<width){
	      //add up the products of the filter values and the pixel channels
	      sumRed += filter[(filY+radius)*(2*radius+1)+(filX+radius)] * inRed[(picY+filY)*width+(picX+filX)];
	      sumBlue += filter[(filY+radius)*(2*radius+1)+(filX+radius)] * inBlue[(picY+filY)*width+(picX+filX)];
	      sumGreen += filter[(filY+radius)*(2*radius+1)+(filX+radius)] * inGreen[(picY+filY)*width+(picX+filX)];
	    }
	  }
	}
      }
      //keep the values within 0 and 255
      if(sumRed<0){
	sumRed = 0;
      }else if(sumRed>255){
	sumRed = 255;
      }
      if(sumBlue<0){
	sumBlue = 0;
      }else if(sumBlue>255){
	sumBlue = 255;
      }
      if(sumGreen<0){
	sumGreen = 0;
      }else if(sumGreen>255){
	sumGreen = 255;
      }
      //set the out channels to the sums
      outRed[picY*width + picX] = sumRed;
      outBlue[picY*width + picX] = sumBlue;
      outGreen[picY*width + picX] = sumGreen;
      outAlpha[picY*width + picX] = inAlpha[picY*width + picX];
    }
  } 
  return;
}

/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         gMonoMult - pointer to array with constants to be multipiled 
 *                     with RBG channels to convert image to grayscale
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convertToGray(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outBlue,
                   uint8_t *outGreen,uint8_t *outAlpha,
                   const double *gMonoMult,int height,int width)
{
  int i;
  double color;
  // go through pixels
  for(i=0;i<height*width;i++){
    // find the average channel value
    color = gMonoMult[0]*inRed[i] + gMonoMult[1]*inGreen[i] + gMonoMult[2]*inBlue[i];
    if(color>255){
      // cap color at 255
      color = 255;
    }
    // set output channels to average channel value
    outRed[i] = color;
    outBlue[i] = color;
    outGreen[i] = color;
    outAlpha[i] = inAlpha[i];
  }
  return;
}

/* flipImage - flips the image in both the horizontal and vertical directions
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void flipImage(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
               uint8_t *inAlpha,uint8_t *outRed,uint8_t *outBlue,
               uint8_t *outGreen,uint8_t *outAlpha,int height,int width)
{
  int x,y;
  // go through pixels row by row
  for(y=0;y<height;y++){
    for(x=0;x<width;x++){
      // set output pixels to corresponding input pixels 
      outRed[y*width+x] = inRed[(height-1-y)*width+(width-1-x)];
      outBlue[y*width+x] = inBlue[(height-1-y)*width+(width-1-x)];
      outGreen[y*width+x] = inGreen[(height-1-y)*width+(width-1-x)];
      outAlpha[y*width+x] = inAlpha[(height-1-y)*width+(width-1-x)];
    }
  }
  return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void invertImage(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outBlue,
                 uint8_t *outGreen,uint8_t *outAlpha,int height,int width)
{
  int i;
  // go through pixels
  for(i=0;i<height*width;i++){
    // set output pixels to inverse of input pixels
    outRed[i] = 255 - inRed[i];
    outBlue[i] = 255 - inBlue[i];
    outGreen[i] = 255 - inGreen[i];
    outAlpha[i] = inAlpha[i];
  }
  return;
}

/* pixelate - pixelates the image
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         pixelateY - height of the block
 *         pixelateX - width of the block
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pixelate(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
              uint8_t *inAlpha,uint8_t *outRed,uint8_t *outBlue,
              uint8_t *outGreen,uint8_t *outAlpha,int pixelY,int pixelX,
              int width,int height)
{
  // initialize variables
  int bigX,bigY,smallX,smallY,totalRed,totalBlue,totalGreen,totalAlpha,area;
  // loops for going through pixel blocks
  for(bigY = 0; bigY < height; bigY+=pixelY){
    for(bigX = 0; bigX < width; bigX+=pixelX){
      // reset totals and area
      totalRed = 0;
      totalBlue = 0;
      totalGreen = 0;
      totalAlpha = 0;
      area = 0;
      // go through all pixels within current block
      for(smallY = bigY; smallY < bigY+pixelY && smallY < height; smallY++){
	for(smallX = bigX; smallX < bigX+pixelX && smallX < width; smallX++){ 
	  // sum up each channel of each pixel within block
	  totalRed += inRed[smallY*width + smallX];
	  totalBlue += inBlue[smallY*width + smallX];
	  totalGreen += inGreen[smallY*width + smallX];
	  totalAlpha += inAlpha[smallY*width + smallX];
	  // increment area
	  area++;
	}
      }
      // loops for outputting average
      for(smallY = bigY; smallY < bigY+pixelY && smallY<height; smallY++){
	for(smallX = bigX; smallX < bigX+pixelX && smallY<width; smallX++){
	  // output average value of each channel to all channels within block
	  outRed[smallY*width + smallX] = totalRed/area;
	  outBlue[smallY*width + smallX] = totalBlue/area;
	  outGreen[smallY*width + smallX] = totalGreen/area;
	  outAlpha[smallY*width + smallX] = totalAlpha/area;
	}
      }
    }
  }	  
  return;
}

/* colorDodge - blends the bottom layer with the top layer
 * INPUTS: botRed - pointer to the bottom red channel
 *         botBlue - pointer to the bottom blue channel
 *         botGreen - pointer to the bottom green channel
 *         botAlpha - pointer to the bottom alpha channel
 *         topRed - pointer to the top red channel
 *         topBlue - pointer to the top blue channel
 *         topGreen - pointer to the top green channel
 *         topAlpha - pointer to the top alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void colorDodge(uint8_t *botRed,uint8_t *botBlue,uint8_t *botGreen,
                uint8_t *botAlpha,uint8_t *topRed,uint8_t *topBlue,
                uint8_t *topGreen,uint8_t *topAlpha,uint8_t *outRed,
                uint8_t *outBlue,uint8_t *outGreen,uint8_t *outAlpha,
                int width,int height)
{
  int i;
  // go through all pixels
  for(i=0;i<height*width;i++){
    // blend pixels from two input images together
    outRed[i] = ((topRed[i]==255)?topRed[i]:min(((botRed[i]<<8)/(255-topRed[i])),255));
    outBlue[i] = ((topBlue[i]==255)?topBlue[i]:min(((botBlue[i]<<8)/(255-topBlue[i])),255));
    outGreen[i] = ((topGreen[i]==255)?topGreen[i]:min(((botGreen[i]<<8)/(255-topGreen[i])),255));
    outAlpha[i] = botAlpha[i];
  }
  return;
}

/* pencilSketch - creates a pencil sketch of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inBlue - pointer to the input blue channel
 *         inGreen - pointer to the input green channel
 *         inAlpha - pointer to the input alpha channel
 *         invRed - pointer to temporary red channel for inversion
 *         invBlue - pointer to temporary blue channel for inversion
 *         invGreen - pointer to temporary green channel for inversion
 *         invAlpha - pointer to temporary alpha channel for inversion
 *         blurRed - pointer to temporary red channel for blurring
 *         blurBlue - pointer to temporary blue channel for blurring
 *         blurGreen - pointer to temporary green channel for blurring
 *         blurAlpha - pointer to temporary alpha channel for blurring
 *         filter - pointer to the gaussian filter to blur the image
 *         radius - radius of the gaussian filter
 *         width - width of the input image
 *         height - height of the input image
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 * OUTPUTS: outRed - pointer to the output red channel
 *          outBlue - pointer to the output blue channel
 *          outGreen - pointer to the output green channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pencilSketch(uint8_t *inRed,uint8_t *inBlue,uint8_t *inGreen,
                  uint8_t *inAlpha,uint8_t *invRed,uint8_t *invBlue,
                  uint8_t *invGreen,uint8_t *invAlpha,uint8_t *blurRed,
                  uint8_t *blurBlue,uint8_t *blurGreen,uint8_t *blurAlpha,
                  uint8_t *outRed,uint8_t *outBlue,uint8_t *outGreen,
                  uint8_t *outAlpha,const double *filter,int radius,
                  int width,int height,const double *gMonoMult)
{
  convertToGray(inRed,inBlue,inGreen,inAlpha,invRed,invBlue,invGreen,invAlpha,gMonoMult,height,width);
  invertImage(invRed,invBlue,invGreen,invAlpha,invRed,invBlue,invGreen,invAlpha,height,width);
  convolveImage(inRed,inBlue,inGreen,inAlpha,blurRed,blurBlue,blurGreen,blurAlpha,filter,radius,width,height);
  colorDodge(blurRed,blurBlue,blurGreen,blurAlpha,invRed,invBlue,invGreen,invAlpha,outRed,outBlue,outGreen,outAlpha,width,height);
  return;
}
