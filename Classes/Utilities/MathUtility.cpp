//
//  MathUtility.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#include "MathUtility.h"
USING_NS_CC;

Color3B MathUtility::randomColor()
{
    const int minSum = 600;
	const int minDelta = 150;
	int r, g, b, min, max;
	while (true) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		r = arc4random_uniform(255);
		g = arc4random_uniform(255);
		b = arc4random_uniform(255);
#else
        r = arc4random() % 256;
        g = arc4random() % 256;
        b = arc4random() % 256;
#endif
		min = MIN(MIN(r, g), b);
		max = MAX(MAX(r, g), b);
		if (max-min < minDelta) continue;
		if (r+g+b < minSum) continue;
		break;
	}
	return Color3B(r, g, b);
}