#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight()		  = delete;
		virtual ~QuadLight() = default;

		QuadLight(const Vec3f& p_position,
			const Vec3f& p_u,
			const Vec3f& p_v,
			const Vec3f& p_color,
			const float	 p_power)
			: BaseLight( p_color, p_power ), _position( p_position ), _u( p_u ), _v( p_v )
		{
			_n = glm::normalize(glm::cross( _u, _v ));
			_area = glm::length( _u ) * glm::length( _v );
			_isSurface = true;
		}

		inline const Vec3f & getPosition() const { return _position; }
		inline const Vec3f & getU() const { return _u; }
		inline const Vec3f & getV() const { return _v; }
		inline const Vec3f & getN() const { return _n; }
		inline const float & getArea() const { return _area; }

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		// TODO: give a name, like objects and materials
		Vec3f		_position = VEC3F_ZERO;
		Vec3f		_u		  = VEC3F_ZERO;
		Vec3f		_v		  = VEC3F_ZERO;
		Vec3f		_n		  = VEC3F_ZERO;
		float		_area		  = 0;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_QUAD_LIGHT__
