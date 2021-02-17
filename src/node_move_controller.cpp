#include "ros_compat.h"
#include <string>
#include <rclcpp/rclcpp.hpp>


// input detection subscriber callback
void det_callback( const vision_msgs::Detection2DArray::SharedPtr input){

	for (vision_msgs::Detection2D detMsg : input->detections){
		
		auto det_result  = detMsg.results[0];

		
		ROS_INFO("detected class #%s confidence=%f bbox center(%f, %f) size w=%f  h=%f", \
		det_result.id.c_str(), det_result.score, detMsg.bbox.center.x, detMsg.bbox.center.y, detMsg.bbox.size_x, detMsg.bbox.size_y);

		
		if (320 < detMsg.bbox.center.x and detMsg.bbox.center.x < 640 and 180 < detMsg.bbox.center.y and detMsg.bbox.center.y < 360){
			if (detMsg.bbox.size_x > 60 and detMsg.bbox.size_y > 60){
				ROS_INFO("\n \n Slow Down ! You're getting too closed to the %s ahead. \n \n", det_result.id.c_str());
			}
		}
		
		
	}

}


// node main loop
int main(int argc, char **argv){

    /*
	 * create node instance
	 */
    ROS_CREATE_NODE("move_controller");


    /*
	 * subscribe to image topic
	 */
	auto det_sub = ROS_CREATE_SUBSCRIBER(vision_msgs::Detection2DArray, "detections", 1000, det_callback);


    /*
	 * wait for messages
	 */
	ROS_INFO("move_controller node initialized, waiting for messages");
	ROS_SPIN();

    return 0;

    
}