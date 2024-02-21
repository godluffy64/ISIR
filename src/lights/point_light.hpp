#pragma once
#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:

		PointLight()		  = delete;
		virtual ~PointLight() = default;

		PointLight( const Vec3f & p_color, const float p_power, const std::string & p_name, const Vec3f & p_position ) : 
			BaseLight( p_color, p_power ), _name( p_name ), _position( p_position )
		{
		}

		inline const Vec3f & getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  protected:
		// TODO: give a name, like objects and materials
		Vec3f _position = VEC3F_ZERO;
		std::string _name;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_POINT_LIGHT__
