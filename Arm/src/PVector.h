#ifndef PVECTOR_H
#define PVECTOR_H

#include "Arduino.h"


/*************������ϸ˵�������CPP�ļ�*************/

class PVector {

  public:

    double x, y, z;                                                              //  Global Variables  ȫ�ֱ�����ͨ����ʾ�������꣩
    word runtime;                                                              //����ʱ�䣬��λms
    PVector();
    PVector(double _x, double _y, double _z);
    
    void add(PVector p);
    PVector sub(PVector p);
    void normalize();
    double dot(PVector p);
    double dist(PVector p);
};

#endif


/*********PVector���ã�Ϊ���������ṩһ��������������*******/

