#pragma once
#include "opencv2/opencv.hpp"
#include <stdint.h>

namespace qs {
	struct IMU {
		double timestamp = .0;
		double gravity[3] = { .0, .0, .0 };
		double userAccleration[3] = { .0, .0, .0 };
		double attitude[3] = { .0, .0, .0 };

		cv::Vec3d cvGravity();
		cv::Vec3d cvUserAccleration();
		cv::Vec3d cvAttitude();
	};

	struct GPS {
		double timestamp = .0;
		double latitude = .0, longitude = .0, altitude = .0;
		double horizontalAccuracy = .0, verticalAccuracy = .0;

		cv::Vec3d cvGPS();
	};

	struct AR {
		float intrinsics[3][3]       = { { .0f, .0f, .0f }, { .0f, .0f, .0f }, { .0f, .0f, .0f } };
		float projectionMatrix[4][4] = { { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f } };
		float viewMatrix[4][4]       = { { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f }, { .0f, .0f, .0f, .0f } };

		cv::Mat cvIntrinsics();
		cv::Mat cvProjectionMatrix();
		cv::Mat cvViewMatrix();
	};

	struct Camera {
		/*
			メモ
			OpenCV 4.x より、cv::Matにムーブコンストラクタとムーブ代入演算子が実装された。
			そのため、Cameraには暗黙的にコピーコンストラクタ、ムーブコンストラクタ、コピー代入演算子、ムーブ代入演算子が定義される。
			また、cv::Matは内部で参照カウンタを持っており、通常のコピーではデータの参照先は同じになる。
			そのため、深いコピーを行うときにはCamera::clone()メソッドを使用する。
		*/

		double timestamp = .0;
		cv::Mat color;
		cv::Mat depth;
		cv::Mat confidence;
		AR ar;

		Camera clone() const;
	};

	struct QuadFrame {
		double timestamp = .0;
		Camera camera;
		IMU imu;
		GPS gps;

		QuadFrame clone() const;
	};
}
