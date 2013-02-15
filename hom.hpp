#ifndef __MY_HOM_H__
#define __MY_HOM_H__

//  img1
// -----> dft ---|                             |---> integral
//               |               corr          |
//               * ------> idft ------> pow ---|---> integral
//  img2         |                             |
// -----> dft ---|                             |---> integral
//

void corr(const Mat& img1, const Mat& img2, Mat& output);
void 

