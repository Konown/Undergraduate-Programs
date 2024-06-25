#ifndef MY_ROBOT_H
#define MY_ROBOT_H

// C header file
#include <memory>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <termios.h>

// Boost header file
#include "boost/asio.hpp"
#include "boost/asio/serial_port.hpp"
#include "boost/system/error_code.hpp"
#include "boost/system/system_error.hpp"
#include "boost/bind.hpp"
#include "boost/thread.hpp"

// ros header file
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"



// Communication Frame
#define HeaderFrame1 0xAA
#define HeaderFrame2 0xBB
#define ID_CPR2ROS_DATA  0x10
#define ID_ROS2CTR_VEL 0x50

// IMU data transformation
// ac +-16g
#define ACC_RATIO (16*9.8/32768)
// gyro +- 2000deg/s
#define GYRO_RATIO (2000/32768)
// angle +-180
#define ANGLE_RATIO (180/32768)

// control period
#define DATA_PERIOD 0.02f


typedef boost::shared_ptr<boost::asio::serial_port> serial_ptr;

struct velocity_data{
    float linear_x;
    float linear_y;
    float angular_z;
};

struct imu_data{
    float acc_x;
    float acc_y;
    float acc_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float angle_x;
    float angle_y;
    float angle_z;
};

struct imu_orientation_data{
    float w;
    float x;
    float y;
    float z;
};

struct pose_data{
    float pos_x;
    float pos_y;
    float angular_z;
};


class MyRobot
{
    public:
        MyRobot();
        ~MyRobot();
    
    private:
        // Uart Control
        bool openSerialPort();
        void closeSeriaPort();

        // Send
        void sendSerialPacket(uint8_t len, uint8_t* pbuf, uint8_t id);

        // multi threading receive function
        void recvCallback();
        void recvDataHandle(uint8_t* buffer_data);

        // speed call function
        void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg);

        void publishOdom();
        void publishImu();
        void publishOdomTF();

        void calculateImuQuaternion(struct imu_data imu_cel);

        // Uart Pointer
        std::string serial_port_;
        int serial_port_baud_;
        boost::shared_ptr<boost::asio::serial_port> serial_ptr_;
        boost::system::error_code err_code_;
        boost::asio::io_service io_service_;
        
        // data defination
        struct imu_data imu_data_;
        struct imu_orientation_data orient_data_;
        struct velocity_data vel_data_;
        struct pose_data pos_data_;

        // Frame
        std::string odom_frame_;
        std::string base_frame_;
        std::string imu_frame_;

        // topic
        std::string odom_topic_;
        std::string imu_topic_;

        // message
        nav_msgs::Odometry odom_msgs_;
        sensor_msgs::Imu imu_msgs_;

        ros::Publisher odom_pub_;
        ros::Publisher imu_pub_;
        
        ros::Subscriber cmd_vel_sub;

        bool pub_odom_tf_;
        geometry_msgs::TransformStamped transform_stamped_;
        tf2_ros::TransformBroadcaster transform_broadcaster_;
};


#endif



