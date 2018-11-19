#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main(int argc, char *argv[])
{
    vector<string> result;
    pcl::PointCloud<pcl::PointXYZRGB> cloud;
    pcl::PointXYZRGB p;
    string filename="";

    cout << "[*] This tool will convert your .xyz with rgb information into .pcd v7 file." << endl;
    cout << "[*] Write the .xyz filename, e.g. test.xyz : " << endl ;
    cin >> filename;

    ifstream xyz_file(filename);
    //Check that the input file has being successfully opened
    if(!(xyz_file.is_open())){
        cout << "[x] Cannot open file!" << endl;
    }

    string content = "";
    int i=0;
    while(getline(xyz_file,content))
    {
        boost::split(result, content, [](char c){return c == ' ';});
//        cout << "x: " << result[0] << " y: " << result[1] << " z: " << result[2] << endl;
        p.x = stof(result[0]);
        p.y = stof(result[1]);
        p.z = stof(result[2]);
        p.r = stof(result[3]);
        p.g = stof(result[4]);
        p.b = stof(result[5]);
        cloud.points.push_back(p);
        i++;
    }

    cloud.width = cloud.points.size();
    cout << "Number of points:" << cloud.width << endl;
    cloud.height = 1;
    cloud.points.resize (cloud.width * cloud.height);
    cloud.is_dense = false;
    xyz_file.close();
    pcl::io::savePCDFileASCII("../test.pcd", cloud);
    cout << "[*] Conversion finished!" << endl;
    return 0;
}
