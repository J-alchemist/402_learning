#! /bin/bash

ws_code=$1
DIR=$(pwd)
if [ "${DIR}" == "/home/gj" ];then
	echo ${DIR}
else
	cd /home/gj
	echo $(pwd)
fi

if [ $# -eq 1 ];then
	if [ ! -d my_ws$ws_code ];then
		mkdir -p ./my_ws$ws_code/src
	else
		echo "error: ws already exist!"
		exit -1
	fi
else
	echo "error: argc!"
	exit -1
fi

cd ./my_ws$ws_code/src
catkin_init_workspace

cd ..
catkin_make

echo "source ~/my_ws$ws_code/devel/setup.bash" 1>> /home/gj/.bashrc
source ~/my_ws$ws_code/devel/setup.bash

echo "ros_ws make finished!"





