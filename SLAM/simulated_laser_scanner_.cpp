#include <assert.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <csignal>
#include <cstdio>

#include "driver_base/driver.h"
#include "driver_base/driver_node.h"
#include <diagnostic_updater/publisher.h>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "hokuyo_node/HokuyoConfig.h"
#include "hokuyo/hokuyo.h"
#include "hokuyo/LMS1xx.h"

#define DEG2RAD M_PI/180.0

using namespace std;
/*****************************************************************
class HokuyoDriver : public driver_base::Driver
class HokuyoNode : public driver_base::DriverNode<HokuyoDriver>
return driver_base::main<HokuyoNode>(argc, argv, "hokuyo_node");
*****************************************************************/


#include <fstream>
using namespace std;
void testByChar()
{
	fstream testByCharFile;
	char c;
	testByCharFile.open("1saic05.txt", ios::in);
	while (!testByCharFile.eof())
	{
		//ROS_INFO("Stuck here!!!");
		testByCharFile >> c;
		//cout<<c;
	}
	testByCharFile.close();
}
/*inline float first_number(char buffer)//将字符数组的第一个数据提取出存入距离数组
{

float number=;
number=()/1000.0;
return number;
}*/
int testByLine()
{
	scanData data;

	char buffer[256];
	fstream outFile;
	//outFile.open("Hokuyo Data/test.txt",ios::in);
	outFile.open("1saic05.txt", ios::in);
	if (!outFile){ cout << "error while opening file" << endl; }
	cout << "1saic05.txt" << "--- all file is as follows:---" << endl;
	int count_frames = 0;
	int count_scan = 0;

	while (!outFile.eof() && count_frames<20000)
	{
		if (count_scan == 280){
			count_frames++;
			cout << endl << "********************current scan frame number:" << count_frames << "********************" << endl << "ranges[]:";
			count_scan = 0;
		}
		outFile.getline(buffer, 256, '\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

		// cout<<buffer<<'\n';

		char* tok = strtok(buffer, " "); //distance(m)
		//char* tok =strtok(buffer,"")
		//cout<<"first number:"<<tok<<endl;
		float dat;
		sscanf(tok, "%e", &dat);
		//
		data.dist_len1 = 280;
		data.dist1[count_scan] = dat;
		cout << ' ' << data.dist1[count_scan] << ' ';
		data.rssi_len1 = 0;

		//one_frame_of_laser_scans[count_scan][count_frames]=dat;
		//ROS_INFO("frame number:%d  laser scan info:%d  ",count_scan,dat);
		// cout<<dat<<' ';
		count_scan++;

	}
	outFile.close();
	return 0;
}

/*int main(int argc, char **argv)
{
ROS_INFO("readin:testByChar() ");
testByChar();
ROS_INFO("output to file:testByLine()");
testByLine();

}
*/



int main(int argc, char **argv)
{
	// laser data
	//LMS1xx laser;
	scanCfg cfg;
	scanDataCfg dataCfg;
	scanData data;
	// published data
	sensor_msgs::LaserScan scan_msg;
	// parameters
	//std::string host;
	std::string frame_id;

	ros::init(argc, argv, "lms1XX");
	ros::NodeHandle nh;
	ros::NodeHandle n("~");
	ros::Publisher scan_pub = nh.advertise<sensor_msgs::LaserScan>("scan", 1);

	// initialize hardware
	//laser.connect(host);

	//if (laser.isConnected())
	//{
	ROS_INFO("Connected to fake laser.");

	//laser.login();
	//cfg = laser.getScanCfg();
	//cfg.angleResolution=(1/3.14)*180/280;//0.2
	//cfg.startAngle=(-0.5/3.14)*18000;
	//cfg.stopAngle=(0.5/3.14)*18000;
	frame_id = "laser";
	scan_msg.header.frame_id = frame_id;

	scan_msg.range_min = 0.01;
	scan_msg.range_max = 50.0;

	scan_msg.scan_time = 100.0 / 20;//100.0/cfg.scaningFrequency

	//scan_msg.angle_increment = (double)cfg.angleResolution/10000.0 * DEG2RAD;
	//scan_msg.angle_min = (double)cfg.startAngle/10000.0 * DEG2RAD - M_PI/2;
	//scan_msg.angle_max = (double)cfg.stopAngle/10000.0 * DEG2RAD - M_PI/2;
	scan_msg.angle_increment = 0.2*DEG2RAD;
	scan_msg.angle_min = -0.5;
	scan_msg.angle_max = 0.5;
	//std::cout << "resolution : " << (double)cfg.angleResolution/100.0 << " deg " << std::endl;
	//std::cout << "frequency : " << (double)cfg.scaningFrequency/100.0 << " Hz " << std::endl;
	std::cout << "resolution : " << 0.2 << " deg " << std::endl;
	std::cout << "frequency : " << "not applied" << "" << std::endl;
	int num_values = 280;
	/*
	if (cfg.angleResolution == 2500)
	{
	num_values = 1081;
	}
	else if (cfg.angleResolution == 5000)
	{
	num_values = 541;
	}
	else
	{
	ROS_ERROR("Unsupported resolution");
	return 0;
	}
	*/
	scan_msg.time_increment = scan_msg.scan_time / num_values;

	scan_msg.ranges.resize(num_values);
	//scan_msg.intensities.resize(num_values);

	dataCfg.outputChannel = 1;
	dataCfg.remission = true;
	dataCfg.resolution = 1;
	dataCfg.encoder = 0;
	dataCfg.position = false;
	dataCfg.deviceName = false;
	dataCfg.outputInterval = 1;

	//laser.setScanDataCfg(dataCfg);

	//laser.startMeas();

	//status_t stat;
	//do // wait for ready status
	//{
	//  stat = laser.queryStatus();
	//  ros::Duration(1.0).sleep();
	//}
	//while (stat != ready_for_measurement);

	//laser.startDevice(); // Log out to properly re-enable system after config

	//laser.scanContinous(1);
	char buffer[256];
	fstream outFile;
	//outFile.open("Hokuyo Data/test.txt",ios::in);
	outFile.open("1saic05.txt", ios::in);
	if (!outFile){ cout << "error while opening file" << endl; }
	cout << "1saic05.txt" << "--- all file is as follows:---" << endl;
	int count_frames = 0;
	int count_scan = 0;
	scan_msg.header.seq = 0;
	while (!outFile.eof() && count_frames<2010)//&&ros::ok()
	{
		//outFile.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

		ros::Time start = ros::Time::now();

		scan_msg.header.stamp = start;
		++scan_msg.header.seq;

		//laser.getData(data);
		ROS_INFO("output to data");

		if (count_scan == 280){
			count_frames++;

			cout << endl << "********************current scan frame number:" << count_frames << "********************" << endl;
			count_scan = 0;
		}
		outFile.getline(buffer, 256, '\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

		//cout<<buffer<<'\n';

		char* tok = strtok(buffer, " "); //distance(m)
		//cout<<"first number:"<<tok<<endl;
		tok = strtok(NULL, " "); //Command
		//cout<<"second number:"<<tok<<endl;
		tok = strtok(NULL, " "); //VersionNumber
		//cout<<"3rd number:"<<tok<<endl;	
		tok = strtok(NULL, " "); //DeviceNumber
		//cout<<"4th number:"<<tok<<endl;
		tok = strtok(NULL, " "); //Serial number
		//cout<<"5th number:"<<tok<<endl;
		tok = strtok(NULL, " "); //DeviceStatus
		//cout<<"6th number:"<<tok<<endl;
		tok = strtok(NULL, " "); //DeviceStatus
		cout << "7th number:" << tok << endl;
		float dat;
		sscanf(tok, "%f", &dat);
		//
		data.dist_len1 = 280;
		data.dist1[count_scan] = dat;
		//cout<<' '<<data.dist1[count_scan]<<' ';
		data.rssi_len1 = 0;
		count_scan++;

		for (int i = 0; i < data.dist_len1; i++)
		{
			scan_msg.ranges[i] = data.dist1[i];//精度实验
		}

		//for (int i = 0; i < data.rssi_len1; i++)
		//{
		//  scan_msg.intensities[i] = data.rssi1[i];
		//}

		scan_pub.publish(scan_msg);

		ros::spinOnce();
	}
	outFile.close();
	//laser.scanContinous(0);
	//laser.stopMeas();
	//laser.disconnect();
	//}
	// else
	// {
	//   ROS_ERROR("Connection to device failed");
	// }
	return 0;
}











