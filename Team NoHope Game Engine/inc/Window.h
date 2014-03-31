//
//  Window.h
//  ggEngine
//
//  Created by Joonatan Sorensen on 12/12/13.
//  Copyright (c) 2013 Joonatan Sorensen. All rights reserved.
//

#if defined(WIN32) || defined(__APPLE__)
    #include "Win/Window.h"
#elif __ANDROID__
	#include "Android/EGLWindow.h"
#endif
