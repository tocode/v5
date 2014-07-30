#ifndef SKELETONANIMATION_H
#define SKELETONANIMATION_H

#include "Mathematics.h"

class Joint
{
public:
	std::string					name;
	Joint*						father;
	std::vector<Joint*>			children;
	Matrix4						offset;
	Matrix4						local;
	//Matrix4						global;
	//int							channel_index;
	Matrix4 CalculateGlobal()
	{
		if (father)
		{
			Matrix4 m = father->CalculateGlobal();
			return m*local;
		}
		else
			return local;
	}
};

class Skeleton
{
public:
	Joint*						root;
	vector<Joint*>				joints;
	map<string,Joint*>			joint_by_name;
	void Update(map<string,Matrix4>& transforms)
	{
		for (auto it=transforms.begin(); it!=transforms.end(); it++)
			if (joint_by_name.find(it->first)!=joint_by_name.end())
				joint_by_name[it->first]->local = it->second;
	}
	vector<Matrix4> GetBoneMatrix()
	{
		vector<Matrix4> matrices;
		for (int i=0; i<joints.size(); i++)
			if (1)
			{
				Matrix4 global = joints[i]->CalculateGlobal();
				Matrix4 off = joints[i]->offset;
				Matrix4 r = global*off;
				matrices.push_back(Transpose(joints[i]->CalculateGlobal()*joints[i]->offset));
			}
			else
				matrices.push_back(Identity());
		return matrices;
	}
};

struct PositionFrame
{
public:
	float						time;
	Vector3						position;
public:
	PositionFrame(float time,Vector3 position)
	{
		this->time = time;
		this->position = position;
	}
};
struct ScaleFrame
{
public:
	float						time;
	Vector3						scale;
public:
	ScaleFrame(float time,Vector3 scale)
	{
		this->time = time;
		this->scale = scale;
	}
};
struct RotationFrame
{
public:
	float						time;
	Quaternion					rotation;
public:
	RotationFrame(float time,Quaternion rotation)
	{
		this->time = time;
		this->rotation = rotation;
	}
};

struct Channel
{
public:
	string						joint_name;
	vector<PositionFrame>		position_frames;
	vector<ScaleFrame>			scale_frames;
	vector<RotationFrame>		rotation_frames;
};

class Animation
{
public:
	float						duration;
	vector<Channel>				channels;
public:
	void AnimateSkeleton(Skeleton* skeleton,float time)
	{
		assert(time>=0);
		assert(time<duration);

		map<string,Matrix4> transforms;

		for (int k=0; k<channels.size(); k++)
		{
			int frame = -1;
			float factor = -1;
			for (int i=0; i<int(channels[k].position_frames.size()-1); i++)
			{
				float time1 = channels[k].position_frames[i].time;
				float time2 = channels[k].position_frames[i+1].time;
				if ( time>=time1 && time<time2 )
				{
					frame = i;
					factor = (time-time1)/(time2-time1);
					break;
				}
			}
			//frame = -1;
			Vector3 present_position = (frame!=-1) ? (1-factor)*channels[k].position_frames[frame].position + factor*channels[k].position_frames[frame+1].position : Vector3(0,0,0);

			frame = -1;
			factor = -1;
			for (int i=0; i<int(channels[k].scale_frames.size()-1); i++)
			{
				float time1 = channels[k].scale_frames[i].time;
				float time2 = channels[k].scale_frames[i+1].time;
				if ( time>=time1 && time<time2 )
				{
					frame = i;
					factor = (time-time1)/(time2-time1);
					break;
				}
			}
			//frame = -1;
			Vector3 present_scale = (frame!=-1) ? (1-factor)*channels[k].scale_frames[frame].scale + factor*channels[k].scale_frames[frame+1].scale : Vector3(1,1,1);

			frame = -1;
			factor = -1;
			for (int i=0; i<int(channels[k].rotation_frames.size()-1); i++)
			{
				float time1 = channels[k].rotation_frames[i].time;
				float time2 = channels[k].rotation_frames[i+1].time;
				if ( time>=time1 && time<time2 )
				{
					frame = i;
					factor = (time-time1)/(time2-time1);
					break;
				}
			}
			//frame = -1;
			Quaternion present_rotation = (frame!=-1) ? Slerp(channels[k].rotation_frames[frame].rotation,channels[k].rotation_frames[frame+1].rotation,factor) : Quaternion(1,0,0,0);
		
			Matrix4 tr = Translate(present_position);
			Matrix4 ro = GenRotationMatrix(present_rotation);
			Matrix4 sc = Scale(present_scale);
			Matrix4 r = tr*ro*sc;
			transforms[channels[k].joint_name] = Translate(present_position)*GenRotationMatrix(present_rotation)*Scale(present_scale);
		}

		skeleton->Update(transforms);
	}
};




#endif