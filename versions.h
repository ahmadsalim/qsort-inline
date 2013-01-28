#ifndef __VERSIONS__H
#define __VERSIONS__H

  #ifdef __STDC__
    #define C89
    #ifdef __STDC_VERSION__
      #define C90
      #if __STDC_VERSION__ >= 199409L
        #define C94
      #endif
      #if __STDC_VERSION__ >= 199901L
        #define C99
      #endif
      #if __STDC_VERSION__ >= 201112L
        #define C11
      #endif
    #endif
  #endif

#endif//__VERSIONS__H
