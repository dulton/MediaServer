#ifndef _CAM_ANA_THREAD_H_
#define _CAM_ANA_THREAD_H_

#include "Common.h"

#include "region/region.h"
#include "fire/VideoHandler.h"
#include "fire/fire.h"
#include "somke/smoke.h"
#include "human/human.h"

#define START_FRAME_INDEX     8
#define INTERVAL_FRAME_INDEX  100
#define STOP_FRAME_INDEX      40

enum warnevent{
    alarmOn   = 0x01;
    alarmStop = 0x02;
};

class CamAnaThread
{
public:
  CamAnaThread(CCamThread* &camera,uint8 ID);
  ~CamAnaThread();

  CCamThread* m_AlarmCamera;
  bool  m_AlarmFlag;
  bool  m_Status;

  Mat frame1;
  Mat frame2;

  uint16 WarnType;
  uint8  alarm;

  uint32 frame;
  uint32 alarmStartframe;
  uint32 alarmStopframe;
  uint8  startflag;
  uint8  stopflag;
  uint8  intervalflag;

  CRegion* region;
  VideoHandler* videoHandler ;
  CFire*   fire;
  CSmoke*  smoke;
  CHuman*  human;

  int alarmStrategy();

  int human_detect(Mat &frame);
  int region_detect(Mat &frame);
  int fire_detect(Mat &frame);
  int smoke_detect(Mat &frame);

  int alarm_run(Mat &frame ,uint8 iType);
  void resource_release();


  void run();
	int  CreateAnaThread();
	static void* RunAnaThread(void*  param){
		CamAnaThread* p = (CamAnaThread*)param;
		p->run();
		return NULL;
	}
  void quit(){ m_AlarmFlag = false;}
  void resume();
  void pause();

private:
  uint8 CameraID;
  uint8 AnaIndex;

  pthread_mutex_t mut;
  pthread_cond_t cond;
};

#endif
