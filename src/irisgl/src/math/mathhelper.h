/**************************************************************************
This file is part of IrisGL
http://www.irisgl.org
Copyright (c) 2016  GPLv3 Jahshaka LLC <coders@jahshaka.com>

This is free software: you may copy, redistribute
and/or modify it under the terms of the GPLv3 License

For more information see the LICENSE file
*************************************************************************/

#ifndef MATHHELPER_H
#define MATHHELPER_H

float lerp(float norm, float min, float max) {
    return (max - min) * norm + min;
}

#endif // MATHHELPER_H
