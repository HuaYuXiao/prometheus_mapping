//
// Created by Eason Hua on 5/2/24.
//

#ifndef MERGE_PC2_H
#define MERGE_PC2_H

#include <deque>
#include <mutex>
#include <vector>
#include <exception>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf/transform_listener.h>

#include "merge_pc2/icp_utils.h"

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class mergePC2 {
public:
    mergePC2(ros::NodeHandle nh);
    ~mergePC2() = default;

    // Method to process buffers
    void sync_process();

private:
    int dura_d;
    std::chrono::milliseconds dura;

    // Subscribers
    std::vector<std::string> pc2_topics_in;
    size_t hardware_concurrency;
    std::vector<ros::Subscriber> pc2_subs;

    double timeout;

    // Transform listener
    tf::TransformListener tf_listener;

    icpUtils icp_utils;

    // Buffers to store point clouds
    std::deque<PointCloudT::Ptr> pcT_buffer;
    std::mutex buffer_mutex;

    // Publisher
    std::string pc2_topic_out;
    std::string pc2_frame_out;
    sensor_msgs::PointCloud2 pc2_out;
    ros::Publisher pc2_pub;

    // Unified callback for point cloud subscribers
    void pc2Callback(const sensor_msgs::PointCloud2ConstPtr& pc2, const size_t index);
};

#endif // MERGE_PC2_H
