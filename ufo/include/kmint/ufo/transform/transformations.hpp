#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
//------------------------------------------------------------------------
//
//  Name:   Transformations.h
//
//  Desc:   Functions for converting 2D vectors between World and Local
//          space.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>
#include "c2dmatrix.hpp"

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------

namespace kmint
{
	namespace ufo {
		inline std::vector<math::vector2d> WorldTransform(std::vector<math::vector2d>& points,
			const math::vector2d& pos,
			const math::vector2d& forward,
			const math::vector2d& side,
			const math::vector2d& scale)
		{
			//copy the original vertices into the buffer about to be transformed
			std::vector<math::vector2d> TranVector2Ds = points;

			//create a transformation matrix
			C2DMatrix matTransform;

			//scale
			if ((scale.x() != 1.0) || (scale.y() != 1.0))
			{
				matTransform.Scale(scale.x(), scale.y());
			}

			//rotate
			matTransform.Rotate(forward, side);

			//and translate
			matTransform.Translate(pos.x(), pos.y());

			//now transform the object's vertices
			matTransform.TransformVector2Ds(TranVector2Ds);

			return TranVector2Ds;
		}

		//--------------------------- WorldTransform -----------------------------
		//
		//  given a std::vector of 2D vectors, a position and  orientation
		//  this function transforms the 2D vectors into the object's world space
		//------------------------------------------------------------------------
		inline std::vector<math::vector2d> WorldTransform(std::vector<math::vector2d>& points,
			const math::vector2d& pos,
			const math::vector2d& forward,
			const math::vector2d& side)
		{
			//copy the original vertices into the buffer about to be transformed
			std::vector<math::vector2d> TranVector2Ds = points;

			//create a transformation matrix
			C2DMatrix matTransform;

			//rotate
			matTransform.Rotate(forward, side);

			//and translate
			matTransform.Translate(pos.x(), pos.y());

			//now transform the object's vertices
			matTransform.TransformVector2Ds(TranVector2Ds);

			return TranVector2Ds;
		}

		//--------------------- PointToWorldSpace --------------------------------
		//
		//  Transforms a point from the agent's local space into world space
		//------------------------------------------------------------------------
		inline math::vector2d PointToWorldSpace(const math::vector2d& point,
			const math::vector2d& AgentHeading,
			const math::vector2d& AgentSide,
			const math::vector2d& AgentPosition)
		{
			//make a copy of the point
			math::vector2d TransPoint = point;

			//create a transformation matrix
			C2DMatrix matTransform;

			//rotate
			matTransform.Rotate(AgentHeading, AgentSide);

			//and translate
			matTransform.Translate(AgentPosition.x(), AgentPosition.y());

			//now transform the vertices
			matTransform.TransformVector2Ds(TransPoint);

			return TransPoint;
		}

		//--------------------- VectorToWorldSpace --------------------------------
		//
		//  Transforms a vector from the agent's local space into world space
		//------------------------------------------------------------------------
		inline math::vector2d VectorToWorldSpace(const math::vector2d& vec,
			const math::vector2d& AgentHeading,
			const math::vector2d& AgentSide)
		{
			//make a copy of the point
			math::vector2d TransVec = vec;

			//create a transformation matrix
			C2DMatrix matTransform;

			//rotate
			matTransform.Rotate(AgentHeading, AgentSide);

			//now transform the vertices
			matTransform.TransformVector2Ds(TransVec);

			return TransVec;
		}


		//--------------------- PointToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		inline math::vector2d PointToLocalSpace(const math::vector2d& point,
			math::vector2d& AgentHeading,
			math::vector2d& AgentSide,
			math::vector2d& AgentPosition)
		{

			//make a copy of the point
			math::vector2d TransPoint = point;

			//create a transformation matrix
			C2DMatrix matTransform;

			double Tx = -dot(AgentPosition, AgentHeading);
			double Ty = -dot(AgentPosition, AgentSide);

			//create the transformation matrix
			matTransform._11(AgentHeading.x()); matTransform._12(AgentSide.x());
			matTransform._21(AgentHeading.y()); matTransform._22(AgentSide.y());
			matTransform._31(Tx);           matTransform._32(Ty);

			//now transform the vertices
			matTransform.TransformVector2Ds(TransPoint);

			return TransPoint;
		}

		//--------------------- VectorToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		inline math::vector2d VectorToLocalSpace(const math::vector2d& vec,
			const math::vector2d& AgentHeading,
			const math::vector2d& AgentSide)
		{

			//make a copy of the point
			math::vector2d TransPoint = vec;

			//create a transformation matrix
			C2DMatrix matTransform;

			//create the transformation matrix
			matTransform._11(AgentHeading.x()); matTransform._12(AgentSide.x());
			matTransform._21(AgentHeading.y()); matTransform._22(AgentSide.y());

			//now transform the vertices
			matTransform.TransformVector2Ds(TransPoint);

			return TransPoint;
		}

		//-------------------------- Vec2DRotateAroundOrigin --------------------------
		//
		//  rotates a vector ang rads around the origin
		//-----------------------------------------------------------------------------
		inline void Vec2DRotateAroundOrigin(math::vector2d& v, double ang)
		{
			//create a transformation matrix
			C2DMatrix mat;

			//rotate
			mat.Rotate(ang);

			//now transform the object's vertices
			mat.TransformVector2Ds(v);
		}

		//------------------------ CreateWhiskers ------------------------------------
		//
		//  given an origin, a facing direction, a 'field of view' describing the 
		//  limit of the outer whiskers, a whisker length and the number of whiskers
		//  this method returns a vector containing the end positions of a series
		//  of whiskers radiating away from the origin and with equal distance between
		//  them. (like the spokes of a wheel clipped to a specific segment size)
		//----------------------------------------------------------------------------
		inline std::vector<math::vector2d> CreateWhiskers(unsigned int  NumWhiskers,
			double        WhiskerLength,
			double        fov,
			math::vector2d      facing,
			math::vector2d      origin)
		{
			//this is the magnitude of the angle separating each whisker
			double SectorSize = fov / (double)(NumWhiskers - 1);

			std::vector<math::vector2d> whiskers;
			math::vector2d temp;
			double angle = -fov * 0.5;

			for (unsigned int w = 0; w < NumWhiskers; ++w)
			{
				//create the whisker extending outwards at this angle
				temp = facing;
				Vec2DRotateAroundOrigin(temp, angle);
				whiskers.push_back(origin + WhiskerLength * temp);

				angle += SectorSize;
			}

			return whiskers;
		}

	}
}
#endif
