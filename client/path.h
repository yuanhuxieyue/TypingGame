#ifndef _PATH_H_
#define _PATH_H_

#include "vector2.h"

#include <vector>

// 对前进路径的封装
class Path
{
public:
	// 传入顶点数组，遍历计算每一个顶点与前一个顶点的片段距离
	Path(const std::vector<Vector2>& point_list)
	{
		this->point_list = point_list;

		for (size_t i = 1; i < point_list.size(); ++i)
		{
			float segment_len = (point_list[i] - point_list[i - 1]).length();
			segment_len_list.push_back(segment_len);
			total_length += segment_len;
		}
	}

	~Path() = default;

	// 获取指定进度坐标方法
	Vector2 get_position_at_progress(float progress) const
	{
		if (progress <= 0) return point_list.front();
		if (progress >= 1) return point_list.back();

		float target_distance = total_length * progress;

		float accumulated_len = 0.0f;
		// 对所有路径进行累加
		for (size_t i = 1; i < point_list.size(); ++i) 
		{
			accumulated_len += segment_len_list[i - 1];
			// 超过当前距离
			if (accumulated_len >= target_distance)
			{
				// 计算线段内剩余距离,找到目标在线段内的进度
				float segment_progress = (target_distance - (accumulated_len - segment_len_list[i - 1])) / segment_len_list[i - 1];
				return point_list[i - 1] + (point_list[i] - point_list[i - 1]) * segment_progress;
			}
		}
		return point_list.back();
	}

private:
	float total_length = 0; // 路径总长度
	std::vector<Vector2> point_list; // 存储所有顶点的位置坐标
	std::vector<float> segment_len_list; // 两顶点之间路径长度

};

#endif // !_PATH_H_
