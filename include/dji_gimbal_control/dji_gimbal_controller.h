#ifndef DJI_GIMBAL_CONTROLLER_H
#define DJI_GIMBAL_CONTROLLER_H

// DJI SDK includes
#include <dji_sdk/Gimbal.h>

// ROS includes
#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Joy.h>

#include "std_srvs/SetBool.h"

#define C_PI (double)3.141592653589793
#define DEG2RAD(DEG) ((DEG) * ((C_PI) / (180.0)))
#define RAD2DEG(RAD) ((RAD) * (180.0) / (C_PI))

class dji_gimbal_controller {
public:
	dji_gimbal_controller(ros::NodeHandle& nh);
	~dji_gimbal_controller(){};

	// Publish commands
	void publishGimbalCmd();

private:
	// Subscribers
	ros::Subscriber gimbalAngleSub;
	ros::Subscriber joySub;
	ros::Subscriber cameraInfoSub;
	ros::Subscriber tagPoseSub;

	// Publishers
	ros::Publisher gimbalSpeedPub;
	ros::Publisher gimbalAnglePub;

	// Services
	ros::ServiceServer facedownServ;
	ros::ServiceServer faceupServ;
	ros::ServiceServer setTrackingServ;

	// Callbacks
	void gimbalAngleCallback(const geometry_msgs::Vector3Stamped::ConstPtr& msg);
	void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);
	void cameraInfoCallback(const sensor_msgs::CameraInfo& msg);
	void tagCallback(const ar_track_alvar_msgs::AlvarMarkers& msg);
	
	// Service Callbacks
	bool facedownCallback(std_srvs::Trigger::Request &req,std_srvs::Trigger::Response &res);	
	bool faceupCallback(std_srvs::Trigger::Request &req,std_srvs::Trigger::Response &res);
	bool setTrackingCallback(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res);

	// Functions
	void initializeParam();
	void resetGimbalAngle();
	void faceDownwards();

	// Data
	bool tagFound;
	double fx, fy;
	double lastX,lastY;
	double velT, Kp,Kd;
	double tagX, tagY;

	bool trackTag;
	std::string cameraInfoTopic;
	std::string tagPoseTopic;
	int yawAxis, pitchAxis, rollAxis, resetButton, faceDownButton, toggleButton;
	geometry_msgs::Vector3Stamped gimbalAngle;
	geometry_msgs::Vector3Stamped speedCmd;
};

#endif //DJI_GIMBAL_CONTROL_H
