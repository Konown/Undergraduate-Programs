#include "robot.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "my_robot_node");
    ROS_INFO("My Robot is Starting ....");

    MyRobot robot;

    return 0;    
}

MyRobot::MyRobot(){
    ros::NodeHandle nh;
    ros::NodeHandle pri_nh("~");

    pri_nh.param<std::string>("odom_frame", odom_frame_, "odom");
    pri_nh.param<std::string>("base_frame", base_frame_, "base_footprint");
    pri_nh.param<std::string>("imu_frame", imu_frame_, "imu_link");

    pri_nh.param<std::string>("odom_topic", odom_topic_, "odom");
    pri_nh.param<std::string>("imu_topic", imu_topic_, "imu");

    pri_nh.param<std::string>("robot_port", serial_port_, "/dev/ttyAMA1");
    pri_nh.param<int>("robot_port_baud", serial_port_baud_, 115200);
    pri_nh.param<bool>("pub_odom_tf", pub_odom_tf_, true);

    odom_pub_ = nh.advertise<nav_msgs::Odometry>(odom_topic_, 50);
    imu_pub_ = nh.advertise<sensor_msgs::Imu>(imu_topic_, 50);
    
    cmd_vel_sub = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 100, &MyRobot::cmdVelCallback, this);
    
    memset(&pos_data_, 0, sizeof(pos_data_));

    ROS_INFO("My Robot Set serial %s at %d baud", serial_port_.c_str(), serial_port_baud_);

    if(openSerialPort()){
        try{
            boost::thread recvSerial_thread(boost::bind(&MyRobot::recvCallback, this));
        }
        catch(...){
            ROS_INFO("Tarkbot Robot can not open recvSerial_thread, Please check the serial port cable");

            ros::shutdown();
        }
        
    }else{
        ros::shutdown();
    }

    ROS_INFO("My Robot is Connected to STM32 board");

    ros::spin();
}

MyRobot::~MyRobot(){
    static uint8_t vel_data[11] = {0};
    uint8_t _cnt = 0;

    vel_data[_cnt++] = 0;
    vel_data[_cnt++] = 0;
    vel_data[_cnt++] = 0;
    vel_data[_cnt++] = 0;
    sendSerialPacket(_cnt, vel_data, ID_ROS2CTR_VEL);

    closeSeriaPort();
    
    ROS_INFO("My Robot is shutting dowm.");
}

bool MyRobot::openSerialPort(){
    if (serial_ptr_){
        ROS_INFO("The SerialPort is already opened!\r\n");
        return false;
    }

    serial_ptr_ = serial_ptr(new boost::asio::serial_port(io_service_));
    serial_ptr_->open(serial_port_, err_code_);

    if (err_code_){
        ROS_INFO("Open Port: %s Failed! Aboart!", serial_port_.c_str());
        return false;
    }

    serial_ptr_->set_option(boost::asio::serial_port_base::baud_rate(serial_port_baud_));
    serial_ptr_->set_option(boost::asio::serial_port_base::character_size(8));
    serial_ptr_->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    serial_ptr_->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    serial_ptr_->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
    
    return true;
}

void MyRobot::closeSeriaPort(){
    if (serial_ptr_){
        serial_ptr_->cancel();
        serial_ptr_->close();
        serial_ptr_.reset();
    }

    io_service_.stop();
    io_service_.reset();
}


void MyRobot::cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg){
    static uint8_t vel_data[11] = {0};
    uint8_t _cnt = 0;

    vel_data[_cnt++] = (int16_t)(msg->linear.x*1000);
    vel_data[_cnt++] = (int16_t)(msg->linear.x*1000)>>8;
    vel_data[_cnt++] = (int16_t)(msg->angular.z*1000);
    vel_data[_cnt++] = (int16_t)(msg->angular.z*1000)>>8;


    sendSerialPacket(_cnt, vel_data, ID_ROS2CTR_VEL);
}

void MyRobot::recvCallback(){
    uint8_t res=0;
    static uint8_t rx_buf[60]={0};
    static uint8_t rx_state=0, rx_num=0;
    uint8_t data_len = 0;

    while(1){
        boost::asio::read(*serial_ptr_.get(), boost::asio::buffer(&res, 1), err_code_);
        
        if(rx_state==0 && res==HeaderFrame1){
            rx_buf[rx_num++] = res;
            rx_state = 1;
        }
        else if(rx_state==1 && res==HeaderFrame2){
            rx_buf[rx_num++] = res;
            rx_state = 2;
        }
        else if(rx_state==2){
            rx_buf[rx_num++] = res;
            rx_state = 3;
        }
        else if(rx_state==3){
            rx_buf[rx_num++] = res;
            data_len = res;

            if (data_len>0 && data_len<=40){
                rx_state = 4;
            }
            else if(data_len == 0){
                rx_state = 5;
            }
            else{
                rx_state = 0;
                rx_num = 0;
            }
        }
        else if (rx_state==4){  
            if (data_len>0){
                data_len -= 1;
                rx_buf[rx_num++] = res;
                
                if(data_len == 0){
                    rx_state = 5;
                }
            }
        }
        else if(rx_state==5){
            uint8_t rx_checksum=0;
            for (uint8_t i = 0; i < rx_num; i++){
                rx_checksum += rx_buf[i];
            }
            if (rx_checksum == res){
                recvDataHandle(rx_buf);
            }
            rx_state = 0;
            rx_num = 0;
        }
        else{
            rx_state = 0;
            rx_num = 0;
        }
    }
}

void MyRobot::recvDataHandle(uint8_t* buffer_data){
    if(buffer_data[2] == ID_CPR2ROS_DATA){
        vel_data_.linear_x = ((double)((int16_t)(buffer_data[5]*256+buffer_data[4]))/1000);
        vel_data_.linear_y = 0;
        vel_data_.angular_z = ((double)((int16_t)(buffer_data[7]*256+buffer_data[6]))/1000);

        imu_data_.acc_x = (double)(((int16_t)(buffer_data[9]*256+buffer_data[8]))*ACC_RATIO);
        imu_data_.acc_y = (double)(((int16_t)(buffer_data[11]*256+buffer_data[10]))*ACC_RATIO);
        imu_data_.acc_z = (double)(((int16_t)(buffer_data[13]*256+buffer_data[12]))*ACC_RATIO);

        imu_data_.gyro_x = (double)(((int16_t)(buffer_data[15]*256+buffer_data[14]))*GYRO_RATIO);
        imu_data_.gyro_x = (double)(((int16_t)(buffer_data[17]*256+buffer_data[16]))*GYRO_RATIO);
        imu_data_.gyro_x = (double)(((int16_t)(buffer_data[19]*256+buffer_data[18]))*GYRO_RATIO);

        imu_data_.angle_x = (double)(((int16_t)(buffer_data[21]*256+buffer_data[20]))*ANGLE_RATIO);
        imu_data_.angle_y = (double)(((int16_t)(buffer_data[23]*256+buffer_data[22]))*ANGLE_RATIO);
        imu_data_.angle_z = (double)(((int16_t)(buffer_data[25]*256+buffer_data[24]))*ANGLE_RATIO);

        pos_data_.pos_x += (vel_data_.linear_x*cos(pos_data_.angular_z) - vel_data_.linear_y*sin(pos_data_.angular_z)) * DATA_PERIOD;
        pos_data_.pos_y += (vel_data_.linear_x*sin(pos_data_.angular_z) + vel_data_.linear_y*cos(pos_data_.angular_z)) * DATA_PERIOD;
        pos_data_.angular_z += vel_data_.angular_z * DATA_PERIOD;

        calculateImuQuaternion(imu_data_);

        publishOdom();
        publishImu();
        publishOdomTF();
    }

    ROS_INFO("speed:%.2f\t angular:%.2f", vel_data_.linear_x, vel_data_.angular_z);
}

void MyRobot::calculateImuQuaternion(struct imu_data imu_cel){
    tf2::Quaternion qtn;
    qtn.setRPY(imu_data_.angle_x, imu_data_.angle_y, imu_data_.angle_z);

    orient_data_.x = qtn.getX();
    orient_data_.y = qtn.getY();
    orient_data_.z = qtn.getZ();
    orient_data_.w = qtn.getW();
}

void MyRobot::publishOdom(){
    tf2::Quaternion odom_quat;
    odom_quat.setRPY(0, 0, pos_data_.angular_z);

    odom_msgs_.header.stamp = ros::Time::now();
    odom_msgs_.header.frame_id = odom_frame_;
    odom_msgs_.child_frame_id = base_frame_;
    odom_msgs_.pose.pose.position.x = pos_data_.pos_x;
    odom_msgs_.pose.pose.position.y = pos_data_.pos_y;
    odom_msgs_.pose.pose.position.z = 0;
    odom_msgs_.pose.pose.orientation.x = odom_quat.getX();
    odom_msgs_.pose.pose.orientation.y = odom_quat.getY();
    odom_msgs_.pose.pose.orientation.z = odom_quat.getZ();
    odom_msgs_.pose.pose.orientation.w = odom_quat.getW();
    odom_msgs_.twist.twist.linear.x = vel_data_.linear_x;
    odom_msgs_.twist.twist.linear.y = vel_data_.linear_y;
    odom_msgs_.twist.twist.angular.z = vel_data_.angular_z;

    if (vel_data_.linear_x==0 && vel_data_.linear_y==0 && vel_data_.angular_z==0){
        odom_msgs_.pose.covariance = {  1e-9,   0,  0,  0,  0,  0,
                                        0,  1e-3,   1e-9,   0,  0,  0,
                                        0,  0,  1e6,    0,  0,  0,
                                        0,  0,  0,  0,  1e6,    0,
                                        0,  0,  0,  0,  0,  1e-9 };

        odom_msgs_.twist.covariance = { 1e-9,   0,  0,  0,  0,  0,
                                        0,  1e-3,   1e-9,   0,  0,  0,
                                        0,  0,  0,  1e6,    0,  0,
                                        0,  0,  0,  0,  1e6,    0,
                                        0,  0,  0,  0,  0,  1e-9 };
    }
    else{
        odom_msgs_.pose.covariance = {  1e-3,   0,  0,  0,  0,  0,
                                        0,  1e-3,   0,  0,  0,  0,
                                        0,  0,  1e6,    0,  0,  0,
                                        0,  0,  0,  1e6,    0,  0,
                                        0,  0,  0,  0,  1e6,    0,
                                        0,  0,  0,  0,  0,  1e3 };

        odom_msgs_.pose.covariance = {  1e-3,   0,  0,  0,  0,  0,
                                        0,  1e-3,   0,  0,  0,  0,
                                        0,  0,  1e6,    0,  0,  0,
                                        0,  0,  0,  1e6,    0,  0,
                                        0,  0,  0,  0,  1e6,    0,
                                        0,  0,  0,  0,  0,  1e3 };
    }

    odom_pub_.publish(odom_msgs_);
}

void MyRobot::publishImu(){
    imu_msgs_.header.stamp = ros::Time::now();
    imu_msgs_.header.frame_id = imu_frame_;
    imu_msgs_.angular_velocity.x = imu_data_.gyro_x;
    imu_msgs_.angular_velocity.y = imu_data_.gyro_y;
    imu_msgs_.angular_velocity.z = imu_data_.gyro_z;
    imu_msgs_.linear_acceleration.x = imu_data_.acc_x;
    imu_msgs_.linear_acceleration.y = imu_data_.acc_y;
    imu_msgs_.linear_acceleration.z = imu_data_.acc_z;
    imu_msgs_.orientation.x = orient_data_.x;
    imu_msgs_.orientation.y = orient_data_.y;
    imu_msgs_.orientation.z = orient_data_.z;
    imu_msgs_.orientation.w = orient_data_.w;

    imu_msgs_.orientation.x = 0;
    imu_msgs_.orientation.y = 0;

    imu_msgs_.orientation_covariance = {    1e6,    0,  0,
                                            0,  1e6,    0,
                                            0,  0,  1e-6 };
    imu_msgs_.angular_velocity_covariance = {   1e6,  0,  0,
                                                0,  1e6,    0,
                                                0,  0,  1e-6};
    imu_msgs_.linear_acceleration_covariance = {    0,  0,  0,
                                                    0,  0,  0, 
                                                    0,  0,  0};

    imu_pub_.publish(imu_msgs_);
}

void MyRobot::publishOdomTF(){
    if (pub_odom_tf_ == true){
        tf2::Quaternion q;
        q.setRPY(0, 0, pos_data_.angular_z);
 
        transform_stamped_.header.stamp = ros::Time::now();
        transform_stamped_.header.frame_id = odom_frame_;
        transform_stamped_.child_frame_id = base_frame_;

        transform_stamped_.transform.translation.x = pos_data_.pos_x;
        transform_stamped_.transform.translation.y = pos_data_.pos_y;
        transform_stamped_.transform.translation.z = 0.0;

        transform_stamped_.transform.rotation.x = q.getX();
        transform_stamped_.transform.rotation.y = q.getY();
        transform_stamped_.transform.rotation.z = q.getZ();
        transform_stamped_.transform.rotation.w = q.getW();

        transform_broadcaster_.sendTransform(transform_stamped_);
    }
}

void MyRobot::sendSerialPacket(uint8_t len, uint8_t* pbuf, uint8_t id){
    uint8_t _cnt=0, tx_buf[64]={0};

    tx_buf[_cnt++] = HeaderFrame1;
    tx_buf[_cnt++] = HeaderFrame2;
    tx_buf[_cnt++] = id;
    tx_buf[_cnt++] = len;
    for (uint8_t i = 0; i < len; i++){
        tx_buf[_cnt++] = *(pbuf + i);
    }
    
    uint8_t _sumcheck=0;
    for (uint8_t i = 0; i < _cnt; i++){
        _sumcheck += tx_buf[i];
    }
    
    tx_buf[_cnt++] = _sumcheck;

    boost::asio::write(*serial_ptr_.get(), boost::asio::buffer(tx_buf, _cnt), err_code_);
}


