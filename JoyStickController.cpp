#include "ControllerEvent.h"
#include "Controller.h"
#include "Logger.h"
#include <iostream>
// #include <boost/python.hpp>
// #include <Python.h>
// #include <dlfcn.h>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>

#define PI 3.141592      
#define DEG2RAD(DEG) ( (PI) * (DEG) / 180.0 )


// namespace py = boost::python; // create namespace variable for boost::python
using namespace std;

// std::string parse_python_exception(); // functional declaration for exception handling

// template <typename T> string tostr(const T& t) { ostringstream os; os<<t; return os.str(); } // template to convert double variables to string

  
class MyController : public Controller {  
public:  
  void onInit(InitEvent &evt);  
  double onAction(ActionEvent&);
  void onRecvMsg(RecvMsgEvent &evt); 
  void onCollision(CollisionEvent &evt);  

  RobotObj *my;  
  double Weel_one;  
  double Weel_two;   
 


// private:
//   RobotObj *my;  
//   double Weel_one;  
//   double Weel_two;  
 
};  



static double val3_no = 0;
static double val1_no = 0;
static double val2_no = 0;

static int axis = 0;  



static int messageCount;

static int onActionCount;

static int flag=1;

static Vector3d pos;


  
void MyController::onInit(InitEvent &evt) {  

  // SimObj *obj = getObj(myname());

  Weel_one = 0.0;  
  Weel_two = 0.0;  
  my = this->getRobotObj(this->myname());  
  my->setWheel(10.0, 10.0);  
 
}  
  
double MyController::onAction(ActionEvent &evt) {  
  //return 1.0;
  // SimObj *obj = getObj(myname());
  // my = this->getRobotObj(this->myname());  
  my->setWheelVelocity(Weel_one,Weel_two);
 
 

return 0.00001;
      
} 

  std::string msg = " ";

  void MyController::onRecvMsg(RecvMsgEvent &evt)
{

  SimObj *my = getObj(myname());

  timeval a;
  timeval b;



  char *all_msg = (char*)evt.getMsg();
  // std::string msg;
  msg= evt.getMsg();
  // cout << " msg is " << msg.c_str() << endl;


  char val1[10] = " ";
  char val2[10] = " ";
  char val3[10] = " ";

  char roll_angle[10]=" "; 
  char pitch_angle[10]=" ";
  char yaw_angle[10]=" ";



  int result=0;

  result = sscanf(msg.c_str(), "%[^','],%[^','],%[^',']", val1, val2, val3); 

  val1_no = atof(val1);
  val2_no = atof(val2); 
  val3_no= atof(val3);


  // The loop below gets the values of the button. '9' is the identifier set by programmer for button related data.

  if (int(val1_no == 9)) 
  {

    // val2_no gets the number of button and val3_no gets the boolean value representing whether the button is OFF or ON.
    cout << "Button " << int(val2_no) << ":  " << int(val3_no) << endl; 
    if (val2_no == 12)
    {
      cout << "__________________" <<endl; 
      cout << "The Axes positions are " << endl;
      
    }

    // Here we make a test, in which robot's wheel velocity is changed depending on the button press
    // Button 1: Move Forward
    // Button 2: Move Backward
    // Button 3: Turn Left
    // Button 4: Turn Right
    // Button 5: Stop

    // Button 1: Move Forward
    if ( val2_no == 1 and val3_no == 1)
    {
      Weel_one = 3.0;  
      Weel_two = 3.0;  
    }

     // Button 2: Move Backward
    if ( val2_no == 2 and val3_no == 1)
    {
      Weel_one = -3.0;  
      Weel_two = -3.0;  
    }

    // Button 3: Turn Left
    if ( val2_no == 3 and val3_no == 1)
    {
      Weel_one = -0.78;  
      Weel_two =  0.78;   
    }
  
    // Button 4: Turn Right
    if ( val2_no == 4 and val3_no == 1)
    {
      Weel_one =   0.78;  
      Weel_two =  -0.78;   
    }
  

    // Button 5: Stop
     if ( val2_no == 5 and val3_no == 1)
    {
      Weel_one =   0;  
      Weel_two =   0;   
    }

  }

  // the loop below gets the postions of the axes.

  else {

    // val2_no gets the number of axix and val3_no gets the position of axis
    cout << "Axis " << int(val2_no) << ":  "<< setprecision (2) << val3_no << endl; 
    if (val2_no == 4)
    {
      cout << "__________________" <<endl; 
      cout << "The Button status is: " << endl;
      
    }
 
  }

 

  messageCount++;
  // std::cout << "The mesage count is" << messageCount <<std::endl;

 

}


  

void MyController::onCollision(CollisionEvent &evt) { 
}


extern "C" Controller * createController() {  
  return new MyController;  
}  


