#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		// On suppose les vecteurs normalises
		float den = glm::dot( this->getNormale(), p_ray.getDirection() );
		// Si le plan et le rayon ne sont pas parallèles
		if ( den != 0 )
		{ // Attention à la comparaison avec 0
			Vec3f po = this->getPoint() - p_ray.getOrigin();
			float t	 = glm::dot( po, this->getNormale() ) / den;
			p_t = t;
			return t > 0 ? t : -1; // Si intersection devant
		}	
		// Sinon, pas d’intersection
		return -1;
	}

} // namespace RT_ISICG
