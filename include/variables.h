#pragma once
#include <ctime>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>

#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

#include <algorithm>
#include <arpa/inet.h>
#include <cstdint>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
// #include <linux/i2c-dev.h>
#include <net/if.h>
#include <sstream>
#include <sys/ioctl.h>
#include <sys/socket.h>
// #include <sys/types.h>





namespace Var {
extern int minH;
extern int maxH;
extern int minS;
extern int maxS;
extern int minV;
extern int maxV;

extern int          WIDTH;
extern int          HEIGHT;
extern int          EXPOSURE;
extern unsigned int waitAfterFrame;

extern double qualityLevel;
extern double minDistance;
extern int    blockSize;
extern bool   useHarisDetector;
extern double k;
extern int    maxCorners;

extern size_t maxTargets;
extern size_t avSize;

extern double IRLOffset;

extern unsigned int videoPort;
} // namespace Var

class Targets {
public:
  Targets() { NullTargets(); };
  int                    status;
  std::string            found;
  cv::Point              center;
  double                 height;
  double                 width;
  double                 area;
  char                   LorR;
  int                    number;
  std::string            reason;
  double                 angle;
  double                 ratio;
  std::vector<cv::Point> corners;
  int                    offby;
  cv::RotatedRect        rect;
  cv::Rect               boundingRect;
  cv::Point2d            points[4];
  void                   NullTargets() {
    status   = 0;
    found    = "";
    center.x = 0;
    center.y = 0;
    height   = 0;
    width    = 0;
    area     = 0;
    LorR     = ' ';
    number   = 0;
    reason   = "";
    angle    = 0;
    ratio    = 0;
    offby    = 0;
    for (int i = 0; i < 4; i++) {
      points[i].x = 0;
      points[i].y = 0;
    }
  }
};

namespace Global {
extern bool             newFrame;
extern double           FrameWidth, FrameHeight;
extern bool             interupt;
extern bool             dataValid;
extern double           gyroAngle;
extern double           gyroVelocity;
extern double           driveAngle;
extern double           turn;
extern double           P, I, D;
extern Targets          target;
extern int              buttonPress;
extern bool             videoError;
extern int              videoSocket;
extern const cv::Scalar BLUE, RED, YELLOW, GREEN;

extern cv::Mat frame;

extern pthread_mutex_t frameMutex;
// extern pthread_mutex_t targetMutex;
// extern pthread_mutex_t positionMutex;

} // namespace Global

namespace Switches {
extern bool         SHOWORIG;
extern bool         SHOWHUE;
extern bool         SHOWTHRESH;
extern bool         SHOWTRACK;
extern bool         USESERVER;
extern bool         USECOLOR;
extern bool         DOPRINT;
extern bool         DISABLE_FRAME;
extern int          printTime;
extern double       InitPID[];
extern int          cameraInput;
} // namespace Switches


typedef struct {
  double x;
  double y;
  double z;
  double dist;
  double alpha1;
  double alpha2;
  double OffSetx;
  double speed;
  double turn;
  double gyro;
  double P;
  double I;
  double D;
  int    dataValid;
} Position;

inline void nullifyStruct(Position& pos) {
  pos.x         = 0;
  pos.z         = 0;
  pos.dist      = 0;
  pos.alpha1    = 0;
  pos.alpha2    = 0;
  pos.OffSetx   = 0;
  pos.speed     = 0;
  pos.turn      = 0;
  pos.gyro      = 0;
  pos.P         = 0;
  pos.I         = 0;
  pos.D         = 0;
  pos.dataValid = 0;
}

bool startThread(std::string name, void* params);
void initSolvePnP(cv::Mat im);
void findAnglePnP(cv::Mat im, Targets target, Position* position);
