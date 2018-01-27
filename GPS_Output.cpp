#include<ros/ros.h>
#include<ublox_gps/gps.h>
#include<iostream>
#include<stdio.h>
#include <string>
using namespace std;
//assume GPGGA output system
*char[] readAndOutput(char x[]){
	*char y[7][15];
	y[0]=x.substr(7,10);
	y[1]=x.substr(18,9);
	y[2]=x[28];
	y[3]=x.substr(30,10);
	y[4]=x[41];
	y[5]=x.substr(46,2);
	y[6]=x.substr(52,6];
	return y;
}
int main(in argc,char **argv){
	ros::Gps a;
	char data[100]; char* output[7];
	char hrMin[5];
	ros::init(argc,argv, "GPS_Output");
	ros::NodeHandle n;
	ros::Subscriber output = n.subscribe("ublox",10000,a);//infomation pass on to GPS
	double seconds,longitude,lattitude, numSat,altitude;

	while(!end){//need adding "end" interface
		data = getMessage(a);// No idea how to obtain the message, 
		//sample output 235317.000,4003.9039,N,10512.5793,W,1,08,1.6,1577.9,M,-20.7,M,,0000*5F
		*output=readAndOutput(data);
		//You can continue by merging time into a class.
		hrMin=output[0].substr(0,2)+':'+output.substr(2,2);
		seconds=parseDouble(output[0].substr(4,6));
		longtitude=parseDouble(output[1]);
		lattitude=parseDouble(output[3]);
		numSat=parseDouble(output[5]);
		altitude=parseDouble(output[6]);
		cout<<"Time: "+hrMin+" and "+seconds+" seconds in Greenwich mean time\nLongtitude: "+longtitude+","+output[2]+" is longitude in degrees decimal minutes\n Latitude: "+lattitude+","+output[4]+" is lattitude in degrees.decimal minutes\nNumber of satellites seen: "+numSat+" \nAltitude"+altitude+" meters"<<endl;
		for (int i=0;i<100;i++)data[i]=NULL;//RESET
		for (int j=0;j<7;j++)*output=NULL;
		//Other subteams can request and use the saved variables;
	}
}